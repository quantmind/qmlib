//
/// @defgroup enums
/// @defgroup finance
/// \file
/// \brief Definition of enums used in qmlib
/// \ingroup enums


#ifndef   __FIN_ENUMS_QM_HPP__
#define   __FIN_ENUMS_QM_HPP__


#include <qmlib/corelib/tools/string.hpp>


/*! \defgroup static Static Financial library

    Classes and enumeration used in the Finance library

    @{
*/

/// \file
/// \brief Core Enumeration File



QM_NAMESPACE


/// \brief Day Count conventions
///
/// Day count convention is a method to calculate the fraction of a year between two dates.
/// It is used in the calculation of accrued interest, and in many other formulae in financial mathematics.
enum DayCountType  {
	/// \brief Act/360 or Actual/360
    /// This convention used in money markets for short-term lending of currencies.
    /// Each month is treated normally and the year is assumed to be 360 days
    _Act360 = 0,
    /// \brief Act/365 Fixed or Actual/365 Fixed
    /// This convention is used by government bonds issued by most countries, including
    /// the U.K., Canada, Australia, and New Zealand. Each month is treated normally
    /// and the year is assumed to have 365 days, regardless of leap year status.
    _Act365,
    /// \brief Act/Act or Actual/Actual
    /// Each month is treated normally, and the year has the usual number of days.
    _ActAct,
    /// \brief 30/360
    /// This convention is used by municipal bonds and corporate bonds. Each month is treated as having 30 days,
    /// so a period from February 1, 2005 to April 1, 2005 is considered to be 60 days.
    /// The year is considered to have 360 days.
    /// This convention is frequently chosen for ease of calcuation: the payments tend to
    /// be regular and at predictable amounts.
    _30_360,      // Bond or 30/360
    _30_360E,     // Eurobond or 30/360
    _30_360Ep,    // Eurobond + or 30/360
    _30_360I,     // Italian 30/360
    //_ExtExt,      // Exact/Exact (French day count)
    //_Act365JGB,   // Interval is no. of full coup pds divided by coup freq plus Actual/365 remainder
    //_WholeMonths, // Round to nearest whole no. of months & divide by 12
    //_Act365JGB2   // Same as  Act365JGB but pure Act/365 unless in final coup period
};
    
    
    
/**\brief Business Day conventions
 * 
 * These conventions specify the algorithm used to adjust a date in case
 * it is not a valid business day. The first three are ISDA conventions (http://www.isda.org/)
 * \ingroup enums
 */
enum BizDayConv  {
	/// \brief (ISDA) Following Business Day Convention:
    /// choose the first business day after the given holiday
    foll,
    /// \brief (ISDA) Modified Following Business Day Convention:
    /// choose the first business day after the given holiday unless it belongs
    /// to a different month, in which case choose the first business day before the holiday
    modfoll,
    /// \brief (ISDA) Preceding Business Day Convention:
    /// choose the first business day before the given holiday
    prec,
    /// \brief (Non ISDA) Modified Preceding Business Day Convention:
    /// choose the first business day before the given holiday unless it belongs
    /// to a different month, in which case choose the first business day after the holiday
    modprec,
    /// \brief (Non ISDA) Do not adjust
    unadjusted,
};
inline qm_string enumtostring(BizDayConv bzc)  {
	switch(bzc)  {
		case foll:			return "following";
		case modfoll:		return "modified following";
		case prec:			return "preceding";
		case modprec:		return "modified preceding";
		case unadjusted:	return "unadjusted";
		default:	return "unadjusted";
	}
}
    
    
    inline BizDayConv parseBizDayConv(const qm_string& cod)  {
    	qm_string va = qmstring::lowercase(cod);
    	if(va == "foll") return foll;
    	else if(va == "modfoll") return modfoll;
    	else if(va == "prec") return prec;
    	else if(va == "modprec") return modprec;
    	else return unadjusted;
    }

/// \brief Coumpound frequency
/// \ingroup enums
enum frequency  {
	dayly = 0,
    weekly,
    monthly,
    bimonthly,
    quarterly,
    semiannually,
    annually,
    frequency_none,
};

    
inline qm_string frequency_to_string(int freq)  {
   	switch(freq)  {
   		case   0: return "continuous";
   		case  -1: return "dayly";
   		case  -7: return "weekly";
   		case   1: return "monthly";
   		case   2: return "bimonthly";
   		case   3: return "quarterly";
   		case   6: return "semiannually";
   		case  12: return "annually";
   		default: return "none";
   	}
}
    //
    //
    enum security_type  {
    	imm_3m_irfuture = 0,
    };
    
    enum optioninputtype  {
    	price_ = 0,
    	blackvol_,
    	bpvol_,
    };
    //
    /// \brief Composite Rate Subfixes
    ///
    /// This enum specifies a set of identifier for composite rates
    /// \ingroup enums
    enum compositeRateSubfix  {
      /// \brief Swap Yield Curve
      /// A swap yield curve will have a code CCYSYC where CCY is a currency code
      SYC = 0,
      /// \brief Overnight Index Swap Curve
      /// An overnight index swap curve CCYOIC where CCY is a currency code
      OIC,
      /// \brief Cap Volatility Surface
      CAP,
      NO_SUBFIX,
    };
    //
    //
    enum SettlementType
    {
      cash_settlement = 0,
      physical_settlement,
    };
    
    /*
    inline optiontype char_to_optiontype(char c)  {
    	return std::tolower(c) == 'p' ? Put_ : Call_;
    }
    inline optiontype string_to_optiontype(const qm_string& c)  {
    	if(c.length() == 0) return Call_;
    	else return char_to_optiontype(c[0]);
    }
    inline qm_string optiontype_to_string(optiontype c)  {
    	if(c == Call_) return "call";
    	else return "put";
    }
    */
    
    /*
	/// \brief Parse a string into a vanillaoptiontype
	inline optiontype parsevanillatype(const qm_string& typ)  {
		if(typ.length() == 0) return Call_;
		char f = std::tolower(typ[0]);
		if(f == 'c') return Call_;
		else if(f == 'p') return Put_;
		else if(f == 's') return Straddle_;
		else if(f == 'd') {
			QM_FAIL("Digital option not available yet");
		}
		else QM_FAIL("Option type not available");
	}
	*/
	
QM_NAMESPACE_END

/*! @} */
    
//
#endif  // __FIN_ENUMS_QM_HPP__
//

