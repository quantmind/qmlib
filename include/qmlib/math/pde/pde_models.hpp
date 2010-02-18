

#ifndef __PDE_MODELS_QM_HPP__
#define __PDE_MODELS_QM_HPP__


#include <qmlib/math/pde/timemarching.hpp>

/**\file
 * \ingroup pde
 * \brief Base template classes for PDE models
 * 
 */

QM_NAMESPACE2(math)


/** \brief Base class for a system of PDEs
 * \ingroup pde
 * 
 * This template defined containers for initial solution and for the
 * time dependent solutions.
 * In a semi-discrete form, a PDE takes the following form
 * 
 * \f$ \frac{\Delta U}{\Delta t} = {\tt RHS}(U) \f$
 * 
 * @param T number type (usually real)
 * @param G grid type
 */
template<typename T, unsigned N>
class pdemodel_base : public basedes {
public:
	typedef T									numtype;
	typedef pdegridtraits<N>					gridtraits;
	typedef	typename gridtraits::gridtype		gridtype;
	typedef typename gridtraits::GRIDTYPE		GRIDTYPE;
	typedef typename gridtraits::gridpoint		gridpoint;
	typedef qmatrix<numtype>					qmat;
	
	pdemodel_base(const GRIDTYPE& gr):m_gr(gr),m_stored(false),m_store(false),m_ready(false) {
		QM_REQUIRE(m_gr,"Grid not available");
		unsigned M = m_gr->points();
		m_U0.resize1(M);
		m_UT.resize1(M);
		m_rhs.resize1(M);
	}
	
	virtual time_marching_result solve(const TIMEGRID& tg) {QM_FAIL("Solver not implemented in base class");}

	// Virtual method, to be re-emplemented
	virtual void      clear() {}
	virtual qm_real   dtmax()    const {return 0;}
	
	/// \brief linear model
	///
	/// @return true if the pde model is linear
	virtual bool      islinear() const {return false;}
	
	/// \brief time-dependent coefficients
	///
	/// @return true if the pde has time-dependent coefficients
	virtual bool	  timedependent() const {return true;}
	
	/// \brief Right hand side evaluation
	///
	/// This function return the explicit vector of the space discretization
	///
	/// @param unk The unknown vector at time t
	/// @param t  the time level
	/// @param t0 previous time level
	/// @return the right-hand-side space-discretization
	virtual const qmat&  rhs(const qmat& unk, unsigned t) {return m_rhs;}
	
	/// \brief Return the initial condition
	const qmat& 	get_initial() 		const {return m_U0;}
	
	/// \brief Set the initial condition
	void  			set_initial(const qmat& u0);
	
	/// \brief Return the final solution
	const qmat& 	final()   			const {return m_UT;}
	unsigned 		dimensions() 		const {return m_gr->dimensions();}
	unsigned 		points()	  		const {return m_gr->points();}
	bool     		stored()     		const {return m_stored;}
	bool			isready()			const {return m_ready;}
	bool     		get_store()  		const {return m_store;}
	void     		set_store(bool v)  {m_store = v;}
	GRIDTYPE 		grid() 				const {return m_gr;}
	
	
	virtual const TIMEGRID& get_timegrid() const {QM_FAIL("not implemented");}
	virtual void set_timegrid(const TIMEGRID& tg) {}
	
	// Some initial conditions
	void calloption(numtype strike)  {
		gridpoint  gp;
		for(unsigned i=0;i<this->points();i++)  {
			gp = this->grid()->point(i);
			this->m_U0(i) = std::max(0.0,gp(0)-strike);
		}
		this->m_ready = true;
	}
	void putoption(numtype strike)  {
		gridpoint  gp;
		for(unsigned i=0;i<this->points();i++)  {
			gp = this->grid()->point(i);
			this->m_U0(i) = std::max(0.0,strike-gp(0));
		}
		this->m_ready = true;
	}
	void worseofcall(numtype strike1 = 0.5, numtype strike2 = 0.5)  {
		QM_REQUIRE(this->dimensions() == 2,"This type of initial condition is for 2D models");
		gridpoint  gp;
		for(unsigned i=0;i<this->points();i++)  {
			gp = this->grid()->point(i);
			this->m_U0(i) = std::min( std::max(0,gp(0) - strike1), std::max(0,gp(1) - strike2) );
		}
		this->m_ready = true;
	}
	void worseofput(numtype strike1 = 0.5, numtype strike2 = 0.5)  {
		QM_REQUIRE(this->dimensions() == 2,"This type of initial condition is for 2D models");
		gridpoint  gp;
		for(unsigned i=0;i<this->points();i++)  {
			gp = this->grid()->point(i);
			this->m_U0(i) = std::min( std::max(0,strike1 - gp(0)), std::max(0,strike2 - gp(1)) );
		}
		this->m_ready = true;
	}
	
protected:
	GRIDTYPE		m_gr;
	qmat			m_U0,m_UT;
	qmat   			m_rhs;
	bool			m_stored,m_store,m_ready;
};



template<typename T, unsigned N>
inline void pdemodel_base<T,N>::set_initial(const qmatrix<numtype>& u0)  {
	QM_REQUIRE(m_U0.is_same_shape(u0),"initial condition with a wrong number of points");
	m_U0 	= u0;
	m_ready = true;
}


	
QM_NAMESPACE_END2


#endif // __PDE_MODELS_QM_HPP__

