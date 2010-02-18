


#include <qmlib/finance/rates/yieldcomposite.hpp>
#include <qmlib/math/tools/spline.hpp>
//#include <qmlib/finance/rates/optionrate.hpp>
#include <qmlib/python/serialize.hpp>



QM_NAMESPACE2(python)

/*
struct discountres_pickle_suite : boost::python::pickle_suite  {
  static  boost::python::tuple
  getinitargs(QM_FROM_NAMESPACE2(finance)discountres const& w)  {
	  return boost::python::make_tuple(w.get_npv(),w.get_pv01(),w.get_pv02(),w.get_rate());
  }
};
*/



void composite_wrap()  {
    	
   	using namespace boost::python;
   	QM_USING_NAMESPACE2(math);
   	QM_USING_NAMESPACE2(finance);
   	
   	return_value_policy<copy_const_reference> ccr;
   	
   	typedef yieldcomposite<cubic_spline,log_discount> yctype;
    
   	class_<basecomposite, bases<lazy> >("basecomposite","Base class for composite rates",no_init)
   		.def("build",				&basecomposite::build,"Build the rate")
   		.def("refresh",				&basecomposite::refresh,"Build the rate")
		.def("rebuild",				&basecomposite::rebuild,"Build the rate")
   		.add_property("solver",		make_function(&basecomposite::solver,ccr),"The solver")
   		;

   	class_<yctype, bases<idiscountcurve, basecomposite> >("compositeyc",
   			"Composite yield curve",init<qdate,qm_string>())
   		.def("add",					&yctype::add<isimplediscount>,arg("el"),"Add an element to the composite rate")
   		.def("insts",				&yctype::instlist<qm_list>,arg("idle"),"Retrive instruments in the composite rate")
   		.add_property("cfmat",		&yctype::cfmat,"The cash flow matrix")
   		.add_property("cfoff",		&yctype::cfoff,"Cash flow matrix of non-support points")
   		.add_property("offsens",	&yctype::offsens,"Sensitivity matrix of off-nodes")
   		;
   	
}


QM_NAMESPACE_END2


