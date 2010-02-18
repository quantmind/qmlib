

#ifndef __IMM_DATE_QM_HPP__
#define __IMM_DATE_QM_HPP__



#include <qmlib/corelib/dates/date.hpp>



QM_NAMESPACE


/**\brief Calculate an IMM date
 * \ingroup dates
 * 
 */
inline qdate immdate(unsigned month, unsigned year) {
	typedef boost::gregorian::nth_day_of_the_week_in_month nth_dow;
	nth_dow pd(nth_dow::third, boost::gregorian::Wednesday, month);
	return pd.get_date(year);
}

QM_NAMESPACE_END


#endif // __IMM_DATE_QM_HPP__

