
/********************************************************************************
 * qmlib/qmat/tiniy.hpp     Declaration of the qmatrix class
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


#ifndef __TINYVEC_QMAT_HPP__
#define __TINYVEC_QMAT_HPP__


#include <qmlib/qmat/qmat.hpp>
#include <qmlib/qmat/oper/promote.hpp>

/// \file
/// \brief Definition of tinyvec and tinymat
/// \ingroup qmat


QM_NAMESPACE2(math)

template<class T, class P> struct matrix_access;

template<typename P_expr, bool F>  class matrix_expr;

template<typename T, unsigned N_len> class tinyvec;
template<typename T, unsigned N_len> class tinyvec_ref;
template<typename T, unsigned N_rows, unsigned N_cols> class tinymat;
template<typename T, unsigned N_rows, unsigned N_cols> class tinymat_ref;

template<typename T, unsigned N_len, class P> struct tinyvec_make {};

template<typename T>
class tinyvec<T,0>{};


template<typename T, class R, bool F>
struct tiny_traits  {
	typedef matrix_expr<R,F>							expression_type;
	typedef typename expression_type::numtype			expression_numtype;
	typedef typename QM_PROMOTE(T,expression_numtype)	numtype;
};



/** \brief Tiny Vector class template
 * 
 * This template defined a small vector
 * @param T type of vector elements
 * @param N_len length of vector
 */
template<typename T, unsigned N_len>
class tinyvec  {
public:
	typedef T							numtype;
	typedef tinyvec<numtype,N_len>		myself;
	typedef tinyvec_ref<numtype,N_len>	myself_ref;
	
	tinyvec(){}
	~tinyvec(){}
	/// \brief value initialization
	tinyvec(const numtype val)  {for(unsigned i=0;i<N_len;++i) m_data[i] = val;}
	/// \brief Copy costructor
	tinyvec(const myself& rhs) {for(unsigned i=0;i<N_len;++i) m_data[i] = rhs.m_data[i];}
	///
	tinyvec(const numtype x0, const numtype x1);
	tinyvec(const numtype x0, const numtype x1,	const numtype x2);
	tinyvec(const numtype x0, const numtype x1,	const numtype x2, const numtype x3);
	tinyvec(const numtype x0, const numtype x1,	const numtype x2, const numtype x3,
			const numtype x4);
	tinyvec(const numtype x0, const numtype x1,	const numtype x2, const numtype x3,
			const numtype x4, const numtype x5);
	tinyvec(const numtype x0, const numtype x1,	const numtype x2, const numtype x3,
			const numtype x4, const numtype x5,	const numtype x6);
	
	/// \brief Create a tinyvec from an object P
	template<class P>
	static tinyvec make(const P& p) {tinyvec t; tinyvec_make<T,N_len,P>::make(p,t); return t;}
	
	unsigned  length() 					const 	{ return N_len; }
	qm_string tostring()				const;
	qm_real   norm2() const {numtype v(0); for(unsigned i=0;i<N_len;i++) v += m_data[i]*m_data[i]; return std::sqrt(std::abs(v)/N_len);}
	
	template<typename T2>
	typename QM_PROMOTE(T,T2) inner(const tinyvec<T2,N_len>& rhs) const {
		typedef typename QM_PROMOTE(T,T2) rettype;
		rettype v(0);
		for(unsigned i=0;i<N_len;i++) v += m_data[i] * rhs[i];
		return v;
	}
	
	template<class R, bool F>
	typename tiny_traits<T,R,F>::numtype
	inner(const matrix_expr<R,F>& rhs) const {
		typename tiny_traits<T,R,F>::numtype v(0);
		for(unsigned i=0;i<N_len;i++) v += m_data[i] * rhs(i);
		return v;
	}
	
	myself_ref	getref() const {return myself_ref(*this);}
	
	/// \brief Fast access operators but unsafe
	const numtype&  operator [] (unsigned i) 	const	{ QMAT_PRECONDITION(i<N_len,"Out of Bound"); return m_data[i];}
	const numtype&  operator () (unsigned i) 	const	{ QMAT_PRECONDITION(i<N_len,"Out of Bound"); return m_data[i];}
	numtype& operator [] (unsigned i) 			        { QMAT_PRECONDITION(i<N_len,"Out of Bound"); return m_data[i];}
	numtype& operator () (unsigned i) 			        { QMAT_PRECONDITION(i<N_len,"Out of Bound"); return m_data[i];}
	
	/// \brief slow operators but safe
	numtype  get(unsigned i) 	const			{ QM_REQUIRE(i<N_len,"Out of Bound"); return m_data[i];}
	void     set(unsigned i, numtype val) 		{ QM_REQUIRE(i<N_len,"Out of Bound"); m_data[i] = val;}
	
	bool operator == (const myself& rhs) const;
	bool operator != (const myself& rhs) const;
	
	template<typename T2>
	myself& operator = (T2 val) {for(unsigned i=0;i<N_len;i++) m_data[i] = val; return *this;}
	template<typename T2>
	myself& operator = (const tinyvec<T2,N_len>& rhs) {for(unsigned i=0;i<N_len;i++) m_data[i] = rhs[i]; return *this;}
	template<typename R, bool F>
	myself& operator = (const matrix_expr<R,F>& rhs) {for(unsigned i=0;i<N_len;i++) m_data[i] = rhs(i); return *this;}
	template<typename T2>
	myself& operator += (const tinyvec<T2,N_len>& rhs) {for(unsigned i=0;i<N_len;i++) m_data[i] += rhs[i]; return *this;}
	template<typename T2>
	myself& operator -= (const tinyvec<T2,N_len>& rhs) {for(unsigned i=0;i<N_len;i++) m_data[i] -= rhs[i]; return *this;}
	template<typename T2>
	myself& operator *= (T2 val) {for(unsigned i=0;i<N_len;i++) m_data[i] *= val; return *this;}
	template<class R, bool F>
	myself& operator += (const matrix_expr<R,F>& rhs) {for(unsigned i=0;i<N_len;i++) m_data[i] += rhs(i); return *this;}
	
	template<class L>
	L tolist() const {
		L co;
		for(unsigned i=0;i<N_len;++i)
			co.append(m_data[i]);
		return co;		
	}
	
	friend std::ostream& operator<<(std::ostream& os, const myself& og)  {
	   os <<  og.tostring() << std::endl;
	   return os;
	}
	
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & m_data;
	}
	
	void fill(const T& v) {*this = v;}
	void copydata(const myself& rhs) {*this = rhs;}
	myself copy() const {return myself(*this);}
private:
	numtype	m_data[N_len];
};



template<typename T, unsigned N_rows, unsigned N_cols>
struct tinymatoper;


template<typename T, unsigned N_rows, unsigned N_cols>
class tinymat  {
public:
	typedef T									numtype;
	typedef tinymat<numtype,N_rows,N_cols>		myself;
	typedef tinymat_ref<numtype,N_rows,N_cols>	myself_ref;
	
	tinymat(){}
	~tinymat(){}
	/// \brief value initialization
	tinymat(const numtype val)  {for(unsigned i=0;i<_size;++i) m_data[i] = val;}
	/// \brief Copy costructor
	tinymat(const myself& rhs) {for(unsigned i=0;i<_size;++i) m_data[i] = rhs.m_data[i];}
	
	tinymat(const numtype v0, const numtype v1,
			const numtype v2, const numtype v3);
	
	unsigned  length() 					const 	{ return _size; }
	unsigned  rows()					const   { return N_rows;}
	unsigned  cols()					const   { return N_cols;}
	qm_string tostring()				const;
	
	numtype  operator [] (unsigned i) 	const	{ QMAT_PRECONDITION(i<_size,"Out of Bound"); return m_data[i];}
	numtype& operator [] (unsigned i) 			{ QMAT_PRECONDITION(i<_size,"Out of Bound"); return m_data[i];}
	const numtype&  operator () (unsigned i, unsigned j) 	const	{ 
		QMAT_PRECONDITION(i<N_rows && j<N_cols,"Out of Bound");
		return m_data[N_rows*j + i];
	}
	numtype& operator () (unsigned i, unsigned j)	{ 
		QMAT_PRECONDITION(i<N_rows && j<N_cols,"Out of Bound");
		return m_data[N_rows*j + i];
	}
	
	/// \brief Slow but safe access functions
	numtype get1(unsigned i, unsigned j) const  {
		QM_REQUIRE(i<N_rows && j<N_cols,"Out of Bound");
		return (*this)(i,j);
	}
	void set1(unsigned i, unsigned j, const numtype& val)  {
		QM_REQUIRE(i<N_rows && j<N_cols,"Out of Bound");
		(*this)(i,j) = val;
	}
	
	myself_ref	getref() const {return myself_ref(*this);}
	
	template<typename T2>
	void operator = (T2 val) {for(unsigned i=0;i<_size;i++) m_data[i] = val;}
	template<typename T2>
	void operator = (const tinymat<T2,N_rows,N_cols>& rhs) {for(unsigned i=0;i<_size;i++) m_data[i] = rhs[i];}
	template<typename R, bool F>
	myself& operator = (const matrix_expr<R,F>& rhs) {
		for(unsigned i=0;i<N_rows;i++)
			for(unsigned j=0;j<N_cols;j++)
				(*this)(i,j) = rhs(i,j);
		return *this;
	}
	
	template<typename T2>
	myself& operator *= (T2 val) {for(unsigned i=0;i<_size;i++) m_data[i] *= val; return *this;}
	
	template<typename T2, typename T3>
	void inner(const tinyvec<T2,N_cols>& b, tinyvec<T3,N_rows>& res)  const  {
		for(unsigned r=0;r<N_rows;r++)  {
			T3 v(0);
			for(unsigned c=0;c<N_cols;c++) v += (*this)(r,c) * b(c);
			res(r) = v;
		}
	}
	template<typename T2, typename T3, unsigned K>
	void inner(const tinymat<T2,N_cols,K>& rhs, tinymat<T3,N_rows,K>& res)  const  {
		for(unsigned r=0;r<N_rows;r++)  {
			for(unsigned k=0;k<K;k++)  {
				T3 v(0);
				for(unsigned c=0;c<N_cols;c++) v += (*this)(r,c) * rhs(c,k);
				res(r,k) = v;
			}
		}
	}
	template<typename T2>
	void transpose(tinymat<T2,N_cols,N_rows>& rhs)  const  {
		for(unsigned r=0;r<N_rows;r++)
			for(unsigned c=0;c<N_cols;c++)  rhs(c,r) = (*this)(r,c);
	}
	
	void inv() {tinymatoper<T, N_rows, N_cols>::invert(*this);}
	myself inverse() const {myself im(*this); im.inv(); return im;}
private:
	numtype	m_data[N_rows * N_cols];
	static const unsigned _size = N_rows * N_cols; 
};




template<typename T, unsigned N_len>
class tinyvec_ref  {
public:
    typedef  T 						numtype;
    typedef  tinyvec<T,N_len>		holder;
    typedef  tinyvec_ref<T,N_len>	reference;
    
    static const bool can_be_nested	= true;
    
    tinyvec_ref(const holder& m):m_vec(&m) { }
    tinyvec_ref(const reference& rhs):m_vec(rhs.m_vec) { }

    const numtype& operator()(unsigned i) const {return (*m_vec)(i);}

private:
	tinyvec_ref() { } 

    const holder* m_vec;
};

template<typename T, unsigned N_rows, unsigned N_cols>
class tinymat_ref  {
public:
    typedef  T 								numtype;
    typedef  tinymat<T,N_rows,N_cols>		holder;
    typedef  tinymat_ref<T,N_rows,N_cols>	reference;
    
    static const bool can_be_nested	= true;
    
    tinymat_ref(const holder& m):m_vec(&m) { }
    tinymat_ref(const reference& rhs):m_vec(rhs.m_vec) { }

    const numtype& operator()(unsigned i,unsigned j) const {return (*m_vec)(i,j);}

private:
	tinymat_ref() { } 

    const holder* m_vec;
};














template<typename T, unsigned N_rows, unsigned N_cols>
struct tinymatoper {
	typedef tinymat<T,N_rows,N_cols> tmat;
	static void invert(tmat& m) {QM_FAIL("tinymatrix inversion not available");}
};



template<typename T>
struct tinymatoper<T,1,1> {
	typedef tinymat<T,1,1> tmat;
	static void invert(tmat& m) {m[0] = 1.0/m[0];}
};

template<typename T>
struct tinymatoper<T,2,2> {
	typedef tinymat<T,2,2> tmat;
	typedef T			   numtype;
	static void invert(tmat& m) {
		numtype a = m[0];
		numtype b = m[1];
		numtype c = m[2];
		numtype d = m[3];
		numtype de = a*d - b*c;
		QM_REQUIRE(de != numtype(0),"Singular matrix");
		de = numtype(1)/de;
		m[0] = d*de;
		m[1] =-b*de;
		m[2] =-c*de;
		m[3] = a*de;
	}	
};

template<typename T>
struct tinymatoper<T,3,3> {
	typedef tinymat<T,3,3>  tmat;
	typedef T				numtype;
	static void invert(tmat& m) {
		numtype a00 = m[0];
		numtype a10 = m[1];
		numtype a20 = m[2];
		numtype a01 = m[3];
		numtype a11 = m[4];
		numtype a21 = m[5];
		numtype a02 = m[6];
		numtype a12 = m[7];
		numtype a22 = m[8];
		numtype d00 = a11*a22 - a12*a21;
		numtype d01 =-a10*a22 + a12*a20;
		numtype d02 = a10*a21 - a11*a20;
		numtype d10 =-a01*a22 + a02*a21;
		numtype d11 = a00*a22 - a02*a20;
		numtype d12 =-a00*a21 + a01*a20;
		numtype d20 = a01*a12 - a02*a11;
		numtype d21 =-a00*a12 + a02*a10;
		numtype d22 = a00*a11 - a01*a10;
		numtype de  = a02*d02 + a12*d12 + a22*d22;
		QM_REQUIRE(de != numtype(0),"Singular matrix");
		de = numtype(1)/de;
		m[0] = d00*de;
		m[1] = d01*de;
		m[2] = d02*de;
		m[3] = d10*de;
		m[4] = d11*de;
		m[5] = d12*de;
		m[6] = d20*de;
		m[7] = d21*de;
		m[8] = d22*de;
	}	
};


/*
template<typename T, unsigned N_len>
struct tinyvec_make<T,N_len,T> {
	typedef tinyvec<T,N> vtype;
	static void make(const T& val, vtype& vec)  {
		QM_REQUIRE(T)
	}
};
*/




QM_NAMESPACE_END2


#include <qmlib/qmat/impl/tiny_impl.hh>




#endif // __TINYVEC_QMAT_HPP__
