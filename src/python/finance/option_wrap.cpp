

#include <qmlib/python/pyconfig.hpp>
//#include <qmlib/finance/instruments/all.hpp>

/*

QM_NAMESPACE2(finance)


template<instrumentype typ, unsigned N, exercisetype et, payofftype pt>
void export_option(const qm_string& name, const qm_string& info = "")  {
	using namespace boost::python;
	//return_value_policy<copy_const_reference> ccr;

	typedef optioninst<typ,N,et,pt> vtype;
	
	register_ptr_to_python<QM_SMART_PTR(vtype) >();
	
	class_<vtype, bases<instrument> >(name.c_str(),info.c_str(),no_init)
	    //.add_property("exercise",		make_function(&vtype::exercise,ccr),"Exercise schedule")
	    .add_property("exercise",		&vtype::exercise,"Exercise schedule")
	    .add_property("payoff",			&vtype::payoff,"Payoff handle")
	    .add_property("style",			&vtype::exerciseType,"Exercise style")
	    .add_property("type",			&vtype::payoffType,"Type of payoff")
	    .add_property("count", 			&vtype::num_underlyings,"Number of underlying instruments")
	    //.add_property("pde",			&vtype::get_pde0,"Get a PDES model for pricing")
    	;
	def("option",vtype::make,"Create an option instrument");
}

QM_NAMESPACE_END2

*/


QM_NAMESPACE2(python)


void option_wrap()  {
/*
	using namespace boost::python;
	QM_USING_NAMESPACE2(finance);
	return_value_policy<copy_const_reference> ccr;
	
    enum_<exercisetype>("exercisetype")
    	.value("European",		European_)
        .value("American",		American_)
        .value("Bermudan",		Bermudan_)
        .export_values()
        ;
    //___________________________________________________________________________________________
    //	OPTIONS
    export_option<option_,1u,European_,Vanilla_>("ev_option","European vanilla option for 1 underlying");
    export_option<option_,1u,European_,Barrier_>("eb_option","European barrier option for 1 underlying");
    export_option<option_,1u,American_,Vanilla_>("ev_option","European vanilla option for 1 underlying");
    export_option<option_,1u,American_,Barrier_>("eb_option","European barrier option for 1 underlying");
    export_option<option_,1u,Bermudan_,Vanilla_>("ev_option","European vanilla option for 1 underlying");
    export_option<option_,1u,Bermudan_,Barrier_>("eb_option","European barrier option for 1 underlying");
    //___________________________________________________________________________________________
    
    
    //___________________________________________________________________________________________
    //	Exercise
    class_<ExerciseBase, bases<icodename,jsonrepr> >("exercise","Exercise class",no_init)
    	.def("__len__",				&ExerciseBase::size)
    	.def("__iter__",            boost::python::iterator<ExerciseBase>())
    	.def("__getitem__",			make_function(&ExerciseBase::get,ccr))
    	.add_property("style",		&ExerciseBase::Type)
    	.add_property("lastdate",	make_function(&ExerciseBase::lastDate,ccr))
    	.def("add",					&ExerciseBase::add,"date. Add a date")
    	.def("timegrid",			&ExerciseBase::get_timegrid)
        ;
    class_<Exercise<European_>, bases<ExerciseBase> >("european_exercise","European Exercise class")
    	;
    class_<Exercise<American_>, bases<ExerciseBase> >("american_exercise","American Exercise class")
    	;
    class_<Exercise<Bermudan_>, bases<ExerciseBase> >("bermudan_exercise","Bermudan Exercise class")
    	;
    //______________________________________________________________________________________________
	*/
}

QM_NAMESPACE_END2


