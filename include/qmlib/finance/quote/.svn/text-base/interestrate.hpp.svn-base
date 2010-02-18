


#ifndef	__INTERESTRATE_QUOTE_QM_HPP__
#define	__INTERESTRATE_QUOTE_QM_HPP__


#include <qmlib/finance/quote/quote.hpp>
#include <qmlib/finance/irhelp.hpp>
#include <qmlib/finance/instrument.hpp>


QM_NAMESPACE2(finance)

// Some forward declarations

class interestrate;
class ratefactory;
typedef QM_SMART_PTR(interestrate) INTERESTRATE;


class interestrate : public iticker {
public:
	IRHELP help()    		 const {return m_irh;}
	CCY    currency() 		 const {return m_ccy;}
	const period& start()    const {return m_start;}
	const period  maturity() const {return m_start + m_irh->tenure();}
	qm_string 	  Short()    const {return m_code;}
	
	virtual instrumentype type() const {QM_FAIL("not implemented");}
	virtual unsigned  	  priority() const {return 0;}
protected:
	interestrate(const CCY& cur, const IRHELP& ir, const period& start);
	CCY				m_ccy;
	IRHELP			m_irh;
	period 		 	m_start;
	qm_string	 	m_code;
};



template<instrumentype typ>
class InterestRate: public interestrate  {
	friend class ratefactory;
public:
	static const instrumentype Type = typ;
	static const unsigned Priority = InstrumentInfo<typ>::priority;
	
	qm_string	  code() const; 
	qm_string	  name() const;
	instrumentype type() const {return Type;}
	unsigned  priority() const {return Priority;}
protected:
	InterestRate(const CCY& cur, const IRHELP& ir, const period& start);
};


class ratefactory  {
public:
	static INTERESTRATE create(const qm_string& cu, const qm_string& schedule);
	static INTERESTRATE create2(const qm_string& cu, const qm_string& schedule, bool isois);
	static INTERESTRATE create3(const CCY& cur, const period& start, const period& tenure, bool isois);
};



QM_NAMESPACE_END2


#include <qmlib/finance/quote/impl/interestrate_impl.hh>


#endif	//	__INTERESTRATE_QUOTE_QM_HPP__

