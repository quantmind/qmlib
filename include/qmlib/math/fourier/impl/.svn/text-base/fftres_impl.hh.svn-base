





#ifndef   __FFT_RESULTS_IMPL_QM_HPP__
#define   __FFT_RESULTS_IMPL_QM_HPP__


QM_NAMESPACE2(math)

template<unsigned N, bool Full> struct fftoptiondim;

struct fftcharsens  {
	static const unsigned startder = 1u;
	static unsigned countdim(unsigned d)  					 {return 2 + d + d*(d+1)/2;}
	static unsigned first(unsigned i, unsigned N) 			 {return startder + i;}
	static unsigned second(unsigned i,unsigned j,unsigned N) {return i+j+startder+N;}
};

template<unsigned N>
struct fftoptiondim<N,true>  {
	const static unsigned Dimension = 2 + N + N*(N+1)/2;
};
template<unsigned N>
struct fftoptiondim<N,false>  {
	const static unsigned Dimension = 1;
};


template<class T>
inline unsigned fftcharresult<T>::countfactors() const  {
	unsigned D = this->dim();
	if(D == 1) return 0;
	for(unsigned d=1;d<=50;d++)
		if(D == fftcharsens::countdim(d)) return d;
	QM_FAIL("Critical error in counting dimensions");
}


template<class T>
inline fftcharresult<T>::fftcharresult(unsigned N, unsigned D, qm_real b, qm_real L, qm_real duu,
									   qm_real tex, qm_real tse, qm_real tma, qm_real tau):
	m_data(N,D),m_b(b),m_du(duu),m_tex(tex),m_tse(tse),m_tma(tma),m_tau(tau){
	QM_REQUIRE(L>0.,"Domain negative not allowed");
	m_dx = 2.*L/this->size();
	m_numfactors = this->countfactors();
}

template<class T>
inline unsigned fftcharresult<T>::locate(qm_real dval, qm_real& u) const  {
	qm_real val = this->xvalue(dval);
	qm_real vs  = val - m_b;
	long n = long(vs/m_dx);
	if(n>=0 && n<(long)this->size()-1) {
		unsigned k = unsigned(n);
		u = (vs - k*m_dx)/m_dx;
		return k+1;
	}
	return 0;
}

template<class T>
inline T fftcharresult<T>::value(qm_real dval, unsigned i) const  {
	qm_real u;
	unsigned k = this->locate(dval,u);
	if(k == 0) QM_FAIL("out of bound");
	QM_REQUIRE(i<this->dim(),"Out of bound");
	return (1.-u)*m_data(k-1,i) + u*m_data(k,i);
}

template<>
inline SENSITIVITY
fftcharresult<qm_real>::sens(const qdate& dte, const qm_string& code, qm_real dval) const  {
	SENSITIVITY se(new sensitivity(dte,code,m_numfactors));
	sensitivity::delta_type de = se->deltas();
	sensitivity::gamma_type ga = se->gammas();
	
	se->set_value(this->value(dval,0));
	for(unsigned i=0;i<m_numfactors;i++)  {
		de(i) = this->value(dval,fftcharsens::first(i,m_numfactors));
		for(unsigned j=0;j<=i;j++)
			ga(i,j) = this->value(dval,fftcharsens::second(i,j,m_numfactors));
	}
	return se;
}

template<>
inline SENSITIVITY fftcharresult<qm_complex>::sens(const qdate& dte, const qm_string& code, qm_real dval) const  {
	QM_FAIL("sensitivity not available for complex results");
}

template<>
inline qm_string fftcharresult<qm_complex>::tostring() const  {
	return "Transform: size "+object_to_string(this->size())+
	       ": du " + object_to_string(this->du());
}

template<>
inline qm_string fftcharresult<qm_real>::tostring() const  {
	return "Inverse Transform: size "+object_to_string(this->size())+
	       ": b " + object_to_string(m_b) +
	       ": dx " + object_to_string(m_dx);
}

template<>
inline fftcharresult<qm_real>::rangetype fftcharresult<qm_real>::range(unsigned nf) const  {
	unsigned Ns = this->size();
	if(nf == 0 || nf > Ns) return rangetype(0,Ns);
	unsigned Nh = Ns/2;
	unsigned nfh = nf/2;
	if(nfh >= Nh) return rangetype(0,Ns);
	else return rangetype(Nh-nfh,std::min(Nh+nfh,Ns));
}

template<>
inline fftcharresult<qm_complex>::rangetype fftcharresult<qm_complex>::range(unsigned nf) const  {
	if(nf == 0 || nf > this->size()) return rangetype(0,this->size());
	else return rangetype(0,nf);
}


inline qm_real fftoptionresult::impliedblack(qm_real K) const  {
	qm_real u;
	unsigned k = this->locate(K,u);
	if(k == 0) {
		QM_FAIL("out of bound");
	}
	qm_real pr = this->makeprice((1.-u)*m_data(k-1,0) + u*m_data(k,0));
	return m_black.volatility(K,1.,this->expiry(),pr);
}


QM_NAMESPACE_END2


#endif	//	__FFT_RESULTS_IMPL_QM_HPP__

