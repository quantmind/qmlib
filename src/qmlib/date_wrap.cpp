

#include <qmlib/python/pyconfig.hpp>
#include <qmlib/corelib/dates/all.hpp>
#include <qmlib/corelib/dates/imm.hpp>


QM_NAMESPACE2(python)




void date_wrap()  {
	using namespace boost::python;
      
    register_ptr_to_python<DC>();
    typedef datestring<qdate>	qdatestring;
    
    return_value_policy<copy_const_reference> ccr;
    
    class_<period, bases<basedes> >("period","Time period string",init<optional<int,int> >())
    	.def(init<qm_string>())
    	.def(init<qm_string,qm_string>())
    	.def("tenure",						&period::tostring)
    	.add_property("frequency",			&period::tofrequency)
    	.add_property("days",				&period::days)
		.add_property("months",				&period::months)
    	.add_property("years",				&period::years)
    	.add_property("totalmonths",		&period::totalmonths)
		.add_property("year_fraction",		&period::dcf)
    	.def(self + self)
    	.def(self - self)
    	.def(self + qm_string())
    	.def(self - qm_string())
    	.def(qm_string() + self)
    	.def(qm_string() - self)
    	.def(self += self)
    	.def(self -= self)
    	.def(self += qm_string())
    	.def(self -= qm_string())
    	;
    
    class_<qdatestring, bases<basedes> >("dateperiod","Date period object. This objec represent a date or a period",init<optional<const char*> >())
    	.def(init<qdate>())
    	.add_property("isdate",				&qdatestring::isdate)
    	.add_property("date",				make_function(&qdatestring::date,ccr))
    	.add_property("period",				make_function(&qdatestring::tenure,ccr))
    	;
      
    class_<daycounter, bases<codename> >("daycounter", "Day count object", no_init)
        .def("daycount",                   	&daycounter::daycount)
        .def("dcf",                   		&daycounter::dcf)
        ;

      
    def("daycount",&daycounter::get,"Create a daycounter object");
    def("daycountlist",&daycounter::keys<qm_list>,"List all avaibale daycounter objects");
    def("dayofweek",&dayoftheweek,arg("date"),"The day of weeak (string)");
	def("immdate",&immdate,args("month","year"),"Calculate an IMM date given a month and year");
}

QM_NAMESPACE_END2


