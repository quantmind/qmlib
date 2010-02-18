

#ifndef		__EXPR_TRAITS_QMAT_HPP__
#define		__EXPR_TRAITS_QMAT_HPP__


#ifndef __MATRIX_QMAT_HPP__
 #error <qmlib/qmat/expr_traits.hpp> must be included via <qmlib/qmat/matrix.hpp>
#endif


QM_NAMESPACE2(math)

// The traits class to_expr converts arbitrary things to
// expression templatable operands.

//  A scalar
template <typename T>
struct to_expr {
    typedef matrix_expr_constant<T> 	expression;
    static expression  get(const T& x) { return expression(x);}
};

//  Already an expression template term

template <typename T>
struct to_expr< matrix_expr<T> > {
    typedef matrix_expr<T> expression;
    static const expression& get(const expression& x) { return x; }
};

//  An array operand

template <typename T,unsigned N>
struct to_expr<matrix<T,N> > {
    typedef fast_iterator<T,N> expression;
    static expression get(const matrix<T,N>& x) { return x.beginFast(); }
};



//  A traits class that provides the return type of a binary operation.
template <template <typename T1> class OP, typename O1>
struct unary_expr_result {
    typedef matrix_expr< matrix_expr_unary_op<typename to_expr<O1>::expression,
        OP<typename as_expr<O1>::expr::numtype> > > result;
};


QM_NAMESPACE_END2


#endif	//	__EXPR_TRAITS_QMAT_HPP__

