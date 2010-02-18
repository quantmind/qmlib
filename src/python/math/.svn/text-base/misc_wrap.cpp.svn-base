//
/// \file
/// \ingroup python
/// \brief Exposes to Python the math library


#include <qmlib/python/pyconfig.hpp>
#include <qmlib/math/numbers/constants.hpp>
#include <qmlib/math/tools/spline.hpp>
//
//
//
QM_NAMESPACE2(python)



void misc_wrap()  {
	using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    
    return_value_policy<copy_const_reference> ccr;
    
    register_ptr_to_python<SPLINE1D>();
    
    typedef cubic_spline thespline;
    class_<thespline, boost::noncopyable>("spline1d", "1D spline", init<>())
      	.def("__str__",						&thespline::tostring)
      	.def("__repr__",					&thespline::tostring)
      	.def("__len__",						&thespline::size)
        .add_property("size",               &thespline::size, "the number of support points")
        .add_property("x",	                &thespline::xlist<qm_list>,"Abscissa")
        .add_property("y",	                &thespline::ylist<qm_list>,"Ordinate")
        .add_property("k",	                &thespline::klist<qm_list>,"Second derivatives")
        //.add_property("lhs",				&thespline::lhs,"The matrix used to evaluate the second derivatives")
        .def("add",			 			    &thespline::add, "x,y Add support point to spline")
        .def("__getitem__",                 &thespline::value)
        .def("der1",                 		&thespline::der1)
        .def("der2",                 		&thespline::der2)
        .add_property("sensitivity",		make_function(&thespline::sensitivity,ccr))
        .def("dvdy",						&thespline::dvaldy,arg("x"),"Sensitivity with respect support point values")
        .def("search",						&thespline::search,arg("x"),"Find the support point just after x")	
        ;
    
    def("primenum",&constlist::primenum,"Get a prime number");
}

    
QM_NAMESPACE_END2


