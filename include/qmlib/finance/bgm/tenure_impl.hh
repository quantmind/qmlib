
#ifndef	__BGM_TENURE_CURVES_IMPL_HPP__
#define	__BGM_TENURE_CURVES_IMPL_HPP__



QM_NAMESPACE2(finance)


inline tenure::tenure(DISCOUNTCURVE yc, const period& horizon,
					  const period& cap, const period& swap,
					  ADJ adj, DC floatDC, DC fixedDC,
					  FWDRATEVOL fv):
				m_horizon(horizon),m_cap(cap),m_swp(swap),m_adj(adj),
				m_fixedDC(fixedDC),m_YC(yc),m_FV(fv) {
	QM_REQUIRE(m_YC,"Yield curve is null");
	QM_REQUIRE(m_FV,"Forward rate volatility is null");
	unsigned ct = m_cap.totalmonths();
	unsigned st = m_swp.totalmonths();
	unsigned ho = m_horizon.totalmonths();
	QM_REQUIRE(m_cap.totaldays() == 0 && m_swp.totaldays() == 0 &&
			   m_horizon.totaldays() == 0 && ct != 0 && st != 0 && ho != 0,
			   "Bad tenure specification");
	m_K  = st/ct;
	unsigned T  = ho/st;
	QM_REQUIRE(m_K*ct == st && T*st == ho,"Bad tenure specification");
	QM_REQUIRE(m_adj,"Date adjustment not specified");
	QM_REQUIRE(m_fixedDC,"Swap DC is null");
	m_TG = DTIMEGRID(new date_timegrid(floatDC));
	m_yc = m_YC.get();
	m_tg = m_TG.get();
	m_fv = m_FV.get();
	create();
}


inline void tenure::create()  {
	unsigned M = m_horizon.totalmonths()/m_cap.totalmonths();
	m_cache.resize(M+1,3);
	period pe = m_cap;
	qdate start = this->date();
	qdate d1    = m_adj->adjust(start);
	qm_real b1  = m_yc->df(d1);
	
	m_tg->add(d1);
	m_cache(0,0) = b1;
	
	qm_real b0,tam;
	qdate d0;
	
	for(unsigned m=1;m<=M;m++)  {
		b0 = b1;
		d0 = d1;
		d1 = m_adj->parseinterval(start,pe);
		m_tg->add(d1);
		b1 = m_yc->df(d1);
		tam = m_tg->dt(m);
		m_cache(m,0)   = b1;
		m_cache(m-1,1) = tam;
		m_cache(m-1,2) = (b0/b1 - 1.)/tam;
		pe += m_cap;
	}
}

inline tenure::datatype tenure::weights(unsigned a, unsigned N, bool full) const {
	return weightsK(a,N,m_K,full);
}

inline tenure::datatype tenure::weightsK(unsigned a, unsigned N, unsigned K, bool full) const {
	unsigned NK = N*K;
	unsigned  b = a + NK;
	QM_REQUIRE(NK>0 && b<this->size(),"Bad tenure");
	qm_real a_ab  = Aab(a,b);
	if(full)  {
		datatype weight(PV01(a,b,K));
		qm_real a_mb,pv01m,tam;
		qm_real pv01 = weight[0];
		for(unsigned m=a;m<b;m++)  {
			a_mb  = Aab(m,b);
			pv01m = weight[m-a];
			tam   = tau(m);
			weight[m-a] = (B(m+1)/a_ab + (a_ab*pv01m - a_mb*pv01)/(a_ab*pv01*(1.+tam*fwd(m))))*tam;
		}
		return weight;
	}
	else  {
		datatype weight(b-a);
		for(unsigned m=a;m<b;m++)
			weight[m-a] = tau(m)*B(m+1)/a_ab;
		return weight;
	}
}

inline qm_real tenure::delta(unsigned m) const  {
	return m_fixedDC->dcf((*m_tg)[m-m_K],(*m_tg)[m]);
}


inline tenure::datatype tenure::PV01(unsigned a, unsigned b, unsigned K) const  {
	datatype pv01(b-a);
	qm_real p = 0;
	unsigned j;
	for(int m=b-1;m>=int(a);m--)  {
		j = m - a + 1;
		if(K*(j/K) == j)
			p += B(m+1)*delta(m+1);
		pv01[m-a] = p;
	}
	return pv01;
}

inline tenure::coeftype tenure::coefs(unsigned a, unsigned N, bool full) const  {
	return coefsK(a,N,m_K,full);
}

inline tenure::coeftype tenure::coefsK(unsigned a, unsigned N, unsigned K, bool full) const {
	datatype w = weightsK(a,N,K,full);
	unsigned R = w.rows();
	coeftype zeta(R,R);
	qm_real wm,wn;
	for(unsigned i=0;i<R;i++)  {
		wm = w[i]*fwd(i+a);
		for(unsigned j=0;j<=i;j++)  {
			wn = w[j]*fwd(j+a);
			zeta(i,j) = wm*wn;
		}
	}
	return zeta;
}

QM_NAMESPACE_END2

#endif	//	__BGM_TENURE_CURVES_IMPL_HPP__

