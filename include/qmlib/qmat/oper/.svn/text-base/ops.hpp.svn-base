
#ifndef		__OPS_QMAT_HPP__
#define		__OPS_QMAT_HPP__


#include <qmlib/qmat/oper/promote.hpp>


QM_NAMESPACE2(math)



#define QM_DEFINE_UNARY_OP(name,op)								\
template<typename T>											\
struct name {													\
    typedef T numtype;											\
                                                               	\
    static inline												\
	numtype apply(numtype a)   { return op a; }					\
};

QM_DEFINE_UNARY_OP(BitwiseNot,~)
QM_DEFINE_UNARY_OP(UnaryPlus,+)
QM_DEFINE_UNARY_OP(UnaryMinus,-)



#define QM_DEFINE_BINARY_OP(name,op)	        	            			\
template<typename numtype1, typename numtype2> 	    	        			\
struct name {                                           	    			\
																			\
	typedef typename QM_PROMOTE(numtype1, numtype2) numtype;		       	\
																			\
    static numtype			                                  				\
    apply(numtype1 a, numtype2 b) { return a op b; }            			\
};


QM_DEFINE_BINARY_OP(Add,+)
QM_DEFINE_BINARY_OP(Subtract,-)
QM_DEFINE_BINARY_OP(Multiply,*)
QM_DEFINE_BINARY_OP(Divide,/)
QM_DEFINE_BINARY_OP(Modulo,%)

//typedef QM_PROMOTE(double,long) test_promote;

QM_NAMESPACE_END2	

#endif		//	__OPS_QMAT_HPP__
