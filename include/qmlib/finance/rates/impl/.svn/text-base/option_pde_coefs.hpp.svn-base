
#ifndef   __OPTION_PDE_COEFS_IMPL_QM_HPP__
#define   __OPTION_PDE_COEFS_IMPL_QM_HPP__



#include <qmlib/math/pde/model_coef.hpp>


QM_NAMESPACE2(finance)


template<unsigned N>
class optionpdecoef : public pde_coefficient<N,qm_real>  {
public:
	qm_real time(unsigned t) const;
};

/** \brief Time-dependent coefficient for discounting
 */
template<unsigned N>
class optionratecoef : public optionpdecoef<N>  {
public:
protected:
	qm_real calcfromcache(unsigned t, bool explic) const;
};


template<unsigned N>
class optionconv : public optionpdecoef<N>  {
public:
	optionconv(DISCOUNTCURVE yc, DISCOUNTCURVE cy);
	qm_string tostring() const {"Time-dependent coefficient for convection part of option pde";}
protected:
	DISCOUNTCURVE m_yc,m_cy;
	qm_real evaluate(unsigned t) const;
};


template<unsigned N>
class optionreac : public optionpdecoef<N>  {
public:
	optionreac(DISCOUNTCURVE yc);
	qm_string tostring() const {"Time-dependent coefficient for reaction part of option pde";}
protected:
	DISCOUNTCURVE m_yc;
	qm_real evaluate(unsigned t) const;
};











template<class G>
inline qm_real optionpdecoef<G>::time(unsigned t) const {
	return m_tg->time(m_tg->length()-t-1);
}

template<class G>
inline qm_real optionratecoef<G>::calcfromcache(unsigned t, bool explic) const {
	unsigned t0 = explic ? t : t-1;
	unsigned t1 = 2*t - t0 + 1;
	return (m_cache[t0] - m_cache[t1])/(this->time(t0) - this->time(t1));
}


template<class G>
inline optionconv<G>::optionconv(DISCOUNTCURVE yc, DISCOUNTCURVE cy):
	m_yc(yc),m_cy(cy)  {
	QM_REQUIRE(m_yc,"Yield curve not available");
	QM_REQUIRE(m_cy,"Convenience Yield curve not available");
}
template<class G>
inline optionconv<G>::optionreac(DISCOUNTCURVE yc):m_yc(yc) {
	QM_REQUIRE(m_yc,"Yield curve not available");
}

template<class G>
inline qm_real optionconv<G>::evaluate(unsigned t)  {
	qm_real tim = this->time(t);
	return -std::log(m_yc->dft(tim)/m_cy->dft(tim)); 
}
template<class G>
inline qm_real optionreac<G>::evaluate(unsigned t)  {
	qm_real tim = this->time(t);
	return std::log(m_yc->dft(tim)); 
}

QM_NAMESPACE_END2


#endif	//	__OPTION_PDE_COEFS_IMPL_QM_HPP__

