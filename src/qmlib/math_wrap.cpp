//
/// \file
/// \ingroup python
/// \brief Exposes to Python the math library

#define NUMPYCPP_FILE_WITH_INIT


#include <qmlib/python/qmat_wrap.hpp>
//#include <qmlib/math/numbers/constants.hpp>
#include <qmlib/math/solvers/NewthonRaphson.hpp>
#include <qmlib/math/tools/brownian_bridge.hpp>


QM_NAMESPACE2(python)

  
template<typename T>
void export_root_result(const std::string& name, const std::string& info)  {
	
	import_array();

	using namespace boost::python;
	QM_USING_NAMESPACE2(math);
	
	typedef root_finder_result<T> root;
	
	register_ptr_to_python<QM_SMART_PTR(root)>();
	
	class_<root>(name.c_str(),info.c_str(),no_init)
		.def("__len__",           	&root::dimension)
		.def("str",					&root::tostring)	
    	.add_property("dimension",  &root::dimension)
    	.add_property("iterations", &root::iterations)
    	.add_property("tolerance",  &root::tolerance)
    	.add_property("ok",  		&root::success)
    	.def("__getitem__",         &root::get)
    	;
	
}
    




void math_wrap()  {
	using namespace boost::python;
    QM_USING_NAMESPACE2(math);

    //numpy_multi_array_converter< qmatrix<qm_real> >::register_to_and_from_python();
    //numpy_multi_array_converter< qmatrix<qm_int> >::register_to_and_from_python();
      
    export_tinyvec<qm_real,1>("dtiny1","1 value double vector");
    export_tinyvec<qm_real,2>("dtiny2","2 values double vector");
    export_tinyvec<qm_real,3>("dtiny3","3 values double vector");
    export_tinyvec<qm_real,4>("dtiny4","4 values double vector");
    export_tinyvec<qm_real,5>("dtiny5","5 values double vector");
    export_tinyvec<qm_real,6>("dtiny6","6 values double vector");
      
    export_tinyvec<qm_complex,1>("ctiny1","1 value complex vector");
    export_tinyvec<qm_complex,2>("ctiny2","2 values complex vector");
    export_tinyvec<qm_complex,3>("ctiny3","3 values complex vector");
    export_tinyvec<qm_complex,4>("ctiny4","4 values complex vector");
    export_tinyvec<qm_complex,5>("ctiny5","5 values complex vector");
    export_tinyvec<qm_complex,6>("ctiny6","6 values complex vector");
    
    export_tinymat<qm_real,1,1>("tmat1x1","1 by 1 tiny double matrix");
    export_tinymat<qm_real,2,2>("tmat2x2","2 by 2 tiny double matrix");
    export_tinymat<qm_real,3,3>("tmat3x3","3 by 3 tiny double matrix");
      
    export_qmatrix<qm_real,matrix_struct<row_column> >("rqmatrix","A matrix of real numbers");
    export_qmatrix<qm_complex,matrix_struct<row_column> >("cqmatrix","A matrix of real numbers");
    export_qmatrix<unsigned,matrix_struct<row_column> >("uqmatrix","A matrix of unsigned integers");
    export_qmatrix<qm_real,matrix_struct<column_row> >("rqmatrix_cr","A matrix of real numbers");
    export_qmatrix<qm_real,diagonal >("diagonal","A diagonal matrix of real numbers");
    export_qmatrix<qm_real,symmetric_matrix >("symmetric","A symmetric matrix of real numbers");
    export_qmatrix<qm_real,tridiagonal >("tridiagonal","A tridiagonal matrix of real numbers");
    export_qmatrix<qm_real,lower_triangular >("lowertriang","A lower tridiagonal matrix of real numbers");
    export_qmatrix<qm_real,upper_triangular >("uppertriang","An Upper tridiagonal matrix of real numbers");
      
    export_root_result<qm_real>("root_finder_result","Class which contains the solution of minimization and root finders results");
      
    export_ludecomp<qm_real>("ludecomp","LU decomposition class");
     
	def("qmatrix", &numpy_converter<qm_real, matrix_struct<column_row> >::convert);
    // Matrix operations and linear algebra
    def("mmult",  &mat_mult<qm_real,default_structure,qm_real,default_structure,default_structure>::doit,"Matrix multiplication");
    def("mmult",  &mat_mult<qm_real,default_structure,qm_real,diagonal,default_structure>::doit);
    def("mmult",  &mat_mult<qm_real,diagonal,qm_real,diagonal,diagonal>::doit);
    def("mmult",  &mat_mult<qm_real,lower_triangular,qm_real,upper_triangular,default_structure>::doit);
    def("mmult",  &mat_mult<qm_real,upper_triangular,qm_real,lower_triangular,default_structure>::doit);
    def("solve",  &linalg_solve<qmatrix<qm_real,tridiagonal> >::solve,"Solve a linear system of equation");
    def("solve",  &linalg_solve<qmatrix<qm_real,symmetric_matrix> >::solve);
    def("solve",  &linalg_solve<qmatrix<qm_real,default_structure> >::solve);
    def("inverse",&linalg_solve<qmatrix<qm_real,default_structure> >::inverse,"Inverse of matrix");
    def("inverse",&linalg_solve<qmatrix<qm_real,diagonal> >::inverse);
}

    
QM_NAMESPACE_END2


