





#ifndef   __FOURIER_PRICER_QM_HPP__
#define   __FOURIER_PRICER_QM_HPP__


#include <qmlib/math/fourier/ifftchar.hpp>
#include <qmlib/finance/tsmodel/affine.hpp>


/**\file
 * \brief Template implementation of ifftchar
 * \ingroup fourier
 */



QM_NAMESPACE2(math)

template<typename T> struct fftcharhelp;

template<> struct fftcharhelp<qm_real>    {
	static qm_real  mult() {return 0.5;}
	static unsigned inverseposition(unsigned k, unsigned K) {return K-1-k;}
};
template<> struct fftcharhelp<qm_complex> {
	static qm_real  mult() {return 1.0;}
	static unsigned inverseposition(unsigned k, unsigned K) {return k;}
};



/** \brief Class Template implementation of ifftchar
 * \ingroup fourier
 * 
 * @param T type to use in Fourier calculations
 * @param C Stochastic model type
 * @param Full flag indicating if full evaluation is required
 */
template<typename T, class C, bool Full>
class fftchar : public ifftchar<T>,
			    public observer,
			    public observable {
public:
	const static unsigned Dimension  = C::Dimension;
	const static unsigned DimensionT = fftoptiondim<Dimension,Full>::Dimension;
	
	typedef ifftchar<T>								baseclass;
	typedef QM_SMART_PTR(baseclass)					FFTCHAR;
	typedef typename baseclass::fouriertype			fouriertype;
	typedef typename baseclass::FOURIERTYPE			FOURIERTYPE;
	typedef typename baseclass::iarraytype			iarraytype;
	typedef typename baseclass::darraytype			darraytype;
	typedef C										modeltype;
	typedef characteristic<Dimension>				chartype;
	typedef QM_SMART_PTR(modeltype)					MODELTYPE;
	typedef typename baseclass::rdatatype			rdatatype;
	typedef typename baseclass::RDATATYPE			RDATATYPE;
	typedef typename baseclass::charestype			charestype;
	typedef dictionaryBase<qm_string,RDATATYPE>		dicttype;
	typedef typename dicttype::iterator				iterator;
	typedef typename chartype::rvec					rvec;
	typedef typename chartype::cvec					cvec;
	typedef typename chartype::rexponent			rexponent;
	typedef typename chartype::cexponent			cexponent;
	typedef typename chartype::REXPONENT			REXPONENT;
	typedef typename chartype::CEXPONENT			CEXPONENT;
	typedef QM_SMART_PTR(chartype)					CHARTYPE;
	typedef qmatrix<qm_real>			  			realvec;
	
	void clear() {m_data.clear();}
	
	STOCHASTIC process() const {return smart_cast<istochastic,chartype>(m_process);}

	/// \brief real affine_exponent used for characteristic pricing 
	///
	/// In general, a characteristic pricing involves the fourier inversion
	/// of a characteristic transform defined on \f$e^{a + {\bf b}\cdot{\bf x}_t}\f$.
	/// This function calculate \f$a\f$ and \f$\bfb\f$ for specific asset classes.
	virtual	REXPONENT rvector(qm_real T1, qm_real T2, qm_real tau) const = 0;

	virtual qm_complex cvector(qm_real u, const rvec& dvec, cvec& vec) const = 0;
	
	virtual RDATATYPE makedata(qm_real b, qm_real L, qm_real du,
							   qm_real tex, qm_real tse, qm_real tma, qm_real tau,
							   qm_real expa) const;
	
	RDATATYPE calculate(qm_real T0, qm_real T1, qm_real T2, qm_real tau);
	
	charestype characteristicfun(qm_real T0, qm_real T1, qm_real T2, qm_real tau);
	
	void update() {this->clear(); this->notify_observers();}
protected:
	fftchar(MODELTYPE mod, unsigned NF, qm_real stdev, qm_real dum, unsigned meth);
	/// \brief Calculate the characteristic transform
	///
	///@param T0	expiry of the transform
	///@param T1	settlement of underlying in the transform (T1 >= T0)
	///@param T2	T2 - T1 is the tenure of the underlying (T2 >= T1)
	///@param tau	Year fraction. should be close to T2-T1
	///@param calc	if true perform the fft inversion of transform
	RDATATYPE  characteristic_calc(qm_real T0, qm_real T1, qm_real T2, qm_real tau, bool calc);
	
	virtual qm_real discretize(const istochastic::momentstype& mom, qm_real& b, qm_real& L) const;
	
	virtual unsigned position(unsigned k, unsigned K) const {return k;}
	
	MODELTYPE		m_model;
	CHARTYPE		m_process;
	chartype*		p_c;
	dicttype		m_data;
	realvec			m_smul;
	qm_real			multtrans;
};



/** \brief ifftchar for marginal density evaluation
 * \ingroup fourier
 * 
 * @param C Stochastic model type
 * @param Full flag indicating if full evaluation is required
 */
template<typename T, class C>
class fftdensity : public fftchar<T,C,false>  {
public:
	typedef fftchar<T,C,false>					baseclass;
	typedef typename baseclass::MODELTYPE		MODELTYPE;
	typedef typename baseclass::rvec			rvec;
	typedef typename baseclass::cvec			cvec;
	typedef typename baseclass::rexponent		rexponent;
	typedef typename baseclass::REXPONENT		REXPONENT;
	typedef typename baseclass::FFTCHAR			FFTCHAR;
	
	const static unsigned Dimension  = baseclass::Dimension;
	
	static FFTCHAR make(unsigned i, MODELTYPE m, unsigned NF, qm_real stdev, qm_real dum, unsigned meth) {
		return FFTCHAR(new fftdensity(i,m,NF,stdev,dum,meth));
	}
	
	REXPONENT rvector(qm_real T1, qm_real T2, qm_real tau) const {
		REXPONENT re(new rexponent(0,T1,0));
		re->b[m_i] = 1.;
		return re;
	}
	qm_complex cvector(qm_real u, const rvec& dvec, cvec& vec) const {
		vec[this->m_i] = qm_complex(0,u);
		return qm_complex(1,0);
	}
	
	qm_string tostring() const {return "Characteristic FFT density transform";}

protected:
	unsigned m_i;
	fftdensity(unsigned i, MODELTYPE m, unsigned NF, qm_real stdev, qm_real dum, unsigned meth):
		baseclass(m,NF,stdev,dum,meth),m_i(i) {
			QM_REQUIRE(m_i<Dimension,"out of dimension");
		}
	
	qm_real discretize(const istochastic::momentstype& mom, qm_real& b, qm_real& L) const  {
		qm_real du = std::sqrt(2.*(1.-0.99))/mom[1];
		if(this->frft())
			L = this->stdmul()*mom[1];
		else
			L = PI/du;
		b	  = mom[0]-L;
		if(this->p_c->ispositive_characteristic(m_i))
			b = std::max(b,0.0);
		return du;
	}
};



/** Base class for fft option pricing
 * \ingroup fourier
 */
template<typename T, class C, bool Full>
class fftoption : public fftchar<T,C,Full>  {
public:
	typedef fftchar<T,C,Full>					baseclass;
	typedef typename baseclass::modeltype		modeltype;
	typedef typename baseclass::MODELTYPE		MODELTYPE;
	typedef typename baseclass::RDATATYPE		RDATATYPE;
	typedef typename baseclass::charestype		charestype;
	typedef typename baseclass::rvec			rvec;
	typedef typename baseclass::cvec			cvec;
	typedef typename baseclass::rexponent		rexponent;
	typedef typename baseclass::REXPONENT		REXPONENT;
	typedef typename baseclass::FFTCHAR			FFTCHAR;
	
	const static unsigned Dimension  = baseclass::Dimension;
	const static unsigned DimensionT = baseclass::DimensionT;
	
	qm_string tostring() const {return "Characteristic FFT option transform";}
	
	static FFTCHAR make(MODELTYPE m, unsigned NF, qm_real stdev, qm_real dum, unsigned meth, bool withsens) {
		if(withsens)
			return FFTCHAR(new fftoption<T,C,true>(m,NF,stdev,dum,meth));
		else
			return FFTCHAR(new fftoption<T,C,false>(m,NF,stdev,dum,meth));
	}
	
	RDATATYPE makedata(qm_real b, qm_real L, qm_real du,
					   qm_real tex, qm_real tse, qm_real tma, qm_real tau,
					   qm_real expa) const  {
		return RDATATYPE(new fftoptionresult(this->size(),DimensionT,b,L,du,tex,tse,tma,tau,expa)); 
	}
	
	REXPONENT rvector(qm_real T1, qm_real T2, qm_real tau) const {
		qm_real ct = this->m_model->correction(0.,T1);
		REXPONENT ret(new rexponent(0,T1,0));
		ret->a =-ct;
		ret->b = this->m_model->multiplier();
		return ret;
	}
	
	qm_complex cvector(qm_real u, const rvec& dvec, cvec& vec) const {
		qm_complex cm;
		qm_complex ou = this->optionu(u,cm);
		for(unsigned i=0;i<Dimension;i++) vec[i] = ou*dvec[i];
		return cm;
	}
	
	qm_real	   alpha() const {return m_alpha;}
	void	   set_alpha(qm_real alp) {if(alp>1.) m_alpha = alp; this->clear();}
	
	fftoption(MODELTYPE p, unsigned NF, qm_real stdev, qm_real dum, unsigned meth):
			baseclass(p,NF,stdev,dum,meth),m_alpha(1.5) {}
	
protected:
	qm_real m_alpha;
	
	qm_complex modifiedu(qm_real u) const {return qm_complex(u,m_alpha);}
	qm_complex optionu(qm_real u, qm_complex& cden) const {
		qm_complex iu = mult_i(this->modifiedu(u));
		qm_complex iu1 = iu + 1.;
		cden = iu*iu1;
		return iu1;
	}
	
	unsigned position(unsigned k, unsigned K) const {return K - 1 - k;}
};



/** \brief FFT result for floorlet
 * \ingroup fourier
 */
class fftfloorletresult: public fftcharresult<qm_real>  {
public:
	fftfloorletresult(unsigned N, unsigned D, qm_real b, qm_real L, qm_real duu,
					  qm_real tex, qm_real tse, qm_real tma, qm_real tau, qm_real expa):
		fftcharresult<qm_real>(N,D,b,L,duu,tex,tse,tma,tau),m_expa(expa){}
		
	qm_real domainvalue(unsigned i) const {
		return (m_expa - 1. - std::exp(this->xv(i)))/m_tau;
	}
	qm_real multiplier(unsigned i) const {
		return 1./this->domainvalue(i);
	}
protected:
	qm_real m_expa;
	qm_real xvalue(qm_real dval) const {return m_expa/(1.+m_tau*dval);}
};


/*
template<unsigned N, bool T>
class fftfloorlet : public fftoption<atsmodel<N>,T>  {
public:
	typedef fftoption<atsmodel<N>,T>				baseclass;
	typedef typename baseclass::modeltype			modeltype;
	typedef typename baseclass::MODELTYPE			MODELTYPE;
	typedef typename baseclass::RDATATYPE			RDATATYPE;
	typedef typename baseclass::charestype			charestype;
	typedef typename baseclass::rvec				rvec;
	typedef typename baseclass::REXPONENT			REXPONENT;
	
	const static unsigned DimensionT = baseclass::DimensionT;
	
	RDATATYPE calculate1(qm_real T1) {QM_FAIL("Cannot use a single time to maturity for this type of transform");}
	charestype characteristicfun1(qm_real T1) {QM_FAIL("Cannot use a single time to maturity for this type of transform");}
	
	RDATATYPE makedata(qm_real b, qm_real L, qm_real expa, qm_real tau) const  {
		return RDATATYPE(new fftfloorletresult(this->size(),DimensionT,b,L,expa,tau)); 
	}
	qm_real	   disc() const {return 1.;}
	
	qm_real   multiplier(qm_real x, qm_real expa, qm_real tau)  const {
		return (1.+tau*x)/expa;
	}
	
	REXPONENT rvector(qm_real T1, qm_real T2, qm_real tau) const {
		REXPONENT re = this->m_model->fwdexp(0,T1,T2,tau,1.);
		re->b *= -1.;
		return re;
	}
	
	fftfloorlet(MODELTYPE p, unsigned NF, qm_real stdev, unsigned meth):
				baseclass(p,NF,stdev,meth) {}
};



template<unsigned N, bool T>
class fftfutoption : public fftfloorlet<N,T>  {
public:
	typedef fftfloorlet<N,T>						baseclass;
	typedef typename baseclass::modeltype			modeltype;
	typedef typename baseclass::MODELTYPE			MODELTYPE;
	typedef typename baseclass::charestype			charestype;
	typedef typename baseclass::rvec				rvec;
	typedef typename baseclass::REXPONENT			REXPONENT;
	
	qm_real	   disc() const {return 0.;}
	
	REXPONENT rvector(qm_real T1, qm_real T2, qm_real tau) const {
		return this->m_model->fwdexp(0,T1,T2,tau,1.);
	}
	
	fftfutoption(MODELTYPE p, unsigned NF, qm_real stdev, unsigned meth):
				 baseclass(p,NF,stdev,meth) {}
};
*/


QM_NAMESPACE_END2


#include <qmlib/math/fourier/impl/fftchar_impl.hh>



#endif	//	__FOURIER_PRICER_QM_HPP__

