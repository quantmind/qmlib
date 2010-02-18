//
/// \file
/// \ingroup finance
//
#ifndef   __TRADING_CENTRE_QM_HPP__
#define   __TRADING_CENTRE_QM_HPP__
//
//
#include <qmlib/corelib/dates/all.hpp>
#include <qmlib/corelib/static/enums.hpp>
//
//
//
QM_NAMESPACE



class tc;
class dateAdjustment;
typedef inlinedb<qm_string,tc>  		tcs;
typedef QM_SMART_PTR(tc)        		TC;
typedef QM_SMART_PTR(dateAdjustment)	ADJ;




// Interface class for TradingCentre
class TradingCentre : public icodename {
public:
    virtual ~TradingCentre(){}
    
    virtual bool isbizday(const qdate& date) const = 0;
    virtual void flush() const = 0;
    
    virtual qm_long    numbizdays(const qdate& start, const qdate& end) const;
    virtual qdate      nextbizday(const qdate& date, qm_long days = 0) const;
    virtual qdate      prevbizday(const qdate& date, qm_long days = 0) const;
    virtual qm_uns_int count() const {return 1;}
    
protected:
    TradingCentre(){}
};





/** \brief Collection of Trading Centres
 * \ingroup static
 * 
 * A collection of TCs, this class is used for calculating valid businnes days
 */
class TradingCentres: public TradingCentre  {
public:
	typedef TC                         value_type;
    typedef std::vector<value_type>    container;
    typedef container::iterator        iterator;
    typedef container::const_iterator  const_iterator;
    
    /// \brief Constructor form a comma separted string of TCs codes.
    /// @param codes a comma separted string of TCs codes such as "NY,TGT,LON"
    TradingCentres(const qm_string& codes = ""):m_tcs(new container) {
    	if(codes.length()) push_back(codes);
    }
    /// \brief Constructor from a pointer to TCs
    /// @param tc A smart pointer to TCs
    TradingCentres(const TC& tc):m_tcs(new container) {push_back(tc);}
    /// \brief Copy Constructor
    TradingCentres(const TradingCentres& tc):m_tcs(tc.m_tcs){}
    
    TradingCentres& operator = (const TradingCentres& rhs)   {m_tcs->clear(); push_back(rhs);   return *this;}
    TradingCentres& operator = (const TC& rhs)               {m_tcs->clear(); push_back(rhs);   return *this;}
    TradingCentres& operator = (const qm_string& codes)      {m_tcs->clear(); push_back(codes); return *this;}
    
    void            push_back(const qm_string& codes);
    void            push_back(const TC& tc);
    void            push_back(const TradingCentres& tc);
    
    qm_string       code() const;
    bool            isbizday(const qdate& date) const;
    void            flush() const {}
    qm_string       tostring() const {return "Trading Centres "+this->code();}
    
    qdate           adjust(const qdate& date, BizDayConv bzc) const;
    
    qm_uns_int      size()  const {return m_tcs->size();}
    bool            empty() const {return m_tcs->empty();}
    iterator        begin()       {return m_tcs->begin();}
    iterator        end()         {return m_tcs->end();}
    const_iterator  begin() const {return m_tcs->begin();}
    const_iterator  end()   const {return m_tcs->end();}
    
    qdate parseinterval(const qdate& valdate, const period& pe, BizDayConv bzc = unadjusted) const;
    qdate parseinterval1(const qdate& valdate, const qm_string& tenure, BizDayConv bzc) const {return parseinterval(valdate,period(tenure),bzc);}
    
    /// \brief Construct a period given two dates
    /// @param start The start date
    /// @param end The end date, with end >= start
    /// @param conv A BizDayConv
    period datestointerval(const qdate& start, const qdate& end, BizDayConv bzc) const;
    
private:
	QM_SMART_PTR(container)  m_tcs;
};


/// \brief Parse a string interval into a date
///
/// Given a base date, it calculates a new forward date
/// @param valdate The starting date
/// @param tenure A tenure stringtostring such as "1Y", "1Y8M", "2D" or "2W" etc...
/// @param tcs A string containing the TradingCentres such as "NY,TGT"
/// @param bzc The BizDayConv used for adjusting holidays
/// @return A forward date
/// \ingroup finance
inline qdate parseinterval(const qdate& valdate, const qm_string& tenure, const qm_string& tcs, BizDayConv bzc)
{TradingCentres t(tcs); return t.parseinterval(valdate,tenure,bzc);}
inline qdate parseinterval1(const qdate& valdate, const qm_string& tenure)
{return parseinterval(valdate,tenure,"",modfoll);}
inline qdate parseinterval2(const qdate& valdate, const qm_string& tenure, const qm_string& tcs)
{return parseinterval(valdate,tenure,tcs,modfoll);}


class dateAdjustment : public basedes {
public:
	dateAdjustment(BizDayConv bz = unadjusted, short del = 0):bzc(bz),delay(del){}
	dateAdjustment(const TradingCentres& hol, BizDayConv bz, short del = 0):hols(hol),bzc(bz),delay(del){}
	dateAdjustment(const qm_string& hol, BizDayConv bzc, short del = 0):hols(hol),bzc(bzc),delay(del){}
	dateAdjustment(const dateAdjustment& adj):hols(adj.hols),bzc(adj.bzc),delay(adj.delay){}
    ~dateAdjustment(){}
    //
    TradingCentres  hols;
    BizDayConv      bzc;
    short			delay;
    
    qdate           adjust(const qdate& date) const  {
    	if(!delay) 	return hols.adjust(date,bzc);
    	else if(delay < 0)  {
    		qdate dte = hols.prevbizday(date,-delay);
    		return hols.adjust(dte,bzc);
    	}
    	else  {
    		qdate dte = hols.nextbizday(date,delay);
    		return hols.adjust(dte,bzc);
    	}
    }
    
    qdate parseinterval(const qdate& date, const period& pe) const  {
    	qdate dte = hols.parseinterval(date,pe,unadjusted);
       	return this->adjust(dte);
    }
    
    qdate adjtenure(const qdate& date, const qm_string& pe) const  {
    	return this->parseinterval(date,period(pe));
    }
    
    qm_string tostring() const {
    	return "hols: " + hols.code() + ", bzc: " + enumtostring(bzc) +
    		   ", delay: " + object_to_string(delay);
    }
};


//
/// \brief A single Trading Centre
///
/// A trading centre contains informations regarding the non-business days for a given calendar.
/// \ingroup finance
class tc: public TradingCentre  {
public:
	typedef std::vector<HolidayGen>  HolidayVector;
    //
    qm_string 		 code() const {return m_code;}
    bool             isbizday(const qdate& date) const;
    void             flush()       const                            {m_all_holidays.clear();}
    qm_Size          numholidays() const                            {return m_holidays.size();}
    
    /// \brief Retrive a ccy object from inline database
  	static TC       get(const qm_string& cod);
  	
  	/// \brief Return a list containing the names of all ccys objects
  	template<class L>
  	static L keys();
    //
protected:
    HolidayVector                                m_holidays;
    qm_string 								   	 m_code;
    qm_string									 m_name;
    mutable qm_short                             m_year_start;
    mutable qm_short                             m_year_end;
    mutable qm_holidays                          m_all_holidays;
    //
    tc(const qm_string& code, const qm_string& name): m_code(code), m_name(name), m_year_start(9999), m_year_end(0){}
    //
private:
    void generatedates(qm_short year) const;
};


    
QM_NAMESPACE_END


#endif  //  __TRADING_CENTRE_QM_HPP__

