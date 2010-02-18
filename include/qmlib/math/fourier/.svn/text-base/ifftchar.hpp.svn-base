





#ifndef   __IFFT_CHARACTERISTIC_QM_HPP__
#define   __IFFT_CHARACTERISTIC_QM_HPP__


#include <qmlib/math/stoch/exponential.hpp>
#include <qmlib/math/fourier/frfft.hpp>
#include <qmlib/math/fourier/fftres.hpp>


/**\file
 * \brief Characteristic function plugin for istochastic processes
 * \ingroup fourier
 */



QM_NAMESPACE2(math)


/** \brief Interface for characteristic transform inversion
 * \ingroup fourier
 */
template<typename T>
class ifftchar: public basedes  {
public:
	typedef frfft<1u,T>							fouriertype;
	typedef QM_SMART_PTR(fouriertype)			FOURIERTYPE;
	typedef typename fouriertype::iarraytype	iarraytype;
	typedef typename fouriertype::darraytype	darraytype;
	typedef fftcharresult<qm_real>				rdatatype;
	typedef QM_SMART_PTR(rdatatype)				RDATATYPE;
	typedef fftcharresult<qm_complex>			charestype;
	typedef qmatrix<qm_real> 					mulvectype;
	
	/// \brief The standard deviation multiplier
	///
	/// This positive real quantity is used to calculate the state domain
	qm_real stdmul() const {return m_stdmul;}
	void    set_stdmul(qm_real st);
	
	/// \brief The standard deviation multiplier
	///
	/// This positive real quantity is used to calculate the state domain
	qm_real dumin() const {return m_dumin;}
	void    set_dumin(qm_real du);
	
	/// \brief High order of integration
	fftmethod    method() const {return m_frfft->method();}
	void    	 set_method(unsigned i);
	
	/// \brief Number of point in fourier discretization
	unsigned size() const {return m_frfft->size();}
	
	/// \brief Clear cache
	virtual void clear() {}
	
	/// \brief Perform calculation
	virtual RDATATYPE calculate(qm_real T0, qm_real T1, qm_real T2, qm_real tau) {QM_FAIL("Not implemented");}
	virtual RDATATYPE calculate1(qm_real T1) {return this->calculate(T1,T1,T1,1.0);}
	
	/// \brief Return the transform in the frequency domain
	virtual charestype characteristicfun(qm_real T0, qm_real T1, qm_real T2, qm_real tau) {QM_FAIL("Not implemented");}
	virtual charestype characteristicfun1(qm_real T1) {return this->characteristicfun(T1,T1,T1,1.0);}
	
	virtual STOCHASTIC process() const {QM_FAIL("not implemented");}
	
	/// \brief Discounting flag
	virtual qm_real	   disc() const {return 0;}
	
	virtual qm_real	   alpha() const {return 0;}
	virtual void	   set_alpha(qm_real alp) {QM_FAIL("alpha not used in this transform");}
	
	FOURIERTYPE		   get_fourier() const {return m_frfft;}
	
	bool	frft()  const {return p_frfft->frft();}
protected:
	qm_real 	 m_stdmul,m_dumin;
	FOURIERTYPE	 m_frfft;
	fouriertype* p_frfft;
	ifftchar(unsigned N, unsigned D, qm_real stde, qm_real du, unsigned meth);
};


QM_NAMESPACE_END2


#include <qmlib/math/fourier/impl/ifftchar_impl.hh>

#endif	//	__IFFT_CHARACTERISTIC_QM_HPP__

