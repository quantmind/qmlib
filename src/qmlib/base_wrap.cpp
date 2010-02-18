

#include <qmlib/corelib/info/timeparam.hpp>
#include <qmlib/python/containers_wrap.hpp>
#include <qmlib/corelib/tools/plugins.hpp>
#include <qmlib/corelib/tools.hpp>





QM_NAMESPACE2(python)


PARAMETER make_param(const qm_string& code, const qm_string& name, qm_real val)  {
	return parameter::make(code,name,val);
}
PARAMETER make_param1(const qm_string& code, const qm_string& name, qm_real val, qm_real lowb)  {
	return parameter::make(code,name,val,lowb);
}
PARAMETER make_param2(const qm_string& code, const qm_string& name, qm_real val, qm_real lowb, qm_real highb)  {
	return parameter::make(code,name,val,lowb,highb);
}


void base_wrap()  {
	using namespace boost::python;
    return_value_policy<copy_const_reference> ccr;
    
   	register_ptr_to_python<IVALUE>();
   	register_ptr_to_python<PARAMETER>();
   	export_hashvector<qm_string,iparameter>("parameters","Hash container of parameters");
    
    class_<basedes>("basedes","Base class for description",no_init)
    	.def("__str__",						&basedes::tostring)
    	.def("__repr__",					&basedes::representation)
    	.add_property("serializable",		&basedes::serializable)
    	;
    
    class_<icodename, bases<basedes> >("icodename", "Codename interface. An interface class of several classes.", no_init)
		.add_property("code",		&icodename::code)
		.add_property("name",		&icodename::name)
		;
    
    class_<codename, bases<basedes> >("codename", "Codename class. A base class of several classes.", no_init)
    	.add_property("code",		make_function(&codename::code,ccr))
    	.add_property("name",		make_function(&codename::name,ccr))
		;
    
    class_<ivalue, bases<basedes> >("ivalue","General Value Object",no_init)
		.add_property("valid",		 &ivalue::validvalue)
       	.add_property("value",		 &ivalue::get_value, &ivalue::set_value)
       	.add_property("rate",		 &ivalue::get_ratevalue)
       	.add_property("aspc",		 &ivalue::aspc)
       	.add_property("asbp",		 &ivalue::asbp)
       	;
    
    class_<iparameter, bases<icodename> >("iparameter","Parameter interface", init<>())
    	.add_property("const",				&iparameter::get_const)
    	.add_property("value",				&iparameter::get_value,   &iparameter::set_value)
    	.def("valuet",						&iparameter::get_valuet)
    	.def("integrated",					&iparameter::get_integrated)
    	.def("squareintegrated",			&iparameter::get_square_integrated)
		.add_property("active",				&iparameter::get_active,  &iparameter::set_active)
		.add_property("positive",			&iparameter::positive,"True if parameter can only be positive")
		.add_property("negative",			&iparameter::negative,"True if parameter can have negative values")
		.add_property("params",				&iparameter::params)
		.def("tojson",						&iparameter::tojson)
		.def("__call__",					&iparameter::get_value)
    	;
    
    class_<itersolver, bases<basedes> >("itersolver",
    		init<optional<unsigned,qm_real> >())
    	//.def(init<const itersolver&>())
    	.add_property("maxiter",			&itersolver::maxiter, 	&itersolver::set_maxiter)
    	.add_property("tolerance",			&itersolver::tolerance, &itersolver::set_tolerance)
    	.add_property("iter",			&itersolver::iter, 	&itersolver::set_iter,"Number of iterations performed")
    	.add_property("tole",			&itersolver::tole, 	&itersolver::set_tole,"Tolerance obtained")
    	;
    /*
    class_<factor, bases<basedes> >("factor","General factor", no_init)
    	.add_property("name",				make_function(&model_parameter::name,ccr))
    	.add_property("description",		make_function(&model_parameter::description,ccr))
    	.add_property("value",				&model_parameter::get_value,   &model_parameter::set_value)
    	;
    typedef parameter_list<true> param_list;
    class_<param_list >("parameter_list","General parameter list", no_init)
    	.def("__len__",						&param_list::numparams)
    	.def("__getitem__",					&param_list::get_slow)
    	.add_property("timehomogeneous",	&param_list::get_timehomo)
    	.def("__iter__",            		boost::python::iterator<param_list>())
    	;
    */
    def("parameter",parameter::make,args("code","name","value","lowboundary","highboundary","active"),"Create a parameter object");
    def("parameter",make_param);
    def("parameter",make_param1);
    def("parameter",make_param2);
    def("round",round<qm_real>,args("value","precision"));
    def("nicereal",nice_real,args("value","precision"));
}

QM_NAMESPACE_END2

