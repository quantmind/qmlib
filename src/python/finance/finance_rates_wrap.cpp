


#include <qmlib/finance/rates/simple_discount_curves.hpp>
#include <qmlib/finance/rates/factorcurves.hpp>
#include <qmlib/finance/bgm/tenure.hpp>
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



void finance_rates_wrap()  {
    	
   	using namespace boost::python;
   	QM_USING_NAMESPACE2(finance);
    	
   	//return_value_policy<copy_const_reference> ccr;
   	
   	//docstring_options doc_options(true,false);
   	register_ptr_to_python<QM_SMART_PTR(scalar_rate)>();
   	register_ptr_to_python<FACTORCURVE>();
  	  	
    class_<scalar_rate, bases<irate> >("scalarrate","Simple object rate",no_init)
       	.add_property("value",		&scalar_rate::value)
       	;

    class_<discountcurve, bases<idiscountcurve> >("discountcurve","base class for discount curves",no_init)
   		;
    
  	class_<interestRate, bases<basedes> >("interestRate","Interest rate", init<optional<qm_real,int> >())
  		.add_property("rate",			&interestRate::rate)
  		;
   	class_<simple_compound_dc, bases<discountcurve> >("simplediscountcurve", "Simple discount curve", init< optional<qm_real, qm_long> >())
   	    ;
   	class_<factorcurve, bases<discountcurve> >("factorcurve", "A factor discount curve", no_init)
   		.add_property("params",			 &factorcurve::params)
		.add_property("factors",	     &factorcurve::factors)
   	    ;
   	class_<tenure, bases<basedes> >("yctenure","Fra-swap yield curve tenure",
   			init<DISCOUNTCURVE, const period&, const period&,
   			const period&,ADJ,DC,DC,FWDRATEVOL>())
 		    .add_property("yc",			  	&tenure::yc)
 		    .add_property("date",			&tenure::date)
 		    .add_property("grid",		  	&tenure::grid)
 		    .add_property("fwdv",		  	&tenure::fwdv)
 		    .add_property("capswapratio", 	&tenure::capswapratio)
 		    .add_property("swapdc", 		&tenure::swapdc)
			.add_property("capdc", 			&tenure::daycount)
			.add_property("daycount", 		&tenure::daycount)
			.def("weights",					&tenure::weights,"Calculate the forward coefficients in a swap")
			.def("weights",					&tenure::weightsK,"Calculate the forward coefficients in a swap")
 		    ;

    def("scalarrate",&scalar_rate::create,"Create a simple scalar rate");
    def("nelsonSiegel", &nelsonSiegel::make);
    def("svensson", &svensson::make);
	//def("optionPDE1", &optionmodel<1u,pde_>::make,"Create a pde option model to be used for pricing");
}


QM_NAMESPACE_END2


