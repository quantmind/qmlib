

#ifndef __BASE_RNDGEN_QM_HPP__
#define __BASE_RNDGEN_QM_HPP__

/** Header file for random library
 */

#include <qmlib/corelib/dates/date.hpp>
#include <qmlib/math/stat/all.hpp>


QM_NAMESPACE2(math)

class rndgen;
class SeedGenerator;
class sobol1;

typedef QM_SMART_PTR(rndgen) 			RNDGEN;


typedef sobol1				 			default_rndgen;
typedef std::vector<qm_uns_long>  		qm_ulvector;

QM_NAMESPACE_END2


#endif  //  __BASE_RNDGEN_QM_HPP__


