

#ifndef		__TINYOPER_QMAT_HPP__
#define		__TINYOPER_QMAT_HPP__


#ifndef __QMATRIX_QMAT_HPP__
 #error <qmlib/qmat/matbops.hpp> must be included via <qmlib/qmat/qmatrix.hpp>
#endif


QM_NAMESPACE2(math)

/// \brief Unary minus matrix expression for tinyvec
///
template<class numtype, unsigned N>
inline matrix_expr< matrix_unary_op< tinyvec_ref<numtype,N>, UnaryMinus<numtype> > >
operator - (const tinyvec<numtype,N>& v)  {
	typedef matrix_unary_op< tinyvec_ref<numtype,N>, UnaryMinus<numtype> > expr;
    return matrix_expr<expr>(expr(v.getref()));														\
}

// tinyvec and tinyvec
#define QM_TINYVEC_OPERATION(opName,opTag)																			\
template<class numtype1, class numtype2, unsigned N1>																\
inline matrix_expr< matrix_binary_op< tinyvec_ref<numtype1,N1>,														\
 									  opName,																		\
 									  tinyvec_ref<numtype2,N1> > >													\
operator opTag (const tinyvec<numtype1,N1>& d1,  const tinyvec<numtype2,N1>& d2)  {									\
    typedef matrix_binary_op< tinyvec_ref<numtype1,N1>, opName, tinyvec_ref<numtype2,N1> > expr;					\
    return matrix_expr<expr>(expr(d1.getref(),d2.getref()));														\
}

// Expression and tinyvec
#define QM_EXPRESSION_TINYVEC_OPERATION(opName,opTag)																\
template<class expr1, class numtype1, unsigned N1, bool F>															\
inline matrix_expr< matrix_binary_op< matrix_expr<expr1,F>,															\
 									  opName,																		\
 									  tinyvec_ref<numtype1,N1> >, F >												\
operator opTag (const matrix_expr<expr1,F>& d1, const tinyvec<numtype1,N1>& d2)  {									\
    typedef matrix_binary_op< matrix_expr<expr1,F>, opName, tinyvec_ref<numtype1,N1> > expr;						\
    return matrix_expr<expr,F>(expr(d1,d2.getref()));																\
}

// tinyvec and Expression
#define QM_TINYVEC_EXPRESSION_OPERATION(opName,opTag)																\
template<class numtype1, unsigned N1, class expr1, bool F>															\
inline matrix_expr< matrix_binary_op< tinyvec_ref<numtype1,N1>,														\
 									  opName,																		\
 									  matrix_expr<expr1,F> >, F >													\
operator opTag (const tinyvec<numtype1,N1>& d1,  const matrix_expr<expr1,F>& d2)  {									\
    typedef matrix_binary_op< tinyvec_ref<numtype1,N1>, opName, matrix_expr<expr1,F> > expr;						\
    return matrix_expr<expr,F>(expr(d1.getref(),d2));																\
}

// constant and tinyvec
#define QM_CONSTANT_TINYVEC_OPERATION(name,opName,opTag)															\
template<class numtype1, unsigned N1>																				\
inline matrix_expr< matrix_binary_op< matrix_expr_constant<name>,													\
 									  opName,																		\
 									  tinyvec_ref<numtype1,N1> > >													\
operator opTag (name c, const tinyvec<numtype1,N1>& d1)  {															\
    typedef matrix_binary_op< matrix_expr_constant<name>, opName, tinyvec_ref<numtype1,N1> > expr;					\
    return matrix_expr<expr>(expr(matrix_expr_constant<name>(c),d1.getref()));										\
}

// constant and tinymat
#define QM_CONSTANT_TINYMAT_OPERATION(name,opName,opTag)															\
template<class numtype1, unsigned R, unsigned C>																	\
inline matrix_expr< matrix_binary_op< matrix_expr_constant<name>,													\
 									  opName,																		\
 									  tinymat_ref<numtype1,R,C> > >													\
operator opTag (name c, const tinymat<numtype1,R,C>& d1)  {															\
    typedef matrix_binary_op< matrix_expr_constant<name>, opName, tinymat_ref<numtype1,R,C> > expr;					\
    return matrix_expr<expr>(expr(matrix_expr_constant<name>(c),d1.getref()));										\
}



/// \brief Matrix expression for row by column between tinymat and tinyvec
/// \ingroup qmat
template<class N1, class N2, unsigned R, unsigned C, unsigned K>
struct tinymat_row_by_column  {
	typedef typename QM_PROMOTE(N1,N2)	numtype;
	typedef tinymat_ref<N1,R,C> 		LHS;
	typedef tinymat_ref<N2,C,K>			RHS;
	
	tinymat_row_by_column(const LHS& lhs, const RHS& rhs):m_lhs(lhs),m_rhs(rhs){}
	
	numtype operator () (unsigned r, unsigned c)  {
		numtype s = 0;
		for(unsigned k=0;k<K;k++) s += m_lhs(r,k)*m_rhs(k,c);
		return s;
	}
	
	/*
	numtype apply(const LHS& lhs, const RHSv& rhs, unsigned r)  {
		numtype s = 0;
		for(unsigned c=0;c<C;c++) s += lhs(r,c)*rhs(c);
		return s;
	}
	
	numtype apply(const LHS& lhs, const RHS& rhs, unsigned r)  {
		QM_FAIL("should not be here, in tinymat_row_by_column");
	}
	
	numtype apply(const LHS& lhs, const RHSv& rhs, unsigned r, unsigned c)  {
		QM_FAIL("should not be here, in tinymat_row_by_column");
	}
	*/
protected:
	LHS		m_lhs;
	RHS		m_rhs;
};

template<class N1, class N2, unsigned R, unsigned C>
struct tinymat_row_by_column<N1,N2,R,C,0>  {};


template<class N1, class N2, unsigned R, unsigned C>
struct tinymat_row_by_column<N1,N2,R,C,1>  {
	typedef typename QM_PROMOTE(N1,N2)	numtype;
	typedef tinymat_ref<N1,R,C> 		LHS;
	typedef tinyvec_ref<N2,C>			RHS;
	
	tinymat_row_by_column(const LHS& lhs, const RHS& rhs):m_lhs(lhs),m_rhs(rhs){}
	
	numtype operator () (unsigned r) const {
		numtype s(0);
		for(unsigned k=0;k<C;k++) s += m_lhs(r,k)*m_rhs(k);
		return s;
	}
	
protected:
	LHS		m_lhs;
	RHS		m_rhs;
};




template<class N1, class N2, unsigned R, unsigned C, unsigned K>
inline matrix_expr< tinymat_row_by_column<N1,N2,R,C,K> , false>
mmult(const tinymat<N1,R,K>& lhs, const tinymat<N2,K,C>& rhs)  {
	typedef tinymat_row_by_column<N1,N2,R,C,K> 		mexpr;
	return matrix_expr<mexpr,false>(mexpr(lhs.getref(),rhs.getref()));
}

template<class N1, class N2, unsigned R, unsigned C>
inline matrix_expr< tinymat_row_by_column<N1,N2,R,C,1> , false>
mmult(const tinymat<N1,R,C>& lhs, const tinyvec<N2,C>& rhs)  {
	typedef tinymat_row_by_column<N1,N2,R,C,1>	mexpr;
	return matrix_expr<mexpr,false>(mexpr(lhs.getref(),rhs.getref()));
}


QM_TINYVEC_OPERATION(Add,+)
QM_TINYVEC_OPERATION(Subtract,-)
QM_TINYVEC_OPERATION(Multiply,*)
QM_TINYVEC_OPERATION(Divide,/)

QM_TINYVEC_EXPRESSION_OPERATION(Add,+)
QM_TINYVEC_EXPRESSION_OPERATION(Subtract,-)
QM_TINYVEC_EXPRESSION_OPERATION(Multiply,*)
QM_TINYVEC_EXPRESSION_OPERATION(Divide,/)

QM_EXPRESSION_TINYVEC_OPERATION(Add,+)
QM_EXPRESSION_TINYVEC_OPERATION(Subtract,-)
QM_EXPRESSION_TINYVEC_OPERATION(Multiply,*)
QM_EXPRESSION_TINYVEC_OPERATION(Divide,/)

QM_CONSTANT_TINYVEC_OPERATION(qm_real,Add,+)
QM_CONSTANT_TINYVEC_OPERATION(qm_real,Subtract,-)
QM_CONSTANT_TINYVEC_OPERATION(qm_real,Multiply,*)
QM_CONSTANT_TINYVEC_OPERATION(qm_real,Divide,/)

QM_CONSTANT_TINYMAT_OPERATION(qm_real,Add,+)
QM_CONSTANT_TINYMAT_OPERATION(qm_real,Subtract,-)
QM_CONSTANT_TINYMAT_OPERATION(qm_real,Multiply,*)
QM_CONSTANT_TINYMAT_OPERATION(qm_real,Divide,/)



template<class T1, class T2, unsigned R, unsigned C, unsigned K>
struct tiny_mult  {
	typedef typename QM_PROMOTE(T1,T2)		numtype;
	typedef tinymat<numtype,R,C>			ret_type;
	static ret_type doit(const tinymat<T1,R,K>& lhs, const tinymat<T2,K,C>& rhs)  {
		ret_type re;
		re = mmult(lhs,rhs);
		return re;
	}
};







QM_NAMESPACE_END2

#endif	//	__TINYOPER_QMAT_HPP__


