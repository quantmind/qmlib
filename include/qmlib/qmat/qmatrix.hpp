
/********************************************************************************
 * qmlib/qmat/qmatrix.hpp     Declaration of the qmatrix class
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

#ifndef __QMATRIX_QMAT_HPP__
#define __QMATRIX_QMAT_HPP__


#include <qmlib/qmat/structure/all.hpp>
#include <qmlib/qmat/memory/memoryblock.hpp>
#include <qmlib/qmat/tiny.hpp>
#include <qmlib/qmat/range.hpp>


/// \file
/// \brief Definition qmatrix, the class for numerical matrix computation
/// \ingroup qmat


QM_NAMESPACE2(math)

typedef matrix_struct<row_column>	default_structure;

template<typename T>
class const_qmat_iterator;


typedef qmatrix<qm_real,default_structure> 							rqmat;
typedef default_structure::transpos 								default_transpos;
typedef qmatrix<qm_real,default_transpos>							rqmatr;
typedef qmatrix<qm_real,symmetric_matrix> 							rsymat;
//typedef qmatrix<qm_real,squared_structure_rc>						rsquare;
typedef qmatrix<qm_int,default_structure>							iqmat;
typedef qmatrix_ref<qm_real,default_structure> 						rqmat_ref;



/** \brief qmatrix class template.
 *  \ingroup qmat
 * 
 * @param T	The number type
 * @param S The matrix structure
 */
template<typename T, class S = default_structure>
class qmatrix : public memoryblockRef<T> {
public:
	typedef T										numtype;
	typedef S										structure;
	typedef typename structure::transpos			transpos_structure;
	typedef typename structure::squaretype			square_structure;
	typedef qmatrix<numtype,structure>				myself;
	typedef qmatrix<numtype,transpos_structure>		transpos;
	typedef qmatrix_ref<numtype,structure>			myself_ref;
	typedef myself_ref								reference;
	typedef memoryblockRef<numtype>					base_class;
	typedef std::vector<unsigned>					shape_type;
	
	static const unsigned dimensionality = structure::dimensionality;
	
	/// \brief Default Constructor
	///
	/// Create a matrix and generate a structure
	/// @param d1 default dimension
	qmatrix(unsigned d1 = 0);
	
	/// \brief Matrix Constructor
	///
	/// Valid only for matrix structures
	/// @param rows number of rows
	/// @param cols number of columns
	explicit qmatrix(unsigned rows, unsigned cols);
	
	/// \brief Shallow Copy costructor. The default copy-constructor
	///
	/// The standard copy constructor perform a shallow copy of the object.
	/// The memory block is shared between the two instances.
	qmatrix(const qmatrix& rhs);
	
	/// \brief Seep Copy constructor
	///
	/// @param rhs The matrix to copy from
	/// @param copycontent If true the data is copied otherwise
	///        is equivalent to the standard copy-constructor
	qmatrix(const qmatrix& rhs, bool copycontent);
	
	qmatrix(const structure& rhs);

	/// \brief external data constructor
	///
	/// @param rows number of rows
	/// @param cols number of columns
	/// @param data pointer to external data
	qmatrix(unsigned rows, unsigned cols, numtype* data);

	template<class S2>
	qmatrix(const qmatrix<numtype,S2>& rhs, const structure& structur);
	/*! @} */
	
	/// \brief Total number of elements in the qmatrix
	unsigned    size()  				const   { return m_structure.size();}
	unsigned  	length(unsigned i)		const   { return m_structure.length(i);}
	/// \brief Number of rows
	unsigned  	rows() 					const 	{ return m_structure.rows();}
	/// \brief Number of columns
	unsigned  	cols() 					const 	{ return m_structure.cols();}
	bool        is_vector()				const   { return m_structure.is_vector();}
	bool        is_matrix()				const   { return m_structure.is_matrix();}
	bool 		is_square() 			const 	{ return m_structure.is_square();}
	bool        is_locked()				const   { return this->numReferences() > 1 || m_lock;}
	unsigned    num_dimensions()        const   { return structure::dimensionality;}
	bool 		is_symmetric(unsigned tole = 1000) const;
	bool 		is_same(const myself& rhs) const;
	const structure&  structur()		const 	{return m_structure;}
	
	qm_string   tostring()				const;
	
	/// \brief Return a symmetric matrix if the matrix is symmetric.
	///
	/// Thows an error if matrix is not symmetric;
	qmatrix<numtype,symmetric_matrix> get_symmetric(unsigned tole = 1000) const;
	
	
	// Fast access operators (in release mode). To be used in C++ only.
	const numtype&  operator () (unsigned r) 			 const 	{return m_structure.get_fast(this->m_data,r);}
	const numtype&  operator () (unsigned r, unsigned c) const 	{return m_structure.get_fast(this->m_data,r,c);}
	numtype& 		operator () (unsigned r)  					{return m_structure.set_fast(this->m_data,r);}
	numtype& 		operator () (unsigned r, unsigned c)  		{return m_structure.set_fast(this->m_data,r,c);}
	
	/// \brief Fast access to data
	numtype& operator [] (unsigned i) {
		QMAT_PRECONDITION(i<this->size(),"Out of bound in data access");
		return this->m_data[i];
	}
	/// \brief Fast access to data
	numtype operator [] (unsigned i) const {
		QMAT_PRECONDITION(i<this->size(),"Out of bound in data access");
		return this->m_data[i];
	}

	// Slow access (but safe) operators
	
	numtype get1(unsigned r, unsigned c) 			const	{return m_structure.get(this->m_data,r,c);}
	void set1(unsigned r, unsigned c, const numtype& val)	{m_structure.set(this->m_data,r,c) = val;}
	//
    myself& 	noConst() const { return const_cast<myself&>(*this); }
    myself_ref	getref() const {return myself_ref(*this);}
	
	myself& operator *= (numtype);
	
	/** \brief Fill the matrix with a given value
	 * 
	 * @param val Value to fill the matrix with
	 */
	void fill(const numtype& val) {(*this) = val;}
	
	//___________________________________________________________________
	// OPERATION ON DIAGONAL
	
	/// \brief Add Element to the diagonal matrix.
	///
	/// Prerequisites: 1) this must be a square matrix, 2) rhs must be e vector
	template<class S2>
	void add_to_diagonal(const qmatrix<numtype,S2>& rhs);
	template<class S2>
	void subtract_from_diagonal(const qmatrix<numtype,S2>& rhs);
	
	/// \brief Add Elements from a matrix_expr to the diagonal matrix
	///
	/// The matrix expression is treated as a vector
	///
	/// Prerequisites:
	///	 - this must be a square matrix 
	template<class R, bool F>
	void add_to_diagonal(const matrix_expr<R,F>& rhs);
	
	//____________________________________________________________________
	
	
	//template<typename N2, class S2>
	//myself& operator = (const qmatrix<N2,S2>&);
	
	//___________________________________________________________________
	// ASSIGNMENT OPERATORS
	
	/// \brief Assignment operator for a numtype
	myself& operator = (numtype);
	
	/// \brief Assignment operator for self
	myself& operator = (const myself&);
	
	/// \brief Assignment operator for a matrix expression
	template<typename R, bool F>
	myself& operator = (const matrix_expr<R,F>& x);
	
	//___________________________________________________________________
	
	//myself operator () (const range& r0) {
	//	return myself(*this,r0);
	//}
	
	//myself operator () (const range& r0, const range& r1) const  {
	//	return myself(this->noCost(),r0,r1);
	//}
	template<class N2, class S2>
	bool is_same_shape(const qmatrix<N2,S2>& rhs) const;
	
	shape_type shape() const {
		shape_type sh;
		sh.push_back(this->rows());
		if(this->cols() > 1)
			sh.push_back(this->cols());
		return sh;
	}

	void copy(const myself& rhs);
	
	myself duplicate(bool copycontent = true) const;
	//bool checkrange(unsigned r, const range& rang) const;
	
	/*! \brief resize the matrix
	 * 
	 * Two methods for resizing the matrix
	 * @{
	 */
	void resize1(unsigned r);
	void resize(unsigned r, unsigned c);
	/*! @} */
	
	// Unary operators returning a scalar number
	numtype min() const;
	numtype norm2() const;
	
	/// \brief square the matrix
	qmatrix<numtype,square_structure> square() const;
	/// \brief get the transpose
	transpos transpose() const;
	
	/// \brief swap the contents of two equal qmatrix
	friend void swapequal(qmatrix& lhs, qmatrix& rhs)  {
		QMAT_PRECONDITION(lhs.is_same_shape(rhs),"Matrices with different shapes");
		swapblockref(lhs,rhs);
	}
	
	friend std::ostream& operator<<(std::ostream& os, const myself& og)  {
	    os <<  og.tostring() << std::endl;
	    return os;
	}
	
	/// \brief fill with random values
	//void fill_random();
	//void fill_normal(qm_real mu, qm_real sigma);
	
	
	/// \brief Return a list containing the qmatrix
	///
	/// The list must support the method append
	template<class L>
	L tolist() const  {
		L l;
		if(this->is_vector())
			for(unsigned i=0;i<this->rows();i++)
				l.append((*this)(i));
		else if (this->is_matrix())
			for(unsigned i=0;i<this->rows();i++)  {
				L rl;
				for(unsigned j=0;j<this->cols();j++)
					rl.append(this->get1(i,j));
				l.append(rl);
			}
		return l;
	}
	
	
	template<class Archive>
	void save(Archive& ar, const unsigned int version) const {
		ar & m_structure;
		this->save_data(ar,m_structure.size());
	}
	
	template<class Archive>
	void load(Archive& ar, const unsigned int version) {
		ar & m_structure;
		this->load_data(ar,m_structure.size());
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()
	
private:
	structure	m_structure;
	bool		m_lock;
};



QM_NAMESPACE_END2




#include <qmlib/qmat/miter.hpp>
#include <qmlib/qmat/oper/matrix_expr.hpp>
#include <qmlib/qmat/oper/tinyoper.hpp>
#include <qmlib/qmat/impl/qmatrix_impl.hh>
#include <qmlib/qmat/oper/rowbycolumn.hpp>
#include <qmlib/qmat/oper/comparison.hpp>



QM_NAMESPACE


/// Specialize the convert struct for qmatrix and qmatrix.
/// Do a copy (shallow copy)
//template<>
template<class T, class S>
struct convert<QM_FROM_NAMESPACE2(math)qmatrix<T,S> ,QM_FROM_NAMESPACE2(math)qmatrix<T,S> >  {
	typedef QM_FROM_NAMESPACE2(math)qmatrix<T,S> qmat;
	convert(const qmat& from, qmat& to) {
		to.copy(from);
	}
};


QM_NAMESPACE_END






QM_NAMESPACE2(math)

typedef matrix_expr_constant<qm_real>	real_expr;
typedef Add<qm_real,qm_real> 			addreal;
typedef Multiply<qm_real,qm_real>		multreal;

QM_NAMESPACE_END2


#endif // __QMATRIX_QMAT_HPP__
