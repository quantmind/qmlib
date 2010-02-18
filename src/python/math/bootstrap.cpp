

#include <qmlib/python/converters.hpp>
#include <qmlib/math/bootstrap/discount.hpp>
#include <qmlib/math/tools/spline.hpp>



QM_NAMESPACE2(math)

template<class V, booststrap_type D>
void export_booststrap(const std::string& name, const std::string& info)  {
   	using namespace boost::python;

	return_value_policy<copy_non_const_reference> cncr;

	typedef discount_bootstrap<V, D> bklass;
	
	class_<bklass, boost::noncopyable>(name.c_str(),info.c_str())
		.def("__getitem__",		&bklass::value)
		.def("__len__",			&bklass::size)
		.def("add",				&bklass::add, args("x","y"))
		.def("__getitem__",		&bklass::value, args("x"))
		.def("build",			&bklass::build, args("lhs,rhs,trhs"))
		.add_property("solver",  make_function(&bklass::get_solver, cncr))
		;
}

QM_NAMESPACE_END2


QM_NAMESPACE2(python)


void bootstrap_wrap()  {
   	QM_USING_NAMESPACE2(math);
   	export_booststrap<cubic_spline,logarithmic>("logsplinediscount", "Cubic spline discount factor");
}

QM_NAMESPACE_END2

