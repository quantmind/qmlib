//
/// \file
/// \brief Declaration of main interfaces for finance
/// \ingroup rates
//
#ifndef   __BOOTSTRAP_COMPOSITE_QM_HPP__
#define   __BOOTSTRAP_COMPOSITE_QM_HPP__

#include <qmlib/qmat/linalg.hpp>
#include <qmlib/corelib/tools.hpp>


QM_NAMESPACE2(math)


enum booststrap_type {
	linear,
	exponential,
	logarithmic
};

template<class T, booststrap_type D> struct booststrap_function  {};


template<class T>
class booststrap_function<T,linear>  {
public:
	typedef T			numtype;
	static numtype func(numtype x, numtype u) {return x;}
	static numtype dfdx(numtype x, numtype u) {return 1.0;}
	static numtype inve(numtype f, numtype u) {return f;}
};

template<class T>
struct booststrap_function<T,logarithmic>  {
	typedef T			numtype;
	static numtype func(numtype x, numtype t)  {return  std::exp(x);}
	static numtype dfdx(numtype x, numtype t)  {return  std::exp(x);}
	static numtype inve(numtype f, numtype t)  {return  std::log(f);}
};


template<class S, booststrap_type D>
class discount_bootstrap  {
	typedef S									support_type;
	typedef typename support_type::numtype		numtype;
	typedef booststrap_function<numtype, D>		function_type;
	typedef qmatrix<numtype>					rhstype;
	typedef rhstype								vectype;
	typedef qmatrix<numtype,lower_triangular>	lhstype;
public:
	discount_bootstrap(){}
	numtype	 value(numtype x) const {return function_type::func(m_support.value(x),x);}
	unsigned size()           const {return m_support.size();}
	void add(numtype x, numtype y)  {m_support.add(x,function_type::inve(y,x));}
	void build(const lhstype& lhs, const rhstype& rhs, const vectype& drhs);

	itersolver& get_solver() {return m_solver;}
private:
	support_type  m_support;
	vectype       m_offsens;
	itersolver	  m_solver;
};


QM_NAMESPACE_END2


#endif  //  __YIELD_COMPOSITE_QM_HPP__
//

