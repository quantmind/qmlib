
#ifndef   __BALCK_FORMULA_QM_HPP__
#define   __BALCK_FORMULA_QM_HPP__

#include <qmlib/math/stat/all.hpp>
#include <qmlib/math/options/black_sensitivity.hpp>
#include <qmlib/qmat/tiny.hpp>


/*! \defgroup op_analytic Analytic option pricing library

    @{
*/


/** \file
 * \brief Black Scholes analytic formulae
 */

QM_NAMESPACE2(math)

/** \brief Black Scholes model
 */
class fwdblackcall  {
public:
	fwdblackcall(unsigned itemax = 30, qm_real tole = 1.e-08):m_tole(tole),m_itemax(itemax){}
	
	/// \brief Calculate the price
	///
	qm_real price(qm_real F, qm_real K, qm_real T, qm_real vol)  {
		qm_real vt = vol*vol*T;
		return ffd(std::log(F/K),F,K,vt);
	}
	
	/// \brief Fast Price calculation
	///
	///@param logFK \f$\ln{\frac{F}{K}}\f$
	///@param F forward price
	///@param K call strike
	///@param vt the total variance \f$\int_0^T\sigma^2_s ds\f$
	qm_real ffd(qm_real logFK, qm_real F, qm_real K, qm_real vt) const {
		qm_real vts   = std::sqrt(vt);
		qm_real d1 	  = (logFK + 0.5*vt)/vts;
		return F*m_nd.cumulative(d1) - K*m_nd.cumulative(d1 - vts);
	}
	
	/// \brief Calculate price and variance sensitivity
	///
	/// Same as ffd with a calculation of the variance sensitivity
	///
	///@param logFK \f$\ln{\frac{F}{K}}\f$
	///@param F forward price
	///@param K call strike
	///@param vt 
	///@return dpdv sensitivity with respect to the variance \f$\sigma^2 T\f$
	///@return forward call option price
	/// \note no checks. Input parameters are assumed to be correct
	qm_real direct(qm_real logFK, qm_real F, qm_real K, qm_real vt, qm_real& dpdv) const {
		qm_real vts   = std::sqrt(vt);
		qm_real d1 	  = (logFK + 0.5*vt)/vts;
		dpdv		  = 0.5*F*m_nd.density(d1)/vts;
		return F*m_nd.cumulative(d1) - K*m_nd.cumulative(d1 - vts);
	}
	
	/// \brief Calculate valtility from forward call option price
	///
	///@param F forward price
	///@param K call strike
	///@param T time to maturity
	///@param pric The forward call option price
	///@return Implied Black volatility
	/// \note no checks. Input parameters are assumed to be correct
	qm_real volatility(qm_real F, qm_real K, qm_real T, qm_real pric) const {
		tinyvec<qm_real,6> tv(0.1,0.15,0.3,0.5,0.7,1.0);
		qm_real fk = std::log(F/K);
		qm_real vp;
		for(unsigned i=0;i<5;i++)  {
			vp = tv[i]*tv[i];
			if(pric <= ffd(fk,F,K,vp*T))
				return inverse(F,K,T,pric,0.7*tv[i]);
		}
		return inverse(F,K,T,pric,2.0);
	}
	
	qm_real inverse(qm_real F, qm_real K, qm_real T, qm_real pric, qm_real volinit) const {
		qm_real veg;
		qm_real va = volinit*volinit*std::sqrt(T);
		qm_real fk = std::log(F/K);
		qm_real tole = 1.;
		qm_real pr,dv;
		unsigned ite = 0;
		
		while(tole>m_tole && ite<m_itemax) {
			ite++;
			pr  = direct(fk,F,K,va,veg);
			dv  = (pr - pric)/veg;
			va -= dv;
			tole = std::abs(dv);
		}
		QM_REQUIRE(ite<m_itemax,"Too many iterations in black inverse solver");
		return std::sqrt(va/T);
	}
	
	/// \brief Full Calculation with sensitivities
	BLACK_ANALYTICS calculate(qm_real F, qm_real K, qm_real T, qm_real vol) const {
		return calculateFromVariance(F,K,vol*vol*T);
	}
	
	BLACK_ANALYTICS calculateFromVariance(qm_real F, qm_real K, qm_real vt) const {
		qm_real fk  = std::log(F/K);
		qm_real vts = std::sqrt(vt);
		BLACK_ANALYTICS ba(new black_analytics);
		black_analytics* ptr = ba.get();
		qm_real d1 	  = (fk + 0.5*vt)/vts;
		qm_real N1    = m_nd.cumulative(d1);
		qm_real n1    = m_nd.density(d1);
		qm_real pr    =	F*N1 - K*m_nd.cumulative(d1 - vts);
		qm_real ve    = 0.5*F*n1/vts;
		ptr->set_value(pr);
		ptr->set_delta(N1);
		ptr->set_gamma(n1/(F*vts));
		ptr->set_vega(ve);
		return ba;
	}
	//static qm_real formula(qm_real fwd, qm_real strike, qm_real T, qm_real sigma)  {
	//	
	//}
protected:
	normal_dist m_nd;
	qm_real 	m_tole;
	unsigned	m_itemax;
};


QM_NAMESPACE_END2


/*! @} */

#endif	//	__BALCK_FORMULA_QM_HPP__

