
#ifndef __COMPILE_STRUCTURE_QMAT_HPP__
#define __COMPILE_STRUCTURE_QMAT_HPP__


#include	<qmlib/qmat/structure/diagonal.hpp>


/// \file
/// \brief Defines compile time structure infomation
/// \ingroup qmat


QM_NAMESPACE2(math)

template<class S>
struct structureinfo {
	static const bool Square = false;
};

#define QM_QMAT_STRUCTURE_INFO(name)								\
template<>															\
struct structureinfo<name>  {										\
	static const bool Square = true;								\
};

QM_QMAT_STRUCTURE_INFO(lower_triangular)
QM_QMAT_STRUCTURE_INFO(upper_triangular)
QM_QMAT_STRUCTURE_INFO(squared_struct)
QM_QMAT_STRUCTURE_INFO(triangular_structure)
QM_QMAT_STRUCTURE_INFO(symmetric_matrix)
QM_QMAT_STRUCTURE_INFO(diagonal)
QM_QMAT_STRUCTURE_INFO(tridiagonal)


QM_NAMESPACE_END2


#endif	//	__COMPILE_STRUCTURE_QMAT_HPP__
