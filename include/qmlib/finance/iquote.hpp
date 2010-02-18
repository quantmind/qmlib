


#ifndef	__IQUOTE_QM_HPP__
#define	__IQUOTE_QM_HPP__


#include <qmlib/corelib/templates/observer.hpp>
#include <qmlib/corelib/dates/all.hpp>


/*! \defgroup quote Financial Quotes library

    Classes for market quotes and tickers

    @{
*/

/** \file
 * \brief iquote and iticker interfaces
 */




QM_NAMESPACE2(finance)

class iquote;
class iticker;
typedef QM_SMART_PTR(iticker) TICKER;
typedef QM_SMART_PTR(iquote)  QUOTE;


/** \brief Base class for a market ticker
 * 
 * A market ticker has information about a iquote.
 * While the iquote is associated with a given date and value,
 * a ticker is associated only with its code.
 * derived class may contain more information than just the code.
 */
class iticker: public icodename  {
public:
	virtual qm_string Short() const {return "";}
	
	qm_string get_providerCode() const  {return m_data_provider_code;}
	void set_providerCode(const qm_string& pc) {m_data_provider_code = pc;}
	qm_string get_providerArgs() const  {return m_data_provider_args;}
	void set_providerArgs(const qm_string& pc) {m_data_provider_args = pc;}
protected:
	qm_string m_data_provider_code;
	qm_string m_data_provider_args;
};

/** \brief A market quote
 * 
 * A market quote has the following properties:
 *  - A market iticker
 *  - A date
 *  - A numeric value
 */
class iquote : public icodename, public observable {
public:
	virtual ~iquote() {}
    //! returns the current value
    virtual qm_real value() const {QM_FAIL("not implemented");};
    void set_value(qm_real val) {if(this->set_value_changed(val)) this->notify_observers();}
    //! returns true if the Quote holds a valid value
    virtual bool isValid() const {QM_FAIL("not implemented");}
    
    virtual qdate date() const {QM_FAIL("not implemented");}
    
    virtual TICKER ticker()   const {QM_FAIL("not implemented");}
    
    qm_string Short() const {QM_FAIL("not implemented");}
protected:
	iquote() {}
	virtual bool set_value_changed(qm_real val) {return false;}
};



QM_NAMESPACE_END2


/*! @} */

#endif	//	__IQUOTE_QM_HPP__


