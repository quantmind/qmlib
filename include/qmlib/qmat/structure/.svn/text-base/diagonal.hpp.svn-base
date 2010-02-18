
#ifndef __DIAGONAL_STRUCTURE_QMAT_HPP__
#define __DIAGONAL_STRUCTURE_QMAT_HPP__


#include	<qmlib/qmat/structure/structure.hpp>


/// \file
/// \brief Definition of diagonal qmatrix structures.
/// \ingroup qmat


QM_NAMESPACE2(math)


/** \brief Diagonal structure
 * \ingroup qmat
 */
class diagonal: public squared_struct  {
public:
	typedef  diagonal		transpos;
	typedef  diagonal		squaretype;
	
	diagonal(unsigned dim = 0):squared_struct(dim){setsize();}
	diagonal(unsigned r, unsigned c):squared_struct(r,c){setsize();}
	diagonal(const diagonal& rhs):squared_struct(rhs){}
	
	transpos   transpose() const {return transpos(this->rows());}
	qm_string	name()	   const {return "diagonal";}
	
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
		QMAT_PRECONDITION(r == c,"Accessing the wrong diagonal. An afficient program should not do this.");
		return data[r];
	}
	
	template<typename numtype>
	numtype& set_fast(numtype* data, unsigned r, unsigned c) {
		QMAT_PRECONDITION(r == c,"Accessing the wrong diagonal. An afficient program should not do this.");
		return data[r];
	}
	
	template<typename numtype>
	numtype get(numtype* data, unsigned r, unsigned c) const  {
		QM_REQUIRE(r <= this->rows() && c <= this->rows(),"Out of bound");
		if(r == c)	return data[r];
		else return numtype(0);
	}
	
	template<typename numtype>
	numtype& set(numtype* data, unsigned r, unsigned c) {
		QM_REQUIRE(r <= this->rows() && c <= this->rows(),"Out of bound");
		if(r == c)	return data[r];
		else QM_FAIL("Cannot assign this index, it is zero.");
	}
protected:
	void setsize() {this->m_size = this->rows();}
};





/** \brief Tridiagonal structure
 * \ingroup qmat
 */
class tridiagonal: public squared_struct  {
public:
	typedef  tridiagonal		transpos;
	typedef  tridiagonal		squaretype;
	
	tridiagonal(unsigned dim = 0):squared_struct(dim){setsize();}
	tridiagonal(unsigned r, unsigned c):squared_struct(r,c){setsize();}
	
	qm_string	name()	   const {return "tridiagonal";}
	
	transpos   transpose() const {QM_FAIL("The transpose of a triangular matrix is not implemented yet");}
	
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
		int d = c - r + 1;
		QMAT_PRECONDITION(check(d,r,c),"Accessing the wrong diagonal. An afficient program should not do this.");
		return data[d*this->rows() + r];
	}
	
	template<typename numtype>
	numtype& set_fast(numtype* data, unsigned r, unsigned c) {
		int d = c - r + 1;
		QMAT_PRECONDITION(check(d,r,c),"Accessing the wrong diagonal. An afficient program should not do this.");
		return data[d*this->rows() + r];
	}
	
	template<typename numtype>
	numtype get(numtype* data, unsigned r, unsigned c) const  {
		int d = c - r + 1;
		if(check(d,r,c)) return data[d*this->rows() + r];
		else if(r < this->rows() && c < this->rows()) return 0;
		QM_FAIL("Out of Bound");
	}
	
	template<typename numtype>
	numtype& set(numtype* data, unsigned r, unsigned c) {
		int d = c - r + 1;
		if(check(d,r,c)) return data[d*this->rows() + r];
		else QM_FAIL("Cannot assign this index, it is zero.");
	}

private:
	bool check(int d, unsigned r, unsigned c) const {
		return d >= 0 && d <= 2 && r < this->rows() && c < this->rows();
	}
	void setsize()	{ this->m_size = 3*this->rows();}
};




class blocktridiagonal: public squared_struct  {
public:
	typedef  blocktridiagonal		transpos;
	typedef  blocktridiagonal		squaretype;
	
	blocktridiagonal(unsigned dim = 0):squared_struct(dim){}
	blocktridiagonal(unsigned r, unsigned c):squared_struct(r,c){}
	blocktridiagonal(const blocktridiagonal& rhs):squared_struct(rhs){}
};





QM_NAMESPACE_END2


#endif	//	__DIAGONAL_STRUCTURE_QMAT_HPP__
