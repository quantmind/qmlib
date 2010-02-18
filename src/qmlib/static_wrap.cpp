


#include <qmlib/python/converters.hpp>
#include <qmlib/corelib/static/all.hpp>


QM_NAMESPACE2(python)


void static_wrap()  {
    
	using namespace boost::python;
    	
   	//return_value_policy<copy_const_reference> ccr;
    
   	register_ptr_to_python<TC>();
   	register_ptr_to_python<ADJ>();
    
    
    enum_<BizDayConv>("BizDayConv")
    	.value("foll",			foll)
        .value("modfoll",		modfoll)
        .value("prec",			prec)
        .value("modprec",		modprec)
        .value("unadjusted",	unadjusted)
        .export_values()
        ;
    
    class_<TradingCentres, bases<icodename> >("tcs", "Collection of TradingCentre object.", init< optional<qm_string> >())
       .add_property("count",         &TradingCentres::count)
       .add_property("code",          &TradingCentres::code)
       .def("isbizday",               &TradingCentres::isbizday)
       .def("adjust",				  &TradingCentres::adjust)
       .def("numbizdays",             &TradingCentres::numbizdays)
       .def("nextbizday",             &TradingCentres::nextbizday)
       .def("prevbizday",             &TradingCentres::prevbizday)
       .def("parseinterval",	      &TradingCentres::parseinterval1)
       ;
    
    class_<dateAdjustment, bases<basedes> >("dateAdjustment",
    		"Object used to adjust dates on non-business days",
    		 init<optional<BizDayConv,short> >())
    	.def(init<qm_string,BizDayConv,short>())
    	.add_property("hols",		 &dateAdjustment::hols)
    	.add_property("bzc",		 &dateAdjustment::bzc)
    	.add_property("delay",		 &dateAdjustment::delay)
    	.def("adjust",				 &dateAdjustment::adjust,"Adjust a date according to a given business day convention")
    	.def("parseinterval",		 &dateAdjustment::parseinterval)
    	;

    def("tradingCentresList",&tc::keys<qm_list>,"Get the list of TradingCentreobjects");
    def("parseinterval",parseinterval,"date,tenure,tcs,bizdayconv  Parse an interval to a date");
    def("parseinterval",parseinterval1,"date,tenure,tcs  Parse an interval to a date");
    def("parseinterval",parseinterval2,"date,tenure  Parse an interval to a date");
    def("parsefrequency",parsefrequency,"freq,tenure Parse a frequency string into a period");
}

    
QM_NAMESPACE_END2

