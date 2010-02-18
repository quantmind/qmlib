

#ifndef __DIFFUSION_PROCESS_QM_HPP__
#define __DIFFUSION_PROCESS_QM_HPP__


#include <qmlib/math/stoch/exponential.hpp>


/** \file
 *  \ingroup stoch
 *  \brief Diffusion processes
 */



QM_NAMESPACE2(math)


template<unsigned N> class diffusion;
template<unsigned N> class CharacteristicDiffusion;

typedef diffusion<1u> diffusion1;
typedef diffusion<2u> diffusion2;
typedef QM_SMART_PTR(diffusion1) DIFFP1;
typedef QM_SMART_PTR(diffusion2) DIFFP2;
typedef CharacteristicDiffusion<1u> cdiffusion1;
typedef CharacteristicDiffusion<2u> cdiffusion2;
typedef CharacteristicDiffusion<3u> cdiffusion3;
typedef QM_SMART_PTR(cdiffusion1) CDIFFP1;
typedef QM_SMART_PTR(cdiffusion2) CDIFFP2;
typedef QM_SMART_PTR(cdiffusion3) CDIFFP3;


/** \brief advance a Square Root process
 * 
 * @param ka	mean reversion speed
 * @param th	mean reversion level
 * @param et	volatility parameter
 * @param v0	initial value
 * @param dt	time step
 * @param sdt	square-root of time step
 * @param nv	normal variate
 * @return		value at time t+dt
 */
qm_real square_root_advance(qm_real ka, qm_real th, qm_real et,
							qm_real v0, qm_real dt, qm_real sdt,
							qm_real nv);


template<typename T, typename U>
void square_root_exponent(const T& k, const T& m, qm_real eta, const U& c,
						  typename QM_PROMOTE(T,U)& a, typename QM_PROMOTE(T,U)& b);

DIST1 squareroot_marginal(qm_real t, qm_real ka, qm_real th, qm_real et, qm_real v0);


template<unsigned N>
struct diffusion_traits  {
	typedef tinyvec<qm_real,N>		 vectype;
	typedef tinymat<qm_real,N,N>	 mattype;
};
template<>/*
inline qm_real square_root_advance(qm_real ka, qm_real th, qm_real et,  qm_real ro,
								   qm_real v0, qm_real dt, qm_real sdt, qm_real nv)  {
	qm_real u2 = v0;
	qm_real u  = std::sqrt(u2);
	qm_real b  = 0.5*et*nv*sdt;
	qm_real a  = 0.5*(ka*(th - u2) - 0.25*et*et)/u;
	qm_real un = u + a*dt + b;
	return un*un;
}
*/
struct diffusion_traits<1u>  {
	typedef qm_real	 vectype;
	typedef qm_real	 mattype;
};


/** \brief Multi-dimensional diffusion processes
 * \ingroup stoch
 * 
 * A one dimensional diffusion process has SDE given by
 * 
 * \f$ d x_t = \mu_t(x_t) dt + \sigma_t(x_t) d w_t \f$
 * 
 * Diffusions processes need to specify the drift and sigma functions
 * which define \f$\mu_t(x_t)\f$ and \f$\sigma_t(x_t)\f$.
 * 
 * Furthermore if we use a diffusion as the model for an underlying financial
 * instrument, a certain number of derivatives can be priced using PDE tecniques.
 * In other words a diffusion is a PDE friendly models.
 * In derivative pricing these type of models are referred as "local volatility model"
 * 
 */
template<unsigned N>
class diffusion : public stochastic  {
public:
	typedef stochastic				 		basestoch;
	typedef basestoch::momentstype 	 		momentstype;
	typedef diffusion_traits<N>		 		difftraits;
	typedef idistribution<N>				disttype;
	typedef QM_SMART_PTR(disttype)			DISTTYPE;
	typedef typename difftraits::vectype	vectype;
	typedef typename difftraits::mattype	mattype;
	static const unsigned Dimension = N;
	
	unsigned count() const  {return Dimension;}
	bool	 isdiffusion() const {return true;}
	virtual  vectype drift(const vectype& x, qm_real t)  const {return vectype(0);}
 	virtual  mattype sigma2(const vectype& x, qm_real t) const {return mattype(0);}
	mattype  sigma(const vectype& x, qm_real t)  const {return mattype(0);}
	void     simula(montecarlo* monte, unsigned numpaths, unsigned& stdim);
protected:
	diffusion(){}
	diffusion(const parameters& pa):basestoch(pa){}
	diffusion(const parameters& pa, const parameters& fa):basestoch(pa,fa){}
	diffusion(const parameters& pa, const parameters& fa,
			  const parameters& ri):basestoch(pa,fa,ri){}

	/** \brief Create monte-carlo paths
	 *
	 */
	virtual void createPaths() {}
};


template<unsigned N>
class CharacteristicDiffusion: public diffusion<N>, public characteristic<N>  {
public:
	typedef diffusion<N>						basestoch;
	typedef characteristic<N>					chartype;
	typedef typename basestoch::momentstype 	momentstype;
	typedef typename chartype::rvec				rvec;
	static const unsigned Dimension = basestoch::Dimension;
	
	momentstype moments(unsigned i, qm_real t1, qm_real t2) const  {
		rvec c(0);
		c[i] = 1;
		return mixmoments(c,t1,t2);
	}
	momentstype mixmoments(const rvec& c, qm_real t1, qm_real t2) const  {
		momentstype m(0,0,0,0);
		this->calcmoments(c,t1,t2,m);
		return m;
	}
	qm_real	exponential_convexity(qm_real t, qm_real t1) const;
	
	bool ispositive_characteristic(unsigned i) const {return this->ispositive();}
protected:
	CharacteristicDiffusion(){}
	void precalc() {this->updateFactors();}
};


/** \brief Exponential characteristic diffusion processes
 * \ingroup stoch
 */
template<unsigned N>
class ExponentialCharacteristicDiffusion: public diffusion<N>,
										  public characteristic_exponential<N>  {
public:
	typedef diffusion<N>							basestoch;
	typedef characteristic_exponential<N>			baseexp;
	typedef CharacteristicDiffusion<N>				exptype;
	typedef QM_SMART_PTR(exptype)					EXPTYPE;
	typedef typename baseexp::chartype				chartype;
	typedef typename baseexp::chartype 				correctiontype;
	typedef typename basestoch::momentstype 		momentstype;
	typedef ExponentialCharacteristicDiffusion<N>	selftype;
	typedef QM_SMART_PTR(selftype)					SELFTYPE;
	
	static const unsigned Dimension = basestoch::Dimension;
	
	bool isexponential() const {return true;}
		
	qm_string code() 	 const {return "Exponential " + p_proc->code();}
		
	bool ispositive()    const {return true;}
	
	EXPTYPE exponent() const {return smart_cast<exptype,chartype>(this->cprocess());}
	
	//momentstype moments(unsigned i, qm_real t1, qm_real t2) const  {
	//	momentstype m(0,0,0,0);
	//	this->cprocess()->calcmoments(i,t1,t2,m);
	//	return m;
	//}
	void simula(montecarlo* monte, unsigned numpaths, unsigned& stdim);
protected:
	exptype*					p_proc;
};


//template<>
template<unsigned N>
struct characteristic_process_traits<ExponentialCharacteristicDiffusion<N> > {
	typedef QM_SMART_PTR(characteristic<N>)	CHARTYPE;
	typedef QM_SMART_PTR(ExponentialCharacteristicDiffusion<N>)	PROCTYPE;
	static CHARTYPE getstoch(PROCTYPE typ) {return typ->cprocess();}
};


QM_NAMESPACE_END2


#include <qmlib/math/stoch/impl/diffusion_impl.hh>


#endif // __DIFFUSION_PROCESS_QM_HPP__

