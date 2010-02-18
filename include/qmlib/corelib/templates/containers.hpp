

#ifndef   __CONTAINERS_QM_HPP__
#define   __CONTAINERS_QM_HPP__
//
//
#include <qmlib/corelib/tools/meta.hpp>
#include <qmlib/corelib/tools/conversions.hpp>
#include <qmlib/corelib/tools/comparison.hpp>
#include <qmlib/corelib/algorithms/search.hpp>
#include <limits>


/*! \defgroup containers Several container templates

    Ordered vector, dataserie, timeserie etc..

    @{
*/



/// \file
/// \brief Definition of some generic Containers
/// \ingroup patterns


QM_NAMESPACE




template<class T>
class smartholder  {
public:
	typedef	T							element_type;
	typedef QM_SMART_PTR(element_type)	SMART_PTR;
	
	smartholder():m_elem(new element_type){}
	
	smartholder(SMART_PTR elem):m_elem(m_elem) {
		QM_REQUIRE(m_elem,"Null element");
	}
	
	smartholder(const smartholder& rhs):m_elem(rhs.m_elem){}
	
	const SMART_PTR&    smart() const {return m_elem;}
	element_type* 		get()   const {return m_elem.get();}
private:
	SMART_PTR		m_elem;
};



typedef std::pair<unsigned,unsigned>		index_pair;


template<class,class,class,bool>  class ordered_vector;
template<class> struct niceIndexWrap;


template<>
struct niceIndexWrap<index_pair> {
	static index_pair doit(long idx)  {
		if(idx >= 0) return index_pair(idx,idx);
		else if(idx == -1) return index_pair(0,0);
		else return index_pair(-idx-2,-idx-1); 
	}
};

#define QM_ORDVEC(name) ordered_vector<name,name,name,false>



/// \brief base class for a container
///
/// This is a random access sequence which wraps the standard library vector template.
/// Very simple and vanilla...
template<class T>
class base_container : public basedes {
public:
    //
    typedef T												value_type;
    typedef std::vector<T> 		             				container;
    typedef typename container::iterator        			iterator;
    typedef typename container::const_iterator  			const_iterator;
    typedef typename container::reverse_iterator   			reverse_iterator;
    typedef typename container::const_reverse_iterator  	const_reverse_iterator;
    //
    base_container():m_data(new container){p_data = m_data.get();}
    base_container(unsigned N):m_data(new container(N)){p_data = m_data.get();}
    base_container(const base_container& rhs):m_data(rhs.m_data){p_data = m_data.get();}
    
    template<class L>
    base_container(const L& list, unsigned flag);
    
    base_container& operator = (const base_container& rhs) {
    	m_data = rhs.m_data;
    	p_data = m_data.get();
    	return *this;
    }
    //
    /// \brief true if the container is empty @return true or false
    bool              empty()				const 	{return p_data->empty();}
    /// \brief the number of entries in the container @return an unsigned integer
    qm_Size           size()				const 	{return p_data->size();}
    
    virtual	unsigned  flag()	  const {return 0;}
    
    const value_type& operator [] (unsigned i)  const  {QMIND_PRECONDITION(i<this->size(),"Out of bound"); return (*p_data)[i];}
    value_type&       operator [] (unsigned i)         {QMIND_PRECONDITION(i<this->size(),"Out of bound"); return (*p_data)[i];}
    
    const_iterator    			begin()       const { return p_data->begin();}
    const_iterator    			end()         const { return p_data->end();}
    iterator    				begin()             { return p_data->begin();}
    iterator    				end()               { return p_data->end();}
    const_reverse_iterator    	rbegin()      const { return p_data->rbegin();}
    const_reverse_iterator    	rend()        const { return p_data->rend();}
    reverse_iterator    		rbegin()            { return p_data->rbegin();}
    reverse_iterator    		rend()              { return p_data->rend();}
    const value_type& 			front()       const { QM_REQUIRE(this->size()>0,"The container is empty"); return (*p_data)[0];}
    const value_type& 			back()        const { QM_REQUIRE(this->size()>0,"The container is empty"); return (*p_data)[this->size()-1];}
    
    bool operator == (const base_container& rhs) const {
    	if(this->size() != rhs.size()) return false;
    	const_iterator ir = rhs.begin();
    	for(const_iterator it = this->begin();it!=this->end();++it)  {
    		if(*it != *ir) return false;
    		++ir;
    	}
    	return true;
    }
    
    /// \brief Convert the container into a list
    ///
    /// The template L is a list which implements the append method.
    template<class L>
    L dataToList() const {
    	L list;
    	for(typename container::const_iterator it = p_data->begin();it!=p_data->end();++it)
    		list.append(element_to_list<T,L>::doit(*it));
    	return list;
    }
    
protected:
	container*	p_data;
   	QM_SMART_PTR(container)&       vector()       { return m_data;}
   	const QM_SMART_PTR(container)& vector() const { return m_data;}
   	const value_type& getd(qm_Size i) const {return (*p_data)[i];}
    	
private:
   	QM_SMART_PTR(container)   m_data;
};






/// \brief base class for a vector element
///
/// This is a random access sequence which wraps the standard library vector template.
/// Very simple and vanilla...
template<class T>
class base_vector_composite : public base_container<T> {
public:
    //
    typedef base_container<T>								base_class;
	typedef typename base_class::value_type					value_type;
	typedef typename base_class::container					container;
	typedef typename base_class::iterator      				iterator;
	typedef typename base_class::const_iterator				const_iterator;
    //
    base_vector_composite(){}
    base_vector_composite(unsigned N):base_class(N){}
    base_vector_composite(const base_vector_composite& rhs):base_class(rhs){}
    
    base_vector_composite& operator = (const base_vector_composite& rhs) {
    	base_class::operator = (rhs);
    	return *this;
    }
    //
    /// \brief Erases all the elements
    void              clear()						{return this->vector()->clear();}
    /// \brief Resize the container
    void              resize(qm_uns_long siz) 		{this->vector()->resize(siz);}
    /// \brief Erases the element at position pos
    iterator          erase(iterator pos) 			{return this->vector()->erase(pos);}
       
    //base_vector_composite& operator = (const base_vector_composite& rhs) {m_data = rhs.m_data; return *this;}
    
};






/// \brief Wrapper class template for the vector sequence
///
/// This class template is a random access sequence
template<class T>
class vector_composite: public base_vector_composite<T>  {
public:
   	typedef base_vector_composite<T>				base_class;
   	typedef typename base_class::value_type			value_type;
   	typedef typename base_class::container			container;
   	typedef typename container::iterator         	iterator;
   	typedef typename container::const_iterator   	const_iterator;
   	
   	vector_composite(){}
   	vector_composite(unsigned N):base_class(N){}
   	vector_composite(const vector_composite& rhs):base_class(rhs){}
   	
   	void push_back(const value_type& val) 			{this->vector()->push_back(val);}
   	
   	vector_composite& operator = (const vector_composite& rhs) {
   		base_class::operator = (rhs);
   		return *this;
   	}
};


template<class K> struct validate_key_type  {
	static const bool validated = true;
};


//template<>
template<class K>
struct validate_key_type<K*>;

//template<>
template<class K>
struct validate_key_type<QM_SMART_PTR(K)>;

    
/// \brief An ordered vctor container template
/// \ingroup patterns
///
/// - It is a Sorted container and if dup is set to false it becomes a unique sorted container meaning
/// that not to elements as the same key.
/// - It is also a Random Access container.
///
/// IMPORTANT caveat - needs further work
/// The key type should not be a pointer or smart pointer, otherwise it could be modified externally breaking the
/// the sorted associative container property. Maybe this feature needs some further work.
///
/// @param D	the key_type of the container
/// @param dup	If true, the container becomes a unique random access sorted associative container,
/// if false it becomes a sorted random access associative container 
template<class K, class T, class V, bool dup = false>
class ordered_vector : public base_vector_composite<V>  {
public:
   	typedef K																key_type;
   	typedef T																data_type;
   	typedef V																value_type;
   	typedef base_vector_composite< V >										base_class;
   	typedef typename base_class::const_iterator								const_iterator;
   	typedef ordered_vector<K,T,V,dup>										myself;
   	
   	ordered_vector(){}
   	ordered_vector(const ordered_vector& rhs):base_class(rhs){}
    	
   	/// \brief Costruct from a list
    template<class L>
    ordered_vector(const L& list, unsigned flag);
  	
    /// \brief search for a key_type
   	/// @return If the return value is not negative than it represents the index associated with the value_type d,
   	/// otherwise idx = -return-1 representes the index where the element would be inserted if added to the container.
   	qm_long           	search(const key_type& key)			const;
   	/// \brief search for a key_type
   	/// @return Always non-negative, it represent the upper index
   	unsigned           	upper_bound(const key_type& key)	const  {
   		QM_USING_NAMESPACE2(algorithm);
   		return bsearchfirst(this->search(key));
    }
   	
    /// \brief check whether the value_type d is available
    bool              	contains(const key_type& key)		const;
    /// \brief get the index associated with the key_type t
    qm_long           	index(const key_type& t)			const;
    index_pair			niceindex(const key_type& t)		const {return niceIndexWrap<index_pair>::doit(this->search(t));}
    template<class P>
    P					niceindext(const key_type& t)		const {return niceIndexWrap<P>::doit(this->search(t));}
    /// @param Time in years @returns the index i such that grid[i] is closest to t
    unsigned           	closestIndex(const key_type& t)		const {qm_long js; return this->closestIndexBase(t,js);}
    /// @param Time in years @return closest time on grid
    const value_type&  	closestValue(const key_type& t)		const { return (*this)[this->closestIndex(t)];}
    /// @param t key value @return the value corresponding to t
    const value_type&  	value(const key_type& t)			const { 
    	long idx = this->index(t);
    	QM_REQUIRE(idx >= 0,"Key " + object_to_string(t) + " not available");
    	return (*this)[(unsigned)idx];
    }
    
    /// \brief Return the horizon of the dataserie
    //qm_real horizon()             const {return realdiff((key_type)this->back(),(key_type)this->front());}
    /// \brief Return a time relative to index idx
    //qm_real	time(qm_uns_long idx) const {return realdiff((key_type)this->get(idx),(key_type)this->front());}
    /// \brief Return the time change beween index idx and idx-1
    //qm_real	dt(qm_uns_long idx)   const {return realdiff((key_type)this->get(idx),(key_type)this->get(idx-1));}
    
    qm_string   tostring() const    { return "Ordered vector composite";}
    
    /// \brief The Add method
    /// This member function should be used to add new elements to the timeserie
    /// @param va The value to add
    void add(const value_type& va);
    
    /// \brief The Add method for ordered vectors
    /// This member function should be used to add new elements to the timeserie
    /// @param d The date
    /// @param value The value associated with d
    void addvector(const myself& va)  {
    	for(const_iterator it = va.begin();it!=va.end();++it)
    		this->add(*it);
    }
    	
    ordered_vector& operator = (const ordered_vector& rhs) {base_class::operator=(rhs); return *this;}

protected:
   	void insert(qm_Size pos, const value_type& kv) { this->vector()->insert(this->vector()->begin()+pos,kv);}
   	qm_Size closestIndexBase(const key_type& t, qm_long& js) const;
   	
private:
   	static const bool s_validated = validate_key_type<K>::validated;
};
    
    
    template<class V, bool dup = false>
    class simple_ordered_vector: public ordered_vector<V,V,V,dup> {
    public:
    	typedef ordered_vector<V,V,V,dup>		base_class;
    	
    	simple_ordered_vector(){}
    	simple_ordered_vector(const simple_ordered_vector& rhs):base_class(rhs){}
    };
    
    
/// \brief A key-value pair class template
template<class K, class V>
class keyvaluepair : public basedes  {
public:
   	typedef	K	first;
   	typedef	V	second;
   	
   	keyvaluepair(){}
   	keyvaluepair(const first& key):m_key(key){}
   	keyvaluepair(const first& key, const second& value):m_key(key),m_value(value){}
   	keyvaluepair(const keyvaluepair& kvp):m_key(kvp.m_key),m_value(kvp.m_value){}
   	virtual ~keyvaluepair(){}
   	//
   	const first& 	key()      	const {return m_key;}
   	const second& 	value()     const {return m_value;}
   	//
   	second&         get_value()       {return m_value;}
   	void set(const second& value) {m_value = value;}
   	//
   	//keyvaluepair& operator = (const keyvaluepair& rhs) {m_key = rhs.m_key; m_value = rhs.m_value; return *this;}
   	//keyvaluepair& operator = (const first& rhs) {m_key = rhs; m_value = rhs.m_value; return *this;}
   	//
   	bool operator == (const keyvaluepair& rhs) const {return m_key == rhs.m_key;}
  	bool operator != (const keyvaluepair& rhs) const {return m_key != rhs.m_key;}
   	bool operator <  (const keyvaluepair& rhs) const {return m_key <  rhs.m_key;}
   	bool operator <= (const keyvaluepair& rhs) const {return m_key <= rhs.m_key;}
   	bool operator >  (const keyvaluepair& rhs) const {return m_key >  rhs.m_key;}
   	bool operator >= (const keyvaluepair& rhs) const {return m_key >= rhs.m_key;}
   	
   	void copy(const keyvaluepair& rhs)  {
   		m_key   = rhs.m_key;
   		m_value = rhs.m_value;
   	}
    	
   	operator const first& () const {return m_key;}
   	
   	qm_string tostring() const {
   		return object_to_string(m_key) + ": " + object_to_string(m_value);
   	}
   	
private:
   	first   m_key;
   	second  m_value;
};






/// \brief A dataserie template
///
/// A container which implements a key-value relationship.
/// It is a Sorted Associative container and if dup is set to false it becomes a unique sorted associative container meaning
/// that not to elements as the same key.
/// It is also a Random Access container for both keys and values.
///
/// IMPORTANT caveat - needs further work
/// The key type should not be a pointer or smart pointer, otherwise it could be modified externally breaking the
/// the sorted associative container property. Maybe this feature needs some further work.
///
/// @param D	the key_type of the container
/// @param dup	If true, the container becomes a unique random access sorted associative container,
/// if false it becomes a sorted random access associative container
/// @param T	the data_type of the container 
template<class D, bool dup = false, class T = nil>
class dataserie : public ordered_vector< D, T, keyvaluepair<D,T>, dup >  {
public:
  	typedef ordered_vector<D, T, keyvaluepair<D,T>, dup>				base_class;
   	typedef keyvaluepair<D,T>											value_type;
   	typedef D															key_type;
   	typedef T         													data_type;
   	
   	dataserie(){}
   	dataserie(const dataserie& rhs):base_class(rhs){}
    template<class L>
    dataserie(const L& list, unsigned flag):base_class(list,flag){}
    
	/// \brief Slow access get operator
	const value_type& get_slow(unsigned i) const {
		QM_REQUIRE(i<this->size(),"Out of bound in timeserie element");
		return (*this->vector())[i];
	}
    const data_type&  at(const key_type& t) const {
    	return this->value(t).value();
    }
    const data_type&  closest(const key_type& t) const {
    	return this->closestValue(t).value();
    }
	
   	
   	/// \brief The Add method
   	/// This member function should be used to add new elements to the timeserie
   	/// @param k The key
   	/// @param value The value associated with key
   	virtual void addkeyval(const key_type& k, const data_type& v = data_type()) {this->add(value_type(k,v));}
    	   	
   	dataserie& operator = (const dataserie& rhs) {base_class::operator=(rhs); return *this;}
   	
   	qm_string   tostring() const    { return "Dataserie. length: " + object_to_string(this->size());}
    	
   	/// \brief Return a sorted list with all the keys
   	template<class L>
   	L keys() const {
   		L list;
   		for(typename base_class::const_iterator it = this->begin();it!=this->end();++it)  list.append(it->key());
  		return list;
   	}
    	
   	/// \brief Return a list with all the values sorted by keys
  	template<class L>
   	L values() const {
   		L list;
  	    for(typename base_class::const_iterator it = this->begin();it!=this->end();++it)  list.append(it->value());
  	    	return list;
   	}
};

    

//
//namespace 	{
//	inline qm_Size instance()  {
//		return sizeof(keyvaluepair<qm_real,qm_real>);
//	}
//}
    
    
QM_NAMESPACE_END


/*! @} */


#include<qmlib/corelib/templates/impl/containers_impl.hh>


#endif  // __CONTAINERS_QM_HPP__


