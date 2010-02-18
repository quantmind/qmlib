


#ifndef   __FFTW_TYPES_QM_HPP__
#define   __FFTW_TYPES_QM_HPP__

#include <qmlib/math/fourier/fourier.hpp>
#include <fftw3.h>

QM_NAMESPACE2(math)

template<unsigned D, typename T>
class fourier;


template<typename T> struct fftwblock 	   {const static bool ok = false;};
template<> struct fftwblock<double>  	   {const static bool ok = true;};
template<> struct fftwblock<fftw_complex>  {const static bool ok = true;};

template<typename T>
struct fftwconvert {
	const static bool ok = false;
};

template<>
struct fftwconvert<double>  {
	typedef double	numtype;
	typedef double  fftwtype;
	const static bool ok = true;
	static numtype out(const fftwtype& n) {return n;}
	static void    in(const numtype& n, fftwtype& v) {v = n;}
};
template<>
struct fftwconvert<qm_complex>  {
	typedef qm_complex    numtype;
	typedef fftw_complex  fftwtype;
	const static bool ok = true;
	static numtype out(const fftwtype& n) {return numtype(n[0],n[1]);}
	static void    in(const numtype& n, fftwtype& v) {
		v[0] = n.real();
		v[1] = n.imag();
	}
};


template<typename T>
class fftdataholder  {
public:
	typedef T	fftwtype;
	fftdataholder(unsigned N)  {
		BOOST_STATIC_ASSERT(fftwblock<fftwtype>::ok);
		m_data = (fftwtype*) fftw_malloc(N * sizeof(fftwtype));
	}
	~fftdataholder() {
		fftw_free(m_data);
	}
	fftwtype*	m_data;
};


/** \brief fftarray to be used with FFTW library
 * \ingroup fourier
 */
template<unsigned N_dim, typename T>
class fftarray: public basedes  {
public:
	typedef fftwconvert<T>					fftwtraits;
	typedef typename fftwtraits::fftwtype	fftwtype;
	typedef typename fftwtraits::numtype	numtype;
	typedef fftdataholder<fftwtype>			holdertype;
	typedef QM_SMART_PTR(holdertype)		HOLDERTYPE;
	
	fftarray(unsigned N) {
		BOOST_STATIC_ASSERT(fftwtraits::ok);
		QM_REQUIRE(N > 2,"Dimension must be higher than two");
		m_dim  = N;
		m_data = HOLDERTYPE(new holdertype(m_dim));
		p_data = m_data->m_data;
	}
	fftarray(const fftarray& rhs):m_data(rhs.m_data),m_dim(rhs.m_dim) {p_data = m_data->m_data;}
	
	qm_string tostring() const {return "Fast Fourier Transform array";}
	unsigned size() const {return m_dim;}
	unsigned dim()  const {return N_dim;}
	
	void operator = (const numtype& num)  {
		for(unsigned i=0;i<m_dim;i++)
			p_data[i] = num;
	}
	
	double get_real(unsigned m) const;
	
	template<typename C>
	void put(C val, unsigned m); 
	
	fftwtype& operator [] (unsigned i) {return p_data[i];}
	const fftwtype& operator [] (unsigned i) const {return p_data[i];}
	
	numtype  get(unsigned i) const 				 {return fftwtraits::out(p_data[i]);}
	void     set(unsigned i, const numtype& num) {fftwtraits::in(num,p_data[i]);}
	numtype  get_slow(unsigned i) const {QM_REQUIRE(i<m_dim,"Out of bound"); return this->get(i);}
	void     set_slow(unsigned i, numtype num) {QM_REQUIRE(i<m_dim,"Out of bound"); this->set(i,num);}
	
	fftarray& operator = (const fftarray& rhs) {
		QM_FAIL("cannot assign fftarray");
		m_data = rhs.m_data;
		p_data = m_data->m_data;
	}
	fftwtype*	data() {return p_data;}
	
	template<class L>
	L tolist() const { 
		L l;
		for(unsigned i=0;i<m_dim;i++)
			l.append(this->get(i));
		return l;
	}
private:
	HOLDERTYPE	m_data;
	unsigned 	m_dim;
	fftwtype*	p_data;
};


template<> inline double 
fftarray<1u,double>::get_real(unsigned m) const {return p_data[m];}
template<> inline double 
fftarray<1u,qm_complex>::get_real(unsigned m) const {return p_data[m][0];}




template<> template<>
inline void fftarray<1u,double>::put(double val, unsigned m) {p_data[m] = val;}
template<> template<>
inline void fftarray<1u,double>::put(fftw_complex val, unsigned m) {p_data[m] = val[0];}
template<> template<>
inline void fftarray<1u,double>::put(qm_complex val, unsigned m) {p_data[m] = val.real();}

template<> template<>
inline void fftarray<1u,qm_complex>::put(double val, unsigned m) {p_data[m][0] = val;}
template<> template<>
inline void fftarray<1u,qm_complex>::put(fftw_complex val, unsigned m) {
	p_data[m][0] = val[0];
	p_data[m][1] = val[1];
}
template<> template<>
inline void fftarray<1u,qm_complex>::put(qm_complex val, unsigned m) {
	p_data[m][0] = val.real();
	p_data[m][1] = val.imag();
}




QM_NAMESPACE_END2



#endif  //  __FFTW_TYPES_QM_HPP__

