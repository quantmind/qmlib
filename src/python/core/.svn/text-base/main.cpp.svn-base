

//#include <qmlib/python/pyconfig.hpp>
#include <qmlib/python/converters.hpp>

QM_NAMESPACE2(python)

void base_wrap();
//void json_wrap();
//void observer_wrap();
void date_wrap();
void static_wrap();
void calcDates_wrap();
void dataserie_wrap();
void math_wrap();
//void sensitivity_wrap();
//void irates_wrap();

QM_NAMESPACE_END2



#ifdef _DEBUG_
BOOST_PYTHON_MODULE(corelibdebug)  {
#else
BOOST_PYTHON_MODULE(corelib)  {
#endif	// _DEBUG_

    QM_USING_NAMESPACE2(python);

    #ifdef  _DEBUG_
    boost::python::scope().attr("__doc__") = "qmlib - debug enabled";
    boost::python::scope().attr("__version__") = "0.10debug";
    #else
    boost::python::scope().attr("__doc__") = "qmlib corelib";
    boost::python::scope().attr("__version__") = "0.10";
    #endif

    date_python_conversion 	dc;

    //observer_wrap();
    base_wrap();
    //json_wrap();
    date_wrap();
    static_wrap();
    calcDates_wrap();
    dataserie_wrap();
    math_wrap();
    //sensitivity_wrap();
    //irates_wrap();
}


