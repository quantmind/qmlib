
/// \file
///
/// Template function to export the qmat library to python




#ifndef		__OPTION_WRAP_QM_HPP__
#define		__OPTION_WRAP_QM_HPP__


#include <qmlib/python/pyconfig.hpp>
//#include <qmlib/finance/options/core.hpp>


QM_NAMESPACE2(python)




/** \brief Export a an option_pricer class to Python
* \ingroup python
*/
/*
template<class M>
inline void export_option_pricer()  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(finance);
    	
    typedef M				 	 model;
    typedef option_pricer<model> modl;
    qm_string kla = model::klass();
    qm_string nam = model::name();
 
    class_<modl, bases<basedes> >(kla.c_str(),nam.c_str())
    	.def("fwdcall",		&modl::fwdcall)
    	;
    
}
*/

QM_NAMESPACE_END2


#endif	//	__OPTION_WRAP_QM_HPP__
