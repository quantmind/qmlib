
#ifndef   __PAYOFF1_QM_HPP__
#define   __PAYOFF1_QM_HPP__

#include <qmlib/finance/payoff/payoff.hpp>


/** \file
 * \brief class template for an Option Payoff
 * 
 * \ingroup finins
 */



QM_NAMESPACE2(finance)

namespace {
	
	struct worsefun  {
		qm_real operator () (qm_real v1, qm_real v2) const {return std::min(v1,v2);}
	};
	
}

class worseoff2: public composite_payoff<2,Vanilla_,worsefun> {
public:
};


QM_NAMESPACE_END2


#endif	//	__PAYOFF1_QM_HPP__
