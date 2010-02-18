
//________________________________________________________________
//
// Implementation of fftchar
//________________________________________________________________




#ifndef   __FOURIER_PRICER_IMPL_QM_HPP__
#define   __FOURIER_PRICER_IMPL_QM_HPP__



QM_NAMESPACE2(math)


template<typename T, unsigned N, bool Full> struct fftchar_sensitivity;

template<typename T, unsigned N> 
struct fftchar_sensitivity<T,N,false>  {
	typedef ifftchar<T>							baseclass;
	typedef typename baseclass::fouriertype		fouriertype;
	typedef typename fouriertype::fftvectorfast	fftvector;
	typedef affine_exponent<qm_complex,N>		exptype;
	typedef QM_SMART_PTR(exptype)				EXPTYPE;
	static void add(const EXPTYPE& psi, const qm_complex& cha, fftvector& fft, unsigned k) {}
};

template<typename T, unsigned N> 
struct fftchar_sensitivity<T,N,true>  {
	typedef ifftchar<T>							baseclass;
	typedef typename baseclass::fouriertype		fouriertype;
	typedef typename baseclass::darraytype		darraytype;
	typedef typename fouriertype::fftvectorfast	fftvector;
	typedef affine_exponent<qm_complex,N>		exptype;
	typedef QM_SMART_PTR(exptype)				EXPTYPE;
	
	static void add(const EXPTYPE& ps, const qm_complex& cha, fftvector& ffts, unsigned k) {
		exptype* psi = ps.get();
		qm_complex cp,cp2;
		unsigned ii,jj;
		
		for(unsigned i=0;i<N;i++)  {
			ii = fftcharsens::first(i,N);
			cp  = psi->b[i]*cha;
			ffts[ii]->ddata().set(k,cp);
			for(unsigned j=0;j<=i;j++)  {
				jj = fftcharsens::second(i,j,N);
				cp2 = psi->b[j]*cp;
				ffts[jj]->ddata().set(k,cp2);
			}
		}
	}
};



template<typename T, class C, bool Full>
inline fftchar<T,C,Full>::fftchar(MODELTYPE m, unsigned N, qm_real stdev, qm_real dumin, unsigned meth):
	ifftchar<T>(N,DimensionT,stdev,dumin,meth),m_model(m),m_smul(N) {
	QM_REQUIRE(m_model,"Model not available");
	m_process = characteristic_process_traits<C>::getstoch(m_model);
	QM_REQUIRE(m_process,"Characteristic process not available");
	this->registerWith(m_model);
	p_c = m_process.get();
	multtrans = fftcharhelp<T>::mult();
}


template<typename T, class C, bool Full>
inline typename fftchar<T,C,Full>::RDATATYPE
fftchar<T,C,Full>::calculate(qm_real T0, qm_real T1, qm_real T2, qm_real tau)  {
	qm_string cod = "T0 = "    + nice_real(T0,5) +
	                ", T1 = "  + nice_real(T1,5) +
	                ", T2 = "  + nice_real(T2,5) +
					", tau = " + nice_real(tau,5);
	iterator it = m_data.find(cod);
	if(it != m_data.end()) return it->second;
	
	RDATATYPE dt = this->characteristic_calc(T0,T1,T2,tau,true);
	if(m_data.insert(typename dicttype::value_type(cod,dt)).second)
		return dt;
	else
		QM_FAIL("Could not add result to cache");
}


template<typename T, class M, bool Full>
inline typename fftchar<T,M,Full>::charestype
fftchar<T,M,Full>::characteristicfun(qm_real T0, qm_real T1, qm_real T2, qm_real tau)  {
	RDATATYPE res = this->characteristic_calc(T0,T1,T2,tau,false);
	unsigned K = this->p_frfft->dsize();
	unsigned D = this->p_frfft->dim();
	charestype cf(K,D,res->bval(),res->Lval(),res->du(),T0,T1,T2,tau);

	for(unsigned j=0;j<D;j++)  {
		darraytype& dft  = this->p_frfft->get(j)->ddata();
		for(unsigned k=0;k<K;k++)
			cf(k,j) = qm_complex(dft[k][0],dft[k][1]);
	}
	return cf;
}


template<typename T, class C, bool Full>
inline qm_real fftchar<T,C,Full>::discretize(const istochastic::momentstype& mom, qm_real& b, qm_real& L) const {
	qm_real du = this->dumin();
	if(this->frft())
		L = this->stdmul()*mom[1];
	else
		L = PI/du;
	b	  = mom[0]-L;
	return du;
	//if(p_c->periodic_characteristic())  {
	//		QM_FAIL("To be implemented");
	//L  = 0.5*K*p_c->characteristic_period();
	//	}
}

template<typename T, class C, bool Full>
inline typename fftchar<T,C,Full>::RDATATYPE
fftchar<T,C,Full>::makedata(qm_real b, qm_real L, qm_real duu,
		                    qm_real tex, qm_real tse, qm_real tma, qm_real tau,
		                    qm_real expa) const {
	return RDATATYPE(new fftcharresult<qm_real>(this->size(),DimensionT,b,L,duu,tex,tse,tma,tau));
}


template<typename T, class C, bool Full>
inline typename fftchar<T,C,Full>::RDATATYPE
fftchar<T,C,Full>::characteristic_calc(qm_real T0, qm_real T1, qm_real T2, qm_real tau, bool calc)  {
	
	// Get the factors and exponent
	rvec ft = p_c->charFactors();
	REXPONENT re = this->rvector(T1,T2,tau);
	qm_real expa = std::exp(re->a);
	rvec ruv     = re->b;
	cvec uv(0);
	CEXPONENT cex(new cexponent(0,T0,this->disc()));
	// Get the moments in order to discretize domain in the best possible manner
	qm_real L,b;
	istochastic::momentstype mom(0);
	p_c->calcmoments(ruv,0,T0,mom);
	qm_real du = this->discretize(mom,b,L);
	fouriertype* pfu = this->p_frfft;
	
	// Create the transform
	RDATATYPE rep = this->makedata(b,L,du,T0,T1,T2,tau,expa);	
	rdatatype* pep  = rep.get();
	darraytype& dft = this->p_frfft->get(0)->ddata();
	
	qm_real  u  = 0;
	
	// Calculate the shift in domain
	qm_complex bd(0);
	if(calc) bd = qm_complex(0,du*b);
	
	qm_complex psi,cha,cden;
	qm_real xval,cmult;
	qm_real smul = multtrans*du/PI;
	unsigned K = pfu->dsize();
	unsigned i,j,k;
	
	// Calculate the transform
	for(k=0;k<K;k++)  {
		cden = this->cvector(u,ruv,uv); 
		p_c->ccumulant(uv,cex);
		psi = cex->value(ft);
		cha = std::exp(psi-qm_real(k)*bd)/cden;
		dft[k][0] = cha.real();
		dft[k][1] = cha.imag();
		fftchar_sensitivity<T,Dimension,Full>::add(cex,cha,pfu->fastvec(),k);
		u  += du;
	}
	
	// Perform the inversion
	if(calc)  {	
		qm_real beta = rep->betanopi();
		pfu->invert(beta);
		
		// Calculate the multiplier
		qm_real al = this->alpha();
		K = m_smul.size();
		for(k=0;k<K;k++)  {
			xval      = pep->xv(k);
			cmult 	  = pep->multiplier(k);
			m_smul[k] = cmult*smul*std::exp(al*xval);
		}
		j = 0;
		for(typename fouriertype::iterator it = pfu->begin();it!=pfu->end();++it) {
			iarraytype& idft = (*it)->idata();
			for(k=0;k<K;k++)  {
				i = this->position(fftcharhelp<T>::inverseposition(k,K),K);
				(*pep)(k,j) = m_smul[k]*idft.get_real(i);
			}
			j++;
		}
	}
	return rep;
}


QM_NAMESPACE_END2


#endif	//	__FOURIER_PRICER_IMPL_QM_HPP__

