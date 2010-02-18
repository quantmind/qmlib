//
/// \file
/// \brief Comparisons for several simple types
//
#ifndef __COMPARISON_QM_H__
#define __COMPARISON_QM_H__

#include <qmlib/corelib/dates/daycount.hpp>
//#include <qmlib/definitions.hpp>
#include <boost/limits.hpp>



QM_NAMESPACE
    

/// \brief Difference beweent x and y
template<class T>
inline qm_real realdiff(const T& x, const T& y)  {
	return 0;
}
	
template<>
inline qm_real realdiff<qm_real>(const qm_real& x, const qm_real& y)  {
	return x - y;
}
		
template<>
inline qm_real realdiff<qdate>(const qdate& x, const qdate& y)  {
	return qm_real(qdate::daydiff(x,y))/365.0;
}


/// \brief Distance between x and y
template<class T>
inline qm_real distance(const T& x, const T& y)  {
	return std::fabs(realdiff(x,y));
}
	
/// \brief True if x and y are close enough computational-wise	
template<class T>
inline bool close_enough(const T& x, const T& y, qm_Size n = 42) {
	return x == y;
}
    ///
    /// Follows somewhat the advice of Knuth on checking for floating-point equality.
    /// The closeness relationship is:
    ///
    /// \f$\mathrm{close_enough}(x,y,n) \equiv |x-y| \leq \varepsilon |x| \vee |x-y| \leq \varepsilon |y| \f$
    /// where \f$ \varepsilon \f$ is \f$ n \f$ times the machine accuracy;
    /// \f$ n \f$ equals 42 if not given.
    /// \ingroup math
	//
	template<>
	inline bool close_enough<qm_real>(const qm_real& x, const qm_real& y, qm_Size n) {
		qm_real diff      = distance(x,y);
	    qm_real tolerance = n*std::numeric_limits<qm_real>::epsilon();
	    return diff <= tolerance*std::fabs(x) &&
	           diff <= tolerance*std::fabs(y);
	}
	
	template<>
	inline bool close_enough<qdate>(const qdate& x, const qdate& y, qm_Size n)  {
		static const qm_real onesec = 1.0/(365*24*60*60);
		qm_real diff = distance(x,y);
		if(diff < n*onesec) return true;
		else return false;
	}
    //
}
//
#endif  //  __COMPARISON_QM_H__
