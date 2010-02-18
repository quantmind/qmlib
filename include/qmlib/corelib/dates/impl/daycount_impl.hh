

QM_NAMESPACE

	namespace	{
    
    class Act360: public daycounter  {
    public:
    	Act360():daycounter("Act360","Actual 360"){}
    };

    class Act365: public daycounter  {
    public:
    	Act365():daycounter("Act365","Actual 365"){}
      	qm_real dcf(const qdate& start, const qdate& end) const {return this->daycount(start,end)/365.0;}
    };
    
    class ActAct: public daycounter  {
    public:
      	ActAct():daycounter("ActAct","Actual Actual"){}
      	qm_real dcf(const qdate& start, const qdate& end) const;
    };
    //
    //
    class thirty360: public daycounter  {
    public:
    	thirty360():daycounter("30360","30 360"){}
    	qm_long daycount(const qdate& start, const qdate& end) const;
    };
    //
    //
    /*
    class thirty360E: public DayCounts
    {
    public:
      thirty360E():DayCounts(_30_360E,s_dcnames[_30_360E],"30/360 EuroBond Basis (ISMA)"){}
      qm_long daycount(qm_date start, qm_date end) const;
    };
    //
    //
    class thirty360Ep: public DayCounts
    {
    public:
      thirty360Ep():DayCounts(_30_360Ep,s_dcnames[_30_360Ep],"30/360 (EuroBond Basis)"){}
      qm_long daycount(qm_date start, qm_date end) const;
    };
    //
    //
    class thirty360I: public DayCounts
    {
    public:
      thirty360I():DayCounts(_30_360I,s_dcnames[_30_360I],"30/360 (Italian Basis)"){}
      qm_long daycount(qm_date start, qm_date end) const;
    };
    */
    //
    //
    //
    //
    //
    //
    //
    inline qm_real ActAct::dcf(const qdate& start, const qdate& end) const  {
      return ActActYears(end) - ActActYears(start);
    }
    //
    //
    inline qm_long thirty360::daycount(const qdate& start, const qdate& end) const  {
      qm_uns_int d1 = start.day();
      qm_uns_int d2 = end.day();
      if (d1 == 31) d1 = 30;
      if (d1 == 30 && d2 == 31) d2 = 30;
      return counting30360(d1,d2,start.month(),end.month(),start.year(),end.year());
    }
    //
    //
    /*
    inline qm_long thirty360E::daycount(qm_date start, qm_date end) const
    {
      qm_short d1 = start.day();
      qm_short d2 = end.day();
      if (d1 == 31) d1 = 30;
      if (d2 == 31) d2 = 30;
      return counting30360(d1,d2,start.month(),end.month(),start.year(),end.year());
    }
    //
    //
    inline qm_long thirty360Ep::daycount(qm_date start, qm_date end) const
    {
      qm_short d1 = start.day();
      qm_short d2 = end.day();
      if (d1 == 31) d1 = 30;
      return counting30360(d1,d2,start.month(),end.month(),start.year(),end.year());
    }
    //
    //
    inline qm_long thirty360I::daycount(qm_date start, qm_date end) const
    {
      qm_short d1 = start.day();
      qm_short d2 = end.day();
      if(d1 == 31) d1 = 30;
      if(end == end.end_of_month()) d2 = 30;
      d2++;
      return counting30360(d1,d2,start.month(),end.month(),start.year(),end.year());
    }
    */
    //
    //
	inline daycounters generate_day_counters()  {
		daycounters dcs("Day counter inline database");
		DC 	dc;
		dc = DC(new Act360());
		dcs.add(dc->code(),dc);
		dc = DC(new Act365());
		dcs.add(dc->code(),dc);
		dc = DC(new ActAct());
		dcs.add(dc->code(),dc);
		dc = DC(new thirty360());
		dcs.add(dc->code(),dc);
		return dcs;
	}
	
	/// \brief Day Count name vector
	static const daycounters c_daycounters = generate_day_counters();

	}


	inline DC daycounter::get(const qm_string& cod)  {
		return c_daycounters.get(cod);
	}
	
	template<class L>
	inline L daycounter::keys()  {
		return c_daycounters.keys<L>();
	}

	QM_NAMESPACE_END

