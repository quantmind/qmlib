


#ifndef   __TRADING_CENTRE_IMPL_QM_HH__
#define   __TRADING_CENTRE_IMPL_QM_HH__




QM_NAMESPACE



inline bool tc::isbizday(const qdate& date) const  {
  this->generatedates(date.year());
  return !date.isweekend() && m_all_holidays.find(holiday(date)) == m_all_holidays.end();
}



inline void tc::generatedates(qm_short year) const {
  if(year >= this->m_year_start && year <= this->m_year_end) return;
  //
  qm_short y1 = m_year_end   + 1;
  qm_short y2 = m_year_start - 1;
  if(year < this->m_year_start)
  {
    y1 = year;
    m_year_start = y1;
  }
  if(year > this->m_year_end)
  {
    y2 = year;
    m_year_end = y2;
  }
  //
  for(qm_short y=y1;y<=y2;y++)
  {
    for(tc::HolidayVector::const_iterator it = m_holidays.begin(); it != m_holidays.end(); ++it)
    {
      (*it)->add_date(y,m_all_holidays);
    }
  }
}






namespace {
    //
    //
    class westernTCs: public tc    {
    protected:
       westernTCs(const qm_string& code, const qm_string& name):tc(code,name){}
    };
    //
    //
    class London: public westernTCs
    {
    public:
    	London();
    };
    //
    //
    class NewYork: public westernTCs
    {
    public:
    	NewYork();
    };
    //
    //
    class Target: public westernTCs
    {
    public:
    	Target();
    };
    //
    class Sidney: public westernTCs
    {
    public:
    	Sidney();
    };
    //
    class Auckland: public westernTCs
    {
    public:
    	Auckland();
    };
    //
  class Zurich: public westernTCs
  {
  public:
    Zurich();
  };
  //
  class Tokyo: public westernTCs
  {
  public:
    Tokyo();
  };
  //
  class Toronto: public westernTCs
  {
  public:
    Toronto();
  };
  //
  class Oslo: public westernTCs
  {
  public:
    Oslo();
  };
  //
  class Stockholm: public westernTCs
  {
  public:
    Stockholm();
  };
  //
  class Istanbul: public westernTCs
  {
  public:
    Istanbul();
  };
  //
  class BuenosAires: public westernTCs
  {
  public:
    BuenosAires();
  };
  //
  class Moscow: public westernTCs
  {
  public:
    Moscow();
  };
  //
  class Johannesburg: public westernTCs
  {
  public:
    Johannesburg();
  };
  //
  class MexicoCity: public westernTCs
  {
  public:
     MexicoCity();
  };
  //
  class SaoPaulo: public westernTCs
  {
  public:
     SaoPaulo();
  };
    //
    class Reykjavik: public westernTCs
    {
    public:
	  Reykjavik();
    };
    //
    class Copenhagen: public westernTCs
    {
    public:
      Copenhagen();
    };
    
    
    
    
    inline void Add_NewYear_Christmas(tc::HolidayVector& hols)    {
      using namespace boost::gregorian;
      hols.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      hols.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    inline void Add_NewYear_Christmas_Boxing(tc::HolidayVector& hols)    {
      using namespace boost::gregorian;
      Add_NewYear_Christmas(hols);
      hols.push_back(HolidayGen(new holidaygen(new partial_date(26,Dec),"Boxing day")));
    }
    inline void Add_NewYear_Christmas_Observed(tc::HolidayVector& hols)    {
      using namespace boost::gregorian;
      Add_NewYear_Christmas(hols);
      hols.push_back(HolidayGen(new holidaygen(new partial_date(2, Jan),"Western New Year Observed",1)));
      hols.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day Observed",1)));
    }
    inline void Add_NewYear_Christmas_Boxing_Observed(tc::HolidayVector& hols)    {
      using namespace boost::gregorian;
      Add_NewYear_Christmas_Observed(hols);
      hols.push_back(HolidayGen(new holidaygen(new partial_date(26,Dec),"Boxing day")));
      hols.push_back(HolidayGen(new holidaygen(new partial_date(26,Dec),"Boxing day Observed",1)));
    }
    inline void Add_EasterMonday(tc::HolidayVector& hols)  {
      using namespace boost::gregorian;
      hols.push_back(HolidayGen(new holidaygen(new gregorian_roman_easter(1),"Easter Monday")));
    }
    inline void Add_GoodFriday(tc::HolidayVector& hols)    {
      using namespace boost::gregorian;
      hols.push_back(HolidayGen(new holidaygen(new gregorian_roman_easter(-2),"Good Friday")));
    }
    inline void Add_GoodFriday_EasterMonday(tc::HolidayVector& hols)    {
      using namespace boost::gregorian;
      Add_GoodFriday(hols);
      Add_EasterMonday(hols);
    }
    //
    //
    //
    //
    inline London::London():westernTCs("LON","London")  {
      using namespace boost::gregorian;
      typedef nth_day_of_the_week_in_month nth_dow;
      Add_NewYear_Christmas_Boxing_Observed(m_holidays);
      Add_GoodFriday_EasterMonday(m_holidays);
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::first,   Monday,   May),"May Day")));
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::fifth,   Monday,   May),"Spring Bank Holiday")));
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::fifth,   Monday,   Aug),"Summer Bank Holiday")));
    }
    //
    inline NewYork::NewYork():westernTCs("NY","NewYork")  {
      using namespace boost::gregorian;
      typedef nth_day_of_the_week_in_month nth_dow;
      Add_NewYear_Christmas_Observed(m_holidays);
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(4, Jul),"Independence Day")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(5, Jul),"Independence Day Observed",1)));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(11,Nov),"Veterans Day")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(12,Nov),"Veterans Day Observed",1)));
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::third,   Monday,   Jan),"MLK Day")));
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::second,  Tuesday,  Feb),"President day")));
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::fifth,   Monday,   May),"Memorial day")));
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::first,   Monday,   Sep),"Labor day")));
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::second,  Monday,   Oct),"Columbus day")));
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::fourth,  Thursday, Nov),"Thanksgiving")));
    }
    //
    inline Target::Target():westernTCs("TGT","Target")  {
      using namespace boost::gregorian;
      Add_NewYear_Christmas_Boxing(m_holidays);
      Add_EasterMonday(m_holidays);
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1,May), "Labor Day")));
    }
    //
    inline Sidney::Sidney():westernTCs("SID","Sidney")  {
      using namespace boost::gregorian;
      typedef nth_day_of_the_week_in_month nth_dow;
      Add_NewYear_Christmas_Boxing_Observed(m_holidays);
      Add_GoodFriday_EasterMonday(m_holidays);
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(26,Jan),"Australia day holiday")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(26,Jan),"Australia day holiday observed",1)));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Apr),"Anzac day")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Apr),"Anzac day observed",1)));
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::second,   Monday,   Jun),"Queen's birthday holiday")));
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::second,   Monday,   Mar),"Labour holiday")));
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::first,    Monday,   Aug),"Bank holiday")));
      m_holidays.push_back(HolidayGen(new holidaygen(new nth_dow(nth_dow::first,    Monday,   Oct),"Labour holiday (NSW)")));
    }
    //
    inline Auckland::Auckland():westernTCs("AUC","Auckland")  {
      using namespace boost::gregorian;
      //
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    //
    inline Tokyo::Tokyo():westernTCs("TOK","Tokyo")  {
      using namespace boost::gregorian;
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
    }
    //
    inline Toronto::Toronto():westernTCs("TOR","Toronto")  {
      using namespace boost::gregorian;
      Add_NewYear_Christmas_Boxing_Observed(m_holidays);
      Add_GoodFriday(m_holidays);
    }
    //
    inline Zurich::Zurich():westernTCs("ZUR","Zurich")   {
      using namespace boost::gregorian;
      //
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    //
    inline Oslo::Oslo():westernTCs("OSL","Oslo")  {
      using namespace boost::gregorian;
      //
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    //
    inline Stockholm::Stockholm():westernTCs("STO","Stockholm")  {
      using namespace boost::gregorian;
      //
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    //
    inline Copenhagen::Copenhagen():westernTCs("COP","Copenhagen")  {
      using namespace boost::gregorian;
      //
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    //
    inline Reykjavik::Reykjavik():westernTCs("REK","Reykjavik")  {
      using namespace boost::gregorian;
      //
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    //
    inline Johannesburg::Johannesburg():westernTCs("JOH","Johannesburg")  {
      using namespace boost::gregorian;
      //
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    //
    inline MexicoCity::MexicoCity():westernTCs("MC","MexicoCity")  {
      using namespace boost::gregorian;
      //
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    //
    inline SaoPaulo::SaoPaulo():westernTCs("SP","SaoPaulo")  {
      using namespace boost::gregorian;
      //
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    //
    inline BuenosAires::BuenosAires():westernTCs("BA","BuenosAires")  {
      using namespace boost::gregorian;
      //
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    //
    inline Istanbul::Istanbul():westernTCs("IST","Istanbul")  {
      using namespace boost::gregorian;
      //
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    //
    inline Moscow::Moscow():westernTCs("MOS","Moscow") {
      using namespace boost::gregorian;
      //
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(1, Jan),"Western New Year")));
      m_holidays.push_back(HolidayGen(new holidaygen(new partial_date(25,Dec),"Christmas Day")));
    }
    
    
    
}

QM_NAMESPACE_END



#endif	//	__TRADING_CENTRE_IMPL_QM_HH__

