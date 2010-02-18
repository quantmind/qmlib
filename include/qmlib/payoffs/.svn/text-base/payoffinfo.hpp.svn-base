
#ifndef   __PAYOFF_INFO_QM_HPP__
#define   __PAYOFF_INFO_QM_HPP__

#include <qmlib/payoffs/enums.hpp>


QM_NAMESPACE

template<payoffname pn> struct  payoffinfo;
template<bool U,barriertype T> struct BarrierTalk;



// Helper class for Barriers
template<> struct BarrierTalk<true,KnockOut_>  {
	static qm_string tostring() {return "Up and Out";}
	static bool	     knocked(qm_real x, qm_real b) {return x >= b;}
};
template<> struct BarrierTalk<false,KnockOut_> {
	static qm_string tostring() {return "Down and Out";}
	static bool	     knocked(qm_real x, qm_real b) {return x <= b;}
};
template<> struct BarrierTalk<true,KnockIn_>   {
	static qm_string tostring() {return "Up and In";}
	static bool	     knocked(qm_real x, qm_real b) {return x >= b;}
};
template<> struct BarrierTalk<false,KnockIn_>  {
	static qm_string tostring() {return "Down and In";}
	static bool	     knocked(qm_real x, qm_real b) {return x <= b;}
};



template<>
struct  payoffinfo<CALL_>  {
	static qm_real get(qm_real strike, qm_real x) {return std::max(x - strike,0.0);}
	static qm_string name() {return "call";}
};
template<>
struct  payoffinfo<PUT_>  {
	static qm_real get(qm_real strike, qm_real x) {return std::max(strike - x,0.0);}
	static qm_string name() {return "put";}
};
template<>
struct  payoffinfo<BINARY_CALL_>  {
	static qm_real get(qm_real strike, qm_real x) {return x >= strike ? 1 : 0;}
	static qm_string name() {return "binary call";}
};
template<>
struct  payoffinfo<BINARY_PUT_>  {
	static qm_real get(qm_real strike, qm_real x) {return x <  strike ? 1 : 0;}
	static qm_string name() {return "binary put";}
};



QM_NAMESPACE_END


#endif	//	__PAYOFF_INFO_QM_HPP__

