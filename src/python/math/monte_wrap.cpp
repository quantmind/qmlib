

#include <qmlib/python/converters.hpp>
#include <qmlib/math/monte/all.hpp>
#include <qmlib/python/numpy.hpp>


QM_NAMESPACE2(python)


using namespace boost::python;
QM_USING_NAMESPACE2(math);

//qmatrixwrap<qm_real,path::mstructure>
PyObject* path_to_python(path& pa)  {
	return numpy_converter<qm_real,path::mstructure>::topython(pa.pathholder());
}


void monte_wrap()  {
	using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    
    //return_value_policy<copy_const_reference> ccr;
    register_ptr_to_python<PATH>();
    register_ptr_to_python<MONTECARLO>();
    
    class_<path_base, bases<icodename> >("path_base",no_init)
    	.add_property("numvar",		&path_base::numvar)
    	.add_property("numpaths",	&path_base::numpaths)
    	.add_property("totaldim",	&path_base::totaldim)
    	.add_property("timedim",	&path_base::timedim)
    	.add_property("grid",		&path_base::grid)
    	;
    class_<path, bases<path_base> >("path",no_init)
		.add_property("data",		path_to_python)
    	;
    class_<Paths, bases<path_base> >("paths",no_init)
    	.def("__len__",				&Paths::size)
    	.def("__iter__",            boost::python::iterator<Paths>())
    	.def("__getitem__",			&Paths::get_slow)
    	;
    class_<montecarlo, bases<basedes> >("montecarlo",init<optional<RNDGEN,STOCHASTIC,bool> >())
    	.def("simula",			 	&montecarlo::simula,arg("numpaths"))
    	.def("diffusion",			&montecarlo::diffusion)
    	.add_property("generator",	&montecarlo::get_generator, &montecarlo::set_generator)
    	.add_property("process", 	&montecarlo::get_process, &montecarlo::set_process)
    	.add_property("bridge", 	&montecarlo::get_bridge, &montecarlo::set_bridge)
    	.def("set_grid",			&montecarlo::set_grid<timegrid>)
    	.def("set_grid",			&montecarlo::set_grid<real_timegrid>)
    	.def("set_grid",			&montecarlo::set_grid<date_timegrid>)
    	;
}

    
QM_NAMESPACE_END2

