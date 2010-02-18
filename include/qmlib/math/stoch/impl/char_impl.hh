


#ifndef   __CHARACTERISTIC_FUNCTION_IMPL_MODELS_QM_HPP__
#define   __CHARACTERISTIC_FUNCTION_IMPL_MODELS_QM_HPP__



QM_NAMESPACE2(math)


template<class T, unsigned N>
struct characteristic_cumulant {};

template<unsigned N>
struct characteristic_cumulant<qm_real,N> {
	typedef chartraits<qm_real,N> 		ctraits;
	typedef typename ctraits::vectype	vectype;
	typedef typename ctraits::exptype	exptype;
	typedef typename ctraits::EXPTYPE	EXPTYPE;
	
	static EXPTYPE
	doit(const characteristic<N>& c, const vectype& u, qm_real m, qm_real t1, qm_real t2)  {
		EXPTYPE re(new exptype(t1,t2,m));
		c.rcumulant(u,re);
		return re;
	}
};
template<unsigned N>
struct characteristic_cumulant<qm_complex,N> {
	typedef chartraits<qm_complex,N>	ctraits;
	typedef typename ctraits::vectype	vectype;
	typedef typename ctraits::exptype	exptype;
	typedef typename ctraits::EXPTYPE	EXPTYPE;
	
	static EXPTYPE
	doit(const characteristic<N>& c, const vectype& u, qm_real m, qm_real t1, qm_real t2)  {
		EXPTYPE re(new exptype(t1,t2,m));
		c.ccumulant(u,re);
		return re;
	}
};



template<unsigned N> template<class T>
inline typename chartraits<T,N>::EXPTYPE
characteristic<N>::get_cumulant(const typename chartraits<T,N>::vectype& u,
								qm_real m, qm_real t0, qm_real t1) const  {
	return characteristic_cumulant<T,N>::doit(*this,u,m,t0,t1);
}


template<unsigned N>
inline void
characteristic<N>::characteristic_exponent(const cvec& u, CEXPONENT& expo) const {
	cvec iu = u;
	for(unsigned i=0;i<N;i++)
		iu[i] = mult_i(u[i]);
	this->ccumulant(iu,expo);
}


template<unsigned N>
template<class C>
inline void 
characteristic<N>::calcmoments(const typename characteristic<N>::rvec& c,
							   qm_real t0, qm_real t1, C& cont) const {
	qm_real du2 = m_du*m_du;
	
	rvec u0(0);
	REXPONENT ex(new rexponent(t0,t1,0));
	rcumulant(u0,ex);
	qm_real v0 = ex->value(m_c_factors);
	
	u0 = m_du*c;
	rcumulant(u0,ex);
	qm_real vp1 = ex->value(m_c_factors);
	
	u0 *=-1.;
	rcumulant(u0,ex);
	qm_real vm1 = ex->value(m_c_factors);
	
	// Get first indication of standard deviation
	// and calculate frequency discretization
	qm_real var = vp1 - 2.*v0 + vm1;
	QM_REQUIRE(var>=0,"Critical error. Variance is negative in moments calculation.");
	qm_real sig = std::sqrt(var/du2);
	qm_real du  = m_du;
	if(var > 0) du = std::min(PI/(6.*sig),m_du);
	du2 = 2.*du;
	
	u0 = du*c;
	rcumulant(u0,ex);
	vp1 = ex->value(m_c_factors);
	
	u0 *=-1.;
	rcumulant(u0,ex);
	vm1 = ex->value(m_c_factors);
	
	u0 = du2*c;
	rcumulant(u0,ex);
	qm_real vp2 = ex->value(m_c_factors);
	
	u0 *=-1.;
	rcumulant(u0,ex);
	qm_real vm2 = ex->value(m_c_factors);
	
	qm_real m1  = (-vp2 +  8.*vp1          -  8.*vm1 + vm2)/12.;
	qm_real m2  = (-vp2 + 16.*vp1 - 30.*v0 + 16.*vm1 - vm2)/12.;
	qm_real m3  = ( vp2 -  2.*vp1          +  2.*vm1 - vm2)/2.; 
	qm_real m4  = ( vp2 -  4.*vp1 +  6.*v0 -  4.*vm1 + vm2);
	qm_real st  = std::sqrt(m2);
	cont[0] = m1/du;
	cont[1] = st/du;
	if(st > 0)  {
		cont[2] = round(m3/(st*m2),5);
		cont[3] = round(m4/(m2*m2),5);
	}
	else  {
		cont[2] = 0;
		cont[3] = 0;
	}
}




template<unsigned N>
inline qm_real 
characteristic<N>::affine_covariance(const rvec& rb1, const rvec& rb2, const rvec& fact) const  {
	rvec c1,c2;
	rmat Th = this->ThetaMat();
	Th.inner(rb1,c1);
	Th.inner(rb2,c2);
	rvec s2 = this->S2value(fact);
	qm_real va = 0;
	for(unsigned i=0;i<N;i++)
		va += c1[i]*c2[i]*s2[i];
	return va;
}







#define QM_DEFINE_CHARACTERISTIC_EXPONENT_CALC(name)															\
template<class P>																								\
struct characteristic_exponent_calc<name,P>  {																	\
	typedef P									process_type;													\
	typedef typename process_type::cvec			cvec;															\
	typedef typename process_type::cexponent	cexponent;														\
	typedef typename process_type::CEXPONENT	CEXPONENT;														\
	static CEXPONENT doit(const process_type& p, const name& u, qm_real t0, qm_real t1, qm_real m)  {			\
		cvec uv(0);																								\
		uv[process_type::Dimension-1] = u;																		\
		CEXPONENT ret(new cexponent(t0,t1,m));															\
		p.characteristic_exponent(uv,ret);																		\
		return ret;																								\
	}																											\
};


QM_DEFINE_CHARACTERISTIC_EXPONENT_CALC(qm_real)
QM_DEFINE_CHARACTERISTIC_EXPONENT_CALC(qm_complex)





QM_NAMESPACE_END2


#endif	//	__CHARACTERISTIC_FUNCTION_IMPL_MODELS_QM_HPP__



