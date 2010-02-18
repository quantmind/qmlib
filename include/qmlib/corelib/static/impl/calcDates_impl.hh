



inline qm_real streamDateItem::dcf(const DC& dc, unsigned i) const    {
	QM_REQUIRE(i<m_relative.size() && dc,"streamDateItem: No dates or no daycounter available");
	return dc->dcf(m_relative[i]->adjusted(), this->adjusted());
}



inline STREAMDATE periodDates::add(const qdate& dte, const ADJ& adj, const qm_string& code)   {
	STREAMDATE A(new streamDateItem(dte,adj,code));
    m_stream.push_back(A);
    return A;
}


template <class L>
L periodDates::datelist() const   {
	L lis;
    for(periodDates::const_iterator it = this->begin();it!=this->end();++it)
    	lis.append((*it)->adjusted());
    return lis;
}

    
inline void calcDates::generate()   {
	QM_REQUIRE(m_dates.firstRegDate >= m_dates.effectiveDate,"First Regular Date must be after effective date");

    STREAMDATE sd;
    // Generate the first dates
    if(m_dates.isfirstregular())
    	sd = this->add(m_dates.effectiveDate,m_adj,"EffectiveDate");
    else  {
        QM_REQUIRE(m_dates.firstPeriodStart < m_dates.firstRegDate,"First Period Start after first Regular Date");
        //sd = this->add(m_dates.effectiveDate,m_adj,"EffectiveDate",false);
        sd = this->add(m_dates.firstPeriodStart,m_adj,"FirstPeriodStart");
        sd = this->add(m_dates.firstRegDate,m_adj,"FirstRegularDate");
    }
    //
    // Generate Regular Dates
    qdate dte = sd->date;
    while(dte < m_dates.lastRegDate)   {
        dte = m_adj->hols.parseinterval(dte,m_freq);
        sd  = this->add(dte,m_adj,"RegularDate");
    }
    QM_REQUIRE(dte == m_dates.lastRegDate,"calcDates: regular date period is invalid");
    //
    // Generate the terminal dates
    if(m_dates.islastregular())
        sd->set_code("TerminationDate");
    else      {
        QM_REQUIRE(m_dates.lastRegDate < m_dates.terminationDate,"Last Regular Date after termination date");
        sd->set_code("LastRegularDate");
        sd = this->add(m_dates.terminationDate,m_adj,"TerminationDate");
    }
}


inline void relativeDates::generate_with_resets(const period& freq_reset, const ADJ& adj_reset) {
	unsigned MR = freq_reset.totalmonths();
	QM_REQUIRE(m_rel->monthfreq() == MR,"Resets frequency must equal calc date frequency")
	QM_REQUIRE(this->monthfreq() >= MR,"Dates frequency must be greater or equal resets dates");
	unsigned step = MR / this->monthfreq();
	QM_REQUIRE(step * this->monthfreq() == MR, "Frequency does not much resets dates");
	
    std::vector<STREAMDATE> vresets;
    const_iterator it = m_rel->begin();
    STREAMDATE pd(*it);
	++it;
	unsigned n = 0;
	
	// Resets are from the start
    if(m_relToStart)
    	for(;it!=m_rel->end();++it)  {
    		n++;
    		vresets.push_back(STREAMDATE(new streamDateItem(pd->date,adj_reset,(*it))));
    		if(n == step)  {
    			m_stream.push_back(STREAMDATE(new streamDateItem((*it)->date,m_adj,vresets)));
    			vresets.clear();
    			n = 0;
    		}
    		pd = (*it);
    	}
    
    // Resets are in arreas
    else
    	QM_FAIL("In arreas resets not available yet");
}


/// Relative dates without resets
inline void relativeDates::generate()  {
	// Check the frequency
    QM_REQUIRE(this->frequency() == m_rel->frequency(),"Dates frequency must be the same as relative dates");
    if(m_rel->size() <= 1) return;
    
    const_iterator it = m_rel->begin();
    STREAMDATE pd(*it);
	++it;
	
    if(m_relToStart)
    	for(;it!=m_rel->end();++it)  {
    		m_stream.push_back(STREAMDATE(new streamDateItem(pd->date,m_adj,(*it))));
    		pd = (*it);
    	}
    else
    	for(;it!=m_rel->end();++it)  {
    		m_stream.push_back(STREAMDATE(new streamDateItem((*it)->date,m_adj,pd)));
    		pd = (*it);
    	}
}



