

#ifndef   __OTC_IR_IMPL_QM_HPP__
#define   __OTC_IR_IMPL_QM_HPP__


QM_NAMESPACE2(finance)

/*
inline bool otcir::base_activate(const qdate& date, BizDayConv bzcmat)    {
	if(!this->istemplate()) return true;
	qdate dte     = m_adj.hols.parseinterval(date,m_settlement.tenure(),unadjusted);
	m_settlement  = m_adj.hols.nextbizday(dte,m_delay);
    m_maturity	  = m_adj.hols.parseinterval(m_settlement.date(),m_tenure,bzcmat);
    return false;
}
*/

template<instrumentype typ>
inline simpleir<typ>::simpleir(const CCY& ccy, const IRHELP& ir,
					  		   const qdate& settle, const qdate& enddate,
							   qm_real notional):
					otcir(ccy,notional),m_rhelp(ir),m_settle(settle),m_enddate(enddate)  {
	QM_REQUIRE(ir,"Interest rate helper not defined");
}

template<instrumentype typ>
inline CASHFLOW simpleir<typ>::build_cashflow(const qdate& dte) const  {
	CASHFLOW cfs;
	qm_real notio = this->notional();
    qm_real dcf = m_rhelp->daycount()->dcf(m_settle,m_enddate);
    cfs.addkeyval(m_settle, 	CASHEVENT(new fixcash(-notio,false)));
    cfs.addkeyval(m_enddate,	CASHEVENT(new fixcash(notio,false)));
    cfs.addkeyval(m_enddate,	CASHEVENT(new couponevent(m_rate,dcf,notio)));
    return cfs;
}

template<instrumentype typ>
inline json simpleir<typ>::tojson() const  {
	json js = Instrument<typ>::tojson();
	filljson<ccyplug>(*this,js);
	return js;
}


template<>
const qdate& simpleir<fra_>::expiry() const {return m_settle;}
template<>
const qdate& simpleir<deposit_>::expiry() const {return m_enddate;}

/*
template<instrumentype typ>
inline json::object simpleir<typ>::tojson() const  {
	json::object obj;
	
	ToJson<otcir>::fill(obj);
	
}
*/



inline simpleir<swap_>::simpleir(const CCY& ccy, const IRHELP& fixedleg,
								 const IRHELP& floatleg,  const IRHELP& fixfreq,
								 const datebasket& dates, qm_real notional):
					 otcir(ccy,notional),m_fixedleg(fixedleg),m_floatleg(floatleg),
					 m_fixingfreq(fixfreq),m_dates(dates)  {
}

/*
template<>
inline CASHFLOW simpleir<swap_>::build_cashflow(const qdate& dte) const  {
	return this->reduced_cashflow(dte);
}
*/


inline void simpleir<swap_>::buildlegs()  {
	this->push_back(SWAPSTREAM(
			new FixLegInterestRateSwap(m_dates, m_fixedleg, m_notional, m_rate)));
	this->push_back(SWAPSTREAM(
			new FloatingLegInterestRateSwap(m_dates, m_floatleg, m_fixingfreq,-m_notional)));
}


template<instrumentype typ>
inline OTCIR simpleir<typ>::create(const INTERESTRATE& irt, const qdate& date)  {
	QM_REQUIRE(irt,"Interest rate tiker is null");
	IRHELP irh  = irt->help();
	ADJ      a  = irh->adj();
	qdate set   = a->adjtenure(date,irt->start().tostring());
	qdate mat   = a->hols.parseinterval(set,irh->tenure(),a->bzc);
	return OTCIR(new simpleir<typ>(irt->currency(),irh,set,mat,1));
}


inline QM_SMART_PTR(simpleir<swap_>)
simpleir<swap_>::make(QM_SMART_PTR(InterestRate<swap_>) irt, const qdate& date)  {
	QM_SMART_PTR(simpleir<swap_>) sw;
	return sw;
}



inline finins otcir::make(const INTERESTRATE& ir, const qdate& dte) {
	QM_REQUIRE(ir,"Interest rate ticker is null");
	OTCIR inst;
	switch(ir->type())  {
		case fra_: 	   inst = simpleir<fra_>::create(ir,dte); 	 break;
		case deposit_: inst = simpleir<deposit_>::create(ir,dte); break;
		default: QM_FAIL("Could not create otc interest rate derivative");
	}
	return finins(inst);
}



/*

inline void fra::activate(const qdate& date)  {
	if(base_activate(date,m_adj.bzc)) return;
	m_fixingdate = m_fix.prevbizday(m_settlement.date(),m_delay);
}

inline qdate vanillaswap::get_fixing(const qdate& dte) const  {
	return m_adj_resets->hols.prevbizday(dte,m_delay);
}
    
inline vanillaswap::vanillaswap(const CCY& ccy, const dateperiod& start, const dateperiod& end,
							    const dateAdjustment& adj, DC dc, qm_uns_char delay, INDEX idx):
							    	otcir(ccy,start,end,adj,dc,delay,idx,true),
							    		activation<vanillaswap>(this) {
	m_floatDC   = this->currency()->floatDC();
    m_fixedfreq = parsefrequency(this->currency()->fixedCoupFred(),m_maturity.tenure());
    m_floatfreq = parsefrequency(this->currency()->floatCoupFred(),m_maturity.tenure());
    m_resetfreq = m_floatfreq;
    //
    int      fd  = this->currency()->cashDelay();
    m_index      = this->currency()->rateIndex();
    QM_REQUIRE(m_index,"vanillaswap: fixing index not available");
    
    m_adj_resets = ADJ(new dateAdjustment(m_index->holidays(),modfoll,-fd));
    if(!this->istemplate())  {
    	QM_FAIL("vanillaswap::vanillaswap. Not implemented yet");
    }
}
    
    

// Activate a standard vanilla swap
inline void vanillaswap::activate(const qdate& date)  {
	if(base_activate(date,unadjusted)) return;
    this->buildlegs();
}

inline void vanillaswap::buildlegs()  {
	if(this->istemplate()) return;
    //
    ADJ adj(new dateAdjustment(m_adj));
    datebasket dates(m_settlement.date(),m_maturity.date());
    
    this->push_back(SWAPSTREAM(new FixLegInterestRateSwap(dates,m_fixedfreq, adj, m_dc, m_notional, m_mktval)));
    
    this->push_back(SWAPSTREAM(new FloatingLegInterestRateSwap(m_index,dates,m_floatfreq,m_resetfreq,adj,m_adj_resets,
                                                               m_floatDC,-m_notional)));
}



inline CASHFLOW vanillaswap::build_cashflow(const qdate& dte) const  {
	QM_REQUIRE(!this->istemplate(),"swap not activated. Cannot obtain a cash flow of contract template");
	return this->reduced_cashflow(dte);
}


    
    
inline OTCIR otcir::create2(const qm_string& cu, const qm_string& tenure, compositeRateSubfix sub)  {
	CCY cur = ccy::get(cu);
    QM_REQUIRE(cur,"Currency not specified");
    INDEX idx = cur->rateIndex();
	dateAdjustment adj(cur->defaultTC(),cur->bizConv());
	return otcir::create3(cur,tenure,sub,adj,DC(),cur->swapDelay(),idx);
}



inline OTCIR otcir::create3(const CCY& cur, const qm_string& tenure, compositeRateSubfix sub,
							const dateAdjustment& adj, DC dc, qm_uns_char delay, INDEX idx)  {
	QM_REQUIRE(cur,"Currency not specified");
	qm_strings tens = qmstring::split(tenure,"+");
    period ps(tens[0]);
    period p(ps);
    QM_REQUIRE(tens.size() <= 2,"Unrecognized otc interest rate instrument: "+tenure);
    if(tens.size() == 2) p = tens[1];
    else ps = "";
    //
    if(sub == SYC)  {
    	// A swap
        if(p.years() >= 1)  {
        	qm_string y;
        	QM_REQUIRE(p.totaldays() == 0,"Could not construct a swap from tenure "+tenure);
        	if(p.months() == 0) y = boost::lexical_cast<qm_string>(p.years());
        	else y = p.tostring();
        	DC dcs = dc;
        	if(!dcs) dcs = cur->fixedDC();
        	return OTCIR(new vanillaswap(cur,ps.tostring(),p.tostring(),adj,dcs,delay,idx));
        }
        //
        // a fra or a deposit
        else  {
          QM_REQUIRE(!p.isempty(),"Could not construct a interest rate instrument from "+tenure);
          DC dcs = dc;
          if(!dcs) dcs = cur->floatDC();
          if(ps.isempty())  {
            return OTCIR(new depo(cur,"",p.tostring(),adj,dcs,delay,idx));
          }
          else  {
            return OTCIR(new fra(cur,ps.tostring(),p.tostring(),adj,dcs,delay,idx));
          }
        }
    }
    return OTCIR();
}

*/

QM_NAMESPACE_END2



#endif	//	__OTC_IR_IMPL_QM_HPP__



