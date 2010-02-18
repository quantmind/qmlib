

#ifndef   __TRADING_CENTRES_IMPL_QM_HH__
#define   __TRADING_CENTRES_IMPL_QM_HH__




QM_NAMESPACE

    

inline void TradingCentres::push_back(const TC& tc)  {
	if(!tc) return;
    for(iterator it = this->begin();it!=this->end();++it)
    	if(*it == tc) return;
    m_tcs->push_back(tc);
}

inline void TradingCentres::push_back(const TradingCentres& tc)  {
	for(const_iterator it = tc.begin();it!=tc.end();++it)
		this->push_back(*it);
}

inline void TradingCentres::push_back(const qm_string& codes)  {
	qm_strings co = qmstring::split(codes,",");
	for(qm_strings::iterator it=co.begin();it!=co.end();++it)  {
		TC tc = tc::get(*it);
		this->push_back(tc);
	}
}

inline qm_long TradingCentre::numbizdays(const qdate& start, const qdate& end) const   {
	using namespace boost::gregorian;
    if(end < start) return 0;
    day_iterator itr(start.boost_date(),1);
    boost::gregorian::date bend = end.boost_date();
    qm_long b = 0;
    for(; itr <= bend; ++itr)
    	if(this->isbizday(qdate(*itr))) b++;
    return b;
}


    
    inline qdate TradingCentre::nextbizday(const qdate& date, qm_long days) const  {
      using namespace boost::gregorian;
      if(days < 0) return this->prevbizday(date,-days);
      day_iterator itr(date.boost_date(),1);
      qm_long d = 0;
      while(d <= days)
      {
        if(this->isbizday(*itr)) d++;
        ++itr;
      }
      return qdate(*(--itr));
    }


    
    inline qdate TradingCentre::prevbizday(const qdate& date, qm_long days) const    {
      using namespace boost::gregorian;
      if(days < 0) return this->nextbizday(date,-days);
      day_iterator itr(date.boost_date(),1);
      qm_long d = 0;
      while(d <= days)
      {
        if(this->isbizday(*itr)) d++;
        --itr;
      }
      return qdate(*(++itr));
    }
    //
    //
    inline qm_string TradingCentres::code() const
    {
      if(this->size() == 0) return "";
      const_iterator it = this->begin();
      qm_string co = (*it)->code();
      ++it;
      for(;it!=this->end();++it)
        co += "," + (*it)->code();
      return co;
    }

    
inline bool TradingCentres::isbizday(const qdate& date) const    {
	if(!this->size()) return !date.isweekend();
	for(const_iterator it=this->begin();it!=this->end();++it)
		if(!(*it)->isbizday(date)) return false;
    return true;
}


inline qdate
TradingCentres::adjust(const qdate& date, BizDayConv bzc) const  {
	if(bzc == unadjusted || this->isbizday(date)) return date;
    qdate dte = date;
    
    switch(bzc)  {
    	case foll: case modfoll: dte = this->nextbizday(date,0); break;
        case prec: case modprec: dte = this->prevbizday(date,0); break;
        case unadjusted: break;
    }
    
    if(dte.month() != date.month())  {
    	if(bzc == modfoll)      dte = this->prevbizday(date,0);
        else if(bzc == modprec) dte = this->nextbizday(date,0);
    }
    return dte;
}


inline qdate
TradingCentres::parseinterval(const qdate& valdate, const period& pe, BizDayConv bzc) const  {
	qdate dte = valdate;
    if(pe.totaldays() > 0)   dte.add_days(pe.totaldays());
    if(pe.totalmonths() > 0) dte.add_months(pe.totalmonths());
    return this->adjust(dte,bzc);
}


    
    inline period TradingCentres::datestointerval(const qdate& start, const qdate& end, BizDayConv bzc) const  {
      QM_REQUIRE(end >= start,"TradingCentres: end date smaller than start date");
      qm_long  d = qdate::daydiff(end,start);
      qm_real dd = (double)d;
      qdate test;
      //
      if(d <= 3)  {
        return period(0,d);
      }
      if(d < 23)  {
        int w = int(ceil(dd/7.0));
        while(w > 0)  {
          period pt(0,7*w);
          test = this->parseinterval(start,pt,bzc);
          if(test == end) return pt;
          else if(test < end) break;
          else QM_FAIL("Critaical problem in TradingCentres::datestointerval algorithm");
          w--;
        }
        return period(0,d);
      }
      else  {
        int m = int(ceil(dd/30.0)) + 1;
        while(m > 0)
        {
          period pt(m,0);
          test = this->parseinterval(start,pt,bzc);
          if(test == end) return pt;
          else if(test < end) break;
          else QM_FAIL("Critaical problem in TradingCentres::datestointerval algorithm");
          m--;
        }
        if(m == 0) return period(0,d);
        else
        {
          period pt(m,0);
          return pt + this->datestointerval(test,end,bzc);
        }
      }
    }
    



QM_NAMESPACE_END



#endif	//	__TRADING_CENTRES_IMPL_QM_HH__


