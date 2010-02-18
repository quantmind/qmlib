


#ifndef   __PAYOFF_ENUMS_QM_HPP__
#define   __PAYOFF_ENUMS_QM_HPP__



#include <boost/numeric/interval.hpp>
#include <qmlib/qmat/tiny.hpp>
#include <qmlib/math/numbers/constants.hpp>

/** \defgroup payoff Option payoff library
 * 
 * Class templates for handling general option payoffs
 * 
 * @{
 */


/** \file
 * \brief Base class templates for an Option Payoff
 * 
 */



QM_NAMESPACE

/** \brief Payoff type
 * 
 * Definition of payoff types. 
 */
enum payofftype  {
	/// A standard vanilla payoff.
	/// This type of payoff depends only on the value of
	/// the underlying at exercise.
    Vanilla_ = 0,
	/// An average Payoff - Path dependent 
	/// This type of payoff depends on some sort of averaging of the underlying
    /// during the option's life. Asian and lookback options are examples of this type
    /// of payoff.
    Average_,
	/// A barrier Payoff
	/// This type of payoff depend on one or more barriers.
    /// It is a weak path-dependent payoff since it does not require
    /// the calculation of any path-dependent quantity.
    Barrier_,
};

/** Barrier Type
 */
enum barriertype  {
	/// A barrier which knock an option out
	KnockOut_ = 0,
	/// A barrier which knock an option in
	KnockIn_,
};


/** \brief List of implemented Payoffs function
 */
enum payoffname  {
	CALL_ = 0,
	PUT_,
	BINARY_CALL_,
	BINARY_PUT_,
	UP_AND_OUT_,
	UP_AND_IN_,
	DOWN_AND_OUT_,
	DOWN_AND_IN_,
	DOUBLE_NO_TOUCH_,
	DOWN_AND_OUT_CALL_,
	DOWN_AND_IN_CALL_,
	UP_AND_OUT_CALL_,
	UP_AND_IN_CALL_,
	DOWN_AND_OUT_PUT_,
	DOWN_AND_IN_PUT_,
	UP_AND_OUT_PUT_,
	UP_AND_IN_PUT_,
	BINARY_CALL_CALL_,
	BINARY_PUT_PUT_,
	DOUBLE_BINARY_CALL_PUT_,
	WORSEOF_CALL_CALL_,
	WORSEOF_PUT_PUT_,
	WORSEOF_CALL_PUT_,
	UNKNOWN_PAYOFF_,
};


QM_NAMESPACE_END

/*! @} */


#endif	//	__PAYOFF_ENUMS_QM_HPP__

