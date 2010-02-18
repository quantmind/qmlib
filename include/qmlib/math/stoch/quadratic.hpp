

#ifndef __QUADRATIC_PROCESS_QM_HPP__
#define __QUADRATIC_PROCESS_QM_HPP__



#include <qmlib/math/stoch/diffusion.hpp>


/** \file
 * \ingroup stoch
 * \brief Quadratic volatility diffusion process
 */



QM_NAMESPACE2(math)



/** \brief A diffusion process with quadratic volatility
 *  \ingroup stoch
 * 
 * The volatility function is given by
 *  - \f$\sigma_t(x_t) = \sqrt{\gamma_t}\,p(x_t)\f$
 *  - \f$p(x_t) = d\left[1 + \left(\frac{x_t - m}{d}\right)^2\right]\f$
 * 
 * The time-dependence of the volatility function is factored out in the \f$\gamma_t\f$
 * deterministic function of time.
 * \see Zuhlsdorff, C., The Pricing of derivatives on Assets with Quadratic Volatility,
 * 		SFB 303 Discussion Paper B-451.
 */
class quadraticvol: public diffusion<1u> {
public:
	typedef diffusion<1u>	basestoch;
	
	static DIFFP1 make(PARAMETER ga, qm_real m, qm_real d);
	qm_real sigma(qm_real x, qm_real t) const;
	
	qm_string code() const {return "Weiner Quadratic volatility";}
	qm_real   qvol(qm_real x) const;
	
private:
	///\brief Protected constructor
	///
	///@param m The annualized mean
	///@param v the annualized variance
	quadraticvol(const parameters& pa):basestoch(pa){}
};

inline DIFFP1 quadraticvol::make(PARAMETER ga, qm_real m, qm_real d)  {
	QM_REQUIRE(ga,"The time dependent parameter is null");
	parameters pa;
	pa.push_back(ga);
	pa.push_back(parameter::make("M","The minimum of the parabola",m));
	pa.push_back(parameter::make("D","Define the curvature of the parabola",d,0));
	return DIFFP1(new quadraticvol(pa));
}

inline qm_real quadraticvol::qvol(qm_real x) const  {
	qm_real m = m_params[1]->get_value();
	qm_real d = m_params[2]->get_value();
	qm_real xd = (x - m)/d;
	return d*(1 + xd*xd);
}

inline qm_real quadraticvol::sigma(qm_real x, qm_real t) const  {
	return m_params[0]->get_valuet(t)*qvol(x);
}


    
QM_NAMESPACE_END2


#endif // __QUADRATIC_PROCESS_QM_HPP__

