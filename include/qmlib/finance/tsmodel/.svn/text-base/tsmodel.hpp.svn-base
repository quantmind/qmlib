


#ifndef   __TERM_STRUCTURE_MODELS_QM_HPP__
#define   __TERM_STRUCTURE_MODELS_QM_HPP__


#include <qmlib/irates.hpp>
#include <qmlib/math/stoch/diffusion.hpp>



/*! \defgroup termstructure Term structure models

    The term structure models library.

    @{
*/

/// \file
/// \brief Base classes for term structure modelling


QM_NAMESPACE2(math)


class tsmodel;
typedef QM_SMART_PTR(tsmodel)	TSMODEL;




/// \brief Base class for general term structure models
class tsmodel : public idiscountcurve,
				public discount_curve_holder,
				public observer,
				public observable {
public:
	
	qdate   date() 		 const { return m_date;}
	unsigned length()    const { return m_driver->count();}
	STOCHASTIC stoch()	 const { return m_driver;}
	qm_string code() 	 const { return m_driver->code();}
	qm_string name() 	 const { return this->code() + " Term structure model";}
	qm_string tostring() const { return this->name();}
	
	/// \brief the model discount factor
	virtual qm_real	modeldf(qm_real t, qm_real T) const {return 1;}
	
	virtual qm_real modelfwdt(qm_real t, qm_real T1, qm_real T2) const;
	
	/// \brief Calculate the value of a Future on a Libor Rate.
	///
	/// @param t current time (usually 0)
	/// @param T1 time to settlement
	/// @param T2 time to expiry
	/// @param tau rate tenure (should be T2 - T1 approx)
	/// @return The future rate
	virtual qm_real future(qm_real, qm_real T1, qm_real T2, qm_real tau) const
	{QM_FAIL("Not implemented");}
	
	/// \brief calculate the instantaneous forward rate covariance
	///
	/// @param t current time (usually 0)
	/// @param T time to maturity
	/// @param tau rate tenure
	/// @return The forward rate instantaneous standard deviation
	virtual tinymat<qm_real,2,2>
	fwdratecovar(qm_real t, qm_real T1, qm_real tau1, qm_real T2, qm_real tau2) const 
	{QM_FAIL("Not implemented");}
	
	/// \brief The discount factor. If you the exactfit is selected (and a yield curve is available)
	/// this method will return the discount factor of the yield curve.
	qm_real		dft(qm_real T) const;
	qm_real		fwdt(qm_real T1, qm_real T2) const;
	qm_real		dfspread(const qdate& dte) const {return this->dfspreadt(this->dcf(dte));}
	qm_real		dfspreadt(qm_real T) const;
	
	/// \brief Return the rate spread between the model and the yield curve
	SENSITIVITY oas(const CASHFLOW& cfs, bool full) const;
	SENSITIVITY oas0(const CASHFLOW& cfs) const {return this->oas(cfs,false);}

	void		set_exactfit(bool fit) {m_fit = fit;}
	bool		get_exactfit() const   {return m_fit;}
	
	void update() {this->clear(); this->notify_observers();}
protected:
	qdate		m_date;
	bool		m_fit;
	STOCHASTIC	m_driver;
	
	virtual void clear() {}
	tsmodel(STOCHASTIC mo, const qdate& dte);
};


inline tsmodel::tsmodel(STOCHASTIC mo, const qdate& dte):
	m_date(dte),m_fit(true),m_driver(mo){
	QM_REQUIRE(m_driver,"Stochastic process not available");
	this->registerWith(m_driver);
}


inline qm_real tsmodel::dft(qm_real T) const  {
	return m_fit && m_yc ? m_yc->dft(T): this->modeldf(0,T);
}

inline qm_real tsmodel::fwdt(qm_real T1, qm_real T2) const  {
	return m_fit && m_yc ? m_yc->fwdt(T1,T2): this->modelfwdt(0,T1,T2);
}

inline qm_real tsmodel::modelfwdt(qm_real t, qm_real T1, qm_real T2) const  {
	return this->modeldf(t,T1)/this->modeldf(t,T2);
}

inline qm_real tsmodel::dfspreadt(qm_real T) const {
	QM_REQUIRE(m_yc,"Yield curve not available");
	return this->modeldf(0,T) - m_yc->dft(T);
}

inline SENSITIVITY tsmodel::oas(const CASHFLOW& cfs, bool full) const  {
	QM_FAIL("not implemented");
	/*
	qm_real npv  = 0;
	qm_real pv01 = 0;
	qm_real cexc = 0;
	qm_real b;
	if(full)  {
		QM_FAIL("not implemented");
	}
	else  {
		DiscountRes res(new discountres);
		for(CASHFLOW::const_iterator ct = cfs.begin(); ct != cfs.end(); ++ct)  {
			b = this->dfspread(ct->key());
			npv  += b*ct->value()->cash();
			pv01 += b*ct->value()->ntau();
			cexc -= b*ct->value()->notional_exchange();
		}
		return DiscountRes(new discountres(npv,0.0001*pv01,0,100*cexc/pv01));
	}
	*/
}





QM_NAMESPACE_END2

/*! @} */

#endif  //  __TERM_STRUCTURE_MODELS_QM_HPP__

