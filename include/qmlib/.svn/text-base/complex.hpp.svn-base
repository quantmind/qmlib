

#ifndef   __COMPLEX_NUMBER_QM_HPP__
#define   __COMPLEX_NUMBER_QM_HPP__


#include <complex>
#include <qmlib/corelib/math.hpp>
#include <qmlib/corelib/tools/string.hpp>
#include <boost/math/complex/details.hpp>


QM_NAMESPACE

typedef std::complex<qm_real>	qm_complex;

//template<>
template<typename T>
struct object_to_string_o<std::complex<T> > {
	static qm_string get(const std::complex<T>& obj)  {
		if(obj.imag() >= 0)
			return object_to_string(obj.real())+"+"+object_to_string(obj.imag())+"j";
		else
			return object_to_string(obj.real())+object_to_string(obj.imag())+"j";
	}
};


	
template <class T>
inline std::complex<T> mult_i(const std::complex<T>& t) 	{
   return std::complex<T>(boost::math::detail::mult_minus_one(t.imag()), t.real());
}

template<class T>
inline qm_real qmrabs(const T& v)  {
	return std::abs(v);
}

template<>
struct qmoper<qm_complex>  {
	static qm_real abs(const qm_complex& x) {
		return std::sqrt(x.real()*x.real() + x.imag()*x.imag());
	}
};


/*
template<class Archive>
inline void load(Archive& ar, qm_complex& c, const unsigned int version)  {
	qm_real rr,cc;
	ar & rr;
	ar & cc;
	c = qm_complex(rr,cc);
}
*/
//BOOST_SERIALIZATION_SPLIT_MEMBER()

//
/*
namespace QMLib {
//
  class complex  {
  private:
    real m_r;
    real m_c;
  public:
    void Init(real r, real c) {m_r=r; m_c=c;}
    complex(real r = 0, real c = 0){Init(r,c);}
    complex(const complex& rval){Init(rval.m_r,rval.m_c);}
    ~complex(){}
//
    complex& operator =  (const complex& rval) {Init(rval.m_r,rval.m_c); return *this;}
    complex& operator =  (real rval)            {Init(rval,0); return *this;}
    complex& operator += (const complex& rval) {m_r += rval.m_r; m_c += rval.m_c; return *this;}
    complex& operator -= (const complex& rval) {m_r -= rval.m_r; m_c -= rval.m_c; return *this;}
    QMDLL complex& operator *= (const complex& rval);
    QMDLL complex& operator /= (const complex& rval);
//
    complex& operator += (real rval) {m_r += rval; return *this;}
    complex& operator -= (real rval) {m_r -= rval; return *this;}
    complex& operator *= (real rval) {m_r *= rval; m_c *= rval; return *this;}
    complex& operator /= (real rval) {m_r /= rval; m_c /= rval; return *this;}
//
    real     Real() const {return m_r;}
    real     Cplx() const {return m_c;}
    real     Abs()  const {return sqrt(m_r*m_r + m_c*m_c);}
    real     Arg()  const {return atan2(m_c,m_r);}
    complex  Log()  const {return complex(log(Abs()),Arg());}
    complex  Exp()  const {return exp(m_r)*complex(cos(m_c),sin(m_c));}
    complex  Pow(real expn) const {complex re = expn*Log(); return re.Exp();}
//
    friend complex operator - (const complex& rval)                      {complex re; return  re -= rval;}
    friend complex operator + (const complex& lval, const complex& rval) {complex re(lval); return  re += rval;}
    friend complex operator + (real lval,           const complex& rval) {complex re(lval); return  re += rval;}
    friend complex operator + (const complex& lval, real rval)           {complex re(lval); return  re += rval;}
    friend complex operator - (const complex& lval, const complex& rval) {complex re(lval); return  re -= rval;}
    friend complex operator - (real lval,           const complex& rval) {complex re(lval); return  re -= rval;}
    friend complex operator - (const complex& lval, real rval)           {complex re(lval); return  re -= rval;}
    friend complex operator * (const complex& lval, const complex& rval) {complex re(lval); return  re *= rval;}
    friend complex operator * (real lval,           const complex& rval) {complex re(lval); return  re *= rval;}
    friend complex operator * (const complex& lval, real rval)           {complex re(lval); return  re *= rval;}
    friend complex operator / (const complex& lval, const complex& rval) {complex re(lval); return  re /= rval;}
    friend complex operator / (real lval,           const complex& rval) {complex re(lval); return  re /= rval;}
    friend complex operator / (const complex& lval, real rval)           {complex re(lval); return  re /= rval;}
    
  private:
      real m_r;
      real m_c;
  };
}
*/


QM_NAMESPACE_END


#ifdef QM_SERIALIZE

namespace boost {
namespace serialization {

template<class Archive, typename T>
inline void serialize(Archive& ar, std::complex<T>& c, const unsigned BOOST_PFTO int version)  {
	ar & c.real();
	ar & c.imag();
}

}}

#endif	// QM_SERIALIZE


#endif  //  __COMPLEX_NUMBER_QM_HPP__
