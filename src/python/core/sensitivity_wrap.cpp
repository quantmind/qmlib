

#include <qmlib/python/qmat_wrap.hpp>
#include <qmlib/sensitivity.hpp>


QM_NAMESPACE2(python)


void sensitivity_wrap()  {
	using namespace boost::python;
	
	return_value_policy<copy_const_reference> ccr;

#	ifdef	QM_SERIALIZE
	typedef qmlib_pickle_suite<sensitivity> sensitivity_pickle;
#	endif	//	QM_SERIALIZE
	
	register_ptr_to_python<SENSITIVITY>();
	register_ptr_to_python<QM_SMART_PTR(tinysens)>();
	
	enum_<pricingValuationMethod>("pricingValuationMethod")
		.value("analytical",	analytical_)
		.value("pde",			pde_)
		.value("montecarlo",	montecarlo_)
		.value("fourier",		fourier_)
		;
	
	class_<sensitivity, bases<icodename> >("sensitivity",
			"Model sensitivities sensitivities",no_init)
		.def("__len__",			&sensitivity::size)
		.add_property("values",	make_function(&sensitivity::values,ccr))
		.add_property("deltas",	make_function(&sensitivity::deltas,ccr))
		.add_property("gammas",	make_function(&sensitivity::gammas,ccr))
		.add_property("value",	&sensitivity::value,   &sensitivity::set_value)
		.add_property("theta",	&sensitivity::theta,   &sensitivity::set_theta)
		.add_property("date",	make_function(&sensitivity::date,ccr))
		.add_property("delta",	&sensitivity::delta,"delta or PV01")
		.add_property("gamma",	&sensitivity::gamma,"gamma or PV02")
		.add_property("rate",	&sensitivity::rate,"internal rate")
#		ifdef	QM_SERIALIZE
		.def_pickle(sensitivity_pickle())
#		endif	//	QM_SERIALIZE
		//.def("__getitem__",		&base_analytics::get_val)
		//.def("__setitem__",		&base_analytics::set_val)
		//.def("description",		&base_analytics::get_descr)
		//.def("tolist",			&base_analytics::tolist<qm_list,boost::python::dict>)
		//.def("dict",			&base_analytics::get_dict<boost::python::dict>)	
		;
	
	class_<sensitivities, bases<icodename> >("sensitivities","A collection of sensitivities")
		.def("__len__",			&sensitivities::size)
		.def("add",				&sensitivities::add<sensitivity>)
		.def("add",   			&sensitivities::update)
		.add_property("date",	make_function(&sensitivities::date,ccr))
		.def("__iter__",         boost::python::iterator<sensitivities>())
		.def("tolist",			&sensitivities::tolist<qm_list>)
		.def("clear",			&sensitivities::clear,"Clear all sensitivities")
#		ifdef	QM_SERIALIZE
		//.def_pickle(sensitivities_pickle())
#		endif	//	QM_SERIALIZE
		;
}

QM_NAMESPACE_END2
