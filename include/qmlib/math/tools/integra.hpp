


#ifndef __INTEGRA_QM_HPP__
#define __INTEGRA_QM_HPP__


#include <qmlib/corelib/tools/string.hpp>


/// \file
/// \brief Spline classes including th cubic spline
/// \ingroup math
//


QM_NAMESPACE2(math)


class simpson1d : public basedes {
public:
	typedef boost::function<qm_real (qm_real x)>  funtype;
	
	simpson1d(qm_real dx):m_dx(dx),m_mult(4,0,2){QM_REQUIRE(m_dx>0,"dx must be positive");}
	qm_string tostring() const {return "Simpson rule";}
	qm_real integra(funtype f, qm_real t0, qm_real t1) const;
protected:
	qm_real 			m_dx;
	tinyvec<unsigned,3> m_mult;
};

inline qm_real simpson1d::integra(funtype f, qm_real x0, qm_real x1) const  {
	if(x1<=x0) return 0;
	unsigned Nt(std::max((int)std::ceil((x1-x0)/m_dx),2));
	unsigned N = 2*(Nt/2) == Nt ? Nt : Nt+1;
	unsigned n;
	qm_real dx = (x1-x0)/N;
	qm_real g  = f(x0)+f(x1);
	qm_real x  = x0;
	unsigned m = 2;
	for(n=1;n<N;++n)  {
		x += dx;
		m  = m_mult[m-2];
		g += m*f(x);
	}
	return dx*g/3.;
}

QM_NAMESPACE_END2



#endif // __INTEGRA_QM_HPP__


