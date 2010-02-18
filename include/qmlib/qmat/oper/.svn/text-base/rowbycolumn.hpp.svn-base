

#ifndef __MATRIX_OPS_QMAT_HPP__
#define __MATRIX_OPS_QMAT_HPP__


#ifndef __QMATRIX_QMAT_HPP__
 #error <qmlib/qmat/matrix_ops.hpp> must be included via <qmlib/qmat/qmatrix.hpp>
#endif



QM_NAMESPACE2(math)

/// \brief Helper struct for row by column matrix multiplication
template<class N1, class S1, class N2, class S2>
struct row_by_column_multiplicator  {
	typedef typename QM_PROMOTE(N1,N2)	numtype;
	typedef qmatrix_ref<N1,S1> 			LHS;
	typedef qmatrix_ref<N2,S2> 			RHS;
	static numtype apply(const LHS& lhs, const RHS& rhs, unsigned K, unsigned r, unsigned c)  {
		numtype s = 0;
		for(unsigned k=0;k<K;k++) s += lhs(r,k)*rhs(k,c);
		return s;
	}
};


template<class N1, class N2, class S1>
struct row_by_column_multiplicator<N1,S1,N2,diagonal>  {
	typedef typename QM_PROMOTE(N1,N2)	numtype;
	typedef qmatrix_ref<N1,S1> 			LHS;
	typedef qmatrix_ref<N2,diagonal>	RHS;
	static numtype apply(const LHS& lhs, const RHS& rhs, unsigned K, unsigned r, unsigned c)  {
		return lhs(r,c)*rhs(c,c);
	}
};
/*
template<class N1, class N2, class S2>
struct row_by_column_multiplicator<N1,diagonal,N2,S2>  {
	typedef typename QM_PROMOTE(N1,N2)	numtype;
	typedef qmatrix_ref<N1,diagonal>	LHS;
	typedef qmatrix_ref<N2,S2>			RHS;
	static numtype apply(const LHS& lhs, const RHS& rhs, unsigned K, unsigned r, unsigned c)  {
		return lhs(r,r)*rhs(r,c);
	}
};
*/

template<class N1, class N2>
struct row_by_column_multiplicator<N1,lower_triangular,N2,upper_triangular>  {
	typedef typename QM_PROMOTE(N1,N2)					numtype;
	typedef qmatrix_ref<N1,lower_triangular> 			LHS;
	typedef qmatrix_ref<N2,upper_triangular> 			RHS;
	static numtype apply(const LHS& lhs, const RHS& rhs, unsigned K, unsigned r, unsigned c)  {
		numtype s = 0;
		unsigned m = std::min(r,c);
		for(unsigned k=0;k<=m;k++) s += lhs(r,k)*rhs(k,c);
		return s;
	}
};

template<class N1, class N2>
struct row_by_column_multiplicator<N1,upper_triangular,N2,lower_triangular>  {
	typedef typename QM_PROMOTE(N1,N2)					numtype;
	typedef qmatrix_ref<N1,upper_triangular> 			LHS;
	typedef qmatrix_ref<N2,lower_triangular> 			RHS;
	static numtype apply(const LHS& lhs, const RHS& rhs, unsigned K, unsigned r, unsigned c)  {
		numtype s = 0;
		unsigned m = std::max(r,c);
		for(unsigned k=m;k<K;k++) s += lhs(r,k)*rhs(k,c);
		return s;
	}
};



#define LOWER_TRIANGULAR_ROW_BY_COLUMN(name)															\
template<class N1, class N2>																			\
struct row_by_column_multiplicator<N1,lower_triangular,N2,name >  {										\
	typedef typename QM_PROMOTE(N1,N2)					numtype;										\
	typedef qmatrix_ref<N1,lower_triangular> 			LHS;											\
	typedef qmatrix_ref<N2,name >						RHS;											\
	static numtype apply(const LHS& lhs, const RHS& rhs, unsigned K, unsigned r, unsigned c)  {			\
		numtype s = 0;																					\
		for(unsigned k=0;k<=r;k++) s += lhs(r,k)*rhs(k,c);												\
		return s;																						\
	}																									\
};

LOWER_TRIANGULAR_ROW_BY_COLUMN(matrix_struct<row_column>)
LOWER_TRIANGULAR_ROW_BY_COLUMN(matrix_struct<column_row>)
LOWER_TRIANGULAR_ROW_BY_COLUMN(symmetric_matrix)





template<class N1, class S1, class N2, class S2>
class matrix_multiplication  {
public:
	typedef typename QM_PROMOTE(N1,N2)					numtype;
	typedef matrix_multiplication<N1,S1,N2,S2>  		myself;
	typedef row_by_column_multiplicator<N1,S1,N2,S2> 	multiplicator;
	
	typedef qmatrix_ref<N1,S1> LHS;
	typedef qmatrix_ref<N2,S2> RHS;

	matrix_multiplication(const myself& rhs):m_lhs(rhs.m_lhs),m_rhs(rhs.m_rhs),m_K(rhs.m_K){}
	
	matrix_multiplication(const LHS& lhs, const RHS& rhs):m_lhs(lhs),m_rhs(rhs)  {
		m_K = lhs.cols();
		QM_REQUIRE(m_K == m_rhs.rows(),"Matrix multiplication not possible");
	}

	numtype operator() (unsigned r) const  {return multiplicator::apply(m_lhs,m_rhs,m_K,r,0);}
	numtype operator() (unsigned, unsigned, unsigned) const  {QM_FAIL("Invalid invocation");}
	
	numtype operator() (unsigned r, unsigned c) const  {return multiplicator::apply(m_lhs,m_rhs,m_K,r,c);}
private:
	LHS			  m_lhs;
	RHS			  m_rhs;
	unsigned 	  m_K;
};




template<class N1, class S1, class N2, class S2>
inline matrix_expr< matrix_multiplication<N1,S1,N2,S2>, false >
mmult(const qmatrix<N1,S1>& lhs, const qmatrix<N2,S2>& rhs)  {
	typedef matrix_multiplication<N1,S1,N2,S2> mexpr;
	return matrix_expr<mexpr,false>(mexpr(lhs.getref(),rhs.getref()));
}


/// \brief Helper struct for row-column multiplication
/// \ingroup qmat
///
/// This structure is mainly used to expose row-column multiplication to Python
template<class N1, class S1, class N2, class S2, class Sr>
struct mat_mult  {
	typedef typename QM_PROMOTE(N1,N2)		numtype;
	typedef qmatrix<numtype,Sr>				ret_type;
	static ret_type doit(const qmatrix<N1,S1>& lhs, const qmatrix<N2,S2>& rhs)  {
		ret_type re(lhs.rows(),rhs.cols());
		re = mmult(lhs,rhs);
		return re;
	}
};



QM_NAMESPACE_END2


#endif	//	__MATRIX_OPS_QMAT_HPP__

