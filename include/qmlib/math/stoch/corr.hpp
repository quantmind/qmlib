
#ifndef __STOCHASTIC_CORRELATION_PROCESS_QM_HPP__
#define __STOCHASTIC_CORRELATION_PROCESS_QM_HPP__


#include <qmlib/math/stoch/diffusion.hpp>



QM_NAMESPACE2(math)


class stochcorr: public diffusion<1u> {
public:
	stochcorr(PARAMETER kappa, PARAMETER theta, PARAMETER var, PARAMETER v0);
	qm_real drift(const qm_real& x, qm_real t) const;
	qm_real sigma(const qm_real& x, qm_real t) const;	
	qm_string code() const {return "Stochastic Correlation";}
protected:
	iparameter* p_kappa;
	iparameter* p_theta;
	iparameter* p_var;
	iparameter* p_v0;
};

inline stochcorr::stochcorr(PARAMETER kappa, PARAMETER theta, PARAMETER var, PARAMETER v0) {
	p_kappa = kappa.get();
	p_theta = theta.get();
	p_var   = var.get();
	p_v0    = v0.get();
	QM_REQUIRE(p_kappa && p_theta && p_var && p_v0,"Parameters not properly defined");
	this->add(kappa);
	this->add(theta);
	this->add(var);
	this->add(v0);
}


qm_real stochcorr::drift(const qm_real& x, qm_real t) const  {
	return p_kappa->get_value()*(p_theta->get_value() - x);
}
qm_real stochcorr::sigma(const qm_real& x, qm_real t) const  {
	return std::sqrt(p_var->get_value()*(1.0 - x*x));
}


QM_NAMESPACE_END2


#endif // __STOCHASTIC_CORRELATION_PROCESS_QM_HPP__


