

#ifndef	__IRATES_QM_HPP__
#define	__IRATES_QM_HPP__


#include <qmlib/cashflow.hpp>


/** \file
 *  \brief Rate class interfaces.
 *  \ingroup rates
 * 
 * Definition of rate interfaces such as
 *  - irate
 *  - itermstructure
 *  - idiscountcurve
 *  - ivolsurface
 *  - ioptionmodel
 * 
 * These interfaces are used throughout the library as
 * building blocks for assets pricing.
 */


QM_NAMESPACE



class idiscountcurve;
class ivolsurface;
class ioptionmodel;
typedef QM_SMART_PTR(idiscountcurve) DISCOUNTCURVE;
typedef QM_SMART_PTR(ivolsurface) 	 IVOLSURFACE;
typedef QM_SMART_PTR(ioptionmodel) 	 OPTION_MODEL;

/** \brief base class for rates
 * \ingroup rates
 */
class irate : public icodename {
public:
	/// \brief Return the number of rates/factors used by the irate.
	///
	qm_string   code()	const	 {return "<no code>";}
	/// If the rate is scalar this method will throw an error
	virtual unsigned  length()  const    {QM_FAIL("this is not a composite rate");}
	/// \brief The date of the rate
	virtual qdate     date() 	const    {return qdate();}
	
	virtual void      set_date(const qdate& dte) {QM_FAIL("Cannot set the date for this rate");}
	
	/// \brief True if the rate is valid and ready for calculation
	virtual bool      valid()   const    {return false;}
	
	SENSITIVITY sen() const;
	virtual sensitivities sens() const;
protected:
	irate(){}
};



/** \brief Interface class for a Term Structure rate
 * \ingroup rates
 */
class itermstructure : public irate {
public:
	itermstructure():m_dc(new Act365){}
	
	/** \brief Day count fraction
	 * This function is used to calculate a numeric value for
	 * a date. This value is then used in all the rate calculation.
	 * \note The day count fraction method could be anything you like. Here we selected Act365
	 * because we like it. What is important is that we use the same method for all our calculations.
	 */
	qm_real   dcf(const qdate& dte) const {return m_dc->dcf(this->date(),dte);}
	
	bool      valid()   const    {return !this->date().is_not_a_date();}
	DC		  DayCounter() const {return m_dc;}
protected:
	DC m_dc;
};



/** \brief Interface class for discount curve rate
 * \ingroup rates
 */
class idiscountcurve : public itermstructure {
public:
	/** \brief Main discount factor function
	* @param T the time in years. T needs to be non-negative
	* @return The discount factor for time T
	* This function should be overwritten by derived classes
	*/
	virtual qm_real	dft(qm_real T) const  { return 1;}
	
	/** \brief Forward factor
	* @param T1 the time in years. T needs to be non-negative
	* @param T2 time in years with T2 > T1.
	* @return The forward value dft(T1)/dft(T2)
	*/
	virtual qm_real	fwdt(qm_real T1, qm_real T2) const  { return this->dft(T1)/this->dft(T2);}
	
	/**\brief discount factor function
	 * @param dte Date for which the discount factor is needed
	 * @return The discount factor for date dte
	 * This function calculate a year fraction from the input dte
	 * and uses dft to calculate the discount factor.
	 */ 
	virtual qm_real	df(const qdate& dte) const { return this->dft(this->dcf(dte));}
	
	/**\brief Discount a CASHFLOW object
	 * @param cfs a CASHFLOW object to discount
	 * @param full true if a full sensitivity analysis needs to be performed
	 * @return a smart-pointer to discountres
	 */
	virtual SENSITIVITY dcashflow(const CASHFLOW& cfs, bool full) const;
	SENSITIVITY dcashflow0(const CASHFLOW& cfs) const {return this->dcashflow(cfs,false);}
	
	/**\brief Full discount function
	 * @param T Time for discounting
	 * @param cash Cash to discount at date dte
	 * @param res a Smart pointer to discounres to add the result to
	 */
	virtual void fulldiscount(qm_real T, qm_real cash, SENSITIVITY& res) const;

	/** \brief Full discount of a single cash value
	 * 
	 * @param dte Cash date
	 * @param cash Cash value
	 * @return a smart pointer to discountres
	 */
	SENSITIVITY dcash(const qdate& dte, qm_real cash) const;
	
	/** \brief Full discount of a single cash value
	 * 
	 * @param T Cash time
	 * @param cash Cash value
	 * @return a smart pointer to discountres
	 */
	SENSITIVITY dcasht(qm_real T, qm_real cash) const;
	
	/**\brief Average continuously compounded rate
	 * 
	 * @param T Time to maturity
	 * @return the continuously coumponded rate
	 */
	qm_real exprate(qm_real T) const;
	
	/**\brief Instantaneous Forward rate
	 *
	 * @param T Time to maturity
	 * @return The instantaneous forward rate is given by the equation
	 *  \f$ f(T) = -\frac{\partial \ln B(T)}{\partial T} \f$
	 */
	virtual qm_real instfwd(qm_real T) const;
	
	/**\brief Forward rate
	 * 
	 * @param T1 Time to maturity
	 * @param T2 Time to maturity plust fare tenure
	 * @param tau day count fraction between T1 and T2
	 */
	qm_real fwdrate(qm_real T1, qm_real T2, qm_real tau) const;
protected:
	idiscountcurve(){}
};



/** \brief Discount curve holder
 * This class is derived by objects which require to hold a discount curve
 * and a convenience yield curve
 * \ingroup rates
 */
class discount_curve_holder  {
public:
	discount_curve_holder(){}
	discount_curve_holder(const discount_curve_holder& rhs):
		m_yc(rhs.m_yc),m_cy(rhs.m_cy){}
	/// \brief Add a curve
	///
	/// The first add is the yield curve, the second the convenience yield curve
	template<class T>
	void addcurve(const QM_SMART_PTR(T)& element)  {
		if(m_yc)  {
			QM_REQUIRE(!m_cy,"Discount and convenience already available. Use flushcurves to add again");
			m_cy = smart_cast<idiscountcurve,T>(element);
		}
		else     m_yc = smart_cast<idiscountcurve,T>(element);
	}
	void			flushcurves()  {m_yc = DISCOUNTCURVE(); m_cy = DISCOUNTCURVE();} 
	DISCOUNTCURVE	ycurve() const {return m_yc;}
	DISCOUNTCURVE	ccurve() const {return m_cy;}
protected:
	DISCOUNTCURVE	m_yc;
	DISCOUNTCURVE	m_cy;
};


/** \brief Interface for volatility surfaces
 * \ingroup rates
 */
class ivolsurface  : public itermstructure, public discount_curve_holder  {
public:
	virtual	qm_real	 striketomoneyness(qm_real k) const {return k;}
	virtual qm_real  blackvol(qm_real strike, const dateperiod& dte) const {QM_FAIL("not implemented");}
	virtual qm_real  bpvol(qm_real strike, const dateperiod& dte)    const {QM_FAIL("not implemented");}
protected:
	ivolsurface(){}
};

/** \brief Interface class for optionmodels
 */
class ioptionmodel : public itermstructure {
public:
	virtual pricingValuationMethod method() const {QM_FAIL("not available");}
	virtual bool	has_analytical() const {return false;}
	virtual bool	has_pde() 		 const {return false;}
	virtual bool	has_fourier() 	 const {return false;}
	virtual unsigned underlyings()   const {return 0;}
protected:
	ioptionmodel(){}
};


class dummydiscount : public idiscountcurve  {
public:
	dummydiscount(){}
	qm_string code() const {return "dummy discount";}
protected:
};


QM_NAMESPACE_END


#include <qmlib/finance/rates/impl/rate_impl.hh>


#endif	//	__IRATES_QM_HPP__

