


#include <qmlib/python/pyconfig.hpp>
#include <qmlib/corelib/tools/json.hpp>

QM_NAMESPACE

boost::python::dict to_dict(json const& self)  {
	boost::python::dict d;
	for(json::const_iterator it=self.begin();it!=self.end();++it)  {
		d[it->first] = it->second;
	}
	return d;
}


template<>
inline void json::insert(const json::key_type& k, const boost::python::list& li)  {
	unsigned n = boost::python::extract<unsigned>(li.attr("__len__")());
	if(!n) return;
	jsonvec jv;
	for(unsigned i=0;i<n;++i)  {
		try  {
			qm_real v = boost::python::extract<qm_real>(li[i]);
			jv.add(v);
		}
		catch(...)  {
			try  {
				qm_string s = boost::python::extract<qm_string>(li[i]);
				jv.add(s);
			}
			catch(...)  {
				try  {
					json js(*boost::python::extract<json*>(li[i]));
					jv.add(js);
				}
				catch(...)  {
					QM_FAIL("Could not add list");
				}
			}
		}
	}		
	this->insert(k,jv);
}


template<>
boost::python::object any_extract<boost::python::object>(boost::any const& self)  {
	if(self.empty()) return boost::python::object(); // None
	if(is_any_int(self)) {
		return boost::python::object(boost::any_cast<int>(self));
	}
	if(is_any_float(self)) {
		return boost::python::object(boost::any_cast<double>(self));
	}
	//if(self.type() == typeid(json)) {
	//	return boost::python::object(*boost::any_cast<json>(self));
	//}
	QM_FAIL("boost::any unknown value type");
}


QM_NAMESPACE_END




QM_NAMESPACE2(python)


void json_wrap()  {
    
	using namespace boost::python;
	
	return_value_policy<copy_const_reference> ccr;
	
	typedef std::pair<qm_string const,boost::any> anypair;
	
	class_<boost::any>("any","Boost:any python wrapper")
		.def("__str__",				&object_to_string<boost::any>)
		.def("__repr__",			&object_to_string<boost::any>)
		.add_property("empty", 		&boost::any::empty)
		.add_property("is_int",		&is_any_int)
		.add_property("is_float",	&is_any_float)
		.add_property("is_number",  &is_any_number)
		.add_property("is_string",	&is_any_string)
		.add_property("is_json",	&is_any_type<json>)
		.add_property("float",      &any_to_float)
		.add_property("string",     &any_to<std::string>)
		.add_property("object",     &any_to<json>)
		;
	
	class_<anypair>("anypair","A string-boost::any key-value pair",init<>())
		.def("__str__",				&object_to_string<anypair>)
		.def("__repr__",			&object_to_string<anypair>)
		.add_property("key",		&anypair::first)
		.add_property("value",		&anypair::second)
		;
	
	class_<json>("json","A json object from C++")
		.def("__str__",				&json::tostring)
		.def("__repr__",			&json::tostring)
		.def("__len__",				&json::size)
		.add_property("empty",		&json::empty)
		.def("__iter__",            boost::python::iterator<json>())
		.def("__getitem__",         make_function(&json::get,ccr))
		.def("__setitem__",			&json::insert<unsigned int>)
		.def("__setitem__",			&json::insert<int>)
		.def("__setitem__",			&json::insert<long>)
		.def("__setitem__",			&json::insert<double>)
		.def("__setitem__",			&json::insert<float>)
		.def("__setitem__",			&json::insert<qm_string>)
		.def("__setitem__",			&json::insert<json>)
		.def("__setitem__",			&json::insert<jsonvec>)
		.def("__setitem__",			&json::insert<qm_list>)
		.def("dict",				&to_dict)	
		;
	
	class_<jsonvec>("jsonvec","A json vector")
		.def("__str__",				&jsonvec::tostring)
		.def("__repr__",			&jsonvec::tostring)
		.def("__len__",				&jsonvec::size)
		.add_property("empty",		&jsonvec::empty)
		.def("__iter__",            boost::python::iterator<jsonvec>())
		.def("__getitem__",         make_function(&json::get,ccr))
		.def("add",					&jsonvec::add<unsigned int>)
		.def("add",					&jsonvec::add<int>)
		.def("add",					&jsonvec::add<long>)
		.def("add",					&jsonvec::add<double>)
		.def("add",					&jsonvec::add<float>)
		.def("add",					&jsonvec::add<qm_string>)
		.def("add",					&jsonvec::add<json>)
		.def("tolist",				&jsonvec::tolist<qm_list>)	
		;
	
	class_<jsonrepr>("jsonrepr",no_init)
		.def("tojson",				&jsonrepr::tojson,"JSON representation of the object")
		;
}

    
QM_NAMESPACE_END2
