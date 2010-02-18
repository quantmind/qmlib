
#ifndef   __CALC_DATES_QM_H__
#define   __CALC_DATES_QM_H__

/// \file
/// \brief calcDates class definitions
/// \ingroup finance


#include <qmlib/corelib/templates/containers.hpp>


QM_NAMESPACE

class periodDates;
class streamDateItem;
typedef QM_SMART_PTR(periodDates)         CALCDATES;
typedef QM_SMART_PTR(streamDateItem)      STREAMDATE;

    

/// \brief The stream Date
///
/// This class define a date for a particular stream. It includes
///  - value, 		The date value
///	 - m_adj,		The date adjustment
///  - m_relative,	A vector of streamDateItem smart pointer which contains dates which are connected to the current stramDateItem
class streamDateItem  {
public:
	typedef std::vector<STREAMDATE>		container;

	streamDateItem(const qdate& sd, const ADJ& adj, const qm_string& code = ""):date(sd),m_code(code),m_adj(adj){}
	streamDateItem(const qdate& sd, const ADJ& adj, const STREAMDATE& pd):date(sd),m_adj(adj){
		m_relative.push_back(pd);
	}
	streamDateItem(const qdate& sd, const ADJ& adj, const container& pd):date(sd),m_adj(adj){
		for(container::const_iterator it=pd.begin();it!=pd.end();++it)
			m_relative.push_back(*it);
		}
	qdate	             date;
    //
	const qdate&         datev()			  const {return date;}
    qdate                adjusted()           const {if(m_adj) return m_adj->adjust(date); return date;}
    const qm_string&     code()               const {return m_code;}
    qm_real              dcf(const DC& dc, unsigned i=0) const;
    unsigned             nrelative()	      const {return m_relative.size();}
    const STREAMDATE&    relative(unsigned i) const {return m_relative[i];}
    qdate				 adjustdate(const qdate& dte)  const {return m_adj ? m_adj->adjust(dte) : dte;}
    void                 push_back(const STREAMDATE& pd) {m_relative.push_back(pd);} 
    //
    void set_code(const qm_string& cod) {m_code = cod;}
    //
    qm_string tostring() const {return date.tostring();}
    //
protected:
	container	      m_relative;
	qm_string         m_code;
    ADJ               m_adj;
};



/// \brief A basket of 5 dates defining a cashflow
///
///   - effectiveDate (or start date)
///   - terminationDate The termination date (or end date)
///   - firstRegDate The first regular date, it must be >= effectiveDate
///   - firstPeriodStart used only if first period is not regular
///   - lastRegDate The last regular date, must be <= terminationDate
///
///  If firstRegDate > effectiveDate than the effectiveDate is a non-relevant date and it is replaced
///  by the firstPeriodStart. In this case the effectiveDate is there only for completness.
/// \ingroup finance
class datebasket  {
public:
	datebasket(const qdate& start, const qdate& end):effectiveDate(start),terminationDate(end),firstPeriodStart(start),
                                                     firstRegDate(start),lastRegDate(end){}
    datebasket(const qdate& start,      const qdate& end,
               const qdate& firstStart, const qdate& firstReg,
               const qdate& lastReg):effectiveDate(start),terminationDate(end),firstPeriodStart(firstStart),
                                     firstRegDate(firstReg),lastRegDate(lastReg){}
    datebasket(const datebasket& rhs) {copy(rhs);}
    ~datebasket(){}
    //
    datebasket& operator = (const datebasket& rhs) {copy(rhs);return *this;}
    bool isfirstregular() const {return effectiveDate   == firstRegDate;}
    bool islastregular()  const {return terminationDate == lastRegDate;}
    //
    qdate   effectiveDate;
    qdate   terminationDate;
    qdate   firstPeriodStart;
    qdate   firstRegDate;
    qdate   lastRegDate;
protected:
    void copy(const datebasket& b)  {
        effectiveDate      = b.effectiveDate;
        terminationDate    = b.terminationDate;
        firstPeriodStart   = b.firstPeriodStart;
        firstRegDate       = b.firstRegDate;
        lastRegDate        = b.lastRegDate;
    }
};



/// \brief Base class for period Dates calculaticalcDateson
/// \ingroup finance
class periodDates  {
public:
	typedef STREAMDATE	                		value_type;
    typedef std::vector<value_type>       		container;
    typedef container::iterator           		iterator;
    typedef container::const_iterator     		const_iterator;
    //
    /// \brief Constructor
    ///
    /// @param code A string code for the periodDates calculator
    /// @param freq A smart pointer to a dateFrequency object
    /// @param adj A dateAdjustment object
    periodDates(const qm_string& cod, const period& freq, const ADJ& adj):
          m_code(cod),m_freq(freq),m_adj(adj){}
    periodDates(const qm_string& cod, const period& freq, const ADJ& adj, const CALCDATES& rel):
                m_code(cod),m_freq(freq),m_adj(adj),m_rel(rel){}
    virtual ~periodDates(){}
    //
    /// \brief code string
    qm_string                   code()           const {return m_code;}
    /// \brief The string representing the tenure of the frequency of regular dates
    qm_string                   frequency()      const {return m_freq.tostring();}
    unsigned                    monthfreq()      const {return m_freq.totalmonths();}
    
    const value_type& operator [] (unsigned i) const {QM_REQUIRE(i<this->size(),"Out of bounds"); return m_stream[i];}
    //
    qm_Size         size()  const {return m_stream.size();}
    bool            empty() const {return m_stream.empty();}
    iterator        begin()       {return m_stream.begin();}
    iterator        end()         {return m_stream.end();}
    const_iterator  begin() const {return m_stream.begin();}
    const_iterator  end()   const {return m_stream.end();}
    //
    template <class L>
    L datelist() const;
protected:
    qdate           addfrequency(const qdate& date) const;
    STREAMDATE      add(const qdate& dte, const ADJ& adj, const qm_string& code);
    qm_string       m_code;
    period          m_freq;
    ADJ             m_adj;
    CALCDATES       m_rel;
    container       m_stream;
};




/// \brief The swap date calculation class
///
/// The main class for swap date claculation. This class calculate all the dates in a swapstream
/// which fully defined a iswap leg. All other dates, such as payment dates, reset dates and fixing dates
/// depend, in a way or another, on calcDates.
/// \ingroup finance
class calcDates: public periodDates {
public:

/// \brief Factory constructor
/// @param code A string code
/// @param dates A datebasket object defining the key dates for calcDates
/// @param freq A the frequency of dates in the regular period
/// @param tcs The TradingCentres used for adjusting dates
/// @param bzc The BizDayConv for udjusting non-business days
	static CALCDATES create(const qm_string&       cod,
                            const datebasket&      dates,
                            const qm_string&       freq,
                            const TradingCentres&  tcs,
                            BizDayConv             bzc){
		ADJ adj(new dateAdjustment(tcs,bzc));
		return CALCDATES(new calcDates(cod,dates,period(freq),adj));
	}
	static CALCDATES create(const qm_string&       cod,
                            const datebasket&      dates,
                            const period&          freq,
                            const ADJ&  		   adj){return CALCDATES(new calcDates(cod,dates,freq,adj));}
    //
    static CALCDATES create0(const qm_string&       cod,
                             const qdate&           start,
                             const qdate&           end,
                             const qm_string&       freq,
                             const qm_string&       tcs,
                             const qm_string&       bzc) {
    	ADJ adj(new dateAdjustment(tcs,parseBizDayConv(bzc)));
    	return CALCDATES(new calcDates(cod,datebasket(start,end),period(freq),adj));
    }
    static CALCDATES create1(const qm_string&       cod,
                             const qdate&           start,
                             const qdate&           end,
                             const qm_string&       freq,
                             const qm_string&       tcs,
                             BizDayConv             bzc) {
    	ADJ adj(new dateAdjustment(tcs,bzc));
    	return CALCDATES(new calcDates(cod,datebasket(start,end),period(freq),adj));
    }
    static CALCDATES create2(const qm_string&       cod,
                             const qdate&           start,
                             const qdate&           end,
                             const qdate&           firstStart,
                             const qdate&           firstReg,
                             const qdate&           lastReg,
                             const qm_string&       freq,
                             const ADJ&				adj) {
    	return CALCDATES(new calcDates(cod,datebasket(start,end,firstStart,firstReg,lastReg),period(freq),adj));
    }
    //
    /// \brief the key dates of a calcDates
    const datebasket&  dates()    const {return m_dates;}
protected:
    datebasket                      m_dates;
    //
    void generate();
    //
    calcDates(const qm_string&       cod,
              const datebasket&      dates,
              const period&          freq,
              const ADJ&             adj):periodDates(cod,freq,adj),m_dates(dates){generate();}
};




/// \brief Calculate dates relative to a given streamDates starting from the enddate
/// \ingroup finance
class relativeDates: public periodDates  {
public:
	relativeDates(const qm_string& cod,
                  const period& freq,
                  const ADJ& adj,
                  bool  relativeToStart,
                  const CALCDATES& rel):
                    periodDates(cod,freq,adj,rel),m_relToStart(relativeToStart)  {
		QM_REQUIRE(m_rel,"calculation dates not available");
		generate();
	}
	relativeDates(const qm_string& cod,
                  const period& freq,
                  const period& freq_reset,
                  const ADJ& adj,
                  const ADJ& adj_reset,
                  bool  relativeToStart,
                  const CALCDATES& rel):
                    periodDates(cod,freq,adj,rel),m_relToStart(relativeToStart)  {
		QM_REQUIRE(m_rel,"calculation dates not available");
		generate_with_resets(freq_reset,adj_reset);
	}
    void generate();
    void generate_with_resets(const period& freq_reset, const ADJ& adj_reset);
protected:
    bool m_relToStart;
};




#include<qmlib/corelib/static/impl/calcDates_impl.hh>




QM_NAMESPACE_END


#endif  //  __CALC_DATES_QM_H__

