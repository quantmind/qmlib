

//
#ifndef   __INSTRUMENT_IMPL_QM_HPP__
#define   __INSTRUMENT_IMPL_QM_HPP__


QM_NAMESPACE2(finance)


/*
inline instrument::instrument(const CCY& cur):m_ccy(cur) {
	/// Set adateAdjustment to default currency values
	if(m_ccy)  {
		m_adj.hols  = TradingCentres(m_ccy->defaultTC());
		m_adj.delay = m_ccy->cashDelay();
	}
}

inline void instrument::activateme(const qdate& date) {
	//qdate dte     = m_adj.hols.parseinterval(date,m_settlement.tenure(),unadjusted);
	//m_settlement  = m_adj.hols.nextbizday(dte,this->delay());
	//m_maturity	  = m_adj.hols.parseinterval(m_settlement.date(),m_maturity.tenure(),this->bzdayConv());
}
*/


/*
inline instrument_base::instrument_base(const dateperiod& mat):m_maturity(mat) {
	check();
}
inline instrument_base::instrument_base(const dateperiod& start, const dateperiod& mat):
	m_settlement(start),m_maturity(mat),m_enddate(mat) {
	check();
}
inline instrument_base::instrument_base(const instrument_base& ib):
	m_settlement(ib.m_settlement),m_maturity(ib.m_maturity),m_enddate(ib.m_enddate){}

inline void instrument_base::check()  {
	if(this->istemplate())
		QM_REQUIRE(!this->maturity().isdate(),
				"instrument: bad date specification, It seems to be a template but the end date is a date");
}
*/

/*
template<class U>
inline void derivative<U>::activate(const qdate& date) {
	if(m_underlying->istemplate()) {
		m_underlying->activate(date);
		this->activate_after_underlying(date,true);
	}
	else
		this->activate_after_underlying(date,false);
}


// Basic activation. This is used only when
// The underlying is not a template itself.
template<class U>
inline void derivative<U>::activate_without_underlying(const qdate& date) {
	CCY cur;
	try  {
		cur = this->currency();
	}
	catch()  {
		// No currency, this is a dummy instrument. Just get the dates without fuss
		
	}
}
*/

/*
inline simpleForward::simpleForward(const dateperiod& mat)  {
	m_maturity   = mat;
	// The settlement date and expiry are irrelevant, so I leave them blank
}
inline void simpleForward::activate(const qdate& date)  {
	if(this->istemplate())  {
		TradingCentres hols;
		m_maturity   = hols.parseinterval(date,m_maturity.tostring(),unadjusted);
		m_settlement = m_maturity;
		m_enddate    = m_maturity;
	}
}
*/




QM_NAMESPACE_END2

    
#endif  //  __INSTRUMENT_IMPL_QM_HPP__
//
