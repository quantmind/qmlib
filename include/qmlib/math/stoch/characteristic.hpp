





#ifndef   __CHARACTERISTIC_FUNCTION_MODELS_QM_HPP__
#define   __CHARACTERISTIC_FUNCTION_MODELS_QM_HPP__


#include <qmlib/complex.hpp>
#include <qmlib/qmat/qmatrix.hpp>



/**\file
 * \brief Characteristic function plugin for istochastic processes
 * \ingroup stoch
 */



QM_NAMESPACE2(math)


template<class U, class P> struct characteristic_exponent_calc;
template<class C>          struct characteristic_process_traits;

/// The affine exponent
/// \f$\psi_{{\bf x}_t}(T,{\bf c},m) = a_t(T,{\bf c},m) + {\bf b}_t(T,{\bf c},m)\cdot {\bf x}_t\f$
/// is given by the transform
/// \f$\chi^0_{{\bf x}_t}(T,{\bf c},m) = e^{\psi_{{\bf x}_t}(T,{\bf c},m)}\f$.
template<typename C, unsigned N>
class affine_exponent : public basedes {
public:
	typedef C						numtype;
	typedef tinyvec<qm_real,N>		rvec;
	typedef tinyvec<numtype,N>		tvec;
	typedef tinymat<numtype,N,N>	tmat;
	
	affine_exponent(qm_real t0_, qm_real t1_, qm_real m):a(0),b(0),t0(t0_),t1(t1_),n(0),itern(0),m_d(m){}
	
	/// \brief  \f$a_t(T,{\bf c},m)\f$
	numtype 	get_a() 	  const {return a;}
	/// \brief \f${\bf b}_t(T,{\bf c},m)\f$
	tvec    	get_b() 	  const {return b;}
	/// \brief \f$m\f$ used in the calculation
	qm_real    	disc()  	  const {return m_d;}
	/// \brief \f$t\f$ used in the calculation
	qm_real    	time()  	  const {return t0;}
	/// \brief \f$T\f$ used in the calculation
	qm_real    	maturity()    const {return t1;}
	
	void    	set_disc(qm_real d)  {m_d = d;}
	void		assign(affine_exponent* ex) {a = ex->a; b = ex->b; t0 = ex->t0; t1 = ex->t1; m_d = ex->m_d;}
	unsigned    get_n() 	  const {return n;}
	unsigned    get_itern()   const {return itern;}
	qm_real     get_aveiter() const {return qm_real(itern)/n;}
	qm_string   tostring()    const {return "Exponential Affine Exponent. a = " + object_to_string(a) +
											" b = " + b.tostring();}
	numtype		value(const rvec& x) const  {
		return this->a + this->b.inner(x);
	}
	numtype  a;
	tvec 	 b;
	qm_real  t0;
	qm_real  t1;
	unsigned n;
	unsigned itern;
protected:
	qm_real  m_d;
};


template<typename T, unsigned N>
struct chartraits  {
	typedef affine_exponent<T,N>	exptype;
	typedef QM_SMART_PTR(exptype)	EXPTYPE;
	typedef tinyvec<T,N>			vectype;
};



/// \brief Process with Independent Increments, in short PII.
///
/// A PII, sometimes referred as additive process, is a cadlag process \f$x_t\f$ such that
///   - \f$x_t - x_s\f$ is independent form \f$x_s - x_u \ \ \forall\ \ 0 \le u \le s \le t\f$
///     (independent increments property)
///   - It is stochastically continuous, that is to say
///     \f$\lim_{s\rightarrow t}\f$
///
/// One of the most important properties of PII is the existance of the characteristic triplet,
/// that is to say
///
/// \f$ E\left[\exp i {\bf u}\cdot{\bf x}_t\right] = e^{-\psi_t({\bf u}\cdot{\bf x}_t)}\f$ where
///
/// \f$ \psi_t(u) = - i u \mu_t + \frac{u^2}{2}c_t + \int [1 - e^{i u x} + i u h(x)] F_t(dx) \f$
/// \ingroup random
template<unsigned N>
class characteristic  {
public:
	const static unsigned Dimension = N;
	typedef characteristic<Dimension>					characteristic_type;
	typedef tinyvec<qm_complex,Dimension>				cvec;
	typedef tinyvec<qm_real,Dimension>					rvec;
	typedef tinymat<qm_real,Dimension,Dimension>		rmat;
	typedef affine_exponent<qm_real,Dimension>			rexponent;
	typedef affine_exponent<qm_complex,Dimension>		cexponent;
	typedef QM_SMART_PTR(rexponent)						REXPONENT;
	typedef QM_SMART_PTR(cexponent)						CEXPONENT;
	
	virtual ~characteristic(){}
	
	unsigned dimension() const {return Dimension;}
	
	template<class C>
	void calcmoments(const rvec& c, qm_real t0, qm_real t1, C& mcont) const;
	
	/// \brief The real cumulant
	virtual void rcumulant(const rvec& u, REXPONENT& expo) const {QM_FAIL("Real cumulant not available");}
	/// \brief The complex cumulant
	virtual void ccumulant(const cvec& u, CEXPONENT& expo) const {QM_FAIL("Complex cumulant not available");}
	
	/// \brief template function for cumulant
	///
	/// It return a rcumulant of ccumulant
	template<class T>
	typename chartraits<T,N>::EXPTYPE
	get_cumulant(const typename chartraits<T,N>::vectype& u,
			     qm_real m, qm_real t1, qm_real t2) const;
	
	/// \brief Return a vector which can be used as input for the cumulan function
	template<class T>
	typename chartraits<T,N>::vectype
	get_vec() const {return typename chartraits<T,N>::vectype(0);}
	
	/// \brief Calculate the covariance between vector rb1 and rb2
	///
	///@param rb1 First vector
	///@param rb2 Second vector vector
	///@param fact factors
	qm_real affine_covariance(const rvec& rb1, const rvec& rb2, const rvec& fact) const;
	
    /// \brief characteristic exponet
    /// @param u complex frequency in \f$R^N\f$.
    /// @param expo the affine_exponent \f$\phi_{t,T}({\bf u})\f$ defined as
	/// \f$e^{-\phi_{t,T}({\bf u})} = E_t\left[e^{i\,{\bf u}\cdot {\bf x}_T}\right]\f$
	void characteristic_exponent(const cvec& u, CEXPONENT& expo) const;
	
	template<class U>
	CEXPONENT get_characteristic_exponent(const U& u, qm_real t1, qm_real t2, qm_real m) const {
		return characteristic_exponent_calc<U,characteristic_type>::doit(this->noConst(),u,t1,t2,m);
	}
	template<class U>
	CEXPONENT get_characteristic_exponent2(const U& u, qm_real t1, qm_real t2) const {
		return get_characteristic_exponent(u,t1,t2,0);
	}
	template<class U>
	CEXPONENT get_characteristic_exponent1(const U& u, qm_real T) const {
		return get_characteristic_exponent(u,0,T,0);
	}
	
	qm_real exponential_convexity(qm_real t0, qm_real t1) const;
	
	/// \brief It indicates if there is a closed-form solution for the analytical exponent
	virtual bool	analytical_exponent() const {return false;}
	
	bool	periodic_characteristic() 		const {return this->characteristic_period() < maxreal();}
	
	virtual qm_real	characteristic_period()	const {return maxreal();}
	
	//virtual const rvec& dbdTr(qm_real t, qm_real T) const {QM_FAIL("not implemented");}
	//virtual const cvec& dbdTc(qm_real t, qm_real T) const {QM_FAIL("not implemented");}
	
	/// \brief Set the analytical calulation flag
	void            set_analyticalcalc(bool v) {m_analyticalcalc = v;}
	
	/// \brief Return true if the calculation of the characteristic exponent is analytical
	bool            get_analyticalcalc() const {return this->analytical_exponent() && m_analyticalcalc;}
	
	qm_real			get_dtchar() const {return m_dtchar;}
	void 			set_dtchar(qm_real dt) {QM_REQUIRE(dt>0,"Time step must be positive"); m_dtchar = dt;}
	
	const rvec&     charFactors() const {return m_c_factors;}
	
	virtual void 	updateFactors() {m_c_factors = 0.;}
	virtual bool    ispositive_characteristic(unsigned i) const {return false;}
	
	unsigned		odemaxiter() const {return m_odemaxiter;}
	void			set_odemaxiter(unsigned n) {m_odemaxiter = n;}
	qm_real			tolerance() const {return m_tolerance;}
	void			set_tolerance(qm_real tol) {if(tol>0.) m_tolerance = tol;}
	
	virtual const rmat&	ThetaMat() 		   const {QM_FAIL("Not implemented");}
	virtual rvec S2value(const rvec& fact) const {QM_FAIL("Not implemented");}
protected:
	rvec			m_c_factors;
	mutable rmat	m_mat;
	mutable rvec	m_rvec;
	mutable cvec	m_cvec;
	
	characteristic():m_analyticalcalc(true),m_dtchar(0.01),
					 m_du(0.01),m_tolerance(1.E-05),
					 m_odemaxiter(20){}
private:
	bool 			m_analyticalcalc;
	qm_real			m_dtchar;
	qm_real			m_du;
	qm_real			m_tolerance;
	unsigned		m_odemaxiter;
	
	characteristic_type& noConst() const { return const_cast<characteristic_type&>(*this); }
};



//template<>
template<unsigned N>
struct characteristic_process_traits<characteristic<N> > {
	typedef QM_SMART_PTR(characteristic<N>)	CHARTYPE;
	static CHARTYPE getstoch(CHARTYPE typ) {return typ;}
};



QM_NAMESPACE_END2

#include <qmlib/math/stoch/impl/char_impl.hh>

#endif	//	__CHARACTERISTIC_FUNCTION_MODELS_QM_HPP__

