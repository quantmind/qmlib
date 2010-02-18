

#ifndef __COMPARISON_QMAT_HPP__
#define __COMPARISON_QMAT_HPP__


#ifndef __QMATRIX_QMAT_HPP__
 #error <qmlib/qmat/comparison.hpp> must be included via <qmlib/qmat/qmatrix.hpp>
#endif



QM_NAMESPACE2(math)


template<typename N, class S1, class S2>
bool mat_close_enough(const qmatrix<N,S1>& m1, const qmatrix<N,S2>& m2, unsigned tole = 1000)  {
	if(!m1.is_same_shape(m2)) return false;
	if(!m1.is_matrix()) return false;
	for(unsigned i=0;i<m1.rows();++i)
		for(unsigned j=0;j<m1.cols();++j)
			if(!close_enough(m1(i,j),m2(i,j),tole)) return false;
	return true;
};


QM_NAMESPACE_END2


#endif	//	__COMPARISON_QMAT_HPP__
