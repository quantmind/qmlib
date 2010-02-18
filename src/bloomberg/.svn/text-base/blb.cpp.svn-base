//
//
//
#include <qmlib/python/pyconfig.hpp>
//#include <qmlib/python/converters.hpp>
#include <qmlib/bloomberg/blb.hpp>

QM_NAMESPACE2(python)
void blb_wrap();
QM_NAMESPACE_END2

#ifdef _DEBUG_
BOOST_PYTHON_MODULE(bloomberglibdebug)  {
#else
BOOST_PYTHON_MODULE(bloomberglib)  {
#endif	_DEBUG_
	QM_USING_NAMESPACE2(python);
	boost::python::scope().attr("__doc__") = "Bloomber Python Library";
	blb_wrap();
}
