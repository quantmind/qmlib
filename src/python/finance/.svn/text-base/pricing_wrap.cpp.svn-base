

#include <qmlib/python/qmat_wrap.hpp>
#include <qmlib/finance/pricers/all.hpp>



QM_NAMESPACE2(python)


void pricing_wrap()  {
	using namespace boost::python;
	QM_USING_NAMESPACE2(finance);
	//return_value_policy<copy_const_reference> ccr;
	//typedef qmlib_pickle_suite<sensitivity> sensitivity_pickle;
	
	typedef pricer<isimplediscount,idiscountcurve,analytical_,idiscountcurve> cashFlowPricer;
	
	register_ptr_to_python<PRICER>();
	
	class_<ipricer, bases<icodename> >("ipricer","Interface class for pricing",no_init)
	    .def("calculate",					&ipricer::calculate,"Perform calculation on demand")
	    .add_property("method",				&ipricer::method,"Valuation method")
	    .add_property("date",				&ipricer::date,"Pricing date")
	    .add_property("threads",			&ipricer::numberOfThreads)
	    .def("insts",						&ipricer::tolist<qm_list>,"Instruments in the pricer")
	    ;
	
	class_<montemodel, bases<irate> >("montemodel","Montecarlo pricing model")
		;
	

	def("cashFlowPricer",    	&cashFlowPricer::make,args("curve","Numthreads","fulleval"),"Create a cashflow pricer object");
	def("montepricer",    		&montepricer::make);
	//def("opPdePricer1D",     &opPdePricer1D::make);
}

QM_NAMESPACE_END2
