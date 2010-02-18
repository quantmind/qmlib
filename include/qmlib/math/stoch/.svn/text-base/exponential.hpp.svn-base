

#ifndef __EXPONENTIAL_PROCESS_QM_HPP__
#define __EXPONENTIAL_PROCESS_QM_HPP__

#include <qmlib/math/stoch/stochastic.hpp>
#include <qmlib/math/stoch/characteristic.hpp>


/** \file
 *  \ingroup stoch
 *  \brief Exponential process template
 */

QM_NAMESPACE2(math)




/** \brief Exponential martingale process template
 * \ingroup stoch
 * 
 * An exponential martingale process is scalar stochastic process
 * defined as
 * 
 * \f$ z_t = e^{{\bf m}\cdot{\bf x_t} - c_t}\f$ where
 * \f$c_t = \ln{E\left[e^{{\bf m}\cdot{\bf x_t}}\right]}\f$
 * is the exponential convexity correction needed to make \f$z_t\f$ a martingale with
 * the property \f$E[z_t] = 1\f$ for all \f$t \ge 0\f$.
 * \f${\bf x}_t\f$ is an affine multidimensional process with a valid characteristic transform.
 *  
 * Exponential characteristic martingale process are very useful in %asset pricing.
 */
template<unsigned N>
class characteristic_exponential  {
public:
	const static unsigned Dimension = N;
	typedef characteristic<N>				chartype;
	typedef QM_SMART_PTR(chartype)			CHARTYPE;
	typedef typename chartype::rvec			rvec;
	typedef typename chartype::rexponent	rexponent;
	typedef typename chartype::REXPONENT	REXPONENT;
	
	/// \brief Calculate the convexity correction affine_exponent
	///
	/// This result is used in this->correction to evaluate the convexity correction
	const REXPONENT& convexitycorrection(qm_real t, qm_real T) const  {
		p_rexpo->t0 = t;
		p_rexpo->t1 = T;
		p_process->rcumulant(m_mult,m_rexpo);
		return m_rexpo;
	}
	
	/// \brief Calculate the convexity correction exponent \f${\bf c}_t\f$
	///
	qm_real correction(qm_real t, qm_real T) const  {
		return this->convexitycorrection(t,T)->value(p_process->charFactors());
	}
	
	/// Template constructor
	///
	/// P must be a istochastic process with characteristic.
	template<class P>
	characteristic_exponential(QM_SMART_PTR(P) pr):m_mult(0), m_rexpo(new rexponent(0,0,0)) {
		m_process = smart_cast<chartype,P>(pr);
		QM_REQUIRE(m_process,"Characteristic process is null");
		p_process = m_process.get();
		m_mult[0] = 1;
		p_rexpo = m_rexpo.get(); 
	}
	
	/// \brief vector exponent multiplier \f$\bf m\f$
	///
	const rvec& multiplier() const {return m_mult;}
	
	/// \brief Exponent process \f${\bf x}_t\f$
	///
	CHARTYPE	cprocess() const {return m_process;}
protected:
	CHARTYPE	m_process;
	rvec		m_mult;
	chartype*   p_process;
	
	mutable REXPONENT	m_rexpo;
	mutable rexponent*  p_rexpo;
	
	void exp_path_correction(Paths& paths) const;
};



//template<>
template<unsigned N>
struct characteristic_process_traits<characteristic_exponential<N> > {
	typedef QM_SMART_PTR(characteristic<N>)	CHARTYPE;
	typedef QM_SMART_PTR(characteristic_exponential<N>)	PROCTYPE;
	static CHARTYPE getstoch(PROCTYPE typ) {return typ->cprocess();}
};



template<unsigned N>
inline void 
characteristic_exponential<N>::exp_path_correction(Paths& paths) const {
	timegrid* tg = paths.grid().get();
	unsigned   T = paths.timedim();
	unsigned t,p;
	qm_real  x,ct;
	
	// Finally apply the exponential function to
	// the the convexity-corrected exponent
	path::holder pas = paths[0]->pathholder();
	for(t=1;t<T;++t)  {
		ct = this->correction(0,tg->time(t));
		for(p=0;p<paths.numpaths();p++)  {
			x = std::exp(pas(t,p) - ct);
			pas(t,p) = x;
		}
	}
}

QM_NAMESPACE_END2


#endif // __EXPONENTIAL_PROCESS_QM_HPP__

