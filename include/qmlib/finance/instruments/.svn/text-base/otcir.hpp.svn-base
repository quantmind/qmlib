
#ifndef   __OTC_IR_QM_HPP__
#define   __OTC_IR_QM_HPP__

#include <boost/static_assert.hpp>
#include <qmlib/finance/quote/interestrate.hpp>
#include <qmlib/finance/ccyinst.hpp>
#include <qmlib/finance/instruments/swapstream.hpp>
#include <qmlib/finance/instruments/simplediscount.hpp>



/** \brief Vanilla fixed income instrument
 * \ingroup finins
 * 
 * This file contains the definition for common fixed income
 * otc instruments such as
 * 	- deposit
 *  - fra
 *  - vanillaswap
 *  - cms
 */

QM_NAMESPACE2(finance)

// Forward declarations
class otcir;
template<instrumentype typ> class simpleir;

typedef simpleir<deposit_>  		deposit;
typedef simpleir<fra_>  			fra;
typedef simpleir<swap_> 			vanillaswap;
typedef QM_SMART_PTR(otcir)			OTCIR;
typedef QM_SMART_PTR(deposit)		DEPOSIT;
typedef QM_SMART_PTR(fra)			FRA;
typedef QM_SMART_PTR(vanillaswap)	VANILLASWAP;



/** \brief Base interface for OTC vanilla interest rate derivatives
 * \ingroup finins
 * 
 */
class otcir: public ccyplug, public simplediscount  {
public:
	static finins make(const INTERESTRATE& ir, const qdate& dte);
protected:
	otcir(const CCY& ccy, qm_real notional):ccyplug(ccy,notional),simplediscount(new rate_value){}
};



/** \brief Common otc fixed income instruments
 * 
 * This class is the the base class for:
 * 	- depo
 *  - fra
 *  - vanillaswap
 *  - interestRateFuture
 */
template<instrumentype typ>
class simpleir: public Instrument<typ>, public otcir  {
public:// Forward declarations
	IRHELP	irleg() const {return m_rhelp;}
	json	tojson() const;
	static OTCIR create(const INTERESTRATE& irt, const qdate& date); 
	
	unsigned curvepriority() const {return InstrumentInfo<typ>::priority;}
	
	const qdate& expiry()   const;
	const qdate& lastdate() const {return m_enddate;}
protected:
	simpleir(const CCY& ccy, const IRHELP& ir, const qdate& settle,
			 const qdate& enddate, qm_real notional);
	CASHFLOW build_cashflow(const qdate& dte) const;
	void updatenotional(){this->clearcf(); this->notify_observers();}
	//json::object tojson() const;
	IRHELP	m_rhelp;
	qdate	m_settle;
	qdate	m_fixing;
	qdate	m_enddate;
};


template<>
class simpleir<swap_>: public Instrument<swap_>,  public otcir, public iswap  {
public:
	static QM_SMART_PTR(simpleir<swap_>)
	make(QM_SMART_PTR(InterestRate<swap_>) irt, const qdate& date);
	
	IRHELP	fixedleg()   const {return m_fixedleg;}
	IRHELP	floatleg()   const {return m_floatleg;}
	IRHELP  fixingfreq() const {return m_fixingfreq;}
	
	unsigned curvepriority() const {return InstrumentInfo<swap_>::priority;}
	
	const qdate& lastdate() const {return m_dates.terminationDate;}
protected:
	simpleir(const CCY& ccy, const IRHELP& fixedleg,
			 const IRHELP& floatleg, const IRHELP& fixfreq,
		     const datebasket& dates, qm_real notional);
	CASHFLOW build_cashflow(const qdate& dte) const;
	void updatenotional(){this->clearcf(); this->notify_observers();}
	void   	 buildlegs();
	IRHELP		m_fixedleg;
	IRHELP		m_floatleg;
	IRHELP		m_fixingfreq;
	datebasket  m_dates;
};


/*
template<instrumentype typ>
struct quoteInstrument<InterestRate<typ>, simpleir<typ> >  {
	typedef InterestRate<typ> 			ticker_type;
	typedef simpleir<typ>	  			inst_type;
	typedef QM_SMART_PTR(inst_type)		INST_TYPE;
	typedef QM_SMART_PTR(ticker_type)	TIKER_TYPE;
	static INST_TYPE make(TIKER_TYPE ticker, const qdate& date)  {
		inst_type::make(ticker,date);
	}
};
*/



QM_NAMESPACE_END2



#include	<qmlib/finance/instruments/impl/otcir_impl.hh>

    
#endif  //  __OTCIRO_QM_H__
//
