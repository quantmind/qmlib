

#include <qmlib/python/pyconfig.hpp>
#include <qmlib/buffer.hpp>
#include <qmlib/corelib/templates/observer.hpp>


QM_NAMESPACE2(python)

template<class T>
class observer_wrapper : public T, public boost::python::wrapper<T>  {
public:
	
	void update() {
		if(boost::python::override overfun = this->get_override("update"))
			overfun();
		else
			T::update();		
	}

	void default_update() { return this->T::update();}
};

template<class T>
class lazy_wrapper : public observer_wrapper<T>  {
public:
	
	void updatelazy() {
        if(boost::python::override overfun = this->get_override("updatelazy"))
			overfun();
		else
			T::updatelazy();		
	}
};

void observer_wrap()  {
	using namespace boost::python;
    //return_value_policy<copy_const_reference> ccr;
	register_ptr_to_python<QM_SMART_PTR(observable)>();
	register_ptr_to_python<QM_SMART_PTR(observer)>();
	//register_ptr_to_python<QM_SMART_PTR(qm_buffer<unsigned>)>();
	typedef observer_wrapper<observer> wobserver;

	return_value_policy<copy_const_reference> ccr;
    
    class_<observable, boost::noncopyable>("observable","Observable object")
    	.add_property("count_observers",		&observable::count_observers,"Number of observers attached to self")		
    	.def("notify_observers",				&observable::notify_observers)
    	;
    
    class_<wobserver,boost::noncopyable>("observer","Observer object")
    	//.def("registerWith",			&observer_wrapper<observer>::registerObserverWithPythonObject,"Register with an observable object")
    	.def("registerWith",			&observer::registerWith<observable>,arg("Observable"),"Register with an observable object")
    	.def("unregisterWith",			&observer::unregisterWith,arg("Observable"),"Unregister from an observable")
		.def("update",					&observer::update, &wobserver::default_update, "Function called by observable to update the observer")
    	.add_property("count_subjects",	&observer::count_subjects,"Count the number of observable")
    	;
    
    class_<lazy_wrapper<lazy>, boost::noncopyable, bases<observable,observer> >("lazyobject","A lazy object, both observer and observable")
    	.add_property("frozen",			&lazy::frozen, &lazy::set_frozen,"frozen property")
    	.def("updatelazy",				&lazy::updatelazy,"Function called by observable to update the observer")
    	;

	typedef qm_buffer<long> ubuf;
	class_<ubuf>("ubuffer","A simple unsigned buffer",init<optional<unsigned> >())
		.def("__str__",			&ubuf::tostring)
		.def("__repr__",		&ubuf::tostring)
		.def("__len__",			&ubuf::size)
		.def("__getitem__",		make_function(&ubuf::get_slow,ccr))
       	.def("__setitem__",		&ubuf::set_slow)
		;

}

QM_NAMESPACE_END2

