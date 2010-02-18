


#include <qmlib/python/dataserie_wrap.hpp>
#include <qmlib/corelib/static/all.hpp>


QM_NAMESPACE2(python)



void calcDates_wrap()   {
	using namespace boost::python;
    
    register_ptr_to_python<CALCDATES>();
    
    return_value_policy<copy_const_reference> ccr;
    
    class_<streamDateItem>("singleDate", "", no_init)
    	.def("__str__",             				&streamDateItem::tostring)
      	.def("__repr__",             				&streamDateItem::tostring)
        .add_property("date",         make_function(&streamDateItem::datev,ccr))
        .add_property("adjusted",                   &streamDateItem::adjusted)
        .add_property("code",         make_function(&streamDateItem::code,ccr))
        ;
    
    class_<periodDates, boost::noncopyable>("calcDates", "", no_init)
        .def("__str__",             &periodDates::code)
        .def("code",                &periodDates::code)
        .def("__len__",             &periodDates::size)
        .add_property("size",       &periodDates::size)
        .add_property("empty",      &periodDates::empty)
        .add_property("frequency",  &periodDates::frequency)
        //.def("__iter__",             boost::python::iterator<periodDates,return_internal_reference<>>())
        .def("dates",               &periodDates::datelist<qm_list>)
        ;
    
    def("calcDates",&calcDates::create0,"code,effectiveDate,terminationDate,freq,holidays,bizDayConv");
    def("calcDates",&calcDates::create1,"code,effectiveDate,terminationDate,freq,holidays,bizDayConv");
    def("calcDates",&calcDates::create2,"code,effectiveDate,terminationDate,startFirstPeriod,firstRegDate,lastRegDate,freq,holidays,bizDayConv");
}

QM_NAMESPACE_END2


