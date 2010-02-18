

#ifndef __HESTON_PROCESS_QM_HPP__
#define __HESTON_PROCESS_QM_HPP__



#include <qmlib/math/stoch/diffusion.hpp>
#include <qmlib/math/stoch/exponential.hpp>




QM_NAMESPACE2(math)


/** \brief Heston Stochastic volatility model
 * 
 * Double-diffusion model
 * \f$dx_t   = \sqrt{1-\rho^2} \sqrt{\nu_t} d w^x_t + \rho \sqrt{\nu_t} d w^\nu_t\f$
 * \f$d\nu_t = -kappa(\theta - \nu_t)dt + \eta\sqrt{\nu_t}s w^{\nu}_t\f$
 */
class heston_exponent: public CharacteristicDiffusion<2u> {
public:
	typedef CharacteristicDiffusion<2u> basestoch;
	
	heston_exponent(PARAMETER kappa, PARAMETER theta, PARAMETER eta2, PARAMETER rho, PARAMETER v0);
	
	vectype drift(const vectype& x, qm_real t) const;
	mattype sigma2(const vectype& x, qm_real t) const;	
	qm_string code() const {return "Heston stochastic volatility exponent";}
	
	void rcumulant(const rvec& u, REXPONENT& expo) const {cumulant(u,expo.get());}
	void ccumulant(const cvec& u, CEXPONENT& expo) const {cumulant(u,expo.get());}
	
	/// \brief Evaluate the exponential convexity correction
	qm_real	  exp_convexity(qm_real t0, qm_real t1) const {return 0;}
	void updateFactors() {m_c_factors[0] = 0.; m_c_factors[1] = p_v0->get_value();}
	
	DIST1 marginal(unsigned i, qm_real t1, qm_real t2) const;
	
	bool    ispositive_characteristic(unsigned i) const {return i==1;}
protected:
	iparameter *p_kappa, *p_theta, *p_eta2, *p_rho, *p_v0;
	
	/// \brief Generate an heston path
	///
	void createPaths();
	
	template<typename T>
	void cumulant(const tinyvec<T,2u>& u, affine_exponent<T,2u>* expo) const;
};


inline heston_exponent::heston_exponent(PARAMETER kappa, PARAMETER theta, PARAMETER eta2,
										PARAMETER rho, PARAMETER v0) {
	p_kappa = kappa.get();
	p_theta = theta.get();
	p_eta2  = eta2.get();
	p_rho   = rho.get();
	p_v0    = v0.get();
	this->add(kappa);
	this->add(theta);
	this->add(eta2);
	this->add(rho);
	this->add(v0);
}

template<typename T>
inline void
heston_exponent::cumulant(const tinyvec<T,2u>& u, affine_exponent<T,2u>* expo) const  {
	qm_real tau		= expo->t1 - expo->t0;
	T		c0		= u[0];
	T		c1  	= u[1];
	qm_real m	   	= expo->disc();
	qm_real ka  = p_kappa->get_value();
	qm_real th  = p_theta->get_value();
	qm_real eta = std::sqrt(p_eta2->get_value());
	qm_real ro  = p_rho->get_value();
   	T 		kh  = ka - eta*ro*c0;
   	T		mh  = m  - 0.5*c0*c0;
   	T a,b;
   	square_root_exponent(kh,mh,eta,tau,c1,a,b);
   	expo->a    = ka*th*a;
   	expo->b[0] = c0;
   	expo->b[1] = b;
}


inline DIST1 heston_exponent::marginal(unsigned i, qm_real t1, qm_real t2) const  {
	QM_REQUIRE(t1>=0. && t2>t1,"Time must be positive");
	QM_REQUIRE(i==1,"Heston model has analytical marginal only for factor 1");
	qm_real ka  = p_kappa->get_value();
	qm_real th  = p_theta->get_value();
	qm_real eta = std::sqrt(p_eta2->get_value());
	return squareroot_marginal(t2-t1,ka,th,eta,m_c_factors[1]);
}

QM_NAMESPACE_END2


#endif // __HESTON_PROCESS_QM_HPP__

