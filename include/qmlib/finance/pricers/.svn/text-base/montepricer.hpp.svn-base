

#ifndef   __MONTECARLO_PRICER_QM_HPP__
#define   __MONTECARLO_PRICER_QM_HPP__

#include <qmlib/finance/pricers/pricer.hpp>
#include <qmlib/math/monte/all.hpp>



QM_NAMESPACE2(finance)


class montemodel : public irate, public smartholder<QM_FROM_NAMESPACE2(math)montecarlo> {
public:
	montemodel(){}
protected:
};

template<>
struct pricerhelp<instrument,montecarlo_,montemodel>  {
	typedef pricerTraits<instrument,montecarlo_,montemodel> ptraits;
	
	static SENSITIVITY
	calculate(const ptraits::INSTRUMENT_TYPE& inst, const ptraits::MODEL_TYPE& model, bool fuleval) {
		QM_FAIL("not implemented");
	}
	
	static qm_string code() {return "MonteCarloPricer";}
};



typedef pricer<instrument,montemodel,montecarlo_,montemodel> montepricer;


QM_NAMESPACE_END2


#endif	//	__MONTECARLO_PRICER_QM_HPP__

