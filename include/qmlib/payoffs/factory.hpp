
#ifndef   __PAYOFF_FACTORY_QM_HPP__
#define   __PAYOFF_FACTORY_QM_HPP__


#include <qmlib/payoffs/payoff1.hpp>


/** \file
 * \brief Factory class for Payoffs
 * 
 * \ingroup finins
 */

QM_NAMESPACE


/** \brief Factory class for Payoffs
 * \ingroup finins
 */
template<payoffname pn>
struct vanilla_factory  {
	typedef vanillaPayoffImpl<pn>				payoff_type;
	typedef Payoff<1u,Vanilla_>					base_payoff;
	typedef QM_SMART_PTR(base_payoff)			PAYOFF_TYPE;
	
	static qm_string inputs() {return "strike";}
	
	static PAYOFF_TYPE make(qm_real strike)  {
		return PAYOFF_TYPE(new payoff_type(strike));
	}
};

template<bool U, barriertype T, payoffname pid, payoffname pn = UNKNOWN_PAYOFF_>
struct barrier_factory  {
	typedef barrierPayoffImpl<U,T,pid,pn>		payoff_type;
	typedef Payoff<1u,Barrier_>					base_payoff;
	typedef QM_SMART_PTR(base_payoff)			PAYOFF_TYPE;
	
	static qm_string inputs() {return "strike,barrier,rebate";}
	
	static PAYOFF_TYPE make(qm_real strike, qm_real barrier, qm_real rebate)  {
		return PAYOFF_TYPE(new payoff_type(strike,barrier,rebate));
	}
};

template<bool U, barriertype T, payoffname pid>
struct barrier_factory<U,T,pid,UNKNOWN_PAYOFF_>  {
	typedef OneTouchImpl<U,T,pid>				payoff_type;
	typedef Payoff<1u,Barrier_>					base_payoff;
	typedef QM_SMART_PTR(base_payoff)			PAYOFF_TYPE;
	
	static qm_string inputs() {return "barrier";}
	
	static PAYOFF_TYPE make(qm_real barrier, qm_real rebate)  {
		return PAYOFF_TYPE(new payoff_type(barrier,rebate));
	}
};
	
QM_NAMESPACE_END


#endif	//	__PAYOFF_FACTORY_QM_HPP__
