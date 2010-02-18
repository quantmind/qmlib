//
/// \file
/// \brief python wrapper for rndgen which extends polyphormism to python
/// \ingroup python
//
#ifndef __RNDGEN_WRAP_QM_HPP__
#define __RNDGEN_WRAP_QM_HPP__
//
//
#include <qmlib/python/converters.hpp>
#include <qmlib/math/stoch/diffusion.hpp>




QM_NAMESPACE2(python)

template<class C, unsigned N>
inline void export_affine_exponent(const std::string& name)  {
	
	using namespace boost::python;
	QM_USING_NAMESPACE2(math);
	
	typedef affine_exponent<C,N> 		rexpo;
	
	register_ptr_to_python<QM_SMART_PTR(rexpo) >();
	
	class_<rexpo, bases<basedes> >(name.c_str(),"Characteristic exponent of an affine stochastic process",no_init)
	   	.add_property("a", 				&rexpo::a)
	   	.add_property("b", 				&rexpo::b)
	   	.add_property("t0", 			&rexpo::t0)
	   	.add_property("t1", 			&rexpo::t1)
	   	.add_property("n", 				&rexpo::n)
	   	.add_property("iterations",		&rexpo::get_itern)
		.add_property("averageiter", 	&rexpo::get_aveiter)
	   	.add_property("disc",			&rexpo::disc)
	   	.def("value",					&rexpo::value)
	   	;
}


template<unsigned N>
void  export_processes()  {
	using namespace boost::python;
	QM_USING_NAMESPACE2(math);
	return_value_policy<copy_const_reference> ccr;
	
	qm_string ns = object_to_string(N);
	
	export_affine_exponent<qm_real,N>("real_char_exponent"+ns);
	export_affine_exponent<qm_complex,N>("cplx_char_exponent"+ns);
	
	qm_string na = "characteristic" + ns;
	typedef characteristic<N>	piin;
    class_<piin>(na.c_str(),"Characteristic function plugin",no_init)
    	.add_property("analytical_exponent",  	 &piin::analytical_exponent)
    	.add_property("analyticalcalc",  		 &piin::get_analyticalcalc, &piin::set_analyticalcalc)
    	.add_property("periodic",		  		 &piin::periodic_characteristic)
    	.add_property("period",					 &piin::characteristic_period)
    	.add_property("charfactors",			 make_function(&piin::charFactors,ccr))
    	.add_property("dtchar",					 &piin::get_dtchar, &piin::set_dtchar)
    	.add_property("rvector",				 &piin::template get_vec<qm_real>,"Return a real vector")
    	.add_property("cvector",				 &piin::template get_vec<qm_complex>,"Return a complex vector")
    	.add_property("odemaxiter",				 &piin::odemaxiter, &piin::set_odemaxiter,"Maximum number of iteration in the newthon Raphson implicit solver for the cumulant exponent")
		.add_property("tolerance",				 &piin::tolerance, &piin::set_tolerance,"Tolerance for checking convergence in the Newthon-Raphson solver")
		//.add_property("Theta",					 &piin::ThetaMat)
    	.def("cumulant",						 &piin::template get_cumulant<qm_real>)
    	.def("cumulant",						 &piin::template get_cumulant<qm_complex>)
    	.def("cexp",					 		 &piin::template get_characteristic_exponent<qm_real>)
    	.def("cexp",					 		 &piin::template get_characteristic_exponent<qm_complex>)
    	.def("cexp",					 		 &piin::template get_characteristic_exponent1<qm_real>)
    	.def("cexp",					 		 &piin::template get_characteristic_exponent1<qm_complex>)
    	.def("cexp",					 		 &piin::template get_characteristic_exponent2<qm_real>)
    	.def("cexp",					 		 &piin::template get_characteristic_exponent2<qm_complex>)
    	.def("ispositivecharacteristic",		 &piin::ispositive_characteristic,arg("i"),"Check if characteristic i is a positive process")
    	;
    
    na = "exponential_characteristic" + ns;
    typedef characteristic_exponential<N>	epiin;
    class_<epiin>(na.c_str(),"Characteristic exponential plugin",no_init)
    	.add_property("cprocess",  	 &epiin::cprocess,"The characteristic exponent process")
    	.add_property("multiplier",  make_function(&epiin::multiplier,ccr),"vector which multiply the characteristic exponent process")
    	;
    
    na = "diffusion" + ns;
    typedef diffusion<N>	dift;
    register_ptr_to_python<QM_SMART_PTR(dift)>();
    class_<dift, bases<istochastic> >(na.c_str(),"Diffusion process",no_init)
    	.def("drift",					&dift::drift)
    	.def("sigma",					&dift::sigma)
    	;
    
    na = "characteristicDiffusion" + ns;
    typedef CharacteristicDiffusion<N>	cdiff;
    register_ptr_to_python<QM_SMART_PTR(cdiff)>();
    class_<cdiff, bases<dift,piin> >(na.c_str(),"Characteristic diffusion process",no_init)
        ;
    
    na = "ExponentialCharacteristicDiffusion" + ns;
    typedef ExponentialCharacteristicDiffusion<N>	ecdiff;
    register_ptr_to_python<QM_SMART_PTR(ecdiff)>();
    class_<ecdiff, bases<dift,epiin> >(na.c_str(),"Exponential characteristic diffusion process",no_init)
        ;
    
    //def("eprocess",ecdiff::template make<dift>,"Create an exponential process");
    //def("eprocess",ecdiff::template make<cdiff>,"Create an exponential process");
}

QM_NAMESPACE_END2


#endif // __RNDGEN_WRAP_QM_HPP__

