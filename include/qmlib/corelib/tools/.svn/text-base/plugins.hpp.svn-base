

#ifndef   __SIMPLE_PLUGINS_QM_HPP__
#define   __SIMPLE_PLUGINS_QM_HPP__


#include	<qmlib/corelib/tools/string.hpp>
#include	<qmlib/corelib/templates/observer.hpp>


/** \file
 * \brief Simple classes used as plug-ins for more complex classes
 * \ingroup utility
 */


QM_NAMESPACE

class   ivalue;
typedef QM_SMART_PTR(ivalue)				IVALUE;


/** \brief Interface class for a scalar value
 * \ingroup utility
 */
class ivalue : public basedes, public observable {
public:
	virtual ~ivalue(){}
    //
    /// \brief Set a market value, this could be a price, a rate.
    virtual void      set_value(qm_real mktval)              {}
    //
    /// \brief Set a market value, this could be a price, a rate.
    virtual qm_real   get_value()                   const    {return 0.0;}
    //
    /// \brief Set a market value, this could be a price, a rate.
    virtual qm_real   get_ratevalue()               const    {return this->get_value();}
    
    virtual bool      validvalue()    const    {return false;}
    
    virtual IVALUE	  duplicate()  const {return IVALUE();}
    
    qm_string aspc() const {return nice_percent(this->get_ratevalue(),5);}
    qm_string asbp() const {return nice_bp(this->get_ratevalue(),3);}
protected:
	ivalue(){}
};

/** \brief Simple ivalue implementation
* \ingroup utility
*/
class simple_value: public ivalue  {
public:
	simple_value(qm_real val = 0.0):m_value(val){}
    void      set_value(qm_real val) {m_value = val; this->notify_observers();}
    bool      validvalue()        const    {return m_value > 0.0;}
    qm_real   get_value()         const    {return m_value;}
    qm_string tostring()		  const    {return "value " + object_to_string(m_value);}
    IVALUE	  duplicate()  		  const    {return IVALUE(new simple_value(m_value));}
protected:
    qm_real m_value;
};


/** \brief Rate value implementation
* \ingroup utility
*/
class rate_value: public simple_value  {
public:
	rate_value(qm_real val = 0.0):simple_value(val){}
    qm_string tostring() 		const {return "rate " + this->aspc();}
    qm_real	  get_ratevalue()   const {return 0.01*m_value;}
};

/** \brief Interest rate future value
* \ingroup utility
*/
class irfuture_value: public simple_value  {
public:
	irfuture_value(qm_real val = 0.0):simple_value(val){}
	bool      validvalue()        const    {return m_value > 50.0 && m_value < 100.0;}
	qm_real	  get_ratevalue()     const	   {return 0.01*(100. - m_value);}
    qm_string tostring() const {return "price " + nice_real(m_value,4);}
};


/** \brief Helper class which holds a smart pointer to ivalue
 * \ingroup utility
 */
class obj_value  {
public:
	obj_value():m_val(new simple_value){}
	obj_value(IVALUE val):m_val(val) {QM_REQUIRE(m_val,"Value not defined");}
	obj_value(const obj_value& rhs):m_val(rhs.m_val->duplicate()) {}
	virtual ~obj_value(){}
	
	IVALUE       value()  const {return m_val;}
protected:
	IVALUE m_val;
};


QM_NAMESPACE_END



#endif  //  __SIMPLE_PLUGINS_QM_HPP__

