



#ifndef   __REBONATO_VOLATILITY_FUNCTION_QM_HPP__
#define   __REBONATO_VOLATILITY_FUNCTION_QM_HPP__


#include <qmlib/math/options/fwdratevol.hpp>



QM_NAMESPACE2(math)



/** \brief Base class for rebonato fwd rates volatility function
 */
class rebonatovol_base: public fwdratevol  {
public:
	//qm_real get_integrated(qm_real t0, qm_real t1) const;
protected:
	iparameter *p_s0,*p_b,*p_c,*p_d,*p_be;
	qm_real a1,b1,c1,d1,c2,b2,m0,m1,m2,m3,m4,de,bet;
	void precalc();
	qm_real volatilityT(qm_real t, qm_real T) const;
	qm_real Integral(qm_real t) const;
	rebonatovol_base(qm_real a, qm_real b, qm_real c, qm_real d, qm_real beta);
private:
	rebonatovol_base(){}
};


class rebonatovol: public rebonatovol_base  {
public:
	static FWDRATEVOL make(qm_real s0, qm_real b, qm_real c, qm_real d, qm_real beta);
	qm_real correlationfunction(qm_real t, qm_real ti, qm_real tj) const;
	qm_string code() const {return "RebonatoVol";}
protected:
	rebonatovol(qm_real a, qm_real b, qm_real c, qm_real d, qm_real beta);
};

class rebonatovol2: public rebonatovol_base  {
public:
	static FWDRATEVOL make(qm_real s0, qm_real b, qm_real c, qm_real d, qm_real beta, qm_real gamma);
	qm_real correlationfunction(qm_real t, qm_real ti, qm_real tj) const;
	qm_string code() const {return "RebonatoVol2";}
protected:
	iparameter *p_ga;
	qm_real 	gam;
	void precalc();
	rebonatovol2(qm_real s0, qm_real b, qm_real c, qm_real d, qm_real beta, qm_real gamma);
};







//_________________________________________________________________________



inline rebonatovol_base::rebonatovol_base(qm_real s0, qm_real b, qm_real c, qm_real d, qm_real beta) {
	QM_REQUIRE(c>=0,"Decay must be not negative");
	QM_REQUIRE(d>0,"d must be positive");
	QM_REQUIRE(b>=0,"b must be not negative");
	QM_REQUIRE(s0>0,"s0 must be positive");
	QM_REQUIRE(beta>0,"beta must be not negative");
	
	m_params.push_back(parameter::make("s0","short vol",s0,0));
	m_params.push_back(parameter::make("b","slope",b,-smallreal()));
	m_params.push_back(parameter::make("c","dacay",c,-smallreal()));
	m_params.push_back(parameter::make("d","long vol",d,0));
	m_params.push_back(parameter::make("beta","correlation",beta,-smallreal()));
	p_s0 = m_params[0].get();
	p_b  = m_params[1].get();
	p_c  = m_params[2].get();
	p_d  = m_params[3].get();
	p_be = m_params[4].get();
}

inline void rebonatovol_base::precalc()  {
	d1 = p_d->get_value();
	b1 = p_b->get_value();
	a1 = p_s0->get_value() - d1;
	c1 = p_c->get_value();
	c2 = c1*c1;
	qm_real c3 = c2*c1;
	b2 = b1*b1;
	m0 = 4.*a1*c2*d1;
	m1 = 4.*c3*d1*d1;
	m2 = 4.*b1*c1*d1;
	m3 = 2.*a1*a1*c2;
	m4 = 2.*a1*b1*c1;
	de = 0.25/c3;
	bet = p_be->get_value();
}

inline qm_real rebonatovol_base::volatilityT(qm_real t, qm_real T) const {
	qm_real tau = T - t;
	return (a1 + b1*tau)*std::exp(-c1*tau) + d1;
}

//inline qm_real rebonatovol::get_integrated(qm_real t0, qm_real t1) const {
//	return Integral(t1) - Integral(t0);
//}

inline qm_real rebonatovol_base::Integral(qm_real t) const {
	qm_real ti = c1*(t - m_Ti);
	qm_real tj = c1*(t - m_Tj);
	qm_real ei = std::exp(ti);
	qm_real ej = std::exp(tj);
	return  de*(m0*(ei+ej) + m1*t -
		        m2*(ei*(ti - 1.) + ej*(tj -1.)) +
		        ei*ej*(m3 + m4*(1. - ti - tj)) +
		        b2*(1. + 2*ti*tj - ti - tj));
}



inline FWDRATEVOL rebonatovol::make(qm_real s0, qm_real b, qm_real c, qm_real d, qm_real beta) {
	return FWDRATEVOL(new rebonatovol(s0,b,c,d,beta));
}

inline FWDRATEVOL rebonatovol2::make(qm_real s0, qm_real b, qm_real c, qm_real d, qm_real beta, qm_real gamma) {
	return FWDRATEVOL(new rebonatovol2(s0,b,c,d,beta,gamma));
}

inline rebonatovol::rebonatovol(qm_real s0, qm_real b, qm_real c, qm_real d, qm_real beta):
	rebonatovol_base(s0,b,c,d,beta)  {
	m_params.set_locked(true);
	registration();
	precalc();
}
inline qm_real rebonatovol::correlationfunction(qm_real t, qm_real ti, qm_real tj) const {
	return std::exp(-bet*std::abs(ti-tj));
}
inline rebonatovol2::rebonatovol2(qm_real s0, qm_real b, qm_real c, qm_real d, qm_real beta, qm_real gamma):
	rebonatovol_base(s0,b,c,d,beta)  {
	m_params.push_back(parameter::make("gamma","second correlation parameter",gamma,0));
	p_ga = m_params[5].get();
	m_params.set_locked(true);
	registration();
	precalc();
}
inline qm_real rebonatovol2::correlationfunction(qm_real t, qm_real ti, qm_real tj) const {
	qm_real ai = std::pow(ti-t,gam);
	qm_real aj = std::pow(tj-t,gam);
	return std::exp(-bet*std::abs(ai-aj));
}

inline void rebonatovol2::precalc()  {
	rebonatovol_base::precalc();
	gam = p_ga->get_value();
}

QM_NAMESPACE_END2


#endif	//	__REBONATO_VOLATILITY_FUNCTION_QM_HPP__


