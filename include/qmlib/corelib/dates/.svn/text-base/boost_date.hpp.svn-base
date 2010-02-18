//
//
#ifndef __BOOST_DATE_QM_HPP__
#define __BOOST_DATE_QM_HPP__
//


#include <qmlib/corelib/dates/date.hpp>
#include <qmlib/corelib/dates/juldate.hpp>



QM_NAMESPACE



class gregorian_roman_easter: public boost::gregorian::year_based_generator  {
public:
	typedef boost::gregorian::date	date_type;
	gregorian_roman_easter(int days):m_days(days){}
    date_type get_date(boost::gregorian::greg_year y) const {
    	return juldate::ToDate<date_type>(juldate(juldate::RomanEaster(y)+m_days));
    }
    std::string to_string() const {return "";}
private:
    int m_days;
};



class gregorian_orthodox_easter: public boost::gregorian::year_based_generator  {
public:
	typedef boost::gregorian::date	date_type;
    //
	gregorian_orthodox_easter(int days):m_days(days){}
    date_type get_date(boost::gregorian::greg_year y) const {
    	return juldate::ToDate<date_type>(juldate(juldate::OrthodoxEaster(y)+m_days));
    }
    std::string to_string() const {return "";}
private:
    int m_days;
};



QM_NAMESPACE_END



#endif // __BOOST_DATE_QM_HPP__

