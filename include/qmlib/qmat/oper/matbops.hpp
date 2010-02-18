

#ifndef		__MATBOPS_QMAT_HPP__
#define		__MATBOPS_QMAT_HPP__


#ifndef __QMATRIX_QMAT_HPP__
 #error <qmlib/qmat/matbops.hpp> must be included via <qmlib/qmat/matrix.hpp>
#endif


QM_NAMESPACE2(math)

// Matrix and Matrix
#define QM_MATRIX_OPERATION(opName,opTag)																			\
template<class numtype1, class numtype2, class S1, class S2>														\
inline matrix_expr< matrix_binary_op< qmatrix_ref<numtype1,S1>,														\
 									  opName,																		\
 									  qmatrix_ref<numtype2,S2> > >													\
operator opTag (const qmatrix<numtype1,S1>& d1,  const qmatrix<numtype2,S2>& d2)  {									\
    typedef matrix_binary_op< qmatrix_ref<numtype1,S1>, opName, qmatrix_ref<numtype2,S2> > expr;					\
    return matrix_expr<expr>(expr(d1.getref(),d2.getref()));														\
}

// Expression and Expression
#define QM_EXPRESSION_OPERATION(opName,opTag)																		\
template<class expr1, class expr2, bool F1, bool F2>																\
inline matrix_expr< matrix_binary_op< matrix_expr<expr1,F1>,														\
 									  opName,																		\
 									  matrix_expr<expr2,F2> >,														\
					check_nested<F1,F2>::can_be_nested>																\
operator opTag (const matrix_expr<expr1,F1>& d1, const matrix_expr<expr2,F2>& d2)  {								\
    typedef matrix_binary_op< matrix_expr<expr1,F1>, opName, matrix_expr<expr2,F2> > expr;							\
	return matrix_expr<expr,check_nested<F1,F2>::can_be_nested>(expr(d1,d2));										\
}

// Expression and Matrix
#define QM_EXPRESSION_MATRIX_OPERATION(opName,opTag)																\
template<class expr1, class numtype1, class S1, bool F1>															\
inline matrix_expr< matrix_binary_op< matrix_expr<expr1,F1>,															\
 									  opName,																		\
 									  qmatrix_ref<numtype1,S1> >, F1 >												\
operator opTag (const matrix_expr<expr1,F1>& d1, const qmatrix<numtype1,S1>& d2)  {									\
    typedef matrix_binary_op< matrix_expr<expr1,F1>, opName, qmatrix_ref<numtype1,S1> > expr;						\
    return matrix_expr<expr,F1>(expr(d1,d2.getref()));																\
}

// Matrix and Expression
#define QM_MATRIX_EXPRESSION_OPERATION(opName,opTag)																\
template<class numtype1, class S1, class expr1, bool F1>															\
inline matrix_expr< matrix_binary_op< qmatrix_ref<numtype1,S1>,														\
 									  opName,																		\
 									  matrix_expr<expr1,F1> >, F1 >													\
operator opTag (const qmatrix<numtype1,S1>& d1,  const matrix_expr<expr1,F1>& d2)  {								\
    typedef matrix_binary_op< qmatrix_ref<numtype1,S1>, opName, matrix_expr<expr1,F1> > expr;						\
    return matrix_expr<expr,F1>(expr(d1.getref(),d2));																\
}

// Matrix and Number
#define QM_MATRIX_AND_NUMBER_OPERATION(name,opName,opTag)															\
template<class numtype, class S>																					\
inline matrix_expr< matrix_binary_op< qmatrix_ref<numtype,S>, opName, matrix_expr_constant<name> > >				\
operator opTag (const qmatrix<numtype,S>& d1,  name d2)  {															\
    typedef matrix_binary_op< qmatrix_ref<numtype,S>, opName, matrix_expr_constant<name> > expr;					\
    return matrix_expr<expr>(expr(d1.getref(),matrix_expr_constant<name>(d2)));										\
}

// Number and Matrix
#define QM_NUMBER_AND_MATRIX_OPERATION(name,opName,opTag)															\
template<class numtype, class S>																					\
inline matrix_expr< matrix_binary_op<matrix_expr_constant<name>, opName, qmatrix_ref<numtype,S> > >					\
operator opTag (name d2, const qmatrix<numtype,S>& d1)  {															\
    typedef matrix_binary_op<matrix_expr_constant<name>, opName, qmatrix_ref<numtype,S> > expr;						\
    return matrix_expr<expr>(expr(matrix_expr_constant<name>(d2),d1.getref()));										\
}


// Expression and number
#define QM_EXPRESSION_AND_NUMBER_OPERATION(name,opName,opTag)														\
template<class expr1, bool F1>																						\
inline matrix_expr< matrix_binary_op< matrix_expr<expr1,F1>,														\
									  opName,																		\
									  matrix_expr_constant<name> >, F1 >											\
operator opTag (const matrix_expr<expr1,F1>& d1,  name d2)  {														\
    typedef matrix_binary_op< 	matrix_expr<expr1,F1>,																\
 								opName,																				\
								matrix_expr_constant<name> > expr;													\
    return matrix_expr<expr,F1>(expr(d1,matrix_expr_constant<name>(d2)));											\
}

// Number and Expression
#define QM_NUMBER_AND_EXPRESSION_OPERATION(name,opName,opTag)														\
template<class expr1, bool F1>																						\
inline matrix_expr< matrix_binary_op< matrix_expr_constant<name>,													\
									  opName,																		\
									  matrix_expr<expr1,F1> >, F1 >													\
operator opTag (name d1, const matrix_expr<expr1,F1>& d2)  {														\
    typedef matrix_binary_op< 	matrix_expr_constant<name>,															\
	  							opName,																				\
	  							matrix_expr<expr1,F1> > expr;														\
    return matrix_expr<expr,F1>(expr(matrix_expr_constant<name>(d1),d2));											\
}


QM_MATRIX_OPERATION(Add,+)
QM_MATRIX_OPERATION(Subtract,-)
QM_MATRIX_OPERATION(Multiply,*)
QM_MATRIX_OPERATION(Divide,/)

QM_EXPRESSION_OPERATION(Add,+)
QM_EXPRESSION_OPERATION(Subtract,-)
QM_EXPRESSION_OPERATION(Multiply,*)
QM_EXPRESSION_OPERATION(Divide,/)

QM_MATRIX_EXPRESSION_OPERATION(Add,+)
QM_MATRIX_EXPRESSION_OPERATION(Subtract,-)
QM_MATRIX_EXPRESSION_OPERATION(Multiply,*)
QM_MATRIX_EXPRESSION_OPERATION(Divide,/)

QM_EXPRESSION_MATRIX_OPERATION(Add,+)
QM_EXPRESSION_MATRIX_OPERATION(Subtract,-)
QM_EXPRESSION_MATRIX_OPERATION(Multiply,*)
QM_EXPRESSION_MATRIX_OPERATION(Divide,/)

QM_MATRIX_AND_NUMBER_OPERATION(int,Add,+)
QM_MATRIX_AND_NUMBER_OPERATION(long,Add,+)
QM_MATRIX_AND_NUMBER_OPERATION(float,Add,+)
QM_MATRIX_AND_NUMBER_OPERATION(double,Add,+)
QM_MATRIX_AND_NUMBER_OPERATION(int,Subtract,-)
QM_MATRIX_AND_NUMBER_OPERATION(long,Subtract,-)
QM_MATRIX_AND_NUMBER_OPERATION(float,Subtract,-)
QM_MATRIX_AND_NUMBER_OPERATION(double,Subtract,-)
QM_MATRIX_AND_NUMBER_OPERATION(int,Multiply,*)
QM_MATRIX_AND_NUMBER_OPERATION(long,Multiply,*)
QM_MATRIX_AND_NUMBER_OPERATION(float,Multiply,*)
QM_MATRIX_AND_NUMBER_OPERATION(double,Multiply,*)
QM_MATRIX_AND_NUMBER_OPERATION(int,Divide,/)
QM_MATRIX_AND_NUMBER_OPERATION(long,Divide,/)
QM_MATRIX_AND_NUMBER_OPERATION(float,Divide,/)
QM_MATRIX_AND_NUMBER_OPERATION(double,Divide,/)

QM_NUMBER_AND_MATRIX_OPERATION(int,Add,+)
QM_NUMBER_AND_MATRIX_OPERATION(long,Add,+)
QM_NUMBER_AND_MATRIX_OPERATION(float,Add,+)
QM_NUMBER_AND_MATRIX_OPERATION(double,Add,+)
QM_NUMBER_AND_MATRIX_OPERATION(int,Subtract,-)
QM_NUMBER_AND_MATRIX_OPERATION(long,Subtract,-)
QM_NUMBER_AND_MATRIX_OPERATION(float,Subtract,-)
QM_NUMBER_AND_MATRIX_OPERATION(double,Subtract,-)
QM_NUMBER_AND_MATRIX_OPERATION(int,Multiply,*)
QM_NUMBER_AND_MATRIX_OPERATION(long,Multiply,*)
QM_NUMBER_AND_MATRIX_OPERATION(float,Multiply,*)
QM_NUMBER_AND_MATRIX_OPERATION(double,Multiply,*)
QM_NUMBER_AND_MATRIX_OPERATION(int,Divide,/)
QM_NUMBER_AND_MATRIX_OPERATION(long,Divide,/)
QM_NUMBER_AND_MATRIX_OPERATION(float,Divide,/)
QM_NUMBER_AND_MATRIX_OPERATION(double,Divide,/)

QM_EXPRESSION_AND_NUMBER_OPERATION(int,Add,+)
QM_EXPRESSION_AND_NUMBER_OPERATION(long,Add,+)
QM_EXPRESSION_AND_NUMBER_OPERATION(float,Add,+)
QM_EXPRESSION_AND_NUMBER_OPERATION(double,Add,+)
QM_EXPRESSION_AND_NUMBER_OPERATION(int,Subtract,-)
QM_EXPRESSION_AND_NUMBER_OPERATION(long,Subtract,-)
QM_EXPRESSION_AND_NUMBER_OPERATION(float,Subtract,-)
QM_EXPRESSION_AND_NUMBER_OPERATION(double,Subtract,-)
QM_EXPRESSION_AND_NUMBER_OPERATION(int,Multiply,*)
QM_EXPRESSION_AND_NUMBER_OPERATION(long,Multiply,*)
QM_EXPRESSION_AND_NUMBER_OPERATION(float,Multiply,*)
QM_EXPRESSION_AND_NUMBER_OPERATION(double,Multiply,*)
QM_EXPRESSION_AND_NUMBER_OPERATION(int,Divide,/)
QM_EXPRESSION_AND_NUMBER_OPERATION(long,Divide,/)
QM_EXPRESSION_AND_NUMBER_OPERATION(float,Divide,/)
QM_EXPRESSION_AND_NUMBER_OPERATION(double,Divide,/)

QM_NUMBER_AND_EXPRESSION_OPERATION(int,Add,+)
QM_NUMBER_AND_EXPRESSION_OPERATION(long,Add,+)
QM_NUMBER_AND_EXPRESSION_OPERATION(float,Add,+)
QM_NUMBER_AND_EXPRESSION_OPERATION(double,Add,+)
QM_NUMBER_AND_EXPRESSION_OPERATION(int,Subtract,-)
QM_NUMBER_AND_EXPRESSION_OPERATION(long,Subtract,-)
QM_NUMBER_AND_EXPRESSION_OPERATION(float,Subtract,-)
QM_NUMBER_AND_EXPRESSION_OPERATION(double,Subtract,-)
QM_NUMBER_AND_EXPRESSION_OPERATION(int,Multiply,*)
QM_NUMBER_AND_EXPRESSION_OPERATION(long,Multiply,*)
QM_NUMBER_AND_EXPRESSION_OPERATION(float,Multiply,*)
QM_NUMBER_AND_EXPRESSION_OPERATION(double,Multiply,*)
QM_NUMBER_AND_EXPRESSION_OPERATION(int,Divide,/)
QM_NUMBER_AND_EXPRESSION_OPERATION(long,Divide,/)
QM_NUMBER_AND_EXPRESSION_OPERATION(float,Divide,/)
QM_NUMBER_AND_EXPRESSION_OPERATION(double,Divide,/)



// Number and Expression
#define QM_ROW_COLUMN_OPERATION(st1,st2)																			\
template<class N1, class st1, class N2, class st2>																	\
inline qmatrix<typename QM_PROMOTE(N1, N2),  matrix_binary_op< matrix_expr_constant<name>,													\
									  opName,																		\
									  matrix_expr<expr1> > >														\
operator opTag (name d1, const matrix_expr<expr1>& d2)  {															\
    typedef matrix_binary_op< 	matrix_expr_constant<name>,															\
	  							opName,																				\
	  							matrix_expr<expr1> > expr;															\
    return matrix_expr<expr>(expr(matrix_expr_constant<name>(d1),d2));												\
}







QM_NAMESPACE_END2

#endif	//	__MATBOPS_QMAT_HPP__
