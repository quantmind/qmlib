

#ifndef __WEINER_PROCESS_QM_HPP__
#define __WEINER_PROCESS_QM_HPP__



#include <qmlib/math/stoch/diffusion.hpp>


/** \file
 * \ingroup stoch
 * The generalized weiner process
 */



QM_NAMESPACE2(math)



/** \brief Generalized Wiener process
 *  \ingroup stoch
 *  
 * It is a continuous-time stochastic process named in honor of Norbert Wiener.
 * It is often called Brownian motion, after Robert Brown.
 * It is one of the best known levy processes and occurs frequently in pure and applied mathematics,
 * economics and physics.
 * 
 * The generalized Wiener process is given by the one-dimensional diffusion
 * 
 * \f$ dx_t = \mu_t dt + \sigma_t dw_t \f$ where $\w_t$ is a wiener process.
 * 
 * \f$\mu_t\f$ and \f$\sigma_t\f$ are deterministic functions of time.
 * 
 * The Generalized Wiener process characterized by two facts:
 *  - \f$w_t\f$ is almost surely continuous.
 *  - It has independent increments with distribution
 * \f$w_T-w_t \sim \mathcal{N}\left[\int_t^T \mu_s ds,\int_t^T \sigma^2_s ds\right]\ \ \forall  t < T\f$
 * where \f$\mathcal{N}[a,b]\f$ is a normal_dist with mean \f$a\f$ and variance
 * \f$b\f$.
 * 
 * \see http://en.wikipedia.org/wiki/Wiener_process
 */
// \mathcal{N}\left[\int_t^T \mu_s ds,\int_t^T \sigma^2_s ds\right]\ \ \forall  t < T\f$.
class wiener: public CharacteristicDiffusion<1u> {
public:	
	///\brief Protected constructor
	///
	///@param m the annualized mean
	///@param v the annualized variance
	wiener(PARAMETER drift, PARAMETER var);
	
	qm_real drift(const qm_real& x, qm_real t)  const {return p_mu->get_valuet(t);}
	qm_real sigma2(const qm_real& x, qm_real t) const {return p_va->get_valuet(t);}
	bool analytical_exponent() const {return true;}
	
	///\brief Calculate the characteristic exponent
	///
	/// The characteristic exponent is given by
	/// \f$-u\int \mu_s ds + \frac{u^2}{2}\int \sigma^2_s ds\f$
	///
	/// The %wiener process has a characteristic exponent with
	void rcumulant(const rvec& u, REXPONENT& expo) const {cumulant(u[0],expo.get());}
	void ccumulant(const cvec& u, CEXPONENT& expo) const {cumulant(u[0],expo.get());}
	
	qm_string code() const {return "Generalized Weiner";}
	
	/// \brief Evaluate the exponential convexity correction
	qm_real	  exp_convexity(qm_real t0, qm_real t1) const;
	
	DIST1 marginal(unsigned i, qm_real t1, qm_real t2) const;
protected:
	iparameter* p_mu;
	iparameter* p_va;
	
	template<typename T>
	void cumulant(const T& u, affine_exponent<T,1u>* expo) const {
		qm_real m  = p_mu->get_integrated(expo->t0,expo->t1);
	   	qm_real v  = p_va->get_integrated(expo->t0,expo->t1);
	   	expo->a = u*(m + 0.5*v*u);
	   	expo->b[0] = u;
	}
};




inline wiener::wiener(PARAMETER drift, PARAMETER var) {
	p_mu = drift.get();
	p_va = var.get();
	QM_REQUIRE(p_mu && p_va,"Parameters not properly defined");
	this->add(drift);
	this->add(var);
}

inline qm_real wiener::exp_convexity(qm_real t0, qm_real t1) const {
	return 0.5*p_va->get_integrated(t0,t1);
}

inline DIST1 wiener::marginal(unsigned i, qm_real t1, qm_real t2) const  {
	QM_REQUIRE(t1>=0. && t2>t1,"Time must be positive");
	QM_REQUIRE(i==0,"Out of bound in marginal");
	qm_real m  = p_mu->get_integrated(t1,t2);
	qm_real v  = p_va->get_integrated(t1,t2);
	return DIST1(new normal_dist(m,v));
}



QM_NAMESPACE_END2    



#endif // __WEINER_PROCESS_QM_HPP__


