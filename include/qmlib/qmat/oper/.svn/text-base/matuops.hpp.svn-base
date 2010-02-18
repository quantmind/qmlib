

#ifndef		__MATUOPS_QMAT_HPP__
#define		__MATUOPS_QMAT_HPP__


#ifndef __QMATRIX_QMAT_HPP__
 #error <qmlib/qmat/matuops.hpp> must be included via <qmlib/qmat/matrix.hpp>
#endif


QM_NAMESPACE2(math)


template<class numtype, class S>
inline numtype min(const qmatrix<numtype,S>& mat)  { return mat.min();}

template<class numtype, class S>
inline qmatrix<numtype,symmetric_matrix> squared(const qmatrix<numtype,S>& mat)  { return mat.squared();}



template<typename N1, class S1, typename N2, class S2>
struct matrix_equal  {
	static void assign(qmatrix<N1,S1>& lhs, const qmatrix<N2,S2>& rhs)  {
		QMAT_PRECONDITION(lhs.rows() == rhs.rows() && lhs.cols() == rhs.cols(),
				"Matrix assignment failed. The two matricies have different structures");
		for(unsigned i=0;i<lhs.rows();++i)
			for(unsigned j=0;j<lhs.rows();++j)
				lhs(i,j) = rhs(i,j);
	}
};

template<typename N1, class S, typename N2>
struct matrix_equal<N1,S,N2,S>  {
	static void assign(qmatrix<N1,S>& lhs, const qmatrix<N2,S>& rhs)  {
		typedef typename qmatrix<N1,S>::structure       structure;
		QMAT_PRECONDITION(lhs.structur() == rhs.structur(),
				"Matrix assignment failed. The two matricies have different structures");
		for(unsigned i=0;i<lhs.size();++i)	lhs[i] = rhs[i];
	}
};

// Hide these
#define QMAT_HIDE_ASSIGNEMENT(st1,st2)										\
template<typename N1, typename N2>											\
struct matrix_equal<N1,st1,N2,st2>  {										\
	static void assign(qmatrix<N1,st2>& lhs, const qmatrix<N2,st1>& rhs)  {	\
		QM_FAIL("Could not assign matrix");									\
	}																		\
};
/*
QMAT_HIDE_ASSIGNEMENT(upper_triangular,lower_triangular);
QMAT_HIDE_ASSIGNEMENT(lower_triangular,upper_triangular);
QMAT_HIDE_ASSIGNEMENT(lower_triangular,symmetric_matrix);
QMAT_HIDE_ASSIGNEMENT(symmetric_matrix,lower_triangular);
QMAT_HIDE_ASSIGNEMENT(upper_triangular,symmetric_matrix);
QMAT_HIDE_ASSIGNEMENT(symmetric_matrix,upper_triangular);
QMAT_HIDE_ASSIGNEMENT(upper_triangular,squared_struct);
QMAT_HIDE_ASSIGNEMENT(lower_triangular,squared_struct);
QMAT_HIDE_ASSIGNEMENT(symmetric_matrix,squared_struct);
QMAT_HIDE_ASSIGNEMENT(upper_triangular,squared_structure_cr);
QMAT_HIDE_ASSIGNEMENT(lower_triangular,squared_structure_cr);
QMAT_HIDE_ASSIGNEMENT(symmetric_matrix,squared_structure_cr);
QMAT_HIDE_ASSIGNEMENT(upper_triangular,matrix_structure_rc);
QMAT_HIDE_ASSIGNEMENT(lower_triangular,matrix_structure_rc);
QMAT_HIDE_ASSIGNEMENT(symmetric_matrix,matrix_structure_rc);
QMAT_HIDE_ASSIGNEMENT(upper_triangular,matrix_structure_cr);
QMAT_HIDE_ASSIGNEMENT(lower_triangular,matrix_structure_cr);
QMAT_HIDE_ASSIGNEMENT(symmetric_matrix,matrix_structure_cr);

*/



QM_NAMESPACE_END2

#endif	//	__MATUOPS_QMAT_HPP__
