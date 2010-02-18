
#ifndef __QMAT_QMAT_HPP__
#define __QMAT_QMAT_HPP__


#include <qmlib/corelib/math.hpp>
#include <qmlib/corelib/tools/tools.hpp>
#include <climits>


/// \defgroup qmat qmatrix library
///
/// The qmatrix library has been designed for optimal number crunching performance


/// \file
/// \brief Header file for qmatrix library
/// \ingroup qmat


#ifdef	_DEBUG_

#	define	QMAT_PRECONDITION(X,Y)	QM_ASSERT(X,Y)

#else

#	define	QMAT_PRECONDITION(X,Y)

#endif


QM_NAMESPACE2(math)


template<class T, class S> class qmatrix;
template<class T, class S> class qmatrix_ref;




QM_NAMESPACE_END2


#endif	//	__QMAT_QMAT_HPP__



