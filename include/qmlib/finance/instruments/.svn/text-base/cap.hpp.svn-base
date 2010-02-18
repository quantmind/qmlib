




class capfloorlet: public option<fra,option<1u,>  {
public:
	capfloorlet(FRA f, qm_real strike);
	qm_string name()     const;
	//
protected:
	capfloorlet(qm_real strike = 0.0):vanilla_option<fra>(strike),idiscount_curve_instrument(this){}
	void activate_after_underlying(const qdate& date) {m_maturity = m_underlying->fixingdate();}
};