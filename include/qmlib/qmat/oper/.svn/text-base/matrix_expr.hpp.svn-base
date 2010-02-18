
/********************************************************************************
 * qmlib/qmat/matrix_expr.hpp     Declaration of the matrix expression templates
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

#ifndef		__MATRIX_EXPR_QMAT_HPP__
#define		__MATRIX_EXPR_QMAT_HPP__


#ifndef __QMATRIX_QMAT_HPP__
 #error <qmlib/qmat/qmatrix_expr.hpp> must be included via <qmlib/qmat/qmatrix.hpp>
#endif

#include <qmlib/qmat/oper/ops.hpp>


/// \file
/// \brief Definition matrix expression templates
/// \ingroup qmat


QM_NAMESPACE2(math)


template<typename T1, typename T2>
class expr_pair {
public:
	expr_pair(const T1& a, const T2& b) : m_first(a), m_second(b) { }

    const T1& first() const  { return m_first; }
    const T2& second() const { return m_second; }

protected:
    T1 m_first;
    T2 m_second;
};

class matrix_expr_base  {
protected:
	matrix_expr_base(){}
};



/// \brief A constant matrix expression
/// \ingroup qmat
template<typename T>
class matrix_expr_constant : public matrix_expr_base {
public:
    typedef T			 						numtype;
    typedef matrix_expr_constant<numtype>		myself;
    typedef myself								reference;
    static const bool can_be_nested	= true;

    matrix_expr_constant(const myself& a): m_value(a.m_value)  { }
    matrix_expr_constant(numtype value): m_value(value) {}

    numtype operator()(unsigned i, unsigned j = 1, unsigned k = 1) const { return m_value; }
    
    numtype get_value() const {return m_value;}
private:
    numtype m_value;
};


/// \brief A general matrix expression
/// \ingroup qmat
template<typename expr, bool F = true>
class matrix_expr : public matrix_expr_base {
public:
	typedef expr								expression;	
	typedef typename expression::numtype 		numtype;
	typedef matrix_expr<expression,F>			myself;
	static const bool can_be_nested	= F;
	
	matrix_expr(const expression& value):m_value(value){}
	
	numtype operator() (unsigned i) 						const  { return m_value(i); }
	numtype operator() (unsigned i, unsigned j) 			const  { return m_value(i,j); }
	numtype operator() (unsigned i, unsigned j, unsigned k) const  { return m_value(i,j,k); }
	
protected:
	expression	m_value; 
};


template<typename expr, typename op>
class matrix_unary_op  {
public:
	typedef typename expr::numtype	numtype;
	typedef op						operation;
	
	matrix_unary_op(const expr& iter):m_expr(iter){}
	matrix_unary_op(const matrix_unary_op& rhs):m_expr(rhs.m_expr){}
	
	numtype operator() (unsigned i) 			const {return operation::apply(m_expr(i));}
	numtype operator() (unsigned i, unsigned j) const {return operation::apply(m_expr(i,j));}
private:
	expr	m_expr;
};


template<bool c1, bool c2>
struct check_nested {
	static const bool can_be_nested = c1 && c2;
};

/*
template<>
struct check_nested<true,true> {
	static const bool can_be_nested = true;
};
*/

/// \brief A binary operation between two matrix expressions
/// \ingroup qmat
template<class expr1, template<class,class> class op, class expr2>
class matrix_binary_op  {
public:
	typedef typename expr1::numtype					numtype1;
	typedef typename expr2::numtype					numtype2;
	typedef op<numtype1,numtype2>					operation;
	typedef typename operation::numtype				numtype;
	static const bool can_be_nested	= check_nested<expr1::can_be_nested, expr2::can_be_nested>::can_be_nested;
	
	matrix_binary_op(const matrix_binary_op& rhs):m_expr1(rhs.m_expr1),m_expr2(rhs.m_expr2){}
	matrix_binary_op(const expr1& expression1, const expr2& expression2):m_expr1(expression1),m_expr2(expression2) {}
	
	numtype operator() (unsigned i) 						const {return operation::apply(m_expr1(i),m_expr2(i));}
	numtype operator() (unsigned i, unsigned j) 			const {return operation::apply(m_expr1(i,j),m_expr2(i,j));}
	numtype operator() (unsigned i, unsigned j, unsigned k) const {return operation::apply(m_expr1(i,j,k),m_expr2(i,j,k));}
	
private:
	expr1	m_expr1;
	expr2	m_expr2;
};


template<class expr>
struct matrix_traits  {
	typedef matrix_expr<expr>	header;	// type in the function headers
	typedef matrix_expr<expr>	arg;	// type in the binary operation
	static arg getarg(const header& co) {return arg(co);}
};

//template<>
template<typename numtype, class S>
struct matrix_traits< qmatrix<numtype,S> >  {
	typedef qmatrix<numtype,S>		header;
	typedef qmatrix_ref<numtype,S>	arg;
	static arg getarg(const header& co) {return co.getref();}
};

/*
#define QM_NUMBER_MATRIX_TRAITS(name)							\
template<> struct matrix_traits< name >  {						\
	typedef name						header;					\
	typedef matrix_expr_constant<name>	arg;					\
	static arg getarg(const header& co) {return arg(co);}		\
};

QM_NUMBER_MATRIX_TRAITS(int);
QM_NUMBER_MATRIX_TRAITS(long);
QM_NUMBER_MATRIX_TRAITS(float);
QM_NUMBER_MATRIX_TRAITS(double);
*/



/// \brief Helper class for assignment of a matrix expression to a qmatrix< T, S >
/// @param T the numeric type
/// @param S the structure type
/// @param R the matrix expression type
/// \ingroup qmat
template<class T, class S, class R, bool F>
struct matrix_assign {
	
	matrix_assign(qmatrix<T,S>& lhs, const matrix_expr<R,F>& x)  {
		if(!lhs.size()) return;
		if(lhs.is_vector())  {
			for(unsigned i=0;i<lhs.rows();i++) lhs(i) = x(i);
		}
		else if(lhs.is_matrix())  {
			for(unsigned i=0;i<lhs.rows();i++)
				for(unsigned j=0;j<lhs.cols();j++)
					lhs(i,j) = x(i,j);
		}
		else QM_FAIL("NOT IMPLEMENTED YET");
	}
	
};


/// \brief Specialization of matrix_assign<T,D,R> for diagonal matrix
/// @param T the numeric type
/// @param R the matrix expression type
/// \ingroup qmat
template<class T, class R, bool F>
struct matrix_assign<T,diagonal,R,F> {
	
	matrix_assign(qmatrix<T,diagonal>& lhs, const matrix_expr<R,F>& x)  {
		if(!lhs.size()) return;
		for(unsigned i=0;i<lhs.rows();i++)
			lhs(i,i) = x(i,i);
	}
	
};

/// \brief Specialization of matrix_assign<T,D,R> for lower_triangular matrix
/// @param T the numeric type
/// @param R the matrix expression type
/// \ingroup qmat
template<class T, class R, bool F>
struct matrix_assign<T,lower_triangular,R,F> {
	
	matrix_assign(qmatrix<T,lower_triangular>& lhs, const matrix_expr<R,F>& x)  {
		if(!lhs.size()) return;
		for(unsigned i=0;i<lhs.rows();i++)
			for(unsigned j=0;j<=i;j++)
				lhs(i,j) = x(i,j);
	}
	
};




QM_NAMESPACE_END2


#include	<qmlib/qmat/oper/matuops.hpp>
#include	<qmlib/qmat/oper/matbops.hpp>

#endif	//	__MATRIX_EXPR_QMAT_HPP__

