

#include <qmlib/python/converters.hpp>
#include <qmlib/math/tools/timegrid.hpp>


QM_NAMESPACE2(python)



void timegrid_wrap()  {
	using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    
    return_value_policy<copy_const_reference> ccr;
    
    register_ptr_to_python<TIMEGRID>();
    register_ptr_to_python<RTIMEGRID>();
    register_ptr_to_python<DTIMEGRID>();
    register_ptr_to_python<BROWNIAN_BRIDGE>();

    class_<timegrid>("timegridBase",no_init)
		.def("__len__",           			&timegrid::length)
    	.def("dt",							&timegrid::dt_slow0)
    	.def("dt",							&timegrid::dt_slow)
    	.def("time",						&timegrid::time_slow)
    	.add_property("dtmax",				&timegrid::dtmax)
    	.def("tolist",						&timegrid::tolist<qm_list>)
    	.add_property("horizon",			&timegrid::horizon)
    	.add_property("bridge",				&timegrid::bridge)
    	;
    
    class_<real_timegrid, bases<timegrid, basedes> >("real_timegrid",init<>())
    	.def("__getitem__",         make_function(&real_timegrid::get_slow,ccr))
    	.def("__iter__",            boost::python::iterator<real_timegrid>())
    	.def("add",	  	  			&real_timegrid::addkeyval)
    	;
    
    class_<date_timegrid, bases<timegrid, basedes > >("dategrid",init<optional<DC> >())
    	.def("__getitem__",         make_function(&date_timegrid::get_slow,ccr))
    	.def("__iter__",            boost::python::iterator<date_timegrid>())
    	.def("add",	  	  			&date_timegrid::addkeyval)
		.add_property("dc",			&date_timegrid::get_dc, &date_timegrid::set_dc)
    	;
    
    class_<BrownianBridge, bases<basedes> >("BrownianBridge",init<unsigned>())
    	.def("__len__",           		&BrownianBridge::size)
    	.add_property("index",			make_function(&BrownianBridge::index,ccr))
    	.add_property("leftindex",		make_function(&BrownianBridge::leftIndex,ccr))
    	.add_property("rightindex",		make_function(&BrownianBridge::rightIndex,ccr))
    	.add_property("stdev",			make_function(&BrownianBridge::stdev,ccr))
    	.add_property("leftweight",		make_function(&BrownianBridge::leftWeight,ccr))
    	.add_property("rightweight",	make_function(&BrownianBridge::righWeight,ccr))
    	;
}

    
QM_NAMESPACE_END2

