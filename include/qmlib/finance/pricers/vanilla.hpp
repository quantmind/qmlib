


#ifndef   __VANILLA_ANALYTIC_QM_HPP__
#define   __VANILLA_ANALYTIC_QM_HPP__


#include <qmlib/finance/analytics/sensitivity.hpp>
#include <qmlib/finance/payoffs/payoff1.hpp>
#include <qmlib/finance/rates/irates.hpp>


/** \file
 * \brief Analytic pricing of barrier options
 * \ingroup analytics
 */



QM_NAMESPACE2(finance)

/** \brief calculate a forward price from spot and discount curves
 * 
 * @param spot		Spot price
 * @param expiry	Forward expiry
 * @param yc		A idiscountcurve which represents the interest rate discount factor curve
 * @param cy		A idiscountcurve which represents the convenience yield discount factor curve
 * @param ba		Interest rate discount factor
 * @param bb		Convenience yield discount factor
 */
inline qm_real forward(qm_real spot, qdate expiry, DISCOUNTCURVE yc,
					   DISCOUNTCURVE cy, qm_real& ba, qm_real& bb)  {
	ba = yc ? yc->df(expiry) : 1;
	bb = cy ? cy->df(expiry) : 1;
	return spot*bb/ba;
}


/** \brief Price a forward vanilla call option using the Black model
 * \ingroup payoff
 */
inline void black_fwdcall(qm_real fwd, qm_real strike, qm_real T, qm_real sigma, BLACKSENSITIVITY& an) {
	QM_REQUIRE(fwd > 0 && strike > 0, "Forward and strike must be positive");
	QM_REQUIRE(T >= 0, "Time to maturity must be non-negative");
	QM_USING_NAMESPACE2(math);
	qm_real S  = strike/fwd;
	qm_real s  = std::log(S);
	qm_real st = std::sqrt(T);
	qm_real vt = sigma*st;
	qm_real d  = (0.5*vt*vt - s)/vt;
	normal_dist nd;
	qm_real Nd1   = nd.cumulative(d);
	qm_real nd1   = nd.density(d);
	qm_real Nd2   = nd.cumulative(d-vt);
	qm_real pva   = Nd1 - S*Nd2;
	an->set_value(fwd*pva);
	an->set_vega(fwd*nd1*st);
	an->set_delta(Nd1);
	an->set_gamma(nd1/(fwd*vt));
	an->set_volga(an->vega()*d*(d - vt)/sigma);
	an->set_vanna(-nd1*(d - vt)/sigma);   // d^2 V / d vol d fwd 
	an->set_theta(-0.5*fwd*nd1*sigma/st);
	return an;
}




template<class V>
struct vanilla_analytic {};


template<>
struct vanilla_analytic<_CALL_> {
	vanilla_analytic(){}
	sensitivities price(qm_real strike, qdate expiry, DISCOUNTCURVE yc, DISCOUNTCURVE cy,
						       qm_real spot, qm_real vol) const  {
		qm_real ba,bb;
		qm_real fwd = forward(spot,expiry,yc,cy,ba,bb);
		qm_real T	= 1;
		BLACKSENSITIVITY an(yc.date(),"Black sensitivity");
		black_fwdcall(fwd,strike,T,vol,an);
		*an *= ba;
		sensitivities s;
		//s.add(an);
		return s;
	}	
};

template<>
struct vanilla_analytic<_PUT_>  {
	
	sensitivities price(qm_real strike, qdate expiry, DISCOUNTCURVE yc, DISCOUNTCURVE cy,
						  qm_real spot, qm_real vol) const  {
		/*
		qm_real ba,bb;
		qm_real fwd = forward(spot,expiry,yc,cy,ba,bb);
		qm_real T	= 1;
		BLACKSENSITIVITY an(black_fwdcall(fwd,strike,T,vol));
		an->set_value(an->value() + strike - fwd);
		an->set_delta(an->delta() - 1);
		*an *= ba;
		*/
		sensitivities s;
		//s.append(an);
		return s;
	}	
};


QM_NAMESPACE_END2



#endif	//	__VANILLA_ANALYTIC_QM_HPP__
