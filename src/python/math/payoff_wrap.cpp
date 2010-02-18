

#include <qmlib/python/qmat_wrap.hpp>
#include <qmlib/payoffs/factory.hpp>


QM_NAMESPACE2(python)


void payoff_wrap()  {
	using namespace boost::python;

	//return_value_policy<copy_const_reference> ccr;
	
	typedef Payoff<1u,Vanilla_> vanilla_payoff;
	typedef Payoff<1u,Barrier_> barrier_payoff;
	
	register_ptr_to_python<BARRIER>();
	register_ptr_to_python<QM_SMART_PTR(vanilla_payoff)>();
	register_ptr_to_python<QM_SMART_PTR(barrier_payoff)>();

#	ifdef	QM_SERIALIZE
	typedef qmlib_pickle_suite<_striked_payoff> _striked_payoff_pickle;
#	endif	//	QM_SERIALIZE
	
    enum_<barriertype>("barriertype")
    	.value("KnockOut",		KnockOut_)
        .value("KnockIn",		KnockIn_)
        .export_values()
        ;
    enum_<payofftype>("payofftype")
    	.value("Vanilla",		Vanilla_)
        .value("Barrier",		Barrier_)
        .value("Average",		Average_)
        .export_values()
        ;
    enum_<payoffname>("payoffname")
    	.value("CALL",						CALL_)
        .value("PUT",						PUT_)
        .value("BINARY_CALL",				BINARY_CALL_)
    	.value("BINARY_PUT",				BINARY_PUT_)
    	.value("UP_AND_OUT", 				UP_AND_OUT_)
    	.value("UP_AND_IN", 				UP_AND_IN_)
    	.value("DOWN_AND_OUT", 				DOWN_AND_OUT_)
    	.value("DOWN_AND_IN", 				DOWN_AND_IN_)
    	.value("DOUBLE_NO_TOUCH", 			DOUBLE_NO_TOUCH_)
		.value("DOWN_AND_OUT_CALL", 		DOWN_AND_OUT_CALL_)
		.value("DOWN_AND_IN_CALL", 			DOWN_AND_IN_CALL_)
		.value("UP_AND_OUT_CALL", 			UP_AND_OUT_CALL_)
		.value("UP_AND_IN_CALL", 			UP_AND_IN_CALL_)
		.value("DOWN_AND_OUT_PUT", 			DOWN_AND_OUT_PUT_)
		.value("DOWN_AND_IN_PUT", 			DOWN_AND_IN_PUT_)
		.value("UP_AND_OUT_PUT", 			UP_AND_OUT_PUT_)
		.value("UP_AND_IN_PUT", 			UP_AND_IN_PUT_)
		.value("BINARY_CALL_CALL", 			BINARY_CALL_CALL_)
		.value("BINARY_PUT_PUT", 			BINARY_PUT_PUT_)
		.value("DOUBLE_BINARY_CALL_PUT", 	DOUBLE_BINARY_CALL_PUT_)
		.value("WORSEOF_CALL_CALL", 		WORSEOF_CALL_CALL_)
		.value("WORSEOF_PUT_PUT", 			WORSEOF_PUT_PUT_)
		.value("WORSEOF_CALL_PUT", 			WORSEOF_CALL_PUT_)
		.value("UNKNOWN_PAYOFF", 			UNKNOWN_PAYOFF_)
		;
    
    class_<BarrierBase, bases<icodename> >("barrier","",no_init)
        .add_property("barrier",		&BarrierBase::get_barrier,   &BarrierBase::set_barrier)
        .add_property("rebate",			&BarrierBase::get_rebate,    &BarrierBase::set_rebate)
        .add_property("type",			&BarrierBase::type)
        .add_property("up",				&BarrierBase::up)
        .def("knocked",					&BarrierBase::knocked,"Check if barrier has been knocked")
        ;
    
    //______________________________________________________________________________________________
    // PAYOFFS
	class_<Payoff<1u,Vanilla_>, bases<icodename> >("vanillaPayoff","A vanilla payoff", no_init)
	    .def("__getitem__",			&Payoff<1u,Vanilla_>::value)
	    .def("__getitem__",         &Payoff<1u,Vanilla_>::value2<tuple>)
	    .add_property("strike",	 	&Payoff<1u,Vanilla_>::get_strike,  &Payoff<1u,Vanilla_>::set_strike)
	    .add_property("input",		&Payoff<1u,Vanilla_>::input,"Input of payoff")
	    .add_property("type",		&Payoff<1u,Vanilla_>::Type)
	    .add_property("id",			&Payoff<1u,Vanilla_>::id)
	    .add_property("dimension",  &Payoff<1u,Vanilla_>::dimension)
	    //.def("makegrid",			&Payoff<1u,Vanilla_>::makegrid)
	    .add_property("boundaries",	&Payoff<1u,Vanilla_>::boundarylist<qm_list>)
    	;
	class_<Payoff<1u,Barrier_>, bases<icodename> >("barrierPayoff","A Barrier payoff", no_init)
	    .def("__getitem__",			&Payoff<1u,Barrier_>::value)
	    .def("__getitem__",         &Payoff<1u,Barrier_>::value2<tuple>)
	    .add_property("strike",	 	&Payoff<1u,Barrier_>::get_strike,  &Payoff<1u,Barrier_>::set_strike)
	    .add_property("upbarrier",	&Payoff<1u,Barrier_>::upbarrier)
	    .add_property("dobarrier",	&Payoff<1u,Barrier_>::dobarrier)
	    .add_property("input",		&Payoff<1u,Barrier_>::input,"Input of payoff")
	    .add_property("type",		&Payoff<1u,Barrier_>::Type)
	    .add_property("id",			&Payoff<1u,Barrier_>::id)
	    .add_property("dimension",  &Payoff<1u,Barrier_>::dimension)
	    .add_property("boundaries",	&Payoff<1u,Barrier_>::boundarylist<qm_list>)
    	;
		
    //______________________________________________________________________________________________

    def("call",		   		vanilla_factory<CALL_>::make);
    def("put",		   		vanilla_factory<PUT_>::make);
    def("bcall",	   		vanilla_factory<BINARY_CALL_>::make);
    def("bput",		   		vanilla_factory<BINARY_PUT_>::make);
    def("upAndOutCall",		barrier_factory<true,KnockOut_,UP_AND_OUT_CALL_,CALL_>::make);
    def("upAndOutPut",		barrier_factory<true,KnockOut_,UP_AND_OUT_PUT_,PUT_>::make);
    def("upAndInCall",		barrier_factory<true,KnockIn_,UP_AND_IN_CALL_,CALL_>::make);
    def("upAndInPut",		barrier_factory<true,KnockIn_,UP_AND_IN_PUT_,PUT_>::make);
    def("downAndOutCall",	barrier_factory<false,KnockOut_,DOWN_AND_OUT_CALL_,CALL_>::make);
    def("downAndOutPut",	barrier_factory<false,KnockOut_,DOWN_AND_OUT_PUT_,PUT_>::make);
    def("downAndInCall",	barrier_factory<false,KnockIn_,DOWN_AND_IN_CALL_,CALL_>::make);
    def("downAndInPut",		barrier_factory<false,KnockIn_,DOWN_AND_IN_PUT_,PUT_>::make);
    def("upAndOut",			barrier_factory<true,KnockOut_,UP_AND_OUT_>::make);
    def("upAndIn",			barrier_factory<true,KnockIn_,UP_AND_IN_>::make);
    def("downAndOut",		barrier_factory<false,KnockOut_,DOWN_AND_OUT_>::make);
    def("downAndIn",		barrier_factory<false,KnockIn_,DOWN_AND_IN_>::make);
    //_______________________________________________________________________________
    
}

QM_NAMESPACE_END2

