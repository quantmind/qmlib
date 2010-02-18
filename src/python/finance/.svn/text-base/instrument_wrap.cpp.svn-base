

#include <qmlib/python/pyconfig.hpp>
#include <qmlib/finance/instruments/all.hpp>
#include <qmlib/finance/ipricer.hpp>

QM_NAMESPACE2(finance)

template<class I>
finins wrap_instrument(QM_SMART_PTR(I) inst)  {
	return finins(inst);
}

QM_NAMESPACE_END2

QM_NAMESPACE2(python)

void instrument_wrap()  {
	using namespace boost::python;
	QM_USING_NAMESPACE2(finance);
	return_value_policy<copy_const_reference> ccr;
	
	register_ptr_to_python<INST>();
	
	enum_<instrumentype>("instrumentype")
		.value("deposit",				deposit_)
		.value("FRA",					fra_)
		.value("vanillaswap",		 	swap_)
		.value("interestRateFuture", 	irfuture_)
		.value("OIS",					ois_)
		.value("CMS",					cms_)
		.value("general",				general_)
		.value("option",				option_)
	;
	
    class_<instrument, bases<icodename, lazy> >("instrument","Financial instrument base class",no_init)
    	.add_property("results",			&instrument::results,"Contain results from calculation")
    	.add_property("type",				&instrument::type)	
    	.def("tojson",						&instrument::tojson)
    	//.add_property("settlement",			make_function(&instrument::settlement,ccr))
    	//.add_property("tenure",				&instrument::tenure)
    	//.add_property("istemplate",			&instrument::istemplate)
    	//.add_property("currency",			&instrument::currency)
    	;
    
    class_<finins, bases<icodename> >("finins","Financial instrument holder",init<const finins&>())
    	.add_property("results",			&finins::get_results,"Contain results from calculation")
    	.add_property("pricer",				&finins::get_pricer, &finins::set_pricer)
    	.add_property("type",				&finins::type)
    	.add_property("instrument",			&finins::get_instrument)
    	.def("tojson",						&finins::tojson)
    	;
    //_________________________________________________________________________
    //	INTERFACES
    //
    class_<instrate>("instrate","",no_init)
    	.add_property("rate",	&instrate::rate)
    	;
    class_<isimplediscount, bases<instrate> >("isimplediscount","",no_init)
    	.def("cashflow",				&isimplediscount::cashflow,arg("date"),"Create a cash flow from date")
    	.def("cashflow",		  		&isimplediscount::cashflow0)
    	.add_property("lastdate",		make_function(&isimplediscount::lastdate,ccr),"Last date in cashflow")
    	.add_property("expiry",		make_function(&isimplediscount::expiry,ccr),"expiry date")
    	.add_property("internalccr",	&isimplediscount::internalccr,"Internal Continuously Compounded Rate")
    	.add_property("priority", 		&isimplediscount::curvepriority,"Priority when used to build a yield curve")
    	.add_property("curvecode", 		&isimplediscount::simple_discount_string,"Code used in composite rate curve")
    	;
    class_<iccyplug>("ccyplug","",no_init)
    	.add_property("currency",		&iccyplug::currency)
    	.add_property("notional",		&iccyplug::notional, &iccyplug::set_notional)
    	;
    class_<otcir, bases<iccyplug, isimplediscount> >("otcir","",no_init)
        ;
    //_________________________________________________________________________
    
    //_________________________________________________________________________
    //	SECURITIES
    class_<security, bases<icodename> >("security","Financial Security",no_init)
        .add_property("currency",		&security::currency)
        .add_property("contrac",		&security::contrac)
        .add_property("expiry",			make_function(&security::expiry,ccr),"Expiry date of security")
        ;
    class_<future, bases<security> >("future","Financial Security",no_init)
        ;
    class_<irfuture, bases<future> >("irfuture","Interest Rate Future",no_init)
    	.add_property("depostart",		make_function(&irfuture::depostart,ccr),"Underlying deposit start date")
		.add_property("depoend",		make_function(&irfuture::depoend,ccr),"Underlying deposit end date")
		.add_property("tau",			&irfuture::tenure,"Day count fraction")
		.add_property("dc",				&irfuture::get_dc,"Day counter object")
    	;
    register_ptr_to_python<SECURITY>();
    register_ptr_to_python<FUTURE>();
    register_ptr_to_python<IRFUTURE>();
    
    def("future", future_factory::make);
    def("futures", future_factory::makelist<qm_list>,args("code","start","n"),"Create a list of n futures from start date");
    def("futures", future_factory::makelist2<qm_list>,args("code","start","end"),"Create a list of futures from start to end date");
    //_________________________________________________________________________
    //	FIXED INCOME
    
    def("otcir", otcir::make, args("interestrate","date"),"Create a vanilla interest rate instrument");

    // DEPOSIT
    class_<simpleir<deposit_>, bases<instrument,otcir> >("deposit","Simple interest rate deposit",no_init)
    	.add_property("info",		&simpleir<deposit_>::irleg)
        ;
    register_ptr_to_python<QM_SMART_PTR(simpleir<deposit_>) >();
    
    // FRA
    class_<simpleir<fra_>, bases<instrument,otcir> >("fra","Forward rate agreement",no_init)
    	.add_property("info",		&simpleir<fra_>::irleg)
        ;
    register_ptr_to_python<QM_SMART_PTR(simpleir<fra_> ) >();
    
    // IR FUTURE
    class_<irfutinst, bases<instrument,isimplediscount,iccyplug,instrate> >
    	("interestratefuture",init<IRFUTURE>())
    	.add_property("future",		&irfutinst::get_future,"Future object")
    	;
    //_________________________________________________________________________
    
    def("fininswrap", wrap_instrument<instrument>,arg("instrument"),"wrap an instrument with finins for pricing");
}

QM_NAMESPACE_END2

