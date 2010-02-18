

#ifndef __DATASERIE_WRAP_QM_HPP__
#define __DATASERIE_WRAP_QM_HPP__
//
//
#include <qmlib/python/tools.hpp>

//
/// \file
/// \ingroup python
//



QM_NAMESPACE

template<>
struct niceIndexWrap<boost::python::tuple> {
	static boost::python::tuple doit(long idx)  {
		if(idx >= 0) return boost::python::make_tuple(idx,idx);
		else if(idx == -1) return boost::python::make_tuple(0,0);
		else return boost::python::make_tuple(-idx-2,-idx-1); 
	}
};

QM_NAMESPACE_END




QM_NAMESPACE2(python)



template<class C>
struct container_pickle_suite : boost::python::pickle_suite  {
	static  boost::python::tuple getinitargs(const C& w)  {
		return boost::python::make_tuple(w.template dataToList<qm_list>(), w.flag());
	}
};

	
template<class V>
inline void export_base_container(const std::string& name, const std::string& info)  {
   	
  	using namespace boost::python;
    	
   	return_value_policy<copy_const_reference> ccr;
    	
   	typedef base_container<V> 	 	container;
   	
   	qm_string na1 = name + "Base";
   	
   	class_<container, bases<basedes> >(name.c_str(),info.c_str())
   		.def("__len__",           	&container::size)
   		.add_property("size",     	&container::size)
   		.add_property("empty",    	&container::empty)
   		.def("__getitem__",         make_function(&container::get,ccr))
   		.add_property("front",      make_function(&container::front,ccr))
   		.add_property("back",       make_function(&container::back,ccr))
   		.def("__iter__",            boost::python::iterator<container>())
   		.def("tolist",				&container::template dataToList< qm_list > )
	    .def_pickle(container_pickle_suite<container>())
        ;
}



template<class K, class T, class V, bool dup>
inline void export_ordered_vector(const std::string& name, const std::string& info)  {
    	
  	using namespace boost::python;
    	
   	return_value_policy<copy_const_reference> ccr;
    	
   	typedef ordered_vector<K,T,V,dup> 	container;
    	
   	class_<container>(name.c_str(),info.c_str(),init<>())
   		.def(init<qm_list,unsigned>())
		.def("__str__",				&container::tostring)
    	.def("__repr__",			&container::representation)
   		.def("resize",         		&container::resize)
   		.def("__len__",           	&container::size)
   		.def("__getitem__",         make_function(&container::get,ccr))
   		.add_property("front",      make_function(&container::front,ccr))
   		.add_property("back",       make_function(&container::back,ccr))
   		.def("__iter__",            boost::python::iterator<container>())
   		.def("tolist",				&container::template dataToList< qm_list > )
   		.def("search",    			&container::search,"search for a key. If return is non-negative than the key has been found and its location is given by the return value. "
	                                       			   "Otherwise, the key it is not availble. If inserted, its position in the container would be at -return-1.")
		.def("index",    			&container::index)
		.def("closestIndex",    	&container::closestIndex)
		.def("value",	            make_function(&container::closestValue,ccr), "Retrive the value pair with the closest key")
		.def("at",		            make_function(&container::value,ccr), "Retrive the value matching a given key")
		.def("add",	  	  			&container::add)
		.def("has_key",             &container::contains)
		.def_pickle(container_pickle_suite<container>())
		;
}



template<class value_type, class key_type, class data_type>
void export_dataserie_keyvalue(const std::string& na, const std::string& nai)  {
    using namespace boost::python;
    return_value_policy<copy_const_reference> ccr;
    
    class_<value_type>(na.c_str(),nai.c_str(), init<>())
		.def(init<key_type const &>())
		.def(init<value_type const &>())
		.def(init<key_type const &, data_type const&>())
		.def("__str__",				&value_type::tostring)
    	.def("__repr__",			&value_type::representation)
		.add_property("key",      	make_function(&value_type::key,ccr))
		.add_property("value",    	make_function(&value_type::value,ccr), &value_type::set)
		;
};




/// \brief Helper function which exposes to python the timeserie class template
/// \ingroup python
///
/// @param name The python class name
/// @param info The python information string of class name
/// @param D The date class used in timeserie
/// @param T The value class used in timeserie
template<class D,bool dup,class T>
inline void export_dataserie(const std::string& name, const std::string& info, bool exportkeyvalue = true)  {
    	
    using namespace boost::python;
    
    typedef dataserie<D,dup,T> 						container;
    typedef typename container::base_class    		base_class;
    typedef typename container::value_type    		value_type;
    typedef typename container::key_type    		key_type;
    typedef typename container::data_type    		data_type;
    
    return_value_policy<copy_const_reference> ccr;
    
    std::string na  = name + "Value";
    
	if(exportkeyvalue)
		export_dataserie_keyvalue<value_type,key_type,data_type>(na,info);
    	
    class_<container>(name.c_str(),info.c_str(),init<>())
    	.def(init<qm_list,unsigned>())
		.def("__str__",				&container::tostring)
    	.def("__repr__",			&container::representation)
    	.def("__len__",           	&container::size)
        .def("add",  	  			&container::addkeyval)
        .def("__getitem__",         make_function(&container::get_slow,ccr))
        .def("has_key",             &container::contains)
        .def("index",    			&container::template niceindext<boost::python::tuple>)
        .def("closest",	            make_function(&container::closest,ccr), "Retrive the data value with the closest key")
        .def("at",		            make_function(&container::at,ccr), "Retrive the data value matching a given key")
        .add_property("front",      make_function(&container::front,ccr))
   		.add_property("back",       make_function(&container::back,ccr))
   		.def("__iter__",            boost::python::iterator<container>())
        .def("tolist",				&container::template dataToList< qm_list > )
        .def("keys",                &container::template keys< qm_list > )
        .def("values",              &container::template values< qm_list > )
        .def_pickle(container_pickle_suite<container>())
        ;
}


QM_NAMESPACE_END2



#endif // __DATASERIE_WRAP_QM_HPP__

