//
//
#ifndef __HOLIDAY_QM_HPP__
#define __HOLIDAY_QM_HPP__

#include <qmlib/corelib/dates/datestring.hpp>
#include <qmlib/corelib/dates/boost_date.hpp>
#include <set>


QM_NAMESPACE
  //
  //
  //
  //
  class holiday  {
  public:
    qdate     hdate;
    qm_string name;
    //
    holiday(const qdate& dte, const qm_string& descr = ""):hdate(dte),name(descr){}
    holiday(const holiday& hol):hdate(hol.hdate),name(hol.name){}
    virtual ~holiday(){}
    //
    holiday& operator = (const holiday& rhs) {this->hdate = rhs.hdate; this->name = rhs.name; return *this;}
    //
    bool operator == (const holiday& rhs) const {return this->hdate == rhs.hdate;}
    bool operator != (const holiday& rhs) const {return this->hdate != rhs.hdate;}
    bool operator >  (const holiday& rhs) const {return this->hdate >  rhs.hdate;}
    bool operator <  (const holiday& rhs) const {return this->hdate <  rhs.hdate;}
    bool operator >= (const holiday& rhs) const {return this->hdate >= rhs.hdate;}
    bool operator <= (const holiday& rhs) const {return this->hdate <= rhs.hdate;}
  };
  typedef   QM_SET(holiday)  qm_holidays;


  
  
  
  class holidaygen  {
  public:
    holidaygen(boost::gregorian::year_based_generator* gen, const qm_string& descr = "", qm_short dayback = 0):m_date_gen(gen),m_descriptor(descr),m_dayback(dayback){}
    virtual ~holidaygen(){if(m_date_gen) delete m_date_gen;}
    bool add_date(qm_short year, qm_holidays& hols) const;
    const qm_string& description() const {return m_descriptor;}
    qm_string datedescr() const {return m_date_gen->to_string();}
    //
  private:
    boost::gregorian::year_based_generator* m_date_gen;
    qm_string                               m_descriptor;
    qm_short                                m_dayback;
  };
  typedef QM_SMART_PTR(holidaygen) HolidayGen;

  
  
  
  
  inline bool holidaygen::add_date(qm_short year, qm_holidays& hols) const  {
    qdate dte = m_date_gen->get_date(year);
    holiday hol(dte,this->description());
    if(hols.find(hol) != hols.end()) return false;
    //
    if(m_dayback == 0)
    {
      if(dte.isweekend()) return false;
      hols.insert(hol);
      return true;
    }
    //
    boost::gregorian::day_iterator itr(dte.boost_date(),m_dayback);
    bool done = false;
    //
    while(!done)
    {
      while(isweekend(*itr)) ++itr;
      hol.hdate = *itr;
      if(hols.find(hol) == hols.end())
      {
        done = true;
        hols.insert(hol);
      }
      else ++itr;
    }
    return true;
  } 
//
QM_NAMESPACE_END
//
//
#endif // __HOLIDAY_QM_HPP__
//
