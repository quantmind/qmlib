

#ifndef __EXCHANGE_DATE_QM_HPP__
#define __EXCHANGE_DATE_QM_HPP__



#include <qmlib/corelib/dates/date.hpp>



QM_NAMESPACE


template<class Impl>
class exchangedate  {
public:
	exchangedate(const qdate& date = qdate::today()):m_count(0){NextValidDate(date);}
    //
    const qdate&   date()    const    {return m_date;}
    const qdate&   NextDate()         {Impl(m_date,true); m_count++; return m_date;}
    const qdate&   SetStartNextDate() {m_count = 0; return this->NextDate();}
protected:
    const qdate&   NextValidDate(const qdate& date);
    qm_int    m_count;
    qdate   m_date;
};



template<class Impl>
inline const qdate& exchangedate<Impl>::NextValidDate(const qdate& date)  {
    m_date = date;
    Impl(m_date,false);
    if(m_date < date) NextDate();
    m_count = 1;
    return m_date;
}




namespace {
    
	// Generate IMM dates
    template<unsigned monthperiod = 3>
    class ImmGenerator  {
    public:
    	typedef boost::gregorian::nth_day_of_the_week_in_month nth_dow;
    	
    	ImmGenerator(qdate& date, bool advance)  {
    		int m     = date.month();
    		int n     = m % monthperiod;
    		int mad   = 0;
    		if(n) mad = monthperiod - n;
    		else if(advance) mad = monthperiod;
    		date.add_months(mad);
    		nth_dow pd(nth_dow::third, boost::gregorian::Wednesday, date.month());
    		date  = pd.get_date(date.year());
    	}
    };
    
    template<> class ImmGenerator<0u>{};
}


typedef exchangedate<ImmGenerator<1> > IMM1generator;
typedef exchangedate<ImmGenerator<3> > IMM3generator;


QM_NAMESPACE_END


#endif // __EXCHANGE_DATE_QM_HPP__

