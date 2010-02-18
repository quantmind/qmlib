//
//
#ifndef   __CONSTANTS_QM_HPP__
#define   __CONSTANTS_QM_HPP__
//
//
#include <qmlib/corelib/tools/string.hpp>


QM_NAMESPACE

inline qm_real Infinity()  {
	return std::numeric_limits<qm_real>::infinity();
}

inline bool isInfinity(qm_real x)  {
	return x == Infinity();
}

QM_NAMESPACE_END


QM_NAMESPACE2(math)
	
/// \brief Generate first N prime numbers
///
/// A prime number is a  natural number  greater than 1 that can be divided evenly only by 1 and itself.
template<unsigned long N>
inline std::vector<unsigned long> GeneratePrimeNumbers()  {
	std::vector<qm_uns_long> r;
	unsigned long i, n, p;
	unsigned long m = 2;
	r.push_back(m);
		
	for(unsigned long l=1;l<N;l++)  {
		do {
			i = 0;
		    ++m;
		    n = static_cast<unsigned long>(std::sqrt(qm_real(m)));
		    do {
		    	p = r[i];
		        ++i;
		    } while ( m%p && p<=n );
		} while ( p<=n );
		r.push_back(m);
	}
	return r;
}
	
static const std::vector<qm_uns_long> primenums = GeneratePrimeNumbers<10000>();
	
class constlist  {
public:
	static unsigned long primenum(unsigned long i) {QM_REQUIRE(i<primenums.size(),"Out of bound"); return primenums[i];}
};
		
	
QM_NAMESPACE_END2

#endif	//	__CONSTANTS_QM_HPP__

