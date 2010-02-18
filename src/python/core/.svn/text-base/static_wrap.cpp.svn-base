


#include <qmlib/python/converters.hpp>
#include <qmlib/corelib/static/all.hpp>


QM_NAMESPACE2(python)


void static_wrap()  {
    
	using namespace boost::python;
    	
   	return_value_policy<copy_const_reference> ccr;
    
   	register_ptr_to_python<TC>();
   	register_ptr_to_python<CCY>();
   	register_ptr_to_python<CONTRACT>();
   	register_ptr_to_python<INDEX>();
   	register_ptr_to_python<EXCHANGE>();
   	register_ptr_to_python<ADJ>();
    
    
    enum_<BizDayConv>("BizDayConv")
    	.value("foll",			foll)
        .value("modfoll",		modfoll)
        .value("prec",			prec)
        .value("modprec",		modprec)
        .value("unadjusted",	unadjusted)
        .export_values()
        ;
   	
    class_<ccy, bases<codename> >("ccy", "Currency Object", no_init)
    	.add_property("twolettercode", make_function(&ccy::twolettercode, ccr))
        .add_property("order",         &ccy::order)
        .add_property("rounding",      &ccy::rounding)
        .add_property("cashDelay",     &ccy::cashDelay)
        .add_property("swapDelay",     &ccy::swapDelay)
        .add_property("bizConv",	   &ccy::bizConv)
        .add_property("floatDC",	   &ccy::floatDC)
        .add_property("fixedDC",	   &ccy::fixedDC)
        .add_property("defaultTC",     make_function(&ccy::defaultTC,ccr))
        .add_property("fixedfreq", 		make_function(&ccy::fixedCoupFred, ccr))
        .add_property("floatfreq", 		make_function(&ccy::floatCoupFred, ccr))
        ;
        
    class_<contract, bases<codename> >("contract", "Security Contract", no_init)
        .add_property("holiday",       make_function(&contract::holiday, ccr))
        .add_property("currency",      &contract::currency)
        ;
    
    class_<index, bases<codename> >("index", "General Index", no_init)
        .add_property("holiday",       make_function(&index::holidays, ccr))
        ;
        
    class_<exchange, bases<contract> >("exchange", "Exchange Contract", no_init)
       	.add_property("tradingUnit",    &exchange::tradingUnit)
       	.add_property("tickSize",   	&exchange::tickSize)
       	.add_property("tickValue",   	&exchange::tickValue)
       	.add_property("delay",   		&exchange::delay)
       	.add_property("exchange",   	make_function(&exchange::exchplace,ccr))
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

    def("currency",&ccy::get,"Create a currency object");
    def("currencylist",&ccy::keys<qm_list>,"List all avaibale currencies objects");
    def("contract",&contract::get,"Create a contract object");
    def("contractlist",&contract::keys<qm_list>,"List all avaibale contract objects");
    def("tradingCentresList",&tc::keys<qm_list>,"Get the list of TradingCentreobjects");
    def("parseinterval",parseinterval,"date,tenure,tcs,bizdayconv  Parse an interval to a date");
    def("parseinterval",parseinterval1,"date,tenure,tcs  Parse an interval to a date");
    def("parseinterval",parseinterval2,"date,tenure  Parse an interval to a date");
    def("parsefrequency",parsefrequency,"freq,tenure Parse a frequency string into a period");
}

    
QM_NAMESPACE_END2

