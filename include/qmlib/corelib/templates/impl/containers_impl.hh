
#ifndef		__CONTAINERS_IMPL_QM_HPP__
#define		__CONTAINERS_IMPL_QM_HPP__


#ifndef __CONTAINERS_QM_HPP__
 #error <qmlib/impl/containers_impl.hpp> must be included via <qmlib/containers.hpp>
#endif



QM_NAMESPACE


template<class T>
template<class L>
inline base_container<T>::base_container(const L& list, unsigned flag):
	m_data(new typename base_container<T>::container)  {
	unsigned N = length(list);
	for(unsigned i=0;i<N;i++)
		m_data->push_back(extract_from_list_object<T,L>::doit(list,i));
}

template<class K, class T, class V, bool dup>
template<class L>
inline ordered_vector<K,T,V,dup>::ordered_vector(const L& list, unsigned flag)  {
	unsigned N = length(list);
	for(unsigned i=0;i<N;i++)
		this->add(extract_from_list_object<V,L>::doit(list,i));
}


template<class K, class T, class V, bool dup>
inline qm_long ordered_vector<K,T,V,dup>::index(const key_type& t) const  {
	if(this->size()==0) return -1;
   	qm_long js;
   	qm_Size i = this->closestIndexBase(t,js);
   	if(js>=0) return i;
   	//
   	if (close_enough(t,(key_type)((*this)[i])))
   		return i;
   	else
   		return js;
}

	
	
    template<class K, class T, class V, bool dup>
	inline qm_Size ordered_vector<K,T,V,dup>::closestIndexBase(const key_type& t, qm_long& js) const	{
		QM_USING_NAMESPACE2(algorithm);
		QM_REQUIRE(this->size()>0,"No elements in the vector");
		js = this->search(t);
		if(js>=0) return js;
		else  {
			unsigned j = bsearchfirst(js);
			if(j == 0) return 0;
			else if(j >= this->size()) return this->size()-1; 
			else 
				return distance<key_type>(t,key_type(this->getd(j-1))) <= distance<key_type>(t,key_type(this->getd(j))) ? j-1 : j;
		}
	}
	
	
	// Add an Element
	template<class K, class T, class V, bool dup>
	inline void ordered_vector<K,T,V,dup>::add(const value_type& kv)  {
		//if(d.is_not_a_date()) return false;
	    QM_USING_NAMESPACE2(algorithm);
	    qm_long num = this->size();
	    //
	    // first element to be added or last element  -   Fast add (no search required)
	    if(num == 0 || kv >= this->back())  {
	    	if(num == 0)
	    		this->vector()->push_back(kv);
	    	else if(!close_enough(key_type(kv),key_type(this->back())))
	    		this->vector()->push_back(kv);
	    	else if(dup)
	    		this->vector()->push_back(kv);
	    	else
	    		QM_FAIL("Key already available. Need to use replace to replace its data");
	    	return;
	    }
	    
	    //if(num == 0 || kv >= this->back())  {
	    //	this->vector().push_back(kv);
	    //	return;
	    //}
	    
	    qm_long idx;
	    if(dup)  {
	        bsearch1(idx,kv,*(this->vector()));
	        this->insert(idx,kv);
	    }
	    else  {
	    	if(!bsearch1(idx,kv,(*this->vector())))  this->insert(idx,kv);
	    	else QM_FAIL("Key already available. Need to use replace to replace its data");
	    }
	 };
	
	
	
  //
  //
  //
  //
	/*
  template<class D, class T, bool dup>
  inline const typename timeserie<D,T,dup>::value_type&
    timeserie<D,T,dup>::element_at(const key_type& d) const
  {
    const_iterator i = this->find(d);
    if(i == this->end()) return m_notavailable;
    else return *i;
  };
  //
  template<class D, class T, bool dup>
  inline const typename timeserie<D,T,dup>::value_type&
    timeserie<D,T,dup>::element_at_or_just_before(const key_type& d) const
  {
    qm_long i = this->find(d);
    if(i<0)
    {
      if(i==-1) return m_notavailable;
      return m_composites[-i-2];
    }
    else return m_composites[i];
  };
  //
  template<class D, class T, bool dup>
  inline const typename timeserie<D,T,dup>::value_type&
    timeserie<D,T,dup>::element_at_or_just_after(const key_type& d) const
  {
    qm_long i = this->find(d);
    if(i<0)
    {
      qm_long num = this->size();
      qm_long ipo =-i-2;
      if(ipo>=num) return m_notavailable;
      return m_composites[ipo];
    }
    else return m_composites[i];
  };
  //
  // Add an Element
  template <class D, class T, bool dup>
  inline bool timeserie<D,T,dup>::add(const key_type& d, const T& obs)  {
    if(d.is_not_a_date()) return false;
    value_type dv(d,obs);
    QM_USING_NAMESPACE(algorithm)
    qm_long num = this->size();
    qm_long idx;
    //
    if(dup)  {
      if(num == 0 || d >= this->last().date()) m_composites.push_back(dv);
      else  {
        bsearch1(idx,dv,m_composites);
        m_composites.insert(m_composites.begin()+idx,dv);
      }
    }
    else  {
      if(num == 0 || d > this->last().date()) m_composites.push_back(dv);
      else
        if(!bsearch1(idx,dv,m_composites)) m_composites.insert(m_composites.begin()+idx,dv);
        else
        {
          m_composites[idx].set(obs);
          return false;
        }
    }
    //
    return true;
  };

  */
  
  
	template<class K, class T, class V, bool dup>
  	inline qm_long ordered_vector<K,T,V,dup>::search(const key_type& key) const  {
  		QM_USING_NAMESPACE2(algorithm);
  		qm_long idx;
  		value_type kv = value_type(key);
  		if(!bsearch1(idx,kv,*(this->vector())))  return -idx-1;
  		
  		// If the container is not unique than return the first element in container with value key
  		// ************************ This part can be implemented better **************************************
  		if(dup)  {
  			// Need to check this!!!!!!!!!!!!!!!!!1
  			for(qm_long i = idx-1;i>=0;--i)
  				if((*this)[i] < kv) return i+1;
  			return 0;
  		}
  		return idx;
  	}
  	
  	
template<class K, class T, class V, bool dup>
inline bool ordered_vector<K,T,V,dup>::contains(const key_type& t)  const  {
	qm_long js;
	if(!this->size())
		return false;
	else if(this->size() == 1)
		return close_enough(t,(key_type)((*this)[0]));
	else  {
		qm_Size i = this->closestIndexBase(t, js);
		if(js>=0) return true;
		else return close_enough(t,(key_type)((*this)[i]));
	}
}
  	
  	
  	
  	
  	
  	/*
  	template <class D, class T, bool dup>
  	inline typename timeserie<D,T,dup>::iterator timeserie<D,T,dup>::lower_bound(const key_type& d)
  	{
  		qm_long idx = this->search(d);
  		if(idx>=0) return this->begin()+idx;
  		else return this->end();
  	}
  //

  //
  template <class D, class T, bool dup>
  inline typename timeserie<D,T,dup>::iterator timeserie<D,T,dup>::upper_bound(const key_type& d)
  {
    if(dup)  {
      equal_range(d).second;
    }
    return this->lower_bound(d);
  }
  //
  //
  template <class D, class T, bool dup>
  inline pair<typename timeserie<D,T,dup>::iterator, typename timeserie<D,T,dup>::iterator>
    timeserie<D,T,dup>::equal_range(const key_type& d)
  {
    pair<iterator, iterator> pt;
    iterator it1   = this->lower_bound(d);
    //
    if(dup)  {
      it2 = it1;
      if(it1 != this->end())
      {
        for(iterator is = it+1;is!=end();++is)
        {
          if(is->date() > d) break;
          ++it2;
        }
      }
      pt.first  = it1;
      pt.second = it2;
    }
    else  {
      pt.first  = it1;
      pt.second = it1;
    }
    return pt;
  }
  //
  //
template<class T> void dated<T>::clear() {
   dates_    .erase(dates_    .begin(),dates_    .end());
   elements_ .erase(elements_ .begin(),elements_ .end());
};

template<class T> void dated<T>::remove(const date& d) {
   int i=index_of_date(d);
   if (i>=0) {
      dates_.erase(dates_.begin()+i);
      elements_.erase(elements_.begin()+i);
   };
};

template<class T> void dated<T>::remove_between(const date& d1, const date& d2) {
    if (!d1.valid()) return;
    if (!d2.valid()) return;
    for (int t=size()-1;t>=0;t--){  // this is very slow, to be replaced with one using vector erase.
	date d=date_at(t);
	if ( (d>d1) && (d<d2) ) { 
	    dates_.erase(dates_.begin()+t);
	    elements_.erase(elements_.begin()+t);
	};
    };
};


template<class T> void dated<T>::remove_between_including_end_points(const date& d1, const date& d2) {
    if (!d1.valid()) return;
    if (!d2.valid()) return;
    for (int t=size()-1;t>=0;t--){  // this is very slow, to be replaced with one using vector erase.
	date d=date_at(t);
	if ( (d>=d1) && (d<=d2) ) { 
	    dates_.erase(dates_.begin()+t);
	    elements_.erase(elements_.begin()+t);
	};
    };
};

template<class T> void dated<T>::remove_before(const date& d) {
   remove_between(--first_date(),d);
};

template<class T> void dated<T>::remove_after(const date& d) {
   remove_between(d,++last_date());
};

template <class T> ostream& operator << (ostream& outf, const dated<T>& dobs ) {
   if (dobs.empty()) return outf;
   for (int t=0; t<dobs.size(); ++t) {
      outf << dobs.date_at(t) << " "  << dobs.element_at(t)  << endl;
   };
   return outf;
};
*/

QM_NAMESPACE_END


#endif		//		__CONTAINERS_IMPL_QM_HPP__


