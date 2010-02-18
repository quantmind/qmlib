//
//
#ifndef   __INLINE_DB_QM_HPP__
#define   __INLINE_DB_QM_HPP__



#include <qmlib/corelib/tools/string.hpp>
#include <qmlib/corelib/tools/error.hpp>



QM_NAMESPACE


template<class T>
inline T trimfordb(const T& t)  {
	return t;
}
	
template<>
inline qm_string trimfordb<qm_string>(const qm_string& t)  {
	return qmstring::uppercase(t);
}




/// \brief Inline database
/// This class template is used for small inline databases
template<class K, class T>
class inlinedb  {
public:
   	typedef K									key_type;
   	typedef QM_SMART_PTR(T)  					data_type;
   	typedef std::map<key_type, data_type>		container;
   	typedef typename container::const_iterator	const_iterator;
   	//
   	inlinedb(const qm_string& code = ""):m_code(code){}
   	
   	qm_string       code()						const  {return m_code;}
   	data_type	 	get(const key_type& code) 	const;
   	qm_Size   		size()       				const  {return m_db.size();}
   	void            add(const key_type& code, const data_type& val) {m_db[trimfordb(code)] = val;}
   	//
   	template<class L>
   	L keys() const {
   	    L list;
   	    for(const_iterator it = m_db.begin();it!=m_db.end();++it)  list.append(it->first);
   	    return list;
   	}
   	//
protected:
   	container  m_db;
   	qm_string  m_code;
};



template<class K, class T>
inline typename inlinedb<K,T>::data_type  inlinedb<K,T>::get(const key_type& code) const {
  	const_iterator it = m_db.find(trimfordb(code));
   	if(it != m_db.end()) return it->second;
   	else QM_FAIL("element not available");
}


QM_NAMESPACE_END


#endif  //  __INLINE_DB_QM_HPP__

