

#ifndef   __PRICER_ENGINE_QM_HPP__
#define   __PRICER_ENGINE_QM_HPP__

#include <qmlib/finance/ipricer.hpp>


QM_NAMESPACE2(finance)



template<class I, pricingValuationMethod V, class T> struct pricerhelp;



template<class I, pricingValuationMethod V, class T>
struct pricerTraits  {
	typedef I								instrument_type;
	typedef T								model_type;
	typedef QM_SMART_PTR(instrument_type) 	INSTRUMENT_TYPE;
	typedef QM_SMART_PTR(model_type) 		MODEL_TYPE;
	typedef pricerhelp<I,V,T>				helper_type;
};




/**\brief Template implementation of ipricer
 * \ingroup pricers
 * 
 * @param I instrument type
 * @param M model input type
 * @param V pricingValuationMethod
 * @param T model type
 */
template<class I, class M, pricingValuationMethod V, class T>
class pricer: public ipricer  {
public:
	typedef pricerTraits<I,V,T>						ptraits;
	typedef typename ptraits::instrument_type		instrument_type;
	typedef typename ptraits::model_type			model_type;
	typedef typename ptraits::INSTRUMENT_TYPE		INSTRUMENT_TYPE;
	typedef typename ptraits::MODEL_TYPE			MODEL_TYPE;
	typedef typename ptraits::helper_type			helper_type;
	
	typedef M										model_input_type;
	typedef QM_SMART_PTR(M) 						MODEL_INPUT_TYPE;
	typedef ipricer::container_type					container_type;
	typedef typename container_type::iterator		iterator;
	typedef typename container_type::const_iterator	const_iterator;
	
	static const pricingValuationMethod valuation_type = V;
	
	/// \brief make the pricer
	///
	///@param mod Model used for pricing
	///@return a smart ipricer pointer
	static PRICER make(MODEL_INPUT_TYPE mod, unsigned NumT, bool fulval) {return PRICER(new pricer(mod,NumT,fulval));}
	
	qdate   date()                  const {return m_model->date();}
	pricingValuationMethod method() const {return valuation_type;}
	
	void calculate() 	 const;
	
	unsigned  numberOfThreads() const {return m_numberOfThreads;}
	qm_string code() 	 		const {return helper_type::code();}
	
	qm_string tostring() const;
	
protected:
	pricer(const MODEL_INPUT_TYPE& mo, unsigned NumT, bool fullevaluation);
	void preprocessing() const {}
	void checkinstrument(const INSTRUMENT_TYPE& inst) const {}
	bool add(const INST& inst);
	MODEL_TYPE m_model;
	unsigned   m_numberOfThreads;
};






//______________________________________________________________________________________
//	IMPLEMENTATION



template<class I, class M, pricingValuationMethod V, class T>
inline pricer<I,M,V,T>::pricer(const typename pricer<I,M,V,T>::MODEL_INPUT_TYPE& mo,
							   unsigned NumT,
							   bool fullevaluation):
	ipricer(fullevaluation),m_numberOfThreads(NumT) {
	m_model = smart_cast<model_type,model_input_type>(mo);
	QM_REQUIRE(m_model,"Pricing model is null");
}

template<class I, class M, pricingValuationMethod V, class T>
inline bool pricer<I,M,V,T>::add(const INST& inst)  {
	INSTRUMENT_TYPE it = smart_cast<instrument_type,instrument>(inst);
	if(it)  {
		this->checkinstrument(it);
		this->append(inst);
		return true;
	}
	return false;
}


template<class I, class M, pricingValuationMethod V, class T>
inline void pricer<I,M,V,T>::calculate() const {
	SENSITIVITY 	se;
	INSTRUMENT_TYPE	bt;
	preprocessing();
	for(const_iterator it=this->begin(); it!=this->end();++it)  {
		bt = smart_cast<instrument_type,instrument>(*it);
		se = helper_type::calculate(bt,m_model,this->fulleval());
		(*it)->results.add(se);
	}
}

template<class I, class M, pricingValuationMethod V, class T>
inline qm_string pricer<I,M,V,T>::tostring() const  {
	qm_string ts = this->code();
	ts += ": { " + m_model->tostring() + " }";
	return ts;  
}


QM_NAMESPACE_END2



#endif	//	__PRICER_ENGINE_QM_HPP__


