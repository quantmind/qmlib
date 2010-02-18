

#ifndef __CONTAINERS_WRAP_QM_HPP__
#define __CONTAINERS_WRAP_QM_HPP__
//
//
#include <qmlib/python/pyconfig.hpp>
#include <qmlib/corelib/templates/stdwrap.hpp>



QM_NAMESPACE2(python)



template<class K, class C>
inline void export_hashvector(const std::string& name, const std::string& info)  {
    	
  	using namespace boost::python;
    
   	//return_value_policy<copy_const_reference> ccr;
    	
   	typedef hashVector<K,C> 	container;
    	
   	class_<container>(name.c_str(),info.c_str())
   		.def("__str__",				&container::tostring)
   		.def("__repr__",			&container::tostring)
   		.def("__len__",           	&container::size)
   		.def("__getitem__",         &container::get_slow)
   		.def("__getitem__",         &container::find)
   		.def("__iter__",            boost::python::iterator<container>())
   		.def("add",					&container::push_back)
   		.add_property("locked",		&container::get_locked, &container::set_locked)
		;
}

QM_NAMESPACE_END2



#endif // __CONTAINERS_WRAP_QM_HPP__

