
#ifndef   __MATH_LIGHT_QM_HPP__
#define   __MATH_LIGHT_QM_HPP__

#include<qmlib/definitions.hpp>

QM_NAMESPACE


template<class T>
struct qmoper  {
	static qm_real abs(const T& x)  {return std::abs(x);}
};

template<class T>
struct rounding {};

template<>
struct rounding<qm_real> {
	static qm_real doit(qm_real x, unsigned precision)  {
		qm_real b   = std::pow(10.,int(precision));
		qm_real bx  = b*x;
		qm_real n   = std::floor(bx);
		qm_real re  = bx - n;
		//long	n  = static_cast<long>(bx);
		if(re > 0.5) n+=1;
		else if(re<-0.5) n-=1;
		return n/b;
	}
};

template<class T>
inline T round(const T& x, unsigned precision)  {
	return rounding<T>::doit(x,precision);
}

template<class T>
inline qm_real change(const T& x, const T& dx)  {
	qm_real dxa = qmoper<T>::abs(dx);
	qm_real xa  = qmoper<T>::abs(x);
	return xa > 0 ? dxa/xa : dxa;
}

QM_NAMESPACE_END


#endif  //  __MATH_LIGHT_QM_HPP__

