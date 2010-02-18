


#ifndef   __FRACTIONAL_FFT_QM_HPP__
#define   __FRACTIONAL_FFT_QM_HPP__


#include <qmlib/math/fourier/fftw.hpp>


/**\file
 * \brief Fractional Fast Fourier Transform method in one dimension
 * \ingroup fourier
 */




QM_NAMESPACE2(math)


/** \brief Fourier transform method used to invert characteristic transforms
 * \ingroup fourier
 */
enum fftmethod  {
	fft_trapezoidal = 0,
	fft_simpson,
	frft_trapezoidal,
	frft_simpson,
};



template<unsigned,class> class frfft;


/** \brief One dimensional Fractional Fourier transform for real numbers
 * \ingroup Fourier
 * 
 * \see
 * Bailey, D. H. and P. N. Swarztrauber (1991). The Fractional Fourier
 * Transform and applications. SIAM Review 33 (3), 389–404.
 * 
 */
template<typename T>
class frfft<1u,T>: public basedes {
public:
	typedef T							   		numtype;
	typedef fourier<1u,numtype>			   		fouriertype;
	typedef fourier<1u,qm_complex>		   		cfouriertype;
	typedef typename fouriertype::iarraytype	iarraytype;
	typedef typename fouriertype::darraytype	darraytype;
	typedef QM_SMART_PTR(fouriertype)	   		FOURIERTYPE;
	typedef QM_SMART_PTR(cfouriertype)	   		CFOURIERTYPE;
	typedef std::vector<FOURIERTYPE>	   		fftvector;
	typedef std::vector<fouriertype*>	   		fftvectorfast;
	typedef typename fftvector::iterator		iterator;
	typedef typename fftvector::const_iterator	const_iterator;
	typedef qmatrix<qm_complex>		  	  		complexvec;
	typedef qmatrix<qm_real>			  		realvec;
	
	frfft(unsigned N, unsigned D, unsigned meth);
	
	qm_string tostring() const {return "darraytypeFractional 1D Fast Fourier Transform. Size: "+object_to_string(this->size());}
	unsigned	   dim() const {return m_rffts.size();}
	unsigned      size() const {return m_rffts[0]->size();}
	unsigned     dsize() const {return m_rffts[0]->dsize();}
	bool  	      frft() const {return m_fftmethod == frft_trapezoidal || m_fftmethod == frft_simpson;}
	bool        trapez() const {return m_fftmethod == frft_trapezoidal || m_fftmethod == fft_trapezoidal;}
	
	FOURIERTYPE get(unsigned i) const {return m_rffts[i];}
	FOURIERTYPE get_slow(unsigned i) const {QM_REQUIRE(i<this->dim(),"Out of bound"); return m_rffts[i];}
	
	/// \brief High order of integration
	fftmethod    method() const {return m_fftmethod;}
	void    	 set_method(unsigned i);
	
	const complexvec&  zvec()    const {return m_z;}
	const realvec&     weights() const {return m_weights;}
	
	const_iterator	begin() const {return m_rffts.begin();}
	const_iterator	end()   const {return m_rffts.end();}
	iterator		begin()       {return m_rffts.begin();}
	iterator		end()         {return m_rffts.end();}
	
	CFOURIERTYPE	zdft(qm_real beta, bool transf);
	CFOURIERTYPE	ydft() const {return m_cfft1;}
	
	/// \brief The inverse transform
	void	invert(qm_real beta);
	
	fftvectorfast&  fastvec() {return p_rffts;} 
public:
	fftvector		m_rffts;
	fftvectorfast   p_rffts;
	CFOURIERTYPE	m_cfft1,m_cfft2;
	cfouriertype	*p_cfft1,*p_cfft2;
	complexvec		m_z;
	realvec			m_weights;
	fftmethod		m_fftmethod;
	
	void calcweights();
	void makefrfft(unsigned prec);
	void invertfrft(qm_real beta);
	void zdata(qm_real beta, bool transf);
	void applyweight(qm_complex& x, unsigned m) const;
	void wrapfrft(iarraytype& idft, const darraytype& idata, unsigned N);
};


QM_NAMESPACE_END2

#include <qmlib/math/fourier/impl/frfft_impl.hh>

#endif  //  __FRACTIONAL_FFT_QM_HPP__

