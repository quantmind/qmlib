


#ifndef   __FOURIER_IMPL_QM_HPP__
#define   __FOURIER_IMPL_QM_HPP__


#include <qmlib/math/fourier/fftwtypes.hpp>


/**\file
 * \brief Wrapper class for FFTW one dimensional Fourier transforms.
 * \ingroup fourier
 * 
 * FFTW is a C subroutine library for computing the discrete Fourier transform (DFT)
 * in one or more dimensions, of arbitrary input size, and of both real and complex
 * data (as well as of even/odd data, i.e. the discrete cosine/sine transforms or DCT/DST).
 * \see http://www.fftw.org/
 */



QM_NAMESPACE2(math)

/** \brief One dimensional Fourier transform for real and complex data
 * \ingroup fourier
 * 
 * @param T	data type of the inverse fourier transform
 * 
 *  - the inverse data array contains T values
 *  - the direct data array contains complex values
 */
template<typename T>
class fourier<1u,T>: public basedes {
public:
	typedef fftwconvert<T>					fftwtraits;
	typedef typename fftwtraits::fftwtype	fftwtype;
	typedef typename fftwtraits::numtype	numtype;
	typedef fftarray<1u,numtype>		  	iarraytype;
	typedef fftarray<1u,qm_complex>	  		darraytype;
	
	fourier(unsigned N);
	~fourier();
	
	qm_string tostring() const {return "1D Fourier Transform. Size: "+object_to_string(this->size());}
	unsigned   size() const {return i_array.size();}
	unsigned  dsize() const;
	iarraytype& idata() {return i_array;}
	darraytype& ddata() {return d_array;}
	
	/// \brief The inverse transform
	void	inverse() {fftw_execute(m_inverse_plan);}
	/// \brief The direct transform
	void	direct()  {fftw_execute(m_direct_plan);}
private:
	fourier& operator = (const fourier& rhs) {QM_FAIL("Cannot assign");}
	iarraytype i_array;
	darraytype d_array;
	fftw_plan  m_inverse_plan,m_direct_plan;
};



template<>
inline unsigned fourier<1u,double>::dsize() const {return d_array.size()-1;}
template<>
inline unsigned fourier<1u,qm_complex>::dsize() const {return d_array.size();}
template<>
inline qm_string fourier<1u,double>::tostring() const {
	return "1D Fourier Transform for real data. Size: "+object_to_string(this->size());
}
template<>
inline qm_string fourier<1u,qm_complex>::tostring() const {
	return "1D Fourier Transform for complex data. Size: "+object_to_string(this->size());
}

template<>
inline fourier<1u,double>::fourier(unsigned N):i_array(N),d_array(N/2+1){
	QM_REQUIRE(N > 4 && 2*(N/2) == N,"Fourier transform should have an even number of point bigger than 2");
	m_inverse_plan = fftw_plan_dft_c2r_1d(size(), d_array.data(), i_array.data(), FFTW_MEASURE);
	m_direct_plan  = fftw_plan_dft_r2c_1d(size(), i_array.data(), d_array.data(), FFTW_MEASURE);
}

template<>
inline fourier<1u,qm_complex>::fourier(unsigned N):i_array(N),d_array(N){
	QM_REQUIRE(N > 2 && 2*(N/2) == N,"Fourier transform should have an even number of point bigger than 2");
	m_inverse_plan = fftw_plan_dft_1d(size(), d_array.data(), i_array.data(), FFTW_FORWARD,  FFTW_MEASURE);
	m_direct_plan  = fftw_plan_dft_1d(size(), i_array.data(), d_array.data(), FFTW_BACKWARD, FFTW_MEASURE);
}

template<typename T>
inline fourier<1u,T>::~fourier() {
	fftw_destroy_plan(m_inverse_plan);
	fftw_destroy_plan(m_direct_plan);
}



QM_NAMESPACE_END2



#endif  //  __FOURIER_IMPL_QM_HPP__

