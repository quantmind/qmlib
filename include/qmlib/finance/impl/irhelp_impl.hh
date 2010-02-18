


QM_NAMESPACE2(finance)



inline IRHELP irhelp::fixedrate(const qm_string& cu, const qm_string& tenure) {
	CCY cur = ccy::get(cu);
	QM_REQUIRE(cur,"Currency not specified");
	INDEX idx;
	DC dcs = cur->fixedDC();
	short de = cur->swapDelay();
	ADJ adj(new dateAdjustment(cur->defaultTC(),cur->bizConv(),de));
	period fre(parsefrequency(cur->fixedCoupFred(),tenure));
	period te(tenure);
	if(fre > te) fre = te;
	return IRHELP(new irhelp(te,adj,dcs,fre,idx));
}

inline IRHELP irhelp::floatrate(const qm_string& cu, const qm_string& tenure) {
	CCY cur = ccy::get(cu);
	QM_REQUIRE(cur,"Currency not specified");
	
	INDEX idx = cur->rateIndex();
	QM_REQUIRE(idx,"Floating rate index not available");
	
	DC dcs   = cur->floatDC();
	short de = cur->cashDelay();
	ADJ adj(new dateAdjustment(idx->holidays(),cur->bizConv(),de));
	
	period te(tenure);
	period fre;
	if(te.years() <= 0)
		fre = te;
	else
		fre = parsefrequency(cur->floatCoupFred(),tenure);
	if(fre > te) fre = te;
	
	return IRHELP(new irhelp(te,adj,dcs,fre,idx));
}

inline IRHELP irhelp::general(const qm_string& tenure,
							  DC dc,
		 			   		  const qm_string& freq)  {
	period fre(freq);
	period te(tenure);
	if(fre > te) fre = te;
	ADJ adj(new dateAdjustment());
	return IRHELP(new irhelp(te,adj,dc,fre,INDEX()));
}


inline irhelp::irhelp(const period& tenure,
					  const ADJ& adj, DC dc,
					  const period& freq, INDEX idx):
						  m_tenure(tenure),m_adj(adj),m_dc(dc),m_freq(freq),m_idx(idx){}


inline qm_string	irhelp::code()		  const  {
	return " tenure: " + m_tenure.tostring() + ", frequency: " + m_freq.tofrequency() +
		   ", daycount: " + m_dc->code();
}



QM_NAMESPACE_END2


