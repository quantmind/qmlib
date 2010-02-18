


#ifndef   __CORE_OPTION_MODELS_QM_HPP__
#define   __CORE_OPTION_MODELS_QM_HPP__


#include <qmlib/finance/pricers/pricer.hpp>
#include <qmlib/finance/rates/optionrate.hpp>





QM_NAMESPACE2(finance)


/** Helper class template for option calculation.
 * \ingroup pricers
 * 
 * This template class cast an option_base into an option object
 * and call the optionmodel for pricing
 */
template<unsigned N, pricingValuationMethod V>
class performOptionCalculation  {
public:
	typedef option_base<N>					optionbt;
	typedef QM_SMART_PTR(optionbt)			OPTIONBT;
	typedef optionmodel<N,V>				model_type;
	typedef QM_SMART_PTR(model_type)		MODEL_TYPE;
	
	template<exercisetype et>
	static SENSITIVITY doit(const OPTIONBT& inst, const MODEL_TYPE& model)  {
		if(inst->payoffType() == Vanilla_)
			return dotype<et,Vanilla_>(inst,model);
		else if(inst->payoffType() == Barrier_)
			return dotype<et,Barrier_>(inst,model);
		else if(inst->payoffType() == Average_)
			return dotype<et,Average_>(inst,model);
		QM_FAIL("Critical error during option calculation. Could not cast option.");
	}
protected:
	template<exercisetype et, payofftype pt>
	static SENSITIVITY dotype(const OPTIONBT& inst, const MODEL_TYPE& model)  {
		typedef option<N,et,pt> option_type;
		QM_SMART_PTR(option_type) op = smart_cast<option_type,optionbt>(inst);
		//QM_REQUIRE(op,"Critical error, could not cast option");
		return model->calculate(op);
	}
};



/** \brief Specialization of pricerhelp for option pricing
 * \ingroup pricers
 */
template<unsigned N, pricingValuationMethod V>
struct pricerhelp<option_base<1u>,V,optionmodel<N,V> >  {
	
	typedef pricerTraits<option_base<1u>,V,optionmodel<N,V> > ptraits;
	
	static SENSITIVITY
	calculate(const typename ptraits::INSTRUMENT_TYPE& inst,
			  const typename ptraits::MODEL_TYPE& model)  {
		typedef performOptionCalculation<N,V> optcalc;
		if(inst->exerciseType() == European_)
			return optcalc::template doit<European_>(inst,model);
		else if(inst->exerciseType() == American_)
			return optcalc::template doit<American_>(inst,model);
		else if(inst->exerciseType() == Bermudan_)
			return optcalc::template doit<Bermudan_>(inst,model);
		QM_FAIL("Could not price the option");
	}
	
	static qm_string code() {return "Option pricer";}
};



//typedef pricer<option_base<1u>,ioptionmodel,pde_,optionmodel<1u,pde_> > opPdePricer1D;



QM_NAMESPACE_END2



#endif  //  __CORE_OPTION_MODELS_QM_HPP__

