


#ifndef __TOOLS_PYTHON_QM_HPP__
#define __TOOLS_PYTHON_QM_HPP__


#include <qmlib/python/pyconfig.hpp>
#include <qmlib/corelib/templates/containers.hpp>


QM_NAMESPACE



template<>
inline unsigned length<boost::python::list>(const boost::python::list& list)  {
	return boost::python::len(list);
}
template<>
inline unsigned length<boost::python::tuple>(const boost::python::tuple& tup)  {
	return boost::python::len(tup);
}


template<> struct object_to_string_o<boost::python::object> {
	static qm_string get(const boost::python::object& obj)  {
		return boost::python::extract<qm_string>(boost::python::str(obj));
	}
};


template<class T>
struct extract_from_list_object<T,boost::python::list>  {
	static T doit(const boost::python::list& cv, unsigned idx)  {
		return boost::python::extract<T>(cv[idx]);
	}
};
template<class T>
struct extract_from_list_object<T,boost::python::tuple>  {
	static T doit(const boost::python::tuple& cv, unsigned idx)  {
		return boost::python::extract<T>(cv[idx]);
	}
};


template<class T>
struct object_conversion<T,boost::python::object>  {
	static T doit(const boost::python::object& c)  {
		return boost::python::extract<T>(c);
	}
};


//////////////////////////////////////////// specialization for smart pointers

//template<>
template<class T>
struct element_to_list<QM_SMART_PTR(T), boost::python::list >  {
	static boost::python::tuple doit(const QM_SMART_PTR(T)& el) {
		QM_FAIL("element_to_list not implemented for smart pointers");
	} 
};


//////////////////////////////////////////// specialization for keyvalue

//template<>
template<class K,class V>
struct element_to_list<keyvaluepair<K,V>, boost::python::list >  {
	static boost::python::tuple doit(const keyvaluepair<K,V>& el) {
		return boost::python::make_tuple(element_to_list<K,boost::python::list>::doit(el.key()),
				                         element_to_list<V,boost::python::list>::doit(el.value()));
	} 
};

//template<>
template<class K, class V>
struct extract_from_list_object<keyvaluepair<K,V>, boost::python::list>  {
	typedef keyvaluepair<K,V> key_value_type;
	
	static key_value_type doit(const boost::python::list& cv, unsigned idx)  {
		using namespace boost::python;
		tuple tup = extract<tuple>(cv[idx]);
		return key_value_type(extract_from_list_object<K,tuple>::doit(tup,0),
							  extract_from_list_object<V,tuple>::doit(tup,1));
	}
};



QM_NAMESPACE_END


#endif // __TOOLS_PYTHON_QM_HPP__



