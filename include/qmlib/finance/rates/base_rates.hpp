
#ifndef   __BASE_RATES_QM_HPP__
#define   __BASE_RATES_QM_HPP__


#include <qmlib/irates.hpp>
#include <qmlib/corelib/static/all.hpp>


/// \file
/// \brief Base classes for rate implementation
/// \ingroup rates


QM_NAMESPACE2(finance)


/** \brief Implements the date and dcf methods of idiscountcurve
 *  \ingroup rates
 */
class discountcurve: public idiscountcurve  {
public:
	discountcurve(const qdate& dte = qdate::today()):m_date(dte){}
	qdate   date() 				const   { return m_date;}
	void    set_date(const qdate& date) { m_date = date;}
public:
	qdate m_date;
};



/// \brief Simple scalar rate
/// \ingroup rates
///
/// This object contains a single rate
class scalar_rate : public irate, public obj_value {
public:
	typedef QM_SMART_PTR(scalar_rate)	RatTyp;
	
	scalar_rate():irate(),obj_value(){}
	//scalar_rate(IVALUE val):obj_value(val) {}
	static RatTyp create() {return RatTyp(new scalar_rate);}
	
	qm_string tostring()    const {return "simple scalar rate";}
	bool      valid()	    const {return this->value()->validvalue();}
};



QM_NAMESPACE_END2



#endif  //  __BASE_RATES_QM_HPP__
//
