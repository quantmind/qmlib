
/********************************************************************************
 * qmlib/qmat/structure_base.hpp     Declaration of the qmatrix class
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

#ifndef __STRUCTURE_BASE_QMAT_HPP__
#define __STRUCTURE_BASE_QMAT_HPP__


#include	<qmlib/qmat/tiny.hpp>
#include 	<boost/serialization/split_member.hpp>

/// \file
/// \brief Definition of qmatrix base structures
/// \ingroup qmat


QM_NAMESPACE2(math)

/// \brief Row-column organization
/// \ingroup qmat
enum row_column_organization  {
	row_column = 0,
	column_row,
};


template<unsigned N> class structure_base;
template<> class structure_base<0> {};
template<> class structure_base<1> {};

template<unsigned> class structure_N;
template<> class structure_N<2> {};

template<row_column_organization D> class matrix_struct {};

template<class From, class To> struct copy_structure {};



/** \brief Base class template for matrix structures
 * \ingroup qmat
 * 
 * @param N The dimensionality of the structure
 */
template<unsigned N>
class structure_base: public basedes {
public:
	/// \brief The dimension holder object
	typedef tinyvec<unsigned,N>		dim_holder;
	/// \brief Dimensionality
	static const unsigned dimensionality = N;
	
	/*! @{ Constructors */
	structure_base():m_dims(0),m_size(0){}
	structure_base(const dim_holder& rhs):m_dims(0),m_size(0){init(rhs);}
	structure_base(const structure_base& rhs):m_dims(rhs.m_dims),m_size(rhs.m_size){}
	
	bool operator == (const structure_base& rhs) const {return m_dims == rhs.m_dims;}
	
	/// \brief Number of rows
	unsigned    rows()		const	{ return m_dims[0];}
	/// \brief Number of columns
	unsigned    cols()		const	{ return m_dims[1];}
	
	/// \brief The length of a dimension
	///
	/// This is a safe function with bound checks.
	///@param i dimension
	///@return the length in dimension i
	unsigned    length(unsigned i)	const   { return m_dims.get(i);}
	
	/// \brief The length of a dimension
	///
	/// This is an unsafe function without bound check in realese version.
	///@param i dimension
	///@return the length in dimension i
	unsigned    dim(unsigned i)	const   { return m_dims[i];}
	
	/// \brief Dimension holder
	///
	///@return an object with the structure dimensions
	const dim_holder& dimens() const {return m_dims;}
	
	/// \brief Size needed for memory allocation
	///
	///@return The number of elements in the structure
	unsigned size()			   const   { return m_size;}
	
	/// \brief True if a matrix structure
	bool     		 is_matrix()         const   { return dimensionality == 2;}
	/// \brief True if a vector (a matrix with a single column)
	virtual bool     is_vector()         const   { return dimensionality == 1;}
	/// \brief True if a square matrix
	virtual bool     is_square()         const   { return false;}
	
	template<class Archive>
	void save(Archive& ar, const unsigned int version) const  {
		ar & m_dims;
	}
	template<class Archive>
	void load(Archive& ar, const unsigned int version) {
		dim_holder dims;
		ar & dims;
		this->init(dims);
	}
	BOOST_SERIALIZATION_SPLIT_MEMBER()
protected:
	dim_holder	m_dims;
	unsigned    m_size;
	
	/// \brief Initialization from a dim_holder object
	///
	///@param rhs A dim_holder object
	bool init(const dim_holder& rhs) {
		this->checkdim(rhs);
		dim_holder d0(m_dims);
		m_dims = rhs;
		unsigned siz = 1;
		for(unsigned i=0;i<dimensionality;i++)
			siz *= m_dims[i];
		if(siz == 0) m_dims = 0;
		this->setsize();
		return m_dims != d0;
	}
	
	/// \brief Check for structure compatibility
	///
	/// @param rhs A dim_holder object.
	/// If compatibility is violated this function should throw an error.
	virtual void checkdim(const dim_holder& rhs) {}
	
	/// \brief Set the size
	///
	virtual void setsize() {
		this->m_size = 1;
		for(unsigned i=0;i<dimensionality;i++)
			this->m_size *= this->m_dims[i];
	}
};



/// \brief class template for generat N dimensions tensor
/// \ingroup qmat
template<unsigned N>
class structure_N : public structure_base<N> {
public:
	static const unsigned dimensionality = N;
	typedef structure_base<N>						base_structure;
	typedef typename base_structure::dim_holder		dim_holder;
	
	structure_N(){}
	structure_N(const structure_N& rhs):base_structure(rhs){}
	structure_N(const dim_holder& rhs):base_structure(rhs){}
	
	//template<class S>
	//structure_N(const S& rhs) {copy_structure<S,myself>(rhs,*this);}
};


/** \brief Base class for matrix structures
 * 
 * A matrix structure is defined as a Rows x Columns matrix
 * \ingroup qmat
 */
class matrix_structure_base: public structure_base<2>  {
public:
	typedef structure_base<2>	base_structure;
	
	matrix_structure_base(){}
	matrix_structure_base(unsigned r, unsigned c){this->init(dim_holder(r,c));}
	matrix_structure_base(const dim_holder& rhs):base_structure(rhs){}
	matrix_structure_base(const matrix_structure_base& rhs):base_structure(rhs){}
	
	bool 		is_vector() const   { return this->cols() == 1;}
	bool        is_square() const   { return this->rows() == this->cols();}
	qm_string   tostring() const {return this->name() + " ( " +
										object_to_string(this->rows()) + " x " +
		                                object_to_string(this->cols()) + " )";}
	
	// New functions
	
	/// \brief Resize the structure
	///
	///@param r Number of rows
	///@param c Number of columns
	bool resize(unsigned r, unsigned c)	{dim_holder d(r,c); return this->init(d);}
	
	// New virtual functions
	
	virtual bool  can_be_symmetric()  const   { return this->is_square();}
	virtual qm_string name()	const	{return "matrix";}
	virtual bool resize1(unsigned r)  	{return this->resize(r,1);}
	virtual bool iscompatible(unsigned r, unsigned c)	const   { return true;}
};



/** \brief Base class for squared matrix structures
 *  \ingroup qmat
 * 
 * Square matrices have the same number of rows and columns,
 * therefore have several properties that general matrices dont have.
 * The is_vector method always return false for this type of structures.
 */
class squared_struct : public matrix_structure_base {
public:
	squared_struct(unsigned dim = 0){initialize(dim,dim);}
	squared_struct(unsigned r, unsigned c){initialize(r,c);}
	squared_struct(const squared_struct& rhs):matrix_structure_base(rhs){}
	
	bool  is_vector() const   {return false;}
	bool  iscompatible(unsigned r, unsigned c) 	const { return r == c;}
	bool  resize1(unsigned r)  {return this->resize(r,r);}
protected:
	void initialize(unsigned r, unsigned c)  {
		QM_REQUIRE(r==c,"Wrong initialization of squared matrix");
		unsigned siz = r*c;
		if(siz > 0)  {
			m_dims[0] = r;
			m_dims[1] = r;
			m_size = r*r;
		}
	}
	void checkdim(const dim_holder& rhs) {
		QM_REQUIRE(rhs[0]==rhs[1],"Wrong initialization of squared matrix");
	}
};



/// Base class for a triangular structure
/// \ingroup qmat
class triangular_structure : public squared_struct {
public:
	triangular_structure(unsigned dim):squared_struct(dim){setsize();}
	triangular_structure(unsigned r, unsigned c):squared_struct(r,c){setsize();}
	triangular_structure(const triangular_structure& rhs):squared_struct(rhs){}
protected:
	void setsize() {this->m_size = this->sum(this->rows());}
	unsigned sum(unsigned n) const {return (unsigned)((n * (n + 1)) / 2);}
};



QM_NAMESPACE_END2

#endif	//	__STRUCTURE_BASE_QMAT_HPP__

