

#include <qmlib/python/pyconfig.hpp>
//#include <qmlib/finance/irhelp.hpp>
#include <qmlib/finance/quote/interestrate.hpp>



QM_NAMESPACE2(python)


void quote_wrap()  {
	using namespace boost::python;
	QM_USING_NAMESPACE2(finance);
	return_value_policy<copy_const_reference> ccr;
	
	register_ptr_to_python<QUOTE>();
	register_ptr_to_python<TICKER>();
	register_ptr_to_python<INTERESTRATE>();
	
	class_<iticker, bases<icodename> >("iticker","Interface for general ticker",no_init)
		.add_property("short",	&iticker::Short)	
		.add_property("providerCode",	&iticker::get_providerCode, &iticker::set_providerCode)
		.add_property("providerArgs",	&iticker::get_providerArgs, &iticker::set_providerArgs)
		;
	
	class_<iquote, bases<icodename> >("iquote","Interface for general quotes",no_init)
		.add_property("value",	&iquote::value, &iquote::set_value)
		.add_property("valid",	&iquote::isValid)
		.add_property("date",	make_function(&iquote::date))
		.add_property("ticker", &iquote::ticker)
		.add_property("short",  &iquote::Short)
		;
	
	//______________________________________________________________________________________
	// INTEREST RATE TICKERS
	
	class_<interestrate, bases<iticker> >("interestrate","Interest rate quote",no_init)
		.add_property("currency",	&interestrate::currency)
		.add_property("help",		&interestrate::help)
		.add_property("start",		make_function(&interestrate::start,ccr))
		.add_property("maturity",  	&interestrate::maturity)
		;
	//______________________________________________________________________________________
	
	def("interestrate", ratefactory::create);
	def("interestrate", ratefactory::create2);
}

QM_NAMESPACE_END2
