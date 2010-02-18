


QM_NAMESPACE2(finance)


inline CASHFLOW iswap::reduced_cashflow(const qdate& dte) const  {
	if(!this->size()) return CASHFLOW();
	const_iterator it = this->begin();
	CASHFLOW cf = (*it)->reduced_cashflow(dte);
	++it;
	for(;it!=this->end();++it)
		cf.addvector((*it)->reduced_cashflow(dte));
	return cf;
}



// Resets dates are not used
inline CASHFLOW vanilla_fixed_leg_stream_ammount::full_cashflow(const CALCDATES& paym, const qdate& date) const    {
	QM_REQUIRE(paym,"Payment dates not available");
    CASHFLOW cf;
    qm_real tau;
    qdate adj;
    for(periodDates::const_iterator it = paym->begin();it!=paym->end();++it)   {
        adj = (*it)->adjusted();
        if(adj <= date) continue;
        tau = (*it)->dcf(m_dc);
        cf.addkeyval(adj,CASHEVENT(new couponevent(m_coup,tau,m_notional)));
    }
    return cf;
}


inline CASHFLOW vanilla_float_leg_stream_ammount::reduced_cashflow(const CALCDATES& paym, const qdate& date) const  {
	QM_REQUIRE(paym,"Payment or Reset dates not available");
    CASHFLOW cf;
    unsigned N = paym->size(); 
    if(!N) return cf;
    
    STREAMDATE sd;
    qdate      adj;
    bool  finito = true;
    for(periodDates::const_iterator it = paym->begin();it!=paym->end();++it)   {
    	if((*it)->adjusted() <= date) continue;
    	unsigned M = (*it)->nrelative();
    	QM_REQUIRE(M,"No relative resets available");
    	sd   = (*it)->relative(0);
    	adj  = sd->adjusted();
    	/// reset has not occur
    	if(adj >= date)  {
    		cf.addkeyval((*it)->adjustdate(sd->date), CASHEVENT(new fixcash(m_notional,true)));
    		finito =false;
    		break;
    	}
    	QM_FAIL("not available yet");
    }
    
    // Add the last dummy cashflow
    if(!finito)  {
    	sd = (*paym)[N-1];
    	cf.addkeyval(sd->adjusted(), CASHEVENT(new fixcash(-m_notional,true)));
    }
    return cf;
}

inline CASHFLOW vanilla_float_leg_stream_ammount::full_cashflow(const CALCDATES& paym,  const qdate& date) const    {
	QM_REQUIRE(paym,"Payment or Reset dates not available");
	QM_FAIL("full cash flow not available");
}


    
inline FixLegInterestRateSwap::FixLegInterestRateSwap(const datebasket&       dates,
        											  const IRHELP&           irh,
        											  qm_real                 notional,
        											  const IVALUE&           rate):swapstream("FixLegInterestRateSwap",irh)  {
	m_calc    = calcDates::create("FixCalcPeriodDates",dates,m_irh->frequency(),m_irh->adj());
    m_payment = CALCDATES(new relativeDates("FixPaymentDates",m_irh->frequency(),m_irh->adj(),false,m_calc));
    m_amount  = STREAMAMOUNT(new vanilla_fixed_leg_stream_ammount(m_irh->daycount(),notional,rate));
}


inline FloatingLegInterestRateSwap::FloatingLegInterestRateSwap(const datebasket&       dates,
		  														const IRHELP&           irh,
		  														const IRHELP&           irfixing,
		  														qm_real                 notional):swapstream("FloatLegInterestRateSwap",irh,irfixing) {
	m_calc    = calcDates::create("FloatCalcPeriodDates",dates,m_irfixing->frequency(),m_irfixing->adj());
    m_payment = CALCDATES(new relativeDates("FloatPaymentDates",m_irh->frequency(),m_irh->adj(),true,m_calc));
    m_amount  = STREAMAMOUNT(new vanilla_float_leg_stream_ammount(m_irh->daycount(),notional));
}


QM_NAMESPACE_END2

