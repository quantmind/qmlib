
#ifndef __DATE_QM_HPP__
#define __DATE_QM_HPP__


#include <qmlib/corelib/dates/juldate.hpp>
//#include "boost/date_time/posix_time/posix_time.hpp" //include all types plus i/o
//#include "boost/date_time/posix_time/posix_time_types.hpp" //no i/o just types
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/serialization/split_member.hpp>
#include <qmlib/corelib/tools/json.hpp>
#include <qmlib/corelib/dates/impl/date_string.hh>



/**\file
 * \brief date class specification
 * \ingroup dates
 * 
 * This class wraps basic functionalities of boost_date_time and introduces several
 * methods for daycounting. This is a minimal class for financial date calculation.
 *
 * The full potential of the boost date_time library can be seen at
 * http://www.boost.org/doc/html/date_time.html
 */


QM_NAMESPACE


static const qm_strings c_shortmonths   = generate_shortmonthcodes();
static const qm_strings c_weekdays      = generate_weekdays();

/**\brief date class
 * \ingroup dates
 * 
 * This class wraps basic functionalities of boost_date_time and introduces several
 * methods for daycounting. This is a minimal class for financial date calculation.
 *
 * The full potential of the boost date_time library can be seen at
 * http://www.boost.org/doc/html/date_time.html
 */
class qdate  {
public:
	typedef	boost::gregorian::date		date_type;
	typedef date_type::calendar_type	calendar_type;
	
	qdate(){}
	qdate(const date_type& dte):m_date(dte){}
	qdate(const qdate& dte):m_date(dte.m_date){}
	qdate(int y, int m, int d):m_date(y,m,d){}
	virtual ~qdate(){}
	//
	/// \brief Get the boost::gregorian::date object
	const date_type& boost_date() const {return m_date;}
		
	qm_string tostring() const;
	qm_string monthyearshort() const;
	//
	// Operators
	qdate& operator = (const date_type& dte) {m_date = dte; return *this;}
	
	/// \brief date year
	///
	///@return date year
	int   year()         const  {return m_date.year();}
	
	/// \brief date month
	///
	///@return date month
	int   month()        const  {return m_date.month();}
	
	/// \brief date day
	///
	///@return date day
	int   day()          const  {return m_date.day();}
	
	/// \brief YYYYMMDD format
	///
	///@return a integer which represent the date in a YYYYMMDD format
	//unsigned  get_yyyymmdd() 			 const  {return this->day() + 100*(this->months() + 100*this->year());}
	//void  	  set_yyyymmdd(unsigned ymd) const;
	
	
	/// \brief True if date is a week end
	///
	///@return true if the date fall on a week-end day
	bool  isweekend()    const  {qm_short dow = m_date.day_of_week(); return dow == 0 || dow == 6;}
	
	/// \brief True if end of month
	///
	///@return true if date is the last day of the month
	bool  isEndOfMonth() const  {return m_date == m_date.end_of_month();}
	
	bool  is_not_a_date() const {return m_date.is_not_a_date();}
		
	bool operator == (const qdate& rhs) const {return m_date == rhs.m_date;}
	bool operator != (const qdate& rhs) const {return m_date != rhs.m_date;}
	bool operator <  (const qdate& rhs) const {return m_date <  rhs.m_date;}
	bool operator <= (const qdate& rhs) const {return m_date <= rhs.m_date;}
	bool operator >  (const qdate& rhs) const {return m_date >  rhs.m_date;}
	bool operator >= (const qdate& rhs) const {return m_date >= rhs.m_date;}
	
	void add_days(int d)   {m_date += boost::gregorian::date_duration(d);}
	void add_months(int m) {m_date += boost::gregorian::months(m);}
	
	//
	// static methods
	
	
	/// \brief Today
	///
	///@return today date
	static qdate today()	{
		return boost::gregorian::day_clock::local_day();
	}
	
	/// \brief Number of days between two dates
	///
	///@param start The start qdate
	///@param end The end qdate
	///@return The number of days between start nad end
	static qm_long daydiff(const qdate& start, const qdate& end)  {
		return (end.boost_date() - start.boost_date()).days();
	}

	/// \brief Create a date from a long number of the form YYYYMMDD
	static qdate fromyyyymmdd(long yyyymmdd)  {
		double dyyyymm = 0.01*yyyymmdd;
		long   yyyymm  = (long)dyyyymm;
		double dyyyy   = 0.01*yyyymm;
		long   y       = (int)dyyyy;
		long d = yyyymmdd - 100*yyyymm;
		long m = yyyymm   - 100*y;
		return qdate(y,m,d);
	}
	
	/// \brief Serialization
	///
	/// Serialize the date
	template<class Archive>
	void save(Archive& ar, const unsigned int version) const {
		int y = this->year();
		int m = this->month();
		int d = this->day();
		ar & y & m & d;
	}
	
	template<class Archive>
	void load(Archive& ar, const unsigned int version) {
		int y,d,m;
		ar & y & m & d;
		this->m_date = date_type(y,m,d);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()
private:
	date_type  m_date;
};


inline bool isweekend(const boost::gregorian::date& dte) {
  qm_short dow = dte.day_of_week();
  return dow == 0 || dow == 6;
}

inline qm_string dayoftheweek(const qdate& dte) {
	unsigned i = dte.boost_date().day_of_week();
	unsigned dw = i == 0 ? 6 : i-1;
	return c_weekdays[dw];
}


inline qm_long counting30360(qm_uns_int d1, qm_uns_int d2,
 							 qm_uns_int m1, qm_uns_int m2,
 							 qm_uns_int y1, qm_uns_int  y2)  {
 	return 360*(y2 - y1) + 30*(m2 - m1) + (d2 - d1);
}

inline qm_real ActActYears(const qdate& dte) 	{
	qm_uns_int  y = dte.year();
	qm_uns_int  r = y % 4;
	qm_real     a = r > 0 ? 1.0 : 0.0;
	return y + qm_real(qdate::daydiff(qdate(y,1,1),dte)) / (365.0 + a);
}
  	/*
  //
  inline qm_date baddate()
  {
    return boost::gregorian::date();
  }
  //
  inline qm_date addMonths(const qm_date& date, qm_int m)
  {
    boost::gregorian::months mo(m);
    return date + mo;
  }
  //
  inline qm_date addDays(const qm_date& date, qm_int d)
  {
    boost::gregorian::date_duration da(d);
    return date + da;
  }
  */
  //
inline qm_string qdate::tostring() const  {
	return object_to_string(this->year()) + "-" +
	       object_to_string(this->month())+ "-" +
	       object_to_string(this->day());
}

inline qm_string qdate::monthyearshort() const  {
	qm_string co = c_shortmonths[this->month()-1];
	qm_string y  = object_to_string(this->year());
	return co + y.substr(2);                 
}


template<>
struct object_to_json<qdate>  {
	static json doit(const qdate& dte)  {
		return json("date",dte.tostring());
	}
};




QM_NAMESPACE_END

#endif // __DATE_QM_HPP__

