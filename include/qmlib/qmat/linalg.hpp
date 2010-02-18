


#ifndef		__LINALG_QMAT_HPP__
#define		__LINALG_QMAT_HPP__


#include <qmlib/qmat/qmatrix.hpp>


/// \file
/// \brief Linear Algebra Computation

/*! \defgroup linalg Linear algebra

    A small linear algebra library

    @{
*/


QM_NAMESPACE2(math)

template<typename T>
struct linalg;

typedef linalg<qm_real> rlinalg;



class linalg_return  {
public:
	linalg_return(bool suc = true, const qm_string msg = ""):m_success(suc),m_msg(msg){}
	linalg_return(const qm_string msg):m_success(true),m_msg(msg){}
	linalg_return(const linalg_return& rhs):m_success(rhs.m_success),m_msg(rhs.m_msg){}
	linalg_return& operator = (const linalg_return& rhs) {
		m_success = rhs.m_success;
		m_msg     = rhs.m_msg;
		return *this;
	}
	operator bool () const {return m_success;}
	//bool operator () const {return m_success;}
	const qm_string& msg() const {return m_msg;}
	void check() const {QM_REQUIRE(m_success,m_msg);}
private:
	bool      m_success;
	qm_string m_msg;
};



/// \brief LU decomposition class
///
/// This class is used to perform LU decomposition of a square matrix A.
/// Given a square matrix, this function calculate the LU decomposition of a rowwise
/// permutation of itself. This method is used in conjunction with LUbacksb to solve
/// linear system of equations or invert a matrix.
/// The algorithm used is the Crout's method which has been adapted from Numerical Recipes.
template<typename T>
class LUdecomp  {
public:
	typedef T										numtype;
	typedef qmatrix<numtype> 						qmat;
	typedef qmatrix<unsigned> 						umat;
	typedef qmatrix<numtype,lower_triangular> 		ltriang;
	typedef qmatrix<numtype,upper_triangular> 		utriang;
	
	LUdecomp(const qmat& A):m_lu(A,true){this->doit();}
	
	qm_string     tostring() const {return "LU decomposition \n" + m_lu.tostring();}
	unsigned	  size()     const {return m_lu.rows();}
	linalg_return solve(qmat& x) const;
	linalg_return inverse(qmat& Ai) const;
	
	ltriang L() const;
	utriang U() const;
	
	template<class Li>
	Li permutation_list() const {
		Li co;
		for(unsigned i=0;i<m_lu.rows();i++)
			co.append(m_indx[i]);
		return co;		
	}
private:
	void doit();
	void backsub(qmat& x) const;
	qmat 			m_lu;
	umat			m_indx;
	linalg_return   m_ret;
};





/// \brief Linear algebra algorithm
///
/// Each algorithm has associated a number of flop to quantify the number of
/// operations involved. A flop is a floating point operation.
template<typename T = qm_real>
struct linalg  {
	typedef T										numtype;
	typedef qmatrix<numtype,lower_triangular> 		ltriang;
	typedef qmatrix<numtype,upper_triangular> 		utriang;
	typedef qmatrix<numtype,symmetric_matrix> 		symat;
	typedef qmatrix<numtype,tridiagonal>			trimat;
	typedef qmatrix<numtype> 						qmat;
	typedef qmatrix<numtype,diagonal>				diag_mat;
	typedef qmatrix<unsigned> 						umat;
	typedef linalg_return							ret_val;
	
	static numtype quiet_sqrt(numtype n)  {
		return n < 0 ? 0 : std::sqrt(n);
	}
	
	/// \brief Inverse of a matrix
	static linalg_return inverse(const qmat& A, qmat& Ai)  {
		LUdecomp<T> lu(A);
		return lu.inverse(Ai);
	}
	
	/// \brief Inverse of a diagonal matrix
	static linalg_return inverse(const diag_mat& A, diag_mat& Ai);
	
	/// \brief Forward substitution algorithm
	///
	/// Solve a linear system \f$L\ x = b\f$ where L is lower triangular.
	/// It requires \f$N^2\f$ flops.
	static linalg_return solve_lower_triangular(const ltriang& lhs, const qmat& b, qmat& x);
	
	/// \brief Backward substitution algorithm
	///
	/// Solve a linear system \f$L\ x = b\f$ where L is lower triangular.
	/// It requires \f$N^2\f$ flops.
	static linalg_return solve_upper_triangular(const utriang& lhs, const qmat& b, qmat& x);
	
	/// \brief Cholesky decomposition of a Symmetric positive definite matrix
	///
	/// The Cholesky decompositon decompose a symmetric positive definite matrix
	/// into the product \f$L\ L^T\f$ where \f$L\f$ is a lower triangular matrix.
	/// Positive definite means \f$ v A v > 0\f$ for all vectors \f$v\f$.
	/// This factorization is sometimes described as taking the square root of A.
	/// It requires \f$n^3/3\f$ flops.
	static linalg_return cholesky(const symat& A, ltriang& L);
	
	/// \brief QR decomposition
	///
	/// Transform a matrix A into the product \f$ Q\ R \f$ where Q is an orthogonal matrix, that is
	/// \f$ Q\ Q^T = I\f$ and R is upper_triangular.
	static linalg_return QR(const qmat& A, const qmat& Q, utriang& R);
	
	static linalg_return solve(const qmat& A, const qmat& b, qmat& x)  {
		LUdecomp<T> lu(A);
		x = b;
		return lu.solve(x);
	}
	
	static linalg_return solve(const symat& A, const qmat& b, qmat& x);
	
	static linalg_return solve(const trimat& A, const qmat& b, qmat& x);
	
	static linalg_return least_square(const qmat& A, const qmat& b, qmat& x);
};

template<class M>
class linalg_solve  {
public:
	typedef M							lhs_type;
	typedef typename lhs_type::numtype	numtype;
	typedef qmatrix<numtype> 			qmat;
	
	static qmat solve(const lhs_type& A, const qmat& b)  {
		qmat x(A.rows());
		linalg<numtype>::solve(A,b,x).check();
		return x;
	}
	
	static lhs_type inverse(const lhs_type& A)  {
		lhs_type Ai(A.rows(),A.rows());
		linalg<numtype>::inverse(A,Ai).check();
		return Ai;
	}
};

	
QM_NAMESPACE_END2

#include <qmlib/qmat/impl/ludecomp_impl.hh>
#include <qmlib/qmat/impl/linalg_impl.hh>

/*! @} */


#endif	//	__LINALG_QMAT_HPP__

