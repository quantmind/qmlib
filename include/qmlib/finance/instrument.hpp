
#ifndef   __INSTRUMENT_INTERFACE_QM_HPP__
#define   __INSTRUMENT_INTERFACE_QM_HPP__


//#include <qmlib/corelib/static/all.hpp>
#include <qmlib/corelib/tools/json.hpp>
#include <qmlib/irates.hpp>


/*! \defgroup finins Financial Instrument library

    Classes for handling finacial instruments

    @{
*/

/// \file
/// \brief Instruments base classes



QM_NAMESPACE2(finance)

class ipricer;
class instrument;
typedef QM_SMART_PTR(ipricer)		PRICER;
typedef QM_SMART_PTR(instrument)	INST;


enum instrumentype {
	deposit_ = 0,
	fra_,
	swap_,
	irfuture_,
	ois_,
	cms_,
	general_,
	option_,
};

template<instrumentype typ> struct InstrumentInfo {};


/** \brief Base class for a general financial instrument.
 * 
 * This class defines the basic method for a financial instrument.
 * A forward declaration of this class is in iquote.hpp
 */
//class instrument: public basedes, public lazy  {
class instrument: public icodename, public lazy {
public:
    virtual instrumentype type() const {return general_;}
    virtual json tojson() const {return json();}
    qm_string tostring()  const {return this->tojson().tostring();}
    void updatelazy() {}
    sensitivities results;
protected:
	instrument(){}
};

class finins : public icodename  {
public:
	template<class I>
	finins(const QM_SMART_PTR(I)& ins);
	finins(const finins& rhs):m_inst(rhs.m_inst),m_pricer(rhs.m_pricer){}
	PRICER get_pricer() const {return m_pricer;}
	void set_pricer(const PRICER& e);
	instrumentype type()     const {return m_inst->type();}
	qm_string     code()     const {return m_inst->code();}
	qm_string     name()     const {return m_inst->name();}
	json 		  tojson()   const {return m_inst->tojson();}
	qm_string     tostring() const {return m_inst->tostring();}
	INST	  get_instrument() {return m_inst;}
	sensitivities get_results() const {return m_inst->results;}
protected:
	INST	m_inst;
	PRICER	m_pricer;
};


template<class I>
inline finins::finins(const QM_SMART_PTR(I)& ins) {
	m_inst = smart_cast<instrument,I>(ins);
}

template<instrumentype typ> 
class Instrument: public instrument {
public:
	static const instrumentype Type = typ;
	instrumentype type()   const {return Type;}
	qm_string     code()   const {return InstrumentInfo<typ>::name();}
	json          tojson() const;
};


/** \brief Interface for instrument containing a scalar rate
 * \ingroup finins
 * 
 */
class instrate  {
public:
	virtual ~instrate(){}
	
	/// \brief the rate
	IVALUE rate() const {return m_rate;}
protected:
	instrate(){}
	instrate(ivalue* ra):m_rate(ra){QM_REQUIRE(m_rate,"Rate not available");}
	IVALUE m_rate;
};


/** \brief Interface for simple discounting instrument
 * \ingroup finins
 * 
 * This interface is used for vanilla fixed income instruments such as deposit, FRA,
 * vanilla interest rate swap, interest rate future.
 */
class isimplediscount: public instrate {
public:
	/// \brief Cash flow
	///
	///@params date Initial date of cash flow
	///@return Cash flow from date to expiry
	virtual CASHFLOW cashflow(const qdate& dte) const {QM_FAIL("build_cashflow not implemented");}
	
	virtual unsigned curvepriority() const {return 0;}
	
	CASHFLOW cashflow0() const {return this->cashflow(qdate::today());}
	
	/// \brief Internal continuously compounded rate
	virtual qm_real internalccr() const {return 0;}
	
	virtual qm_string simple_discount_string() const {return "";}
	
	virtual const qdate& lastdate() const {QM_FAIL("not implemented");}
	virtual const qdate& expiry()   const {return this->lastdate();}
protected:
	isimplediscount(){}
	isimplediscount(ivalue* ra):instrate(ra){}
};


template<instrumentype typ>
inline json Instrument<typ>::tojson() const  {
	json js;
	js.insert("type",InstrumentInfo<typ>::name());
	return js;
}



QM_NAMESPACE_END2


#include <qmlib/finance/impl/instrumentInfo.hh>

/*! @} */

#endif	//	__INSTRUMENT_INTERFACE_QM_HPP__





