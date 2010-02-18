//
/// \file
/// \ingroup dates
//
#ifndef __DATE_STRING_QM_HPP__
#define __DATE_STRING_QM_HPP__
//
//
#include <qmlib/corelib/dates/daycount.hpp>




QM_NAMESPACE





/// \brief Period manager
///
/// This class perform the basic conversions between a string period and numeric values
/// \ingroup dates
class period : public basedes {
public:
	period(qm_int months = 0, qm_int days = 0):m_months(months),m_days(days){}
    period(const qm_string& str):m_months(0),m_days(0){this->add_tenure(str,"Y");}
    period(const qm_string& str, const qm_string& defpe):m_months(0),m_days(0){
    	this->add_tenure(str,defpe);
    }
    period(const period& rhs):m_months(rhs.m_months),m_days(rhs.m_days){}
    period(const qdate& start, const qdate& end);
    
    const period& operator = (const period& rhs)    {m_months = rhs.m_months; m_days = rhs.m_days; return *this;}
    const period& operator = (const qm_string& rhs) {period p(rhs); return *this = p;}
    
    bool operator >  (const period& pe) const {return this->total() >  pe.total();}
    bool operator >= (const period& pe) const {return this->total() >= pe.total();}
    bool operator == (const period& pe) const {return this->total() == pe.total();}
    bool operator <  (const period& pe) const {return this->total() <  pe.total();}
    bool operator <= (const period& pe) const {return this->total() <= pe.total();}
    
    bool isempty() const {return m_months == 0 && m_days == 0;}
    void add_days(qm_int d)   {m_days    += d;}
    void add_weeks(qm_int w)  {m_days    += 7*w;}
    void add_months(qm_int m) {m_months  += m;}
    void add_years(qm_int y)  {m_months  += 12*y;}
    void add_tenure(const qm_string& str, const qm_string& defpe);
 
    period& operator += (const period& pe)     {m_months += pe.m_months; m_days += pe.m_days; return *this;}
    period& operator -= (const period& pe)     {m_months -= pe.m_months; m_days -= pe.m_days; return *this;}
    period& operator += (const qm_string& rhs) {period pe(rhs); m_months += pe.m_months; m_days += pe.m_days; return *this;}
    period& operator -= (const qm_string& rhs) {period pe(rhs); m_months -= pe.m_months; m_days -= pe.m_days; return *this;}

    qm_int  years()       const {return m_months/12;}
    qm_int  months()      const {return m_months % 12;}
    qm_int  totalmonths() const {return m_months;}
    qm_int  weeks()       const {return m_days/7;}
    qm_int  days()        const {return m_days % 7;}
    qm_int  totaldays()   const {return m_days;}
    qm_long total()       const {return 30*m_months + m_days;}
    qm_real dcf()         const {return this->totalmonths()/12.0 + this->totaldays()/365.0;} 

    qm_string tostring() const;
    qm_string tofrequency() const;

    friend period operator + (const period& lhs, const period& rhs)    {period p(lhs); return p+=rhs;}
    friend period operator + (const period& lhs, const qm_string& rhs) {period p(lhs); return p+=rhs;}
    friend period operator + (const qm_string& lhs, const period& rhs) {period p(lhs); return p+=rhs;}
    friend period operator - (const period& lhs, const period& rhs)    {period p(lhs); return p-=rhs;}
    friend period operator - (const period& lhs, const qm_string& rhs) {period p(lhs); return p-=rhs;}
    friend period operator - (const qm_string& lhs, const period& rhs) {period p(lhs); return p-=rhs;}
private:
    qm_long m_months;
    qm_long m_days;
};





/// \brief An object used for specifing a date either by qm_date or by a tenure string
///
/// This objec could be either a qm_date or a string such as "3M" or "1Y3M" etc..
/// \ingroup dates
template<class D>
class datestring : public basedes  {
public:
  	typedef	D	datetype;
    //datestring(const qm_string& tenure = ""):m_tenure(tenure),m_isdate(false){}
    /// \brief default constructor
    datestring(const char* tenure = ""):m_period(tenure),m_isdate(false){}
    /// \brief string constructor
    datestring(const qm_string& tenure):m_period(tenure),m_isdate(false){}
    /// \brief date constructor
    datestring(const datetype& date):m_date(date),m_isdate(true){}
    /// \brief copy constructor
    datestring(const datestring& dtst);
    
    datestring& operator = (const datestring& rhs);
    datestring& operator = (const datetype& rhs);
    datestring& operator = (const qm_string& rhs);
    datestring& operator = (const period& rhs);
    
    bool operator >  (const datestring& rh) const {return m_isdate ? m_date >  rh.date() : m_period >  rh.tenure();}
    bool operator >= (const datestring& rh) const {return m_isdate ? m_date >= rh.date() : m_period >= rh.tenure();}
    bool operator == (const datestring& rh) const {return m_isdate ? m_date == rh.date() : m_period == rh.tenure();}
    bool operator <  (const datestring& rh) const {return m_isdate ? m_date <  rh.date() : m_period <  rh.tenure();}
    bool operator <= (const datestring& rh) const {return m_isdate ? m_date <= rh.date() : m_period <= rh.tenure();}

    const datetype&     date()     const;
    const period& 		tenure()   const;
    bool          		isdate()   const {return m_isdate;}
    bool                isempty()  const {return !m_isdate && m_period.isempty();}
    qm_string     		tostring() const;
    qm_real             dcf(const D& date, const qm_string& dct = "ActAct") const;
 
    operator const qm_string& () {return this->tostring();}
    
private:
    period     m_period;
    datetype   m_date;
    bool       m_isdate;
};


//
//
/// \brief parse a character into a string frequency
/// @param freq a character in 'A' (annual), 'S' (semiannual), 'Q' (quarterly),
/// 'B' (bimonthly) 'M' (monthly)
/// @return a integer indicationg the number of months
/// \ingroup tools
inline period charFrequencyToPeriod(const char& freq)  {
  char uf = std::toupper(freq);
  if(uf == 'A')      return period(12);
  else if(uf == 'S') return period(6);
  else if(uf == 'Q') return period(3);
  else if(uf == 'B') return period(2);
  else if(uf == 'M') return period(1);
  else if(uf == 'W') return period(0,7);
  else if(uf == 'D') return period(0,1);
  else QM_FAIL("unrecognized frequency character. It must be in ('A','S','Q','M','W','D')");
}




typedef datestring<qdate>	dateperiod;


inline period::period(const qdate& start, const qdate& end):m_months(0),m_days(0)  {
	qm_long d = qdate::daydiff(start,end);
	if(d < 0)  {
		QM_FAIL("negative period");
	}
	else if(d < 4) m_days = d;
	else if(d < 25)
	{
		qm_real wr = d/7.0;
		int w = int(wr);
		if(wr - w > 0.5) m_days = 7*(w+1);
		else m_days = 7*w;
	}
	else  {
		qm_real  y = d/365.0;
		int     yi = int(y);
		qm_real  m = (d - 365*yi)/30.0;
		int     mi = int(m);
		if(m - mi > 0.5) mi++;
		m_months = 12*yi + mi;
	}
}



inline void period::add_tenure(const qm_string& str, const qm_string& defaultPeriod)  {
	if(str.length() == 0) return;
    qm_string st = qmstring::uppercase(str);
    if(st == "ON") {
    	this->add_days(1);
        return;
    }
    else if(st == "TN")  {
        this->add_days(2);
        return;
    }
    
    char abbr;
    for(;;)  {
        qm_Size ip = st.find_first_of("DdWwMmYy");
        if(ip >= st.length() && st.length() > 0) {
          ip   = st.length();
          QM_REQUIRE(defaultPeriod.length()>0,"Unknown period");
          abbr = std::toupper(defaultPeriod[0]);
        }
        else if(ip <= str.length()-1)  {
          QM_REQUIRE(ip>0,"Could not parse tenure string " + str);
          abbr = std::toupper(st[ip]);
        }
        else break;
        qm_int n = boost::lexical_cast<qm_int>(st.substr(0,ip));
        if (abbr == 'D')       this->add_days(n);
        else if (abbr == 'W')  this->add_weeks(n);
        else if (abbr == 'M')  this->add_months(n);
        else if (abbr == 'Y')  this->add_years(n);
        if(ip >= st.length()-1) break;
        st = st.substr(ip+1);
    }
}

    
inline qm_string period::tostring() const  {
	if(m_months == 0 && m_days == 1) return "ON";
    if(m_months == 0 && m_days == 2) return "TN";
    qm_int y = this->years();
    qm_int m = this->months();
    qm_int w = this->weeks();
    qm_int d = this->days();
    qm_string te;
    if(y>0) te += boost::lexical_cast<qm_string>(y)+"Y";
    if(m>0) te += boost::lexical_cast<qm_string>(m)+"M";
    if(w>0) te += boost::lexical_cast<qm_string>(w)+"W";
    if(d>0) te += boost::lexical_cast<qm_string>(d)+"D";
    return te;
}

inline qm_string period::tofrequency() const  {
	if(m_months == 0)  {
		switch(m_days)  {
			case 0:  return "continuous";
			case 1:  return "daily";
			case 7:  return "weekly";
			case 14: return "biweekly";
			default: return this->tostring();
		}
	}
	else if(m_days == 0)  {
		switch(m_months)  {
   			case   1: return "monthly";
   			case   2: return "bimonthly";
   			case   3: return "quarterly";
   			case   6: return "semiannually";
   			case  12: return "annually";
   			case  24: return "biannually";
   			default: return this->tostring();
		}
   	}
	else return this->tostring();
}


template<class D>
inline datestring<D>::datestring(const datestring<D>& rhs):m_isdate(rhs.m_isdate)  {
	if(m_isdate) m_date = rhs.m_date;
    else m_period = rhs.m_period;
}
    
    
template<class D>
inline datestring<D>& datestring<D>::operator = (const datestring<D>& rhs) {
	m_period = rhs.m_period;
	m_date   = rhs.m_date;
	m_isdate = rhs.m_isdate;
	return *this;
}

template<class D>
inline datestring<D>& datestring<D>::operator = (const D& rhs) {
	m_date   = rhs;
	m_isdate = true;
	return *this;
}

template<class D>
inline datestring<D>&  datestring<D>::operator = (const qm_string& rhs) {
	m_period = rhs;
	m_isdate = false;
	return *this;
}

template<class D>
inline datestring<D>&  datestring<D>::operator = (const period& rhs) {
	m_period = rhs;
	m_isdate = false;
	return *this;
}

template<class D>
inline const D& datestring<D>::date() const {
	QM_REQUIRE(this->isdate(),"not a date");
	return m_date;
}

template<class D>
inline const period& datestring<D>::tenure() const {
	QM_REQUIRE(!this->isdate(),"not a tenure");
	return m_period;
}

template<class D>
inline qm_string datestring<D>::tostring() const {
	if(this->isdate()) return m_date.tostring();
	else return m_period.tostring();
}

template<class D>
inline qm_real datestring<D>::dcf(const D& date, const qm_string& dcname) const  {
	if(this->isdate())  {
		DC dc = daycounter::get(dcname);
		if(dc) return dc->dcf(date,m_date);
		else QM_FAIL("Day counter not specified");
	}
	else return m_period.dcf();
}


QM_NAMESPACE_END


#endif // __DATE_STRING_QM_HPP__

