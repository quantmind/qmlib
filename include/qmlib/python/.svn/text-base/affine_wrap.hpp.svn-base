
/// \file
///
/// Template function to export the qmat library to python




#ifndef		__AFFINE_WRAP_QM_HPP__
#define		__AFFINE_WRAP_QM_HPP__


#include <qmlib/python/rndgen_wrap.hpp>


QM_NAMESPACE2(python)




/// \brief Export a term structure model base class to Python
/// \ingroup python
template<unsigned N>
inline void export_tsmodel(const std::string& name, const std::string& info)  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(finance);
    	
    typedef ts_model<N> modl;
 
    class_<modl, bases<discountcurve, discount_curve_holder> >(name.c_str(),info.c_str(),no_init)
    	.add_property("analytical",  	 &modl::analytical)
    	.add_property("analyticalcalc",  &modl::analyticalcalc, &modl::set_calc)
    	.add_property("linear",     	 &modl::linear)
    	.add_property("factors",         &modl::factors)
    	.add_property("exactfit",		 &modl::get_exactfit, &modl::set_exactfit)
    	.def("dfspread",				 &modl::dfspread)
    	.def("dfspread",				 &modl::dfspreadt)
    	.def("oas",				 		 &modl::oas)
    	.def("oas",				 		 &modl::oas0)
    	;
    
}




/// \brief Export an Affine model to Python
/// \ingroup python
template<class Im>
inline void export_affine(const std::string& name, const std::string& info)  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(math);

    return_value_policy<copy_const_reference> ccr;
    
    typedef affine_model<Im>   			modl;
    
    register_ptr_to_python<QM_SMART_PTR(modl) >();
    
    class_<modl, bases<pii> >(name.c_str(),info.c_str(),init<>())
       	.add_property("params",     &modl::get_model)
       	.def("rho0",				&modl::get_rho0)
       	.def("rho0",				&modl::gets_rho0)
       	.def("rho1",				make_function(&modl::get_rho1,ccr))
       	.def("rho1",				make_function(&modl::gets_rho1,ccr))
       	.def("kappa",				make_function(&modl::get_Kappa,ccr))
       	.def("kappa",				make_function(&modl::gets_Kappa,ccr))
       	.def("kappat",				make_function(&modl::get_KappaT,ccr))
       	.def("kappat",				make_function(&modl::gets_KappaT,ccr))
       	.def("theta",				make_function(&modl::get_theta,ccr))
       	.def("theta",				make_function(&modl::gets_theta,ccr))
       	.def("Theta",				make_function(&modl::get_Theta,ccr))
       	.def("Theta",				make_function(&modl::gets_Theta,ccr))
       	.def("beta",				make_function(&modl::get_Beta,ccr))
       	.def("beta",				make_function(&modl::gets_Beta,ccr))
       	.def("alpha",				make_function(&modl::get_alpha,ccr))
       	.def("alpha",				make_function(&modl::gets_alpha,ccr))
       	.def("mktrisk",				&modl::get_mktrisk)
       	.add_property("factors",	&modl::factors)
       	.add_property("dt",		 	&modl::get_dt, &modl::set_dt)
       	.def("transform",           &modl::template transform<qm_real>)
       	.def("transform",           &modl::template transform<qm_complex>)
       	;
}


/// \brief Export an Affine Term Structure model to Python
/// \ingroup python
template<class Im>
inline void export_tsaffine(const std::string& name, const std::string& info)  {
	using namespace boost::python;
	QM_USING_NAMESPACE2(finance);
	
	typedef affine_tsmodel<Im>   		modl;
    typedef typename modl::base_class	base_class;
    typedef typename modl::MODEL_TYPE   MODEL_TYPE;
    
    register_ptr_to_python<QM_SMART_PTR(modl) >();
    
    class_<modl, bases<base_class> >(name.c_str(),info.c_str(),no_init)
       	.add_property("model",    	&modl::get_model)
       	.add_property("params",    	&modl::get_params)
       	;
}



QM_NAMESPACE_END2

#endif	//	__AFFINE_WRAP_QM_HPP__
