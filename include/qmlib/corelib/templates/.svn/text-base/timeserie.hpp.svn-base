

#ifndef   __TIMESERIE_QM_HPP__
#define   __TIMESERIE_QM_HPP__



#include <qmlib/corelib/templates/containers.hpp>


/// \file
/// \brief Definition of some generic Containers
/// \ingroup containers



QM_NAMESPACE

template<class D, class T> class timeserie;


/// \brief timeserie element
/// \ingroup containers
template<class T>
class timeserie_elem : public base_container<T>  {
public:
    typedef base_container<T>								base_class;
	typedef typename base_class::value_type					value_type;
	typedef typename base_class::container					container;
	typedef typename base_class::iterator      				iterator;
	typedef typename base_class::const_iterator				const_iterator;
	
	timeserie_elem(unsigned dim = 1):base_class(dim){}
	timeserie_elem(const timeserie_elem& rhs):base_class(rhs){}
	
	template<class L>
	timeserie_elem(const L& lis, unsigned dimens):base_class(lis,dimens){}
	
	qm_string tostring() const;
	
	/// \brief Slow access set operator
	void set_slow(unsigned i, const T& val) {
		QM_REQUIRE(i<this->size(),"Out of bound in timeserie element");
		(*this->vector())[i] = val;
	}
	/// \brief Slow access get operator
	const T& get_slow(unsigned i) const {
		QM_REQUIRE(i<this->size(),"Out of bound in timeserie element");
		return (*this->vector())[i];
	}
};



template<class D, class T, class L> struct time_serie_traits;

/// \brief timeserie container
/// \ingroup containers
template<class D, class T>
class timeserie: public dataserie<D,false,timeserie_elem<T> >  {
public:
	typedef dataserie<D,false,timeserie_elem<T> >				base_class;
	typedef typename base_class::value_type						value_type;
	typedef typename base_class::key_type						key_type;
	typedef typename base_class::data_type						data_type;
	typedef typename data_type::value_type						element_type;

 	timeserie(qm_Size numpaths = 1):m_numpaths(numpaths) {QM_REQUIRE(m_numpaths>0,"Number of paths must be positive");}
 	
 	template<class L>
 	timeserie(const L& list, unsigned flag):m_numpaths(flag)  {
 		unsigned N = length(list);
 		for(unsigned i=0;i<N;i++)  {
 			value_type va = extract_from_list_object<value_type,L>::doit(list,i);
 			QM_REQUIRE(va.value().size() == m_numpaths,"Error building time serie from list.")
 			this->add(va);
 		}
 	}
    unsigned  flag()	  const {return m_numpaths;}
   	unsigned  count()     const {return m_numpaths;}
   	void	  set_numpaths(unsigned numpaths)  {
   		QM_REQUIRE(numpaths > 0,"Number of paths must be bigger than zero");
   		this->clear();
   		m_numpaths = numpaths;
   	}
   	
   	const element_type& operator () (unsigned i, unsigned j) const {return (*this)[i].value()[j];}
   	
   	qm_string         tostring() const { return "timeserie object. Numseries "+object_to_string(m_numpaths) +
    							    	        ". length: " + object_to_string(this->size());}
   	
   	void addkeyval(const key_type& k, const data_type& v) {
   		QM_REQUIRE(v.size() == m_numpaths,"Adding a cross section to a timeserie with diffenet number of series");
   		this->add(value_type(k,v));
   	}
   	
   	template<class L>
   	void addcross_sec(const key_type& k, const L& cs) {
	    this->addkeyval(k,this->check(data_type(cs,0)));
   	}

private:
   	unsigned m_numpaths;
   	
   	const data_type& check(const data_type& val) const {
   		QM_REQUIRE(val.size() == m_numpaths,"Adding to time serie an element with diffent number of size");
   		return val;
   	}
};



template<class T>
inline qm_string timeserie_elem<T>::tostring() const  {
	const_iterator it=this->begin();
	qm_string str = "[" + object_to_string(*it);
	it++;
	for(;it!=this->end();++it)
		str += " , " + object_to_string(*it);
	str += "]";
	return str;
}


QM_NAMESPACE_END

#endif  // __TIMESERIE_QM_HPP__


