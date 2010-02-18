

#ifndef   __CASHFLOW_PRICER_QM_HPP__
#define   __CASHFLOW_PRICER_QM_HPP__

#include <qmlib/finance/pricers/pricer.hpp>



QM_NAMESPACE2(finance)


/*
class cashFlowPricer : public pricer<isimplediscount,idiscountcurve,analytical_> {
public:
	typedef pricer<isimplediscount,idiscountcurve,analytical_> base_class;
	qm_string code() const {return "cashFlowPricer";}
	static PRICER make(DISCOUNTCURVE crv) {return PRICER(new cashFlowPricer(crv,true));}
protected:
	void  calculateone(const INSTRUMENT_TYPE& ist) const;
	cashFlowPricer(DISCOUNTCURVE crv, bool fe):base_class(crv,fe){}
};
*/

template<>
struct pricerhelp<isimplediscount,analytical_,idiscountcurve>  {
	typedef pricerTraits<isimplediscount,analytical_,idiscountcurve> ptraits;
	
	static SENSITIVITY
	calculate(const ptraits::INSTRUMENT_TYPE& inst, const ptraits::MODEL_TYPE& model, bool fulev) {
		return model->dcashflow(inst->cashflow(model->date()),fulev);
	}
	
	static qm_string code() {return "cashFlowPricer";}
};



//typedef pricer<isimplediscount,idiscountcurve,analytical_,idiscountcurve> cashFlowPricer;


QM_NAMESPACE_END2


#endif	//	__CASHFLOW_PRICER_QM_HPP__

