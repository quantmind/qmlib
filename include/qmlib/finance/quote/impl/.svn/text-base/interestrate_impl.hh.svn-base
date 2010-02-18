


QM_NAMESPACE2(finance)


inline INTERESTRATE ratefactory::create(const qm_string& cu, const qm_string& tenure)  {
	return ratefactory::create2(cu,tenure,false);
}

inline INTERESTRATE ratefactory::create2(const qm_string& cu, const qm_string& tenure, bool isois)  {
	CCY cur = ccy::get(cu);
    QM_REQUIRE(cur,"Currency not specified");
    INDEX idx = cur->rateIndex();
	dateAdjustment adj(cur->defaultTC(),cur->bizConv());
	
	// Forward swap convention
	qm_strings tens = qmstring::split(tenure,"+");
	if(tens.size() == 2)
		return ratefactory::create3(cur,period(tens[0]),period(tens[1]),isois);
	
	// FRA convention
	// usually 3x9 meaning a 3m fra on 6m libor
	tens = qmstring::split(tenure,"x");
	if(tens.size() == 2)  {
		period st(tens[0],"M");
		period en(tens[1],"M");
		return ratefactory::create3(cur,st,en-st,isois);
	}
	
	// Not forward starting
	return ratefactory::create3(cur,period(),period(tenure),isois);
}

inline INTERESTRATE ratefactory::create3(const CCY& cur,
										 const period& start,
										 const period& tenure,
										 bool isois)  {
	QM_REQUIRE(cur,"Currency not specified");
	IRHELP ir;
    if(!isois)  {
    	// A swap
        if(tenure.years() >= 1)  {
        	ir = irhelp::fixedrate(cur->code(),tenure.tostring());
        	return INTERESTRATE(new InterestRate<swap_>(cur,ir,start));
        }
        //
        // a fra or a deposit
        else  {
          QM_REQUIRE(!tenure.isempty(),"Could not construct a interest rate instrument from "+tenure.tostring());
          ir = irhelp::floatrate(cur->code(),tenure.tostring());
          if(start.isempty()) return INTERESTRATE(new InterestRate<deposit_>(cur,ir,start));
          else return INTERESTRATE(new InterestRate<fra_>(cur,ir,start));
        }
    }
    else  {
    	if(tenure.years() >= 1) ir = irhelp::fixedrate(cur->code(),tenure.tostring());
    	else ir = irhelp::floatrate(cur->code(),tenure.tostring());
    	return INTERESTRATE(new InterestRate<ois_>(cur,ir,start));
    }
}

inline interestrate::interestrate(const CCY& cur, const IRHELP& ir, const period& start):
	m_ccy(cur),m_irh(ir),m_start(start) {}


template<instrumentype typ>
inline InterestRate<typ>::InterestRate(const CCY& cur, const IRHELP& ir, const period& start):
		                               interestrate(cur,ir,start){
	qm_string st = "";
	if(!m_start.isempty())  {
		st += m_start.tostring();
		if(this->type() == fra_ || this->type() == ois_) st += 'x';
		else st += '+';
	}
	st += m_irh->tenure().tostring();
	m_code = st;
}


template<instrumentype typ>
inline qm_string InterestRate<typ>::code() const {
	return m_ccy->code() + " " + this->Short() + " " + InstrumentInfo<Type>::name();
}

template<instrumentype typ>
inline qm_string InterestRate<typ>::name() const {
	qm_string st = m_ccy->code() + " " + InstrumentInfo<typ>::name();
	if(!m_start.isempty())
		st += " settle: " + m_start.tostring() + ",";
	st += m_irh->code();
	return st;
}


QM_NAMESPACE_END2


