
/********************************************************************************
 * qmlib/qmat/structure.hpp     Declaration of the qmatrix class
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

#ifndef __STRUCTURE_QMAT_HPP__
#define __STRUCTURE_QMAT_HPP__


#include	<qmlib/qmat/structure/structure_base.hpp>


/// \file
/// \brief Definition of qmatrix structures
/// \ingroup qmat



QM_NAMESPACE2(math)


class symmetric_matrix;





/// \brief Matrix structure, row-column organization
/// \ingroup qmat
template<>
class matrix_struct<row_column> : public matrix_structure_base  {
public:
	typedef matrix_struct<row_column>			myself;
	typedef matrix_struct<column_row>			transpos;
	typedef symmetric_matrix					squaretype;
	matrix_struct(){}
	matrix_struct(unsigned r, unsigned c = 1):matrix_structure_base(r,c){}
	matrix_struct(const myself& rhs):matrix_structure_base(rhs){}
	
	transpos    transpose()		const;
	
	//bool operator == (const myself& rhs) const {return m_rows == rhs.m_rows && m_cols == rhs.m_cols;}

	template<typename numtype>
	const numtype& get_fast(numtype* data, unsigned r) const  {
		QMAT_PRECONDITION(r < this->rows(),"Out of bound.");
		return data[r];
	}
	template<typename numtype>
	const numtype& get_fast(numtype* data, unsigned r, unsigned c) const  {
		QMAT_PRECONDITION(r < this->rows() && c < this->cols(),"Out of bound.");
		return data[c*this->rows() + r];
	}
	template<typename numtype>
	numtype& set_fast(numtype* data, unsigned r) {
		QMAT_PRECONDITION(r < this->rows(),"Out of bound.");
		return data[r];
	}	
	template<typename numtype>
	numtype& set_fast(numtype* data, unsigned r, unsigned c) {
		QMAT_PRECONDITION(r < this->rows() && c < this->cols(),"Out of bound.");
		return data[c*this->rows() + r];
	}

	template<typename numtype>
	const numtype& get(numtype* data, unsigned r, unsigned c) const  {
		QM_REQUIRE(r < this->rows() && c < this->cols(),"Out of bound.");
		return data[c*this->rows() + r];
	}	
	template<typename numtype>
	numtype& set(numtype* data, unsigned r, unsigned c) {
		QM_REQUIRE(r < this->rows() && c < this->cols(),"Out of bound.");
		return data[c*this->rows() + r];
	}
};


/// \brief Matrix structure, column-row organization
/// \ingroup qmat
template<>
class matrix_struct<column_row> : public matrix_structure_base  {
public:
	typedef matrix_struct<column_row>			myself;
	typedef matrix_struct<row_column>			transpos;
	typedef symmetric_matrix					squaretype;
	
	matrix_struct(){}
	matrix_struct(unsigned r, unsigned c = 1):matrix_structure_base(r,c){}
	matrix_struct(const myself& rhs):matrix_structure_base(rhs){}
	
	transpos    transpose()		const   { return transpos(this->cols(),this->rows());}
	
	//bool operator == (const myself& rhs) const {return m_rows == rhs.m_rows && m_cols == rhs.m_cols;}

	template<typename numtype>
	const numtype& get_fast(numtype* data, unsigned r) const  {
		QMAT_PRECONDITION(r < this->rows(),"Out of bound.");
		return data[r*this->cols()];
	}
	template<typename numtype>
	const numtype& get_fast(numtype* data, unsigned r, unsigned c) const  {
		QMAT_PRECONDITION(r < this->rows() && c < this->cols(),"Out of bound.");
		return data[r*this->cols() + c];
	}
	template<typename numtype>
	numtype& set_fast(numtype* data, unsigned r) const  {
		QMAT_PRECONDITION(r < this->rows(),"Out of bound.");
		return data[r*this->cols()];
	}	
	template<typename numtype>
	numtype& set_fast(numtype* data, unsigned r, unsigned c) {
		QMAT_PRECONDITION(r < this->rows() && c < this->cols(),"Out of bound.");
		return data[r*this->cols() + c];
	}
	
	template<typename numtype>
	const numtype& get(numtype* data, unsigned r, unsigned c) const  {
		QM_REQUIRE(r < this->rows() && c < this->cols(),"Out of bound.");
		return data[r*this->cols() + c];
	}
	
	template<typename numtype>
	numtype& set(numtype* data, unsigned r, unsigned c) {
		QM_REQUIRE(r < this->rows() && c < this->cols(),"Out of bound.");
		return data[r*this->cols() + c];
	}
};


inline matrix_struct<column_row>
matrix_struct<row_column>::transpose()	const {
	return matrix_struct<column_row>(this->cols(),this->rows());
}




class upper_triangular;


/// \brief lower trianular structure
/// \ingroup qmat
class lower_triangular: public triangular_structure  {
public:
	typedef  lower_triangular   	myself;
	typedef  triangular_structure	base_class;
	typedef  upper_triangular		transpos;
	typedef  symmetric_matrix		squaretype;
	
	lower_triangular(unsigned dim = 0):triangular_structure(dim){}
	lower_triangular(unsigned r, unsigned c):triangular_structure(r,c){}
	lower_triangular(const lower_triangular& rhs):triangular_structure(rhs){}
	
	qm_string  name() const {return "lower triangular";}
	
	bool      can_be_symmetric()     const {return false;}
	transpos	   	transpose()		 const;
	
	/// \brief fast get operator
	template<typename numtype>
	const numtype& get_fast(numtype* data, unsigned r, unsigned c) const  {
		QMAT_PRECONDITION(r >= c && r < this->rows(),"Bad access in lower triangulat matrix");
		return data[this->sum(r)+c];
	}
	/// \brief fast set operator	
	template<typename numtype>
	numtype& set_fast(numtype* data, unsigned r, unsigned c) {
		QMAT_PRECONDITION(r >= c && r < this->rows(),"Bad access in lower triangulat matrix");
		return data[this->sum(r)+c];
	}
	/// \brief slow get operator
	template<typename numtype>
	numtype get(numtype* data, unsigned r, unsigned c) const  {
		QM_REQUIRE(r < this->rows() && c < this->rows(),"Bad access in lower triangulat matrix");
		if(r < c) return numtype(0);
		return data[this->sum(r)+c];
	}
	/// \brief slow set operator
	template<typename numtype>
	numtype& set(numtype* data, unsigned r, unsigned c) {
		QM_REQUIRE(r >= c && r < this->rows(),"Bad access in lower triangulat matrix");
		return data[this->sum(r)+c];
	}
	
	
	/// \brief Bad access, Always throw an error
	template<typename numtype>
	const numtype& get_fast(numtype* data, unsigned r) const  {
		QM_FAIL("bad access in lower triangular. You cannot access with only one index");
	}
	/// \brief Bad access, Always throw an error
	template<typename numtype>
	numtype& set_fast(numtype* data, unsigned r) const  {
		QM_FAIL("bad access in lower triangular. You cannot access with only one index");
	}
	
};



/// \brief upper trianular structure
/// \ingroup qmat
class upper_triangular: public triangular_structure  {
public:
	typedef  upper_triangular	   				myself;
	typedef  triangular_structure				base_class;
	typedef  lower_triangular					transpos;
	typedef  symmetric_matrix					squaretype;
	
	upper_triangular(unsigned dim = 0):triangular_structure(dim){}
	upper_triangular(unsigned r, unsigned c):triangular_structure(r,c){}
	upper_triangular(const upper_triangular& rhs):triangular_structure(rhs){}
	
	qm_string  name() const {return "upper triangular";}
	
	bool can_be_symmetric()     const {return false;}
	transpos    transpose()     const {return transpos(this->rows());}
	
	template<typename numtype>
	const numtype& get_fast(numtype* data, unsigned r, unsigned c) const  {
		QMAT_PRECONDITION(r <= c && c < this->rows(),"Bad access in upper triangulat matrix");
		return data[this->sum(c)+r];
	}
	
	template<typename numtype>
	numtype& set_fast(numtype* data, unsigned r, unsigned c) {
		QMAT_PRECONDITION(r <= c && c < this->rows(),"Bad access in upper triangulat matrix");
		return data[this->sum(c)+r];
	}
	/// \brief slow get operator
	template<typename numtype>
	numtype get(numtype* data, unsigned r, unsigned c) const  {
		QM_REQUIRE(r < this->rows() && c < this->rows(),"Bad access in upper triangulat matrix");
		if(r > c) return numtype(0);
		return data[this->sum(c)+r];
	}
	/// \brief slow set operator
	template<typename numtype>
	numtype& set(numtype* data, unsigned r, unsigned c) {
		QM_REQUIRE(r <= c && c < this->rows(),"Bad access in upper triangulat matrix");
		return data[this->sum(c)+r];
	}
	
	
	/// \brief Bad access, Always throw an error
	template<typename numtype>
	const numtype& get_fast(numtype* data, unsigned r) const  {
		QM_FAIL("bad access in upper triangular. You cannot access with only one index");
	}
	/// \brief Bad access, Always throw an error
	template<typename numtype>
	numtype& set_fast(numtype* data, unsigned r) const  {
		QM_FAIL("bad access in upper triangular. You cannot access with only one index");
	}
};

inline upper_triangular lower_triangular::transpose() const {
	return upper_triangular(this->rows());
}



/// \brief Symmetric structure
/// \ingroup qmat
class symmetric_matrix: public triangular_structure  {
public:
	typedef symmetric_matrix	   	myself;
	typedef triangular_structure	base_class;
	typedef symmetric_matrix		transpos;
	typedef symmetric_matrix		squaretype;
	
	symmetric_matrix(unsigned dim = 0):base_class(dim){}
	symmetric_matrix(unsigned r, unsigned c):base_class(r,c){}
	symmetric_matrix(const symmetric_matrix& rhs):base_class(rhs){}
	
	qm_string  name() const {return "symmetrix";}
	
	bool is_symmetric() 		const {return true;}
	//bool operator == (const myself& rhs) const {return m_dim == rhs.m_dim;}
	//myself& operator = (const myself& rhs) {m_dim = rhs.m_dim; return *this;}
	
	transpos   transpose() const {return symmetric_matrix(this->rows());}
	
	template<typename numtype>
	const numtype& get_fast(numtype* data, unsigned r) const  {QM_FAIL("Need to access with two indices");}
	template<typename numtype>
	numtype& set_fast(numtype* data, unsigned r)   {QM_FAIL("Need to access with two indices");}
	template<typename numtype>
	numtype  get(numtype* data, unsigned r) const {QM_FAIL("Need to access with two indices");}
	template<typename numtype>
	numtype& set(numtype* data, unsigned r)  {QM_FAIL("Need to access with two indices");}
	
	template<typename numtype>
	const numtype& get_fast(numtype* data, unsigned r, unsigned c) const  {
		QMAT_PRECONDITION(c < this->rows() && r < this->rows(),"Bad access in symmetric matrix");
		return r >= c ? data[this->sum(r)+c] : data[this->sum(c)+r]; 
	}
	
	template<typename numtype>
	numtype& set_fast(numtype* data, unsigned r, unsigned c) {
		QMAT_PRECONDITION(c < this->rows() && r < this->rows(),"Bad access in symmetric matrix");
		return r >= c ? data[this->sum(r)+c] : data[this->sum(c)+r];
	}
	
	/// \brief Slow get operator
	template<typename numtype>
	numtype get(numtype* data, unsigned r, unsigned c) const  {
		QM_REQUIRE(c < this->rows() && r < this->rows(),"Bad access in symmetric matrix");
		return r >= c ? data[this->sum(r)+c] : data[this->sum(c)+r];
	}
	
	/// \brief Slow set operator
	template<typename numtype>
	numtype& set(numtype* data, unsigned r, unsigned c) {
		QM_REQUIRE(c < this->rows() && r < this->rows(),"Bad access in symmetric matrix");
		return r >= c ? data[this->sum(r)+c] : data[this->sum(c)+r];
	}
};




/// \brief Helper struct for comparison between qmatrix structures
/// \ingroup qmat
template<class S1, class S2>
struct structure_compare {
	static bool same_shape(const S1& s1, const S2& s2)  {
		return s1.rows() == s2.rows() && s1.cols() == s2.cols();
	}										
};


template<class S, unsigned N>
struct structure_compare<structure_N<N>,S>  {
	static bool same_shape(const structure_N<N> s1, const S& s2)  {return false;}
};

template<class S, unsigned N>
struct structure_compare<S,structure_N<N> >  {
	static bool same_shape(const S& s1, const structure_N<N> s2)  {return false;}
};

//template<>
template<unsigned N1, unsigned N2>
struct structure_compare<structure_N<N1>, structure_N<N2> >  {
	static bool same_shape(const structure_N<N1>& s1, const structure_N<N2>& s2)  {return false;}
};


QM_NAMESPACE_END2

#endif	//	__STRUCTURE_QMAT_HPP__
