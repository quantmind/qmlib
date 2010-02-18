
#ifndef	__SIMPLE_DISCOUNT_CURVES_HPP__
#define	__SIMPLE_DISCOUNT_CURVES_HPP__



#include	<qmlib/finance/rates/base_rates.hpp>


QM_NAMESPACE2(finance)


/** \brief A scalar interest rate
 * \ingroup rates
 * 
 * A simple interest rate defined by a value and a frequency
 */
class interestRate : public basedes  {
public:
	interestRate(qm_real rate = 0.05, int monthsfreq = 0):m_rate(rate),m_months(monthsfreq),m_mrate(rate) {
		if(m_months > 0)
			m_mrate = 12.0*std::log(1.0 + m_rate*m_months/12.0)/m_months;
		else if(m_months < 0)
			QM_FAIL("daily frequency not implemented yet");
	}
	qm_real		ccrate()   		const {return m_mrate;}
	qm_string tostring()   		const {return "InterestRate "+this->frequency()+" "+nice_percent(m_rate);}
	qm_real		rate()	   		const {return m_rate;}
	qm_string	frequency()	    const {return frequency_to_string(m_months);}
protected:
	qm_real		m_rate;
	int     	m_months;
	qm_real		m_mrate;
};

	
class simple_compound_dc : public discountcurve {
public:
	typedef interestRate   			irtype;
	typedef QM_SMART_PTR(irtype)   	IRTYPE;
	simple_compound_dc(qm_real rate = 0.05, qm_uns_int monthsfreq = 0):m_rate(new irtype(rate,monthsfreq)) {}
	
	qm_real	dft(qm_real t) const  {
		if(t <= 0) return 1;
		return std::exp(-m_rate->ccrate()*t); 
	}
	IRTYPE	get(unsigned i) const {QM_REQUIRE(i==0,"Out of bound"); return m_rate;}
	
	unsigned length()      const {return 1;}
	
	qm_string tostring()   const {return "Simple compound discount curve: "+m_rate->tostring();}
	
	void fulldiscount(qm_real T, qm_real cash, SENSITIVITY& res) const  {
		static const qm_real c = 0.0001;
		sensitivity::delta_type de = res->deltas();
		sensitivity::gamma_type ga = res->gammas();
		qm_real np  = res->value();
		qm_real b   = cash*this->dft(T);
		qm_real cT  = c*T;
		qm_real db  = -cT*b;
		qm_real db2 = -cT*db;
		res->set_value(np + b);
		de[0] += db;
		ga[0] += db2;
	}
private:
	IRTYPE	m_rate;
};


QM_NAMESPACE_END2

#endif	//	__SIMPLE_DISCOUNT_CURVES_HPP__



