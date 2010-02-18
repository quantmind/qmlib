
#ifndef   __CASHFLOW_QM_HPP__
#define   __CASHFLOW_QM_HPP__


#include 	<qmlib/sensitivity.hpp>
#include 	<qmlib/corelib/tools/plugins.hpp>
#include 	<qmlib/corelib/templates/containers.hpp>


/*! \defgroup rates Rate Library

    Interfaces and implementation of rates, simple and composite.

    @{
*/

/// \file
/// \ingroup rates


QM_NAMESPACE

class   icashevent;

/** \brief Smart pointer to icashevent
 */
typedef QM_SMART_PTR(icashevent)            CASHEVENT;

/** \brief Cashflow object
 * 
 * A cash flow object is a template specialization of a dataserie
 * with qdate as keys and smart pointer to icashevent as values
 */
typedef dataserie<qdate,true,CASHEVENT>     CASHFLOW;


/** \brief Interface for a cash event
 */
class icashevent : public basedes {
public:
    virtual ~icashevent(){}
    //
    /// \brief return the cash ammount
    virtual qm_real   cash()       	      const { return 0;}
    /// \brief return the the notional ammount
    virtual qm_real   notional()          const { return 0;}
    /// \brief return the the notional exchange ammount
    virtual qm_real   notional_exchange() const { return 0;}
    /// \brief return a year fraction
    virtual qm_real   tau()			const { return 0;}    
    /// \brief True if the cash flow is dummy (not a real cash flow)
    virtual bool      isdummy()     const { return false;}
    /// \brief Fetch a value from the cahs flow
    virtual IVALUE    get_value()   const { return IVALUE();}
    ///
    virtual unsigned  size()        const {QM_FAIL("this is not a multiple cash event.");}
    virtual void      add(const CASHEVENT& c) {QM_FAIL("this is not a multiple cash event.");}
    
    /// \brief To string
    qm_string tostring()    const { return m_description;}
    //
    /** \brief notional times a year fraction
     * 
     * @return The notional ammount times a time fraction
     */ 
    qm_real           ntau()                                   const  { return this->notional()*this->tau();}
    void              set_description(const qm_string& descr)         { m_description = descr;}
    const  qm_string& get_description()                        const  { return m_description;}
protected:
	icashevent(const qm_string& descr=""):m_description(descr){}
    qm_string   m_description;
};


/// \brief Simple fix Cash flow
class fixcash : public icashevent  {
public:
	fixcash(qm_real cashval, bool dummy = false, const qm_string& descr=""):icashevent(descr),m_cash(cashval),m_dummy(dummy){}
	qm_real    cash()      			const { return m_cash;}
	bool 	   isdummy()			const { return m_dummy;}
	qm_real    notional()  			const { return m_cash;}
	qm_real    notional_exchange() 	const { return m_cash;}
	qm_string  tostring()  			const { 
		qm_string str = this->isdummy() ? "Dummy Cash, " : "Fix Cash, ";
		return str + m_description + " " + pretty_print(this->notional());
	}
	static CASHEVENT	make1(qm_real val) {return CASHEVENT(new fixcash(val));} 
	static CASHEVENT	make2(qm_real val, bool dummy) {return CASHEVENT(new fixcash(val,dummy));}
protected:
	qm_real m_cash;
	bool	m_dummy;
};


/// \brief Base class for an event which uses the IVALUE pointer
class value_event : public icashevent {
public:
    IVALUE     get_value() const  { return m_value;}
protected:
	value_event(qm_real val, const qm_string& descr=""):icashevent(descr),m_value(new simple_value(val)){}
	value_event(IVALUE val, const qm_string& descr=""):icashevent(descr),m_value(val){QM_REQUIRE(m_value,"value not defined");}
    IVALUE    m_value;
};


/// \brief Coupon cash
class couponevent: public value_event  {
public:
	couponevent(qm_real coupon, qm_real dcf, qm_real notional = 1, const qm_string& des = ""):
		value_event(coupon,des),m_dcf(dcf),m_notional(notional){}
	couponevent(IVALUE coup, qm_real dcf, qm_real notional = 1, const qm_string& des = ""):
		value_event(coup,des),m_dcf(dcf),m_notional(notional){}
	qm_real    tau()        const {return m_dcf;}
	qm_real    notional()   const {return m_notional;}
    qm_real    cash()       const {return m_value->get_ratevalue()*this->ntau();}
    qm_string  tostring()   const {
    	return "Coupon Event.  coupon: " + m_value->aspc() +
    		   ", tau: "      + pretty_print(this->tau()) +
    		   ", notional: " + pretty_print(this->notional()) +
    		   ", cash: "     + pretty_print(this->cash());
    }
protected:
    qm_real   m_dcf;
    qm_real   m_notional;
};



/// \brief Cash flow containing several cash flows
class multcash: public icashevent  {
public:
	typedef std::vector<CASHEVENT>		container;
	multcash(){}
	multcash(const CASHEVENT& c) {this->add(c);}
	multcash(const multcash& rhs){*this = rhs;}
	
	multcash& operator = (const multcash& rhs) {
		m_flows.clear();
		for(container::const_iterator it = rhs.m_flows.begin();it!=rhs.m_flows.end();++it)
			m_flows.push_back(*it);
		return *this;
	}
	
	void add(const CASHEVENT& c) {if(c) m_flows.push_back(c);}
	unsigned size() const {return m_flows.size();}
	
	qm_real    cash()       const {
		qm_real c = 0;
		for(container::const_iterator it = m_flows.begin();it!=m_flows.end();++it)
			c += (*it)->cash();
		return c;
	}
	
	qm_real    tau()        const {QM_FAIL("multiple cash event does not support this functionality");}
	qm_real    notional()   const {QM_FAIL("multiple cash event does not support this functionality");}
	
    qm_string  tostring()   const {
    	qm_real c = this->cash();
    	return "Multiple cash event " + object_to_string(c);
    }
private:
	container  m_flows;
};



QM_NAMESPACE_END


/*! @} */


#endif  //  __CASHFLOW_QM_HPP__

