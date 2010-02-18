

#include <qmlib/python/pyconfig.hpp>
#include <qmlib/finance/irhelp.hpp>



QM_NAMESPACE2(python)


void interestrate_wrap()  {
	using namespace boost::python;
	QM_USING_NAMESPACE2(finance);
	return_value_policy<copy_const_reference> ccr;
	
	register_ptr_to_python<IRHELP>();
	
	class_<irhelp, bases<icodename> >("irhelp","Interest rate helper",no_init)
		.add_property("index",  	&irhelp::index)
		.add_property("tenure",  	make_function(&irhelp::tenure,ccr))
		.add_property("adj",	  	&irhelp::adj)
		.add_property("dc",   		&irhelp::daycount)
		.add_property("frequency",  make_function(&irhelp::frequency,ccr))
		;
	
	def("irhelper", &irhelp::general);
}

QM_NAMESPACE_END2

