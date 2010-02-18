//
//
#ifndef __STRING_QM_HPP__
#define __STRING_QM_HPP__


#include <qmlib/corelib/math.hpp>
#include <qmlib/corelib/tools/error.hpp>



QM_NAMESPACE


/** \brief String helper class
 * 
 * \ingroup utility
 */
class qmstring  {
public:
	static qm_string  lowercase(const qm_string&);
	static qm_string  uppercase(const qm_string&);
	static qm_strings split(const qm_string& str, const qm_string& fielddelim);
	static qm_string  trim(const qm_string& file);
	static qm_string  concat(const qm_strings& vec, const qm_string& fielddelim);
};



	
inline qm_string qmstring::lowercase(const qm_string& s)  {
	using namespace std;
	qm_string output = s;
	for (qm_string::iterator i=output.begin(); i!=output.end(); i++)
           *i = tolower(*i);
	return output;
}

inline qm_string qmstring::uppercase(const qm_string& s)  {
	using namespace std;
	qm_string output = s;
	for (std::string::iterator i=output.begin(); i!=output.end(); i++)
		*i = toupper(*i);
	return output;
}
	
	
/// \brief Simple base class which provides descriptive information of derived objects
/// \ingroup utility
class basedes  {
public:
	virtual ~basedes(){}
	/// \brief Return a string describing the object 
	virtual qm_string tostring() 		const { return "";}
	/// \brief String representation of the object
	virtual qm_string representation() 	const { return this->tostring();}
	/// \brief True if the object can be serialized
	virtual bool	  serializable()   	const { return false;}
protected:
	basedes(){}
};


/// \brief Code name interface
/// \ingroup utility
class icodename : public basedes {
public:
	virtual qm_string  code() const {return "";}
	virtual qm_string  name() const {return this->code();}
	qm_string tostring() const {return this->name();}
protected:
	icodename(){}
};


/// \brief codename class
/// \ingroup utility
class codename : public basedes {
public:
	codename(const qm_string& cod, const qm_string& nam):m_code(cod),m_name(nam){}
	const qm_string&  code()     const {return m_code;}
	const qm_string&  name()     const {return m_name;}
	qm_string tostring() const {return this->name();}
protected:
    qm_string         m_code;
    qm_string         m_name;
};



inline qm_strings qmstring::split(const qm_string& str, const qm_string& delim)  {
    qm_uns_int offset = 0;
    qm_uns_int delimIndex = 0;
    delimIndex = str.find(delim, offset);
    qm_strings output;
    qm_uns_int npo = qm_string::npos;
    while (delimIndex != npo)  {
      output.push_back(str.substr(offset, delimIndex - offset));
      offset += delimIndex - offset + delim.length();
      delimIndex = str.find(delim, offset);
    }
    output.push_back(str.substr(offset));
    return output;
}


inline qm_string qmstring::concat(const qm_strings& vec, const qm_string& delim)  {
    if(vec.size() == 0) return "";
    qm_strings::const_iterator it = vec.begin();
    qm_string re = *it;
    ++it;
    for(;it!=vec.end();++it)
      re += delim + *it;
    return re;
}

  
inline qm_string qmstring::trim(const qm_string& file)  {
  // find last path separator
    qm_string::size_type n = file.find_last_of("/\\");
    if (n == std::string::npos)
    // return the whole thing--it's a naked file name anyway
      return file;
    else
      // keep the file name only
    return file.substr(n+1);
}
    
  
/*** \brief template struct for converting an object into a string
 * \ingroup utility 
 */
template<class C>
struct object_to_string_o  {
	static qm_string get(const C& obj)  {
		return obj.tostring();
		//return "";
	}
};


//template<>
template<class Q>
struct object_to_string_o<QM_SMART_PTR(Q)>  {
	static qm_string get(const QM_SMART_PTR(Q)& obj)  {
		return object_to_string_o<Q>::get(*obj);
	}
};

#define QM_OBJ_TO_STRING_NUMBER(name)										\
template<> struct object_to_string_o<name>  {								\
	static qm_string get(const name& y)  {									\
		return boost::lexical_cast<qm_string>(y);							\
	}																		\
};

QM_OBJ_TO_STRING_NUMBER(int)
QM_OBJ_TO_STRING_NUMBER(short)
QM_OBJ_TO_STRING_NUMBER(long)
QM_OBJ_TO_STRING_NUMBER(unsigned short)
QM_OBJ_TO_STRING_NUMBER(unsigned)
QM_OBJ_TO_STRING_NUMBER(unsigned long)
QM_OBJ_TO_STRING_NUMBER(float)
QM_OBJ_TO_STRING_NUMBER(double)

inline std::string double_quote(const std::string& str)  {
	std::string q("'");
	if(str.find(q) != std::string::npos)
		q[0] = '"';
	return q+str+q;
}

template<>
struct object_to_string_o<qm_string> {
	static qm_string get(const qm_string& obj)  {
		return double_quote(obj);
	}
};


// Specialization for std::pair
template<class K, class T>
struct object_to_string_o<std::pair<K,T> >  {
	typedef std::pair<K,T> pair_type;
	static std::string get(const pair_type& pa)  {
		return object_to_string(pa.first) + ": " + 
			   object_to_string(pa.second);
	}
};


template<class C>
inline qm_string object_to_string(const C& obj)  {
	return object_to_string_o<C>::get(obj);
}

template<class C>
inline qm_string pretty_print(const C& val)  {
	return object_to_string(val);
}

inline qm_string nice_real(qm_real num, unsigned precision = 5)  {
	return object_to_string(round(num,precision));
}

template<>
inline qm_string pretty_print<qm_real>(const qm_real& val)  {
	return nice_real(val,8);
}

/** \brief Transform a real number into a percentage string rapresentation
* 
* \ingroup utility
*/
inline qm_string nice_percent(qm_real pcnum, unsigned precision = 5)  {
	return nice_real(100*pcnum,precision)+"%";
}

/** \brief Transform a real number into a basis point string rapresentation
* 
* \ingroup utility
*/
inline qm_string nice_bp(qm_real val, unsigned precision = 2)  {
	return nice_real(10000*val,precision)+" bp";
}

inline qm_real smallreal() {return std::numeric_limits<qm_real>::min();}
inline qm_real maxreal()   {return std::numeric_limits<qm_real>::max();}
  
QM_NAMESPACE_END



#endif  //  __STRING_QM_HPP__

