

#ifndef __ALL_RNDGEN_QM_HPP__
#define __ALL_RNDGEN_QM_HPP__



#include <qmlib/math/random/lowdiscrepancy.hpp>

QM_NAMESPACE2(math)

#include <qmlib/math/random/impl/mersenneTwister_impl.hh>
#include <qmlib/math/random/impl/sobol_impl.hh>

inline qdate randomdate(RNDGEN gen, qdate start, qdate end)  {
	qm_real d = qdate::daydiff(start,end);
	QM_REQUIRE(d>0,"Dates are not correct for random generation");
	unsigned dr = (unsigned)(gen->nextUniform()*d);
	qdate re = start;
	re.add_days(dr);
	return re;
}

QM_NAMESPACE_END2


#endif  //  __ALL_RNDGEN_QM_HPP__

