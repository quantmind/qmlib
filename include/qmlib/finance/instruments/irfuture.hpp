

#ifndef   __IRFUTURE_QM_HPP__
#define   __IRFUTURE_QM_HPP__

#include <qmlib/finance/security.hpp>
#include <qmlib/finance/instruments/otcir.hpp>


QM_NAMESPACE2(finance)


class irfuture: public future  {
public:
	irfuture(const EXCHANGE& ex, const qdate& expiry,
			 const qdate& depo_start, const qdate& depo_end,
			 DC dc):future(ex,expiry),
			 m_depo_start(depo_start),m_depo_end(depo_end),m_dc(dc) {
		QM_REQUIRE(m_dc,"Day count is null");
	}
	const qdate& depostart() const {return m_depo_start;}
	const qdate& depoend()   const {return m_depo_end;}
	const qm_real tenure()   const {return m_dc->dcf(m_depo_start,m_depo_end);}
	DC			  get_dc()	 const {return m_dc;}
protected:
	qdate m_depo_start,m_depo_end;
	DC	  m_dc;
};
typedef QM_SMART_PTR(irfuture)	IRFUTURE;



/** \brief Interest Rate Future Instrument
 * \ingroup finins
 * 
 */
class irfutinst: public Instrument<irfuture_>,
				 public iccyplug,
			     public simplediscount {
public:
	irfutinst(IRFUTURE irt);
	CCY			currency()	    const {return m_irf->currency();}
	qm_real		notional()      const {return m_size;}
	void		set_notional(qm_real notio);
	IRFUTURE	get_future()    const {return m_irf;}
	unsigned 	curvepriority() const {return InstrumentInfo<irfuture_>::priority;}
	const qdate& expiry() 		const {return m_irf->expiry();}
	const qdate& lastdate()     const {return m_irf->depoend();}
	qm_real internalccr() const;
	
	qm_string simple_discount_string() const;
protected:
	CASHFLOW build_cashflow(const qdate& dte) const;
	IRFUTURE		m_irf;
	qm_real			m_size;
};



inline irfutinst::irfutinst(IRFUTURE irf):m_irf(irf),m_size(1) {
	QM_REQUIRE(m_irf,"Interest rate future is null");
	m_rate = IVALUE(new irfuture_value);
	this->registerWith(m_rate);
}

inline qm_string irfutinst::simple_discount_string() const  {
	return this->expiry().monthyearshort();
}

inline CASHFLOW irfutinst::build_cashflow(const qdate& dte) const  {
	CASHFLOW cfs;
	qm_real notio = this->notional();
	irfuture* f   = m_irf.get();
	qm_real tau   = f->tenure();
    cfs.addkeyval(f->depostart(), 	CASHEVENT(new fixcash(-notio,true)));
    cfs.addkeyval(f->depoend(),	    CASHEVENT(new fixcash(notio,true)));
    cfs.addkeyval(f->depoend(),	    CASHEVENT(new couponevent(m_rate,tau,notio)));
    return cfs;
}

inline void irfutinst::set_notional(qm_real notio) {
	m_size = notio;
	this->clearcf();
	this->update();
}

inline qm_real irfutinst::internalccr() const  {
	qm_real ra = this->rate()->get_ratevalue();
	qm_real tau = m_irf->tenure();
	return std::log(tau*ra+1.)/tau;
}

template<class G>
struct future_next<irfuture,G>  {
	typedef QM_SMART_PTR(irfuture) FUTYPE;
	static FUTYPE get(const EXCHANGE& ex, const qdate& date, unsigned n)  {
		qm_uns_char del = ex->delay();
		TradingCentres hols(ex->holiday());
		G gen(date);
		qdate sta   = gen.date();
		qdate end   = gen.NextDate();
		for(unsigned i=0;i<n;i++)  {
			sta = end;
			end = gen.NextDate();
		}
		qdate expry = hols.prevbizday(sta,del);
		return FUTYPE(new irfuture(ex,expry,sta,end,ex->currency()->floatDC()));
	}
};




QM_NAMESPACE_END2

#endif	//	__IRFUTURE_QM_HPP__
