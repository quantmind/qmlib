


#include <qmlib/irates.hpp>
#include <qmlib/python/dataserie_wrap.hpp>
#include <qmlib/python/serialize.hpp>



QM_NAMESPACE2(python)


void irates_wrap()  {
    	
   	using namespace boost::python;
    	
   	//return_value_policy<copy_const_reference> ccr;
   	
   	//docstring_options doc_options(true,false);
   	register_ptr_to_python<DISCOUNTCURVE>();
   	register_ptr_to_python<OPTION_MODEL>();
   	register_ptr_to_python<CASHEVENT>();
    
   	export_dataserie<qdate,true,CASHEVENT>("cashflow","A keyvalue pair with keys given by dates for cash flows");
        
    class_<icashevent, bases<basedes> >("cashevent","Cash event",no_init)
       	.add_property("cash",				&icashevent::cash)
       	.add_property("notional",			&icashevent::notional)
       	.add_property("notional_exchange",	&icashevent::notional_exchange)
       	.add_property("tau",				&icashevent::tau)
       	.add_property("ntau",				&icashevent::ntau)
       	.add_property("dummy",				&icashevent::isdummy)
       	.add_property("value",				&icashevent::get_value)
       	;
    
    def("fixcash", fixcash::make1,"val,dummy.  Create a simple fix cash flow.");
    def("fixcash", fixcash::make2);
  	
  	class_<irate, bases<icodename> >("irate",
  			"Interface class for general Rates",no_init)
  		.def("__len__",				 	&irate::length)
  		.add_property("valid",		 	&irate::valid)
  		.add_property("date",	 	 	&irate::date, &irate::set_date,"Anchor date for the rate")
  		.def("sensitivities",			&irate::sens)
  		;

   	class_<itermstructure, bases<irate> >("itermstructure",
   			"base class for term structures",no_init)
   		.def("dcf",						&itermstructure::dcf, arg("dateT"), "Day count fraction between the rate date and dateT")
   		.add_property("daycounter",		&itermstructure::DayCounter, "Day counter object")
   		;
    	
   	class_<idiscountcurve, bases<itermstructure> >("idiscountcurve",
   			"base class for discount curves",no_init)
   		.def("df",						&idiscountcurve::dft,arg("Time"),"Discount factor at time Time")
   		.def("df",						&idiscountcurve::df,arg("Date"),"Discount factor at date Date")
   		.def("fwd",						&idiscountcurve::fwdt,args("T1","T2"),"Forward value between T1 and T2")
   		.def("dcashflow",				&idiscountcurve::dcashflow)
   		.def("dcashflow",				&idiscountcurve::dcashflow0)
   		.def("dcash",					&idiscountcurve::dcash,"Full discount of a single cash flow","inputs: {date/time} dte, {double} cash")
   		.def("dcash",					&idiscountcurve::dcasht)
   		.def("ccrate",					&idiscountcurve::exprate,arg("T"), "Continuously compounded rate")
   		.def("instfwd",					&idiscountcurve::instfwd,arg("T"), "Instantaneous forward rate")
   		.def("fwdrate",					&idiscountcurve::fwdrate,args("T1","T2","tau"),"forward rate between times T1 and T2 with year fraction tau")
   		;
   	
   	class_<discount_curve_holder>("discount_curve_holder",
   			"Helper class which holds a yield curve and a convenience yield curve",no_init)
   		.def("append",					&discount_curve_holder::addcurve<idiscountcurve>)
   		.add_property("ycurve",			&discount_curve_holder::ycurve)
   		.add_property("ccurve",			&discount_curve_holder::ccurve)
   		;
   	
   	class_<ivolsurface, bases<itermstructure, discount_curve_holder> >("ivolsurface",
   			"interface for volatility surfaces",no_init)
   		.def("striketomoneyness",		&ivolsurface::striketomoneyness)
   		.def("blackvol",				&ivolsurface::blackvol)
   		.def("bpvol",					&ivolsurface::bpvol)
   		;
   	
	class_<ioptionmodel, bases<itermstructure> >("ioptionmodel",
			"Interface class for option models",no_init)
		.add_property("method",			&ioptionmodel::method)
		;
}


QM_NAMESPACE_END2


