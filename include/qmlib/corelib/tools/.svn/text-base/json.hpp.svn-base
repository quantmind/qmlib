// json.hpp (Version 0.1.2)
//
//__________________________________________________________________________________________
// Copyright 2008, Luca Sbardella. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided  that
// the following conditions are met:
//   * Redistributions of source code must retain the above copyright notice, this list of  conditions  and  the
//     following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
//     following disclaimer in the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT  SHALL
// THOMAS JANSEN BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,  OR  CONSEQUENTIAL  DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  OR  PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF  THIS  SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//__________________________________________________________________________________________


#ifndef __JSON_OBJECT_HPP__
#define __JSON_OBJECT_HPP__

#include	<boost/any.hpp>
#include	<string>
#include	<map>
#include    <qmlib/corelib/tools/string.hpp>



QM_NAMESPACE

class json {
public:
	typedef boost::any						data_type;
	typedef std::string						key_type;
	typedef std::map<key_type,data_type>	container_type;
	//typedef std::list<data_type>			vector_type;
	typedef container_type::const_iterator	const_iterator;
	typedef container_type::iterator		iterator;
	
	json():m_data(new container_type){}
	json(const json &rhs):m_data(rhs.m_data){}
	template<class D>
	json(const key_type& k, const D& data);
	
	json& operator = (const json& rhs) {m_data = rhs.m_data; return *this;}
	
	unsigned			 size()			const { return m_data->size();}
	bool				 empty()		const { return m_data->empty();}
	const_iterator    	 begin()       	const { return m_data->begin();}
	const_iterator    	 end()         	const { return m_data->end();}
	iterator    		 begin()              { return m_data->begin();}
	iterator    		 end()                { return m_data->end();}
	const data_type&     get(const key_type& k) const {return (*m_data)[k];}
	template<class D>
	void			     insert(const key_type& k, const D& obj);
	
	qm_string			 tostring() const;
protected:
	boost::shared_ptr<container_type>	m_data;
};


class jsonvec  {
public:
	typedef json::data_type				data_type;
	typedef std::vector<data_type>		vector_type;
	typedef vector_type::const_iterator	const_iterator;
	typedef vector_type::iterator		iterator;
	
	jsonvec():m_data(new vector_type){}
	jsonvec(const jsonvec &rhs):m_data(rhs.m_data){}
	jsonvec& operator = (const jsonvec& rhs) {m_data = rhs.m_data; return *this;}
	
	unsigned			 size()			const  { return m_data->size();}
	bool				 empty()		const  { return m_data->empty();}
	const_iterator    	 begin()       	const  { return m_data->begin();}
	const_iterator    	 end()         	const  { return m_data->end();}
	iterator    		 begin()               { return m_data->begin();}
	iterator    		 end()                 { return m_data->end();}
	const data_type&     get(unsigned k) const { QM_REQUIRE(k<this->size(),"Out of bound"); return (*m_data)[k];}
	template<class D>
	void			     add(const D& obj);
	
	qm_string			 tostring() const;
	
	template<class L>
	L tolist() const {
		L l;
		for(const_iterator it=this->begin();it!=this->end();++it)  {
			l.append(*it);
		}
		return l;
	}
protected:
	boost::shared_ptr<vector_type>	m_data;
};



class jsonrepr  {
public:
	virtual ~jsonrepr() {}
	virtual json tojson() const {return json();}
};


/** \brief Convert an object into a json representation
 */
template<class C>
struct object_to_json  {
	static json doit(const C& obj)  {QM_FAIL("Cannot conver object to json");}
};


template<class C>
jsonvec tojsonvec(const C& c)  {
	typedef typename C::const_iterator  const_iterator;
	jsonvec jv;
	for(const_iterator it = c.begin();it!=c.end();++it)
		jv.add(*it);
	return jv;
}



template<class D>
inline json::json(const json::key_type& k, const D& obj):m_data(new json::container_type)  {
	this->insert(k,obj); 
}


template<class D>
inline void json::insert(const json::key_type& k, const D& obj)  {
	(*m_data)[k] = object_to_json<D>::doit(obj);
}

template<class D>
inline void jsonvec::add(const D& obj)  {
	m_data->push_back(object_to_json<D>::doit(obj));
}



inline std::string json::tostring() const  {
	if(this->size() == 0) return "{}";
	const_iterator it=this->begin();
	std::string obj = object_to_string(*it);
	it++;
	for(;it!=this->end();++it)
		obj += ", " + object_to_string(*it);
	return "{" + obj + "}";
}

inline std::string jsonvec::tostring() const  {
	if(this->size() == 0) return "[]";
	const_iterator it=this->begin();
	std::string obj = object_to_string(*it);
	it++;
	for(;it!=this->end();++it)
		obj += ", " + object_to_string(*it);
	return "[" + obj + "]";
}


#define JSON_INSERT_TYPE(name)													\
template<>																		\
inline void json::insert<name>(const json::key_type& k, const name& obj)  {		\
	(*m_data)[k] = obj;															\
}
#define JSONVEC_INSERT_TYPE(name)												\
template<>																		\
inline void jsonvec::add<name>(const name& obj)  {								\
	m_data->push_back(obj);														\
}



template<class T>
struct filljson_o  {
	static void doit(const T& obj, json& js) {}
};

template<class T>
inline void filljson(const T& obj, json& js) {
	filljson_o<T>::doit(obj,js);
}


JSON_INSERT_TYPE(int)
JSON_INSERT_TYPE(long)
JSON_INSERT_TYPE(unsigned int)
JSON_INSERT_TYPE(unsigned long)
JSON_INSERT_TYPE(double)
JSON_INSERT_TYPE(float)
JSON_INSERT_TYPE(std::string)
JSON_INSERT_TYPE(json)
JSON_INSERT_TYPE(jsonvec)

JSONVEC_INSERT_TYPE(int)
JSONVEC_INSERT_TYPE(long)
JSONVEC_INSERT_TYPE(unsigned int)
JSONVEC_INSERT_TYPE(unsigned long)
JSONVEC_INSERT_TYPE(double)
JSONVEC_INSERT_TYPE(float)
JSONVEC_INSERT_TYPE(std::string)
JSONVEC_INSERT_TYPE(json)


// FUNCTION ON BOOST::ANY

template<class N>
bool is_any_type(const boost::any& value)  {
	return value.type() == typeid(N);
}
template<class T>
T any_extract(boost::any const& self);


inline bool is_any_float(const boost::any& value)  {
	return is_any_type<float>(value) || is_any_type<double>(value);
}
inline bool is_any_int(const boost::any& value)  {
	return is_any_type<int>(value) || is_any_type<long>(value) ||
			is_any_type<unsigned>(value) || is_any_type<short>(value);
}
inline bool is_any_number(const boost::any& value)  {
	return is_any_float(value) || is_any_int(value);
}
inline bool is_any_string(const boost::any& self) {
	try  {
		boost::any_cast<std::string>(&self);
		return true;
	}
	catch(...)  {
		return false;
	}
}


template<class T>
inline T any_to(const boost::any& self) {
	try  {
		T obj = boost::any_cast<T>(self);
		return obj;
	}
	catch(...)  {
		QM_FAIL("Could not convert");
	}
}
inline qm_real any_to_float(const boost::any& value)  {
	if(is_any_type<float>(value))
		return boost::any_cast<float>(value);
	else if(is_any_type<double>(value))
		return boost::any_cast<double>(value);
	QM_FAIL("Value not a float");		
}


template<>
struct object_to_string_o<boost::any>  {
	static qm_string get(const boost::any& obj)  {
		if(is_any_float(obj))
			return object_to_string(any_to_float(obj));
		else if(is_any_string(obj))
			return double_quote(any_to<std::string>(obj));
		else if(is_any_type<json>(obj))
			return any_to<json>(obj).tostring();
		else if(is_any_type<jsonvec>(obj))
			return any_to<jsonvec>(obj).tostring();
		else return "";
	}
};


template<>
inline void jsonvec::add<boost::any>(const boost::any& obj)  {
	if(is_any_float(obj) || is_any_string(obj) || is_any_type<json>(obj)) 
		m_data->push_back(obj);
	else
		QM_FAIL("type not supported");
}


QM_NAMESPACE_END


#endif  //  __JSON_OBJECT_HPP__



