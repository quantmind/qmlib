

#ifndef   __SECURITY_QM_H__
#define   __SECURITY_QM_H__


#include <qmlib/corelib/tools/json.hpp>
#include <qmlib/corelib/static/all.hpp>


QM_NAMESPACE2(finance)

template<class F, class G> struct future_next;

class security;
class future;
typedef QM_SMART_PTR(security)	SECURITY;
typedef QM_SMART_PTR(future)	FUTURE;


/** \brief Base class for securities
 * \ingroup finins
 * 
 */
class security: public icodename  {
public:
	security(){}
	virtual CCY			currency() const {QM_FAIL("not implemented");}
	virtual CONTRACT	contrac()  const {QM_FAIL("not implemented");}
	const qdate&		expiry()   const {return m_expiry;}
	
	qm_string tostring() const {return this->code();}
	qm_string name() 	 const {return this->code();}
	qm_string code() 	 const {return m_code;}
protected:
	qm_string   m_code;
	qdate		m_expiry;
	
	security(const qdate& expiry):m_expiry(expiry){}
};


class future: public security  {
public:	
	CCY			currency() const {return m_ex->currency();}
	CONTRACT	contrac()  const {return smart_cast<contract,exchange>(m_ex);}
	const qdate& expiry()  const {return m_expiry;}
	
protected:
	EXCHANGE	m_ex;
	
	future(const EXCHANGE& ex, const qdate& expiry):security(expiry),m_ex(ex) { 
		QM_REQUIRE(m_ex,"Contract not specified");
		int       m = m_expiry.month();
		qm_string y = object_to_string(m_expiry.year());
		qm_string c = y.substr(1);
		c[0]        = monthcodes[m-1];
		m_code      = m_ex->code() + c;
	}
};


QM_NAMESPACE_END2

    
#endif  //  __SECURITY_QM_H__

