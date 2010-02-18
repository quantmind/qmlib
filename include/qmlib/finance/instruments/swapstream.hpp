//
/// \file
/// \brief swapstream class definitions
/// \ingroup finance
//
#ifndef   __SWAP_DEFINITION_QM_HPP__
#define   __SWAP_DEFINITION_QM_HPP__


#include <qmlib/finance/irhelp.hpp>
#include <qmlib/irates.hpp>



QM_NAMESPACE2(finance)



class swapstream;
class streamAmount;
class iswap;
typedef QM_SMART_PTR(swapstream)    SWAPSTREAM;
typedef QM_SMART_PTR(streamAmount)  STREAMAMOUNT;
typedef QM_SMART_PTR(iswap)         SWAP;


/// \brief Base class for swapStream cash flow definition
/// \ingroup finance/swaps
class streamAmount  {
public:
	streamAmount(){}
    virtual ~streamAmount(){}
    //
    virtual CASHFLOW  reduced_cashflow(const CALCDATES& paym, const qdate& date) const {return full_cashflow(paym,date);}
    virtual CASHFLOW     full_cashflow(const CALCDATES& paym, const qdate& date) const = 0;
};

    
class ir_stream_amount: public streamAmount {
public:
    ir_stream_amount(const DC& dc):m_dc(dc){}
protected:
   	DC  m_dc;
};

    

/// \brief Fix leg for a vanilla ir swap
class vanilla_fixed_leg_stream_ammount: public ir_stream_amount {
public:
	vanilla_fixed_leg_stream_ammount(const DC& dc, qm_real notional, IVALUE coup):
		ir_stream_amount(dc),m_notional(notional),m_coup(coup){}
    CASHFLOW     full_cashflow(const CALCDATES& paym, const qdate& date) const;
protected:
    qm_real  m_notional;
    IVALUE   m_coup;
};


/// \brief Floating leg for a vanilla ir swap
class vanilla_float_leg_stream_ammount: public ir_stream_amount {
public:
	vanilla_float_leg_stream_ammount(const DC& dc, qm_real notional):
		ir_stream_amount(dc),m_notional(notional){}
    CASHFLOW     reduced_cashflow(const CALCDATES& paym, const qdate& date) const;
    CASHFLOW     full_cashflow(const CALCDATES& paym, const qdate& date) const;
protected:
    qm_real m_notional;
};





/// \brief A Swap Stream
///
/// A swapStream contains the elements required to define an individual swap leg.
/// A swap component contains one or more instances of the swapStream component (usually two).
/// \ingroup finance
class swapstream : public icodename {
public:
	swapstream(){}
    swapstream(const qm_string& code, const IRHELP& irh, const IRHELP& fix = IRHELP()):
    	m_code(code),m_irh(irh),m_irfixing(fix){}
    virtual ~swapstream(){}
    //
    /// \brief Evaluate the schedule of dates.
    virtual const CALCDATES calculationPeriodDates() const {return m_calc;}
    //
    /// \brief Payment Dates.
    /// The schedule of payment dates
    virtual const CALCDATES paymentDates() const {return m_payment;}
    //
    /// \brief Reset Dates.
    /// The sechedule of reset dates. This is available only for
    /// swapstream which fix to a certain index.
    virtual const CALCDATES resetDates() const {return CALCDATES();}
    //
    /// \brief the reduced cash flow
    /// @return a reduced cashflow, if it exists, which approximate the full cashflow
    ///  This is used for modelling and boostrapping
    virtual CASHFLOW reduced_cashflow(const qdate& date) const {QM_REQUIRE(m_amount,"Cash flow ammounts not specified"); return m_amount->reduced_cashflow(m_payment,date);}
    ///
    /// \brief the full cash flow
    virtual CASHFLOW    full_cashflow(const qdate& date) const {QM_REQUIRE(m_amount,"Cash flow ammounts not specified"); return m_amount->full_cashflow(m_payment,date);}
    //
    /// \brief Reset Dates.
    /// Contain the information necessary to construct a schedule of
    /// reset dates relative to the calculationPeriodDates(). resetDates() are
    /// implemented for floating swap Stream.
    //streamDates fixing() const {if(m_fixing) return m_fixing->generate(); return streamDates();}
    //
    qm_string     code()     const {return m_code;}
protected:
	CALCDATES     m_calc;
    CALCDATES     m_payment;
    STREAMAMOUNT  m_amount;
    qm_string     m_code;
    IRHELP		  m_irh;
    IRHELP		  m_irfixing;
};


    
    
/// \brief Class interface for a general swap product
///
/// \ingroup finance
class iswap  {
public:
    //
    typedef SWAPSTREAM                 value_type;
    typedef std::vector<value_type>    container;
    typedef container::iterator        iterator;
    typedef container::const_iterator  const_iterator;
    //
    iswap(){}
    virtual ~iswap(){}
    //
    bool              empty()       const {return m_legs.empty();}
    qm_Size           size()        const {return m_legs.size();}
    value_type&       get(unsigned i)     {QM_REQUIRE(i<size(),"iswap, Out of bound"); return m_legs[i];}
    iterator          begin()             {return m_legs.begin();}
    iterator          end()               {return m_legs.end();}
    const_iterator    begin()       const {return m_legs.begin();}
    const_iterator    end()         const {return m_legs.end();}
    
protected:
	CASHFLOW reduced_cashflow(const qdate& dte) const;
	void push_back(const value_type& val) {m_legs.push_back(val);}
    container   m_legs;
    iswap(const iswap& rhs){}
};




/// \brief The fixed leg of a vanilla interest rate swap
///
/// \ingroup finance
class FixLegInterestRateSwap: public swapstream   {
public:
	///
    /// \brief Construct The fixed leg of a vanilla interest rate swap.
    /// 
    ///
    /// A vanilla Fixed rate swapstream satisfies the following conditions
    ///  - the fixed rate reamains constant throughout the life of the swap
    ///  - Constant notional
    ///  - Payments occur at the calculation dates (same adjustment)
    /// @param start Start date, the effective date. This date must be a valid business day
    /// @param end   End date, the last coupon date (unadjusted)
    /// @param firstPeriodStart The date from which the first period is calculated
    /// @param firstRegDate First coupon date if a non regular period is present
    /// @param lastRegDate Last regular coupon date
    /// @param tenure Fix rate frequency in the regular period, in months
    /// @param tcs A TradingCentres object
    /// @param dc DayCounts pointer
    /// @param bzc The BizDayConv for adjusting non-business days
    /// @param notional The leg notional
    /// @param rate The interest rate in percentage (for example 4.5)
    FixLegInterestRateSwap(const datebasket&       dates,
                           const IRHELP&           irh,
                           qm_real                 notional,
                           const IVALUE&           rate);
};





    /// \brief The floating leg of a Interest Rate Swap
    ///
    /// \ingroup finance
class FloatingLegInterestRateSwap: public swapstream    {
	public:
    
    /** \brief Construct a standard vanilla floating rate Leg
     * 
     * A standard vanilla Fix rate swapstream satisfies the following conditions
     *  - the term of the swap is a whole number of years
  	 *  - start date and end date are regular dates
  	 *  - the fixed rate reamains constant throughout the life of the swap
  	 *  - Constant notional
  	 * @param dates A datebasket
  	 * @param irh An irhelp pointer for the floating leg
  	 * @param irfixing An irhelp pointer for the fixing frequency
  	 * @param notional The leg notional
  	 */
    FloatingLegInterestRateSwap(const datebasket&       dates,
                                const IRHELP&           irh,
                                const IRHELP&           irfixing,
                                qm_real                 notional);
};


QM_NAMESPACE_END2

#include <qmlib/finance/instruments/impl/swapstream_impl.hh>

#endif  //  __SWAP_DEFINITION_QM_HPP__

