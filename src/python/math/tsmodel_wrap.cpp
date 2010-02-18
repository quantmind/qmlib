


#include <qmlib/finance/tsmodel/affine.hpp>
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



void tsmodel_wrap()  {
    	
   	using namespace boost::python;
   	QM_USING_NAMESPACE2(math);
    	
   	//return_value_policy<copy_const_reference> ccr;
   	
   	register_ptr_to_python<TSMODEL>();
  	  	
    class_<tsmodel, bases<idiscountcurve, discount_curve_holder> >("tsmodel","Term structure model",no_init)
       	.add_property("stoch",		&tsmodel::stoch)
       	.add_property("fit",		&tsmodel::get_exactfit, &tsmodel::set_exactfit)
       	.def("fwdratecovar",		&tsmodel::fwdratecovar,args("t","T1","tenure1","T2","tenure2"),"Calculate the instantaneous forward rate covariance")
       	.def("future", 				&tsmodel::future,args("t","T1","T2","tau"),"Calculate a future libor rate")	
       	;

    def("tsaffine",&affinefactory::make,"Create an affine term-structure model");
}


QM_NAMESPACE_END2


