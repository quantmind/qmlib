
#ifndef	__FACTOR_DISCOUNT_CURVES_HPP__
#define	__FACTOR_DISCOUNT_CURVES_HPP__

#include	<qmlib/finance/rates/base_rates.hpp>
#include	<qmlib/corelib/info/params.hpp>


QM_NAMESPACE2(finance)

class factorcurve;
typedef QM_SMART_PTR(factorcurve)	FACTORCURVE;


/** \brief Base class for a parametric discount curve
 * \ingroup rates
 * 
 * Curves of this family are specified by a set of parameters and
 * a set of factors. However there is no stochastic dynamic associated with factors
 */
class factorcurve : public discountcurve {
public:
	unsigned length()      const {return m_factors.size();}
	parameters	params()   const {return m_params;}
	parameters	factors()  const {return m_factors;}
protected:
	factorcurve(){}
	parameters	m_params;
	parameters  m_factors;
};

class basefactorcurve : public factorcurve {
protected:
	iparameter *p_r,*p_l,*p_h,*p_k,*p_k2;
	basefactorcurve(qm_real sr, qm_real lr, qm_real hu, qm_real k1, qm_real k2);
}; 


class nelsonSiegel : public basefactorcurve {
public:
	static FACTORCURVE make(qm_real sr, qm_real lr, qm_real hu, qm_real k1, qm_real k2) {
		return FACTORCURVE(new nelsonSiegel(sr,lr,hu,k1,k2));
	}
	qm_string tostring() const {return "Nelson-Siegel discount curve";}
	qm_real	dft(qm_real t) const;
	void fulldiscount(qm_real T, qm_real cash, SENSITIVITY& res) const;
private:
	nelsonSiegel(qm_real sr, qm_real lr, qm_real hu, qm_real k1, qm_real k2);
};

class svensson : public basefactorcurve {
public:
	static FACTORCURVE make(qm_real sr, qm_real lr, qm_real hu, qm_real hu2, qm_real k1, qm_real k2) {
		return FACTORCURVE(new svensson(sr,lr,hu,hu2,k1,k2));
	}
	qm_string tostring() const {return "Nelson-Siegel discount curve";}
	qm_real	dft(qm_real t) const;
	void fulldiscount(qm_real T, qm_real cash, SENSITIVITY& res) const;
private:
	iparameter *p_h2;
	svensson(qm_real sr, qm_real lr, qm_real hu, qm_real hu2, qm_real k1, qm_real k2);
};



inline basefactorcurve::basefactorcurve(qm_real shortrate, qm_real longrate, qm_real hump, qm_real kappa, qm_real kappa2)  {		
	m_factors.push_back(parameter::make("short","Short rate",shortrate,0));
	m_factors.push_back(parameter::make("long","Long rate",longrate,0));
	m_factors.push_back(parameter::make("hump","Rate hump",hump));
	m_params.push_back(parameter::make("kappa","Time decay",kappa,0));
	m_params.push_back(parameter::make("kappa2","Time decay",kappa2,0));
	p_r  = m_factors[0].get();
	p_l  = m_factors[1].get();
	p_h  = m_factors[2].get();
	p_k  = m_params[0].get();
	p_k2 = m_params[1].get();
}

inline nelsonSiegel::nelsonSiegel(qm_real sr, qm_real lr, qm_real hu,
		                          qm_real k1, qm_real k2):basefactorcurve(sr,lr,hu,k1,k2)  {
	m_params.set_locked(true);
	m_factors.set_locked(true);
}
inline svensson::svensson(qm_real sr,  qm_real lr, qm_real hu,
		                  qm_real hu2, qm_real k1, qm_real k2):basefactorcurve(sr,lr,hu,k1,k2)  {
	m_factors.push_back(parameter::make("hump2","Rate hump2",hu2));
	p_h2  = m_factors[3].get();
	m_params.set_locked(true);
	m_factors.set_locked(true);
}

inline qm_real nelsonSiegel::dft(qm_real t) const  {
	if(t <= 0) return 1;
	qm_real kt  = p_k->get_value()*t;
	qm_real kt2 = p_k2->get_value()*t;
	qm_real ek  = std::exp(-kt);
	qm_real ek2 = std::exp(-kt2);
	qm_real b2  = (1. - ek)/kt;
	qm_real b3  = (1. - ek2)/kt2 - ek2;
	qm_real x1  = p_l->get_value();
	qm_real x2  = p_r->get_value() - x1;
	qm_real x3  = p_h->get_value();
	qm_real ra  = x1 + x2*b2 + x3*b3;
	return std::exp(-t*ra); 
}

inline qm_real svensson::dft(qm_real t) const  {
	if(t <= 0) return 1;
	qm_real kt  = p_k->get_value()*t;
	qm_real kt2 = p_k2->get_value()*t;
	qm_real ek  = std::exp(-kt);
	qm_real ek2 = std::exp(-kt2);
	qm_real b2  = (1. - ek)/kt;
	qm_real b3  = b2 - ek;
	qm_real b4  = (1. - ek2)/kt2 - ek2;
	qm_real x1  = p_l->get_value();
	qm_real x2  = p_r->get_value() - x1;
	qm_real x3  = p_h->get_value();
	qm_real x4  = p_h2->get_value();
	qm_real ra  = x1 + x2*b2 + x3*b3 + x4*b4;
	return std::exp(-t*ra); 
}

inline void nelsonSiegel::fulldiscount(qm_real T, qm_real cash, SENSITIVITY& res) const  {
	
}

inline void svensson::fulldiscount(qm_real T, qm_real cash, SENSITIVITY& res) const  {
	
}

QM_NAMESPACE_END2

#endif	//	__FACTOR_DISCOUNT_CURVES_HPP__



