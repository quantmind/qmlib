/*******************************************************************************
 * qmlib/math/spline.hpp     Declaration of the qmatrix class
 *
 *
 * Copyright (C) 2007-2008 Luca Sbardella <luca.sbardella@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Suggestions:          quant.mind@gmail.com
 * Bugs:                 quant.mind@gmail.com
 *
 * For more information, please see the quantmind Home Page:
 *    http://www.quantmind.com
 *
 *******************************************************************************/



#ifndef __SPLINE_QM_HPP__
#define __SPLINE_QM_HPP__


//#include <qmlib/algorithm/linalg.h>
#include <qmlib/qmat/linalg.hpp>
#include <qmlib/corelib/templates/containers.hpp>


/// \file
/// \brief Spline classes including th cubic spline
/// \ingroup math
//


QM_NAMESPACE2(math)

enum splinetype  {
	standard = 0,
	periodic,
};

/// \brief Spline boundary conditions
/// \ingroup math
enum splineBoundaryCondition  {
	/// \brief the natural spline, second derivatives are zero at end points, extrapolations are lianr polynomials
    zeroSecondDerivative = 0,
    /// \brief third derivative are zero at end points, extrapolations are quadratic polynomials
    zeroThirdDerivative,
    /// \brief defined first derivative end points, extrapolations are linear polynomials
    definedFirstDerivative,
};


/// \brief Base template for splines
/// \ingroup math
template<class S, class T>
class splineSupport  {
public:
	typedef S											support_type;
	typedef dataserie<S,false,T>						spline_support;
	typedef typename spline_support::const_iterator		const_iterator;
	
	splineSupport():m_lowerBound(zeroSecondDerivative),m_upperBound(zeroSecondDerivative){}
	splineSupport(const splineSupport& rhs):m_sup(rhs.m_sup),
	                                        m_lowerBound(rhs.m_lowerBound),
	                                        m_upperBound(rhs.m_upperBound){}
    virtual ~splineSupport(){}
    //
    /// \brief size of spline
    /// @return the number of support points
    unsigned         size()             				const {return m_sup.size();}
    unsigned     	 search(const support_type& x)      const {return m_sup.upper_bound(x);}
    /// \brief The first element key in the spline
    support_type     front()            				const {return m_sup.front().key();}
    /// \brief The last element key in the spline
    support_type     back()             				const {return m_sup.back().key();}
    const_iterator	 begin()							const {return m_sup.begin();}
    const_iterator	 end()  							const {return m_sup.end();}
    
    virtual void     clear() {}
    void set_lower_condition(splineBoundaryCondition bc) {m_lowerBound = bc;}
    void set_upper_condition(splineBoundaryCondition bc) {m_upperBound = bc;}
    void set_both_condition(splineBoundaryCondition bc)  {m_lowerBound = bc; m_upperBound = bc;}
    
	template<class L>
	L xlist()  {
		L list;
		for(const_iterator it = m_sup.begin();it!=m_sup.end();++it)  list.append(it->key());
		return list;
	}
protected:
	spline_support			   m_sup;
    splineBoundaryCondition    m_lowerBound;
    splineBoundaryCondition    m_upperBound;
};


/// \brief Base class for splines
/// \ingroup math 
class spline_base: public splineSupport<qm_real,tinyvec<qm_real,3> >  {
public:
	typedef qm_real											numtype;
	typedef tinyvec<qm_real,3>								value_type;
	typedef splineSupport<qm_real,value_type>				base_class;
	typedef base_class::support_type						support_type;
	typedef base_class::spline_support						spline_support;
	typedef base_class::const_iterator						const_iterator;
	typedef qmatrix<qm_real,tridiagonal>					qmat_type;
	
	spline_base():m_ready(false),m_lowerDer(0),m_upperDer(0),m_lower_extrapolation(1),m_upper_extrapolation(1){}
	spline_base(const spline_base& rhs):base_class(rhs),m_ready(rhs.m_ready),
	                                    m_lowerDer(rhs.m_lowerDer),
	                                    m_upperDer(rhs.m_upperDer),
	                                    m_lower_extrapolation(rhs.m_lower_extrapolation),
	                                    m_upper_extrapolation(rhs.m_upper_extrapolation){}
	
	template<class L>
	spline_base(const L& inst);
	template<class L>
	void dump(L& inst) const;
	
	/// \brief Add a spline support point
	/// @param x abscissa @param @y ordinate
	void add(qm_real x, qm_real y) {m_sup.addkeyval(x,value_type(y,0,0)); m_ready = false;}
    /// \brief get a y-value form the spline
    /// @param x abscissa, @return ordinate
    virtual qm_real value(qm_real x) const {return 0;}
    virtual qm_real der1(qm_real x)  const {return 0;}
    virtual qm_real der2(qm_real x)  const {return 0;}
    
	template<class L>
	L ylist() const {
		L list;
		for(const_iterator it = m_sup.begin();it!=m_sup.end();++it)  list.append(it->value()[0]);
		return list;
	}
	
	template<class L>
	L klist() const {
		L list;
		for(const_iterator it = m_sup.begin();it!=m_sup.end();++it)  list.append(it->value()[1]);
		return list;
	}
    qm_real xval(unsigned i) 				const {return m_sup[i].key();}
    qm_real yval(unsigned i) 				const {return m_sup[i].value()[0];}
    void    set_yval(unsigned i, qm_real v)       {m_sup[i].get_value()[0] = v; m_ready = false;}
protected:
	bool        m_ready;
    qm_real     m_lowerDer;
    qm_real     m_upperDer;
    unsigned    m_lower_extrapolation;
    unsigned    m_upper_extrapolation;
    
    qm_real kval(unsigned i) const {return m_sup[i].value()[1];}
    void    set_kval(unsigned i, qm_real val) {m_sup[i].get_value()[1] = val;}
};



/// \brief The cubic spline.. Quite famous!!!
class cubic_spline: public spline_base  {
public:
	//typedef qmatrix<qm_real,tridiagonal>		qmat_type;
	typedef qmatrix<qm_real>		qmat_type;
	
	cubic_spline():m_sens_ready(false){}
	
    qm_real value(qm_real x) const;
    qm_real der1(qm_real x)  const;
    qm_real der2(qm_real x)  const;
    
    void     clear() {m_sens.resize(0,0); m_sens_ready = false;}
    
    /// \brief The Second derivative sensitivity matrix
    const qmat_type& sensitivity()  const;
    
    /// \brief evaluate the sensitivity of the value at x with respect node values
    qm_real dvdy(qm_real x, qmatrix<qm_real>& der) const;
    
    qmatrix<qm_real> dvaldy(qm_real x) const {
    	qmatrix<qm_real> der(this->size());
    	der.fill(0);
    	this->dvdy(x,der);
    	return der;
    }
    
    qm_string tostring() const {return "One dimensional cubic spline";}
protected:
	bool		m_sens_ready;
	qmat_type	m_sens;
	
	virtual void evaluate(bool evasens);
	virtual void evaluate_two_points();
    /// \brief retrive the coefficient of the cuic polinomial
    unsigned coef(qm_real x, qm_real& u, qm_real& h, qm_real& a, qm_real& b, qm_real& c, qm_real& d) const;
    cubic_spline& 	noConst() const { return const_cast<cubic_spline&>(*this); }
};



/// \brief 1D spline class for real numbers
/// \ingroup math 
class spline1d: public splineSupport<qm_real,tinyvec<qm_real,2> >  {
public:
	typedef qm_real											numtype;
	typedef tinyvec<qm_real,2>								value_type;
	typedef splineSupport<qm_real,value_type>				base_class;
	typedef base_class::support_type						support_type;
	typedef base_class::spline_support						spline_support;
	typedef base_class::const_iterator						const_iterator;
	typedef qmatrix<qm_real,tridiagonal>					qmat_type;
	
	spline1d():m_ready(false){}
	
	/// \brief Add a spline support point
	/// @param x abscissa @param @y ordinate
	void add(qm_real x, qm_real y) {m_sup.addkeyval(x,value_type(y,0)); m_ready = false;}
    /// \brief get a y-value form the spline
    /// @param x abscissa, @return ordinate
    qm_real value(qm_real x) const;
    qm_real der1(qm_real x)  const;
    //qm_real der2(qm_real x)  const;
    /// \brief evaluate the spline
    virtual void   evaluate(bool evalder = true);
    qm_string tostring() const {return "One dimensional cubic spline";}
    
    qmat_type lhs() const;
    
	template<class L>
	L ylist() const {
		L list;
		for(const_iterator it = m_sup.begin();it!=m_sup.end();++it)  list.append(it->value()[0]);
		return list;
	}
	
	template<class L>
	L klist() const {
		L list;
		for(const_iterator it = m_sup.begin();it!=m_sup.end();++it)  list.append(it->value()[1]);
		return list;
	}
protected:
	bool        m_ready;
    qm_real     m_lowerDer;
    qm_real     m_upperDer;

    /// \brief retrive the coefficient of the cuic polinomial
    void   coef(qm_int i, qm_real x, qm_real& A, qm_real& B, qm_real& C, qm_real& D) const;
    qm_int getCoef(qm_real x, qm_real& A, qm_real& B, qm_real& C, qm_real& D) const;
    unsigned dimension(unsigned&,unsigned&) const;
    void evaluate_matrices(qmat_type&, qmatrix<qm_real>&, unsigned, unsigned) const;
    
    qm_real xval(unsigned i) const {return m_sup[i].key();}
    qm_real yval(unsigned i) const {return m_sup[i].value()[0];}
    qm_real kval(unsigned i) const {return m_sup[i].value()[1];}
    void    set_kval(unsigned i, qm_real val) {m_sup[i].get_value()[1] = val;}
    spline1d& 	noConst() const { return const_cast<spline1d&>(*this); }
};

typedef QM_SMART_PTR(spline1d) SPLINE1D;



/*
class lspline1d: public spline1d  {
public:
	lspline1d(){}
	void   evaluate(bool evalder);
	qm_string tostring() const {return "ENO One dimensional cubic spline";}
private:
};
*/


QM_NAMESPACE_END2


#include <qmlib/math/tools/impl/spline_impl.hh>



#endif // __SPLINE_QM_HPP__


