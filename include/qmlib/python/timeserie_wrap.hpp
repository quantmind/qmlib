

#ifndef __TIMESERIE_WRAP_QM_HPP__
#define __TIMESERIE_WRAP_QM_HPP__
//
//
#include <qmlib/python/dataserie_wrap.hpp>
#include <qmlib/corelib/templates/timeserie.hpp>

//
/// \file
/// \ingroup python
//


//////////////////////////////////////////// specialization for timeserie_elem
QM_NAMESPACE

//template<>
template<class T>
struct element_to_list<timeserie_elem<T>, boost::python::list >  {
	static boost::python::list doit(const timeserie_elem<T>& el) {
		boost::python::list lis;
		for(typename timeserie_elem<T>::const_iterator it = el.begin(); it!= el.end(); ++it)
			lis.append(element_to_list<T,boost::python::list>::doit(*it));
		return lis;
	} 
};

//template<>
template<class T>
struct extract_from_list_object<timeserie_elem<T>, boost::python::tuple>  {
	static timeserie_elem<T> doit(const boost::python::tuple& cv, unsigned idx)  {
		using namespace boost::python;
		list lis = extract<list>(cv[idx]);
		return timeserie_elem<T>(lis,0);
	}
};

QM_NAMESPACE_END


QM_NAMESPACE2(python)


template<class D, class V>
inline void export_timeserie(const std::string& name, const std::string& info)  {   	
   	using namespace boost::python;
   	typedef timeserie_elem<V> 			elem;
   	typedef typename elem::base_class	elem_base;
   	typedef timeserie<D,V>    			time_serie;
   	typedef dataserie<D,false,elem> 	time_serie_base;

   	return_value_policy<copy_const_reference> ccr;
   	
   	qm_string nab  = name + "Base";
    qm_string nae  = name + "Elem";

    // Export the data type
    class_<elem>(nae.c_str(),"Element of timeserie",init<optional<unsigned> >())
		.def("__str__",				&elem::tostring)
    	.def("__repr__",			&elem::representation)
    	.def("__len__",           	&elem::size)
    	.def("__getitem__",         make_function(&elem::get_slow,ccr))
    	.def("__setitem__",         &elem::set_slow)
    	.def("__iter__",            boost::python::iterator<elem>())
    	.def("tolist",				&elem::template dataToList< qm_list > )
       	;
    
    // Export the dataserie base class
    export_dataserie<D,false,elem>(nab,"Base class for timeserie");
    
    // Finally export the timeserie
    class_<time_serie, bases<time_serie_base> >(name.c_str(),info.c_str(),init<optional<unsigned> >())
    	.def(init<qm_list,unsigned>())
    	.add_property("numseries",		&time_serie::count)
    	.def("__setitem__",         	&time_serie::template addcross_sec< qm_list >)
    	.def("__setitem__",         	&time_serie::template addcross_sec< boost::python::tuple >)
    	;
}


QM_NAMESPACE_END2



#endif // __TIMESERIE_WRAP_QM_HPP__
