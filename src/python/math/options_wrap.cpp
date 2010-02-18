

#include <qmlib/python/pyconfig.hpp>
#include <qmlib/math/options/black.hpp>
#include <qmlib/math/options/rebonatovol.hpp>

QM_NAMESPACE2(python)


void options_wrap()  {
	using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    //return_value_policy<copy_const_reference> ccr;
    
    register_ptr_to_python<QM_SMART_PTR(black_analytics) >();
    register_ptr_to_python<FWDRATEVOL>();
    
	class_<black_analytics, bases<sensitivity> >("black_analytics","Black Scholes analytics",
			init<optional<qdate,qm_string> >())
		.add_property("delta",			&black_analytics::delta,   &black_analytics::set_delta)
		.add_property("gamma",			&black_analytics::gamma,   &black_analytics::set_gamma)
		.add_property("vega",			&black_analytics::vega,    &black_analytics::set_vega)
		.add_property("volga",			&black_analytics::volga,   &black_analytics::set_volga)
		.add_property("vanna",			&black_analytics::vanna,   &black_analytics::set_vanna)
		//.def_pickle(qmlib_pickle_suite<black_analytics>())
		;
    
    typedef fwdblackcall bvp;
    class_<bvp>("fwdblackcall","Forward black pricer",
    		init<optional<unsigned,qm_real> >())
    	.def("price",		&bvp::price,"Forward,Strike,TTM,Vol Get the black forward call price")
    	.def("volatility",	&bvp::volatility,"Forward,Strike,TTM,Price Get the implied black volatility from a forward call price")
    	.def("calculate",	&bvp::calculate,"Forward,Strike,TTM,Vol Get the black forward call price and sensitivities")
    	;
    
    class_<fwdratevol, bases<iparameter> >("fwdratevol","Time dependent volatility function",no_init)
    	.add_property("Ti",	&fwdratevol::Ti,   &fwdratevol::set_Ti)
    	.add_property("Tj",	&fwdratevol::Tj,   &fwdratevol::set_Tj)
    	.add_property("T",	&fwdratevol::T,    &fwdratevol::set_T)
    	.def("volatility",	&fwdratevol::volatility)
    	.def("covariance",	&fwdratevol::covariance)
    	.def("correlation",	&fwdratevol::correlation)
    	.def("rho",		&fwdratevol::correlationfunction,"Instantaneous correlation function")
    	;
    
    def("rebonatovol",rebonatovol::make);
    def("rebonatovol2",rebonatovol2::make);
}


QM_NAMESPACE_END2
