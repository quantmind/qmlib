

#ifndef __PDE_MODELS_COEFFICIENT_QM_HPP__
#define __PDE_MODELS_COEFFICIENT_QM_HPP__


#include <qmlib/math/pde/pde_models.hpp>

/**\file
 * \ingroup pde
 * \brief Base template classes for PDE models
 */

QM_NAMESPACE2(math)



/** \brief Base class template interface for coefficients
 * \ingroup pde
 */
template<unsigned N, typename T>
class pde_coefficient : public timedependentcoef<T> {
public:
	typedef T									numtype;
	typedef pde_coefficient<N,numtype>			selftype;
	typedef pdegridtraits<N>					gridtraits;
	typedef	typename gridtraits::gridtype		gridtype;
	typedef typename gridtraits::GRIDTYPE		GRIDTYPE;
	
	pde_coefficient(){}
	
	virtual numtype eval(unsigned i, unsigned t, bool explic) const {return 0;}
	virtual bool    timedependent() const {return true;}
	
	void    clear() {this->clearcache(); this->clearall();}
	
	GRIDTYPE get_grid() const {return m_grid;}
	
	/// \brief Set the grid
	void 	set_grid(const GRIDTYPE& gr){m_grid = gr;}
protected:
	GRIDTYPE 	m_grid;
	virtual void clearall() {}
};


template<unsigned N, typename T>
class const_pde_coefficient : public pde_coefficient<N,T>  {
public:
	typedef pde_coefficient<N,T>		basetype;
	typedef typename basetype::numtype	numtype;
	typedef typename basetype::GRIDTYPE GRIDTYPE;
	
	const_pde_coefficient(const numtype& val, const GRIDTYPE& gr):m_value(val){this->set_grid(gr);}
	
	numtype eval(unsigned i, unsigned t, bool explic) const {return m_value;}
	
	qm_string tostring() const {return "Constand PDE coefficient, value " + object_to_string(m_value);}
	
	bool    timedependent() const {return false;}
protected:
	qm_real   m_value;
};



//template<>
template<unsigned N, class T>
class matrix_expr<pde_coefficient<N,T>,true> : public matrix_expr_base {
public:
	typedef pde_coefficient<N,T>				coef_type;
	typedef QM_SMART_PTR(coef_type)				expression;
	typedef typename coef_type::numtype 		numtype;
	typedef matrix_expr<expression,true>		myself;
	static const bool can_be_nested	= true;
	
	matrix_expr(const expression& value, unsigned t, bool explic):m_value(value),m_t(t),m_explic(explic){}
	matrix_expr(const matrix_expr& rhs):m_value(rhs.m_value),m_t(rhs.m_t){}
	
	numtype operator() (unsigned i) 			const  { return m_value->eval(i,m_t,m_explic); }
	numtype operator() (unsigned i, unsigned j) const  { QM_FAIL("i didn't know we can go here"); }
protected:
	expression	m_value; 
	unsigned    m_t;
	bool		m_explic;
};



template<unsigned N, class T>
inline matrix_expr<pde_coefficient<N,T>, true>
timecoef(const boost::shared_ptr<pde_coefficient<N,T> >& coef, unsigned t, unsigned t0)  {
	return matrix_expr<pde_coefficient<N,T>,true>(coef,t,t0);
}

	
QM_NAMESPACE_END2


#endif // __PDE_MODELS_COEFFICIENT_QM_HPP__

