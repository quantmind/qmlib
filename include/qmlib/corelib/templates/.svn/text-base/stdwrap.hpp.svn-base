

#ifndef   __STDWRAP_QM_HPP__
#define   __STDWRAP_QM_HPP__
//

#include <qmlib/corelib/templates/observer.hpp>
#include <qmlib/corelib/tools/string.hpp>


QM_NAMESPACE

template<class C> class listwrap;
template<class K, class C> class dictionaryBase;



template<class C, class U>
struct append_to_list  {
	static void doit(listwrap<C>& li, const U& c)  {}
};



template<class C>
class listwrap  {
public:
	typedef C										value_type;
	typedef std::list<value_type>					container_type;
	typedef typename container_type::iterator		iterator;
	typedef typename container_type::const_iterator	const_iterator;
	
	listwrap():m_data(new container_type){p_data = m_data.get();}
	listwrap(const listwrap& rhs):m_data(rhs.m_data){p_data = m_data.get();}
	
	template<class U>
	void				append(const U& vt)   { append_to_list<C,U>::doit(*this,vt);}
	void				push_back(const value_type& v) { p_data->push_back(v);}
	void				append_list(const listwrap<C>& se);
	unsigned			size()			const { return p_data->size();}
    const_iterator    	begin()       	const { return p_data->begin();}
    const_iterator    	end()         	const { return p_data->end();}
    iterator    		begin()               { return p_data->begin();}
    iterator    		end()                 { return p_data->end();}
    
    template<class L>
    L tolist() const {
    	L l;
    	for(const_iterator it=this->begin();it!=this->end();++it)
    		l.append(*it);
    	return l;
    }
protected:
	container_type*				 p_data;
private:
	QM_SMART_PTR(container_type) m_data;
};


template<class K, class C>
class dictionaryBase  {
public:
	typedef C										data_type;
	typedef K										key_type;
	typedef std::map<key_type,data_type>			container_type;
	typedef typename container_type::value_type		value_type;
	typedef typename container_type::iterator		iterator;
	typedef typename container_type::const_iterator	const_iterator;
	typedef std::pair<iterator,bool>				insert_type;
	
	dictionaryBase():m_data(new container_type){p_data = m_data.get();}
	dictionaryBase(const dictionaryBase& rhs):m_data(rhs.m_data){p_data = m_data.get();}
	virtual ~dictionaryBase() {}
	
	void				 clear()			  { p_data->clear();}
	bool				 update(const dictionaryBase& se);
	iterator			 find(const key_type& k) 	    {return p_data->find(k);}
	const_iterator 		 find(const key_type& k) const {return p_data->find(k);} 
	unsigned			 size()			const { return p_data->size();}
    const_iterator    	 begin()       	const { return p_data->begin();}
    const_iterator    	 end()         	const { return p_data->end();}
    iterator    		 begin()              { return p_data->begin();}
    iterator    		 end()                { return p_data->end();}
    
    /// \brief Insert a value_type into the dictionary
    ///
    /// We make this a virtual function so that derived classes can control
    /// the way element are inserted.
    virtual insert_type	 insert(const value_type& vt) { return p_data->insert(vt);}
    
protected:
	container_type* p_data;
private:
	QM_SMART_PTR(container_type) m_data;
};


template<class K, class C>
class hashVector  {
public:
	typedef C										data_obj;
	typedef QM_SMART_PTR(data_obj)					data_type;
	typedef K										key_type;
	typedef std::vector<data_type>					container_type;
	typedef std::map<key_type,data_type>			dictionary_type;
	typedef typename container_type::iterator		iterator;
	typedef typename container_type::const_iterator	const_iterator;
	typedef typename dictionary_type::value_type	dict_type;
	
	hashVector():m_data(new container_type),m_dict(new dictionary_type),m_locked(false){setptr();}
	hashVector(const hashVector& rhs);
	
	hashVector& operator = (const hashVector& rhs);
	bool				 get_locked()   	const { return m_locked;}
	void				 set_locked(bool lo);
	unsigned			 size()				const { return p_data->size();}
    const_iterator    	 begin()       		const { return p_data->begin();}
    const_iterator    	 end()         		const { return p_data->end();}
    iterator    		 begin()               	  { return p_data->begin();}
    iterator    		 end()                 	  { return p_data->end();}
    void				 push_back(const data_type& dta);
    const data_type&	 operator [] (unsigned i) const {return (*p_data)[i];}
    data_type			 get_slow(unsigned i)     {QM_REQUIRE(i<this->size(),"Out of bound"); return (*p_data)[i];}
    data_type			 find(const key_type& k);
    qm_string			 tostring() const;
    void				 registerObserver(observer* ob);
protected:
	QM_SMART_PTR(container_type)  m_data;
	QM_SMART_PTR(dictionary_type) m_dict;
	container_type*  p_data;
	dictionary_type* p_dict;
	bool m_locked;
	void setptr() {
		p_data = m_data.get();
		p_dict = m_dict.get();
	}
};

template<class K, class C>
inline hashVector<K,C>::hashVector(const hashVector<K,C>& rhs):
	m_data(rhs.m_data),m_dict(rhs.m_dict),m_locked(rhs.m_locked) {
	setptr();
}

template<class K, class C>
inline hashVector<K,C>& hashVector<K,C>::operator = (const hashVector<K,C>& rhs)  {
	m_data = rhs.m_data;
	m_dict = rhs.m_dict;
	setptr();
	return *this;
}


template<class K, class C>
inline void hashVector<K,C>::set_locked(bool lo) {
	QM_REQUIRE(!m_locked,"HashVector is locked. Cannot change status");
	m_locked = lo;
}

template<class K, class C>
inline void hashVector<K,C>::push_back(const typename hashVector<K,C>::data_type& dta) {
	if(!dta) return;
	QM_REQUIRE(!m_locked,"Container is locked. Cannot add elements");
	try  {
		p_dict->insert(dict_type(dta->code(),dta));
		p_data->push_back(dta);
	}
	catch(...) {
		QM_FAIL("Fail to add data to hashvector");
	}
}

template<class K, class C>
inline typename hashVector<K,C>::data_type
hashVector<K,C>::find(const typename hashVector<K,C>::key_type& k) {
	typename dictionary_type::iterator it = p_dict->find(k);
	if(it != p_dict->end()) return it->second;
	QM_FAIL("Key not available");
}



template<class K, class C>
inline qm_string hashVector<K,C>::tostring() const {
	if(!this->size()) return "[]";
	const_iterator it=this->begin();
	qm_string st = (*it)->tostring();
	it++;
	for(;it!=this->end();++it) st += ", " + (*it)->tostring();
	return "["+st+"]";
}

template<class K, class C>
inline void hashVector<K,C>::registerObserver(observer* ob)  {
	if(!ob) return;
	for(iterator it=this->begin();it!=this->end();++it)  {
		//ob->template registerWith(*it);
		ob->registerWith(*it);
	}
}



//template<>
template<class C, class U>
struct append_to_list<QM_SMART_PTR(C),QM_SMART_PTR(U)>  {
	static void doit(listwrap<QM_SMART_PTR(C)>& li, const QM_SMART_PTR(U)& u)  {
		QM_SMART_PTR(C) v = smart_cast<C,U>(u);
		if(v) li.push_back(v);
	}
};


template<class C>
inline void listwrap<C>::append_list(const listwrap<C>& se)  {
	for(const_iterator it=se.begin();it!=se.end();++it)
		this->push_back(*it);
}


template<class K, class C>
inline bool dictionaryBase<K,C>::update(const dictionaryBase<K,C>& se)  {
	insert_type p;
	bool ok = true;
	for(const_iterator it=se.begin();it!=se.end();++it)  {
		p = this->insert(*it);
		if(!p.second) ok = false;
	}
	return ok;
}



QM_NAMESPACE_END

#endif	//	__STDWRAP_QM_HPP__
