

#ifndef __MEANREV_PROCESS_QM_HPP__
#define __MEANREV_PROCESS_QM_HPP__



#include <qmlib/math/stoch/diffusion.hpp>




QM_NAMESPACE2(math)


/** \brief Gaussian OU process
 * \ingroup stoch
 * 
 * \f$ d x_t = \kappa(\theta - x_t) dt + \sigma d w_t\f$
 */
class gaussianOU: public CharacteristicDiffusion<1u> {
public:	
	gaussianOU(PARAMETER kappa, PARAMETER theta, PARAMETER var, PARAMETER v0);
	
    bool analytical_exponent() const {return true;}
    void rcumulant(const rvec& u, REXPONENT& expo) const {cumulant(u[0],expo.get());}
    void ccumulant(const cvec& u, CEXPONENT& expo) const {cumulant(u[0],expo.get());}
	
	qm_string code() const {return "Gaussian OU";}
	void createPaths();
	void updateFactors() {m_c_factors[0] = p_v0->get_value();}
protected:
	iparameter* p_kappa;
	iparameter* p_theta;
	iparameter* p_var;
	iparameter* p_v0;

	template<typename T>
	void cumulant(const T& u, affine_exponent<T,1u>* expo) const;

	virtual qm_real advance(qm_real ka, qm_real th, qm_real eta, qm_real x0,
					        qm_real dt, qm_real sdt, qm_real nv) const;
	virtual qm_real sdt(qm_real ka, qm_real dt) const {return std::exp(-ka*dt);}
};


/** \brief The square root mean-reverting diffusion process
 * \ingroup stoch
 * 
 * \f$ d x_t = \kappa(\theta - x_t) dt + \sigma \sqrt{x_t} d w_t\f$
 */
class squareroot: public gaussianOU {
public:
	
	squareroot(PARAMETER kappa, PARAMETER theta, PARAMETER var, PARAMETER v0):gaussianOU(kappa,theta,var,v0){}
	
    bool analytical_exponent() const {return true;}
    void rcumulant(const rvec& u, REXPONENT& expo) const {cumulant(u[0],expo.get());}
    void ccumulant(const cvec& u, CEXPONENT& expo) const {cumulant(u[0],expo.get());}
    bool  ispositive()		   const {return true;}
	
	qm_string code() const {return "Square root mean-reverting gaussian";}
	
	DIST1 marginal(unsigned i, qm_real t1, qm_real t2) const;
protected:

	template<typename T>
	void cumulant(const T& u, affine_exponent<T,1u>* expo) const;

	qm_real advance(qm_real ka, qm_real th, qm_real eta, qm_real x0,
					qm_real dt, qm_real sdt, qm_real nv) const;
	qm_real sdt(qm_real ka, qm_real dt) const {return std::sqrt(dt);}
};

template<typename T>
inline void gaussianOU::cumulant(const T& c, affine_exponent<T,1u>* expo) const {
	qm_real tau    = expo->t1 - expo->t0;
	qm_real m	   = expo->disc();
	qm_real ka     = p_kappa->get_valuet(tau);
	qm_real th     = p_theta->get_valuet(tau);
	qm_real va     = p_var->get_valuet(tau);
   	qm_real sk2    = va/(ka*ka);
   	qm_real et     = std::exp(-ka*tau);
   	T  bt  = ((m+ka*c)*et - m)/ka;
   	T  ct  = bt - c + m*tau;
   	expo->a = ct*(0.5*sk2*m - th) - 0.25*ka*sk2*(bt*bt - c*c);
   	expo->b[0] = bt;
}

template<typename T>
inline void squareroot::cumulant(const T& c, affine_exponent<T,1u>* expo) const {
	qm_real tau = expo->t1 - expo->t0;
	qm_real ka  = p_kappa->get_valuet(tau);
	qm_real th  = p_theta->get_valuet(tau);
	qm_real va  = p_var->get_valuet(tau);
	qm_real m	= expo->disc();
   	T a,b;
   	square_root_exponent(ka,m,va,tau,c,a,b);
   	expo->a    = ka*th*a;
   	expo->b[0] = b;
}


inline DIST1 squareroot::marginal(unsigned i, qm_real t1, qm_real t2) const  {
	QM_REQUIRE(t1>=0. && t2>t1,"Time must be positive");
	QM_REQUIRE(i==0,"Out of bound in marginal");
	qm_real ka = p_kappa->get_valuet(t2);
	qm_real th = p_theta->get_valuet(t2);
	qm_real va = p_var->get_valuet(t2);
	qm_real v0 = m_c_factors[0];
	return squareroot_marginal(t2-t1,ka,th,va,v0);
}


QM_NAMESPACE_END2


#endif // __MEANREV_PROCESS_QM_HPP__
