

#ifndef   __COMPOSITE_RATE_QM_HPP__
#define   __COMPOSITE_RATE_QM_HPP__


#include <qmlib/corelib/static/all.hpp>
#include <qmlib/corelib/tools.hpp>
#include <qmlib/corelib/templates/observer.hpp>


/** \file
 *  \brief Composite rate base class template
 *  \ingroup rates
 * 
 */


QM_NAMESPACE2(finance)


template<class C> struct composite_rate_element {};


class basecomposite:  public lazy  {
public:
	void rebuild() {this->build(); this->refresh();}
	
	/// \brief build the composite rate
	virtual void build()   {}
	
	/// \brief refresh the composite rate
	///
	/// This function does not require to rebuild the compositerate but only
	/// to refresh its values
	virtual void refresh() {}
	
	const itersolver&		solver()		 const  { return m_solve;}
protected:
	itersolver	m_solve;
};



/** \brief Class template for a general composite rate
 *  \ingroup rates
 * 
 * Class template for handling composite rates
 * 
 * @param C element type
 */
template<class C>
class composite_rate :  public basecomposite {
public:
	typedef C											element_type;
	typedef QM_SMART_PTR(element_type)					ELEMENT;
	typedef composite_rate_element<element_type>		element_wrap;
	typedef typename element_wrap::key_type				key_type;
	typedef dataserie<key_type,false,ELEMENT>  			element_serie;
	typedef typename element_serie::iterator			iterator;
	typedef typename element_serie::const_iterator		const_iterator;
	
	/// \brief Add a rate to the composite rate list
	template<class T>
	void add(const QM_SMART_PTR(T)& element)  {this->addelement(smart_cast<C,T>(element));}
	
	/// \brief number of rates used in the composite rate
	unsigned 				size()	   	     const  { return m_used_insts.size();}
	iterator				begin()        		    { return m_used_insts.begin();}
	iterator				end()           		{ return m_used_insts.end();}
	const_iterator			begin()          const 	{ return m_used_insts.begin();}
	const_iterator			end()            const 	{ return m_used_insts.end();}
	ELEMENT				 	get(unsigned i)  const 	{ return m_used_insts.get_slow(i).value().elem;}
	const qdate&			referenceDate()  const 	{ return m_date;}
	
	template<class L>
	L instlist(bool idl) const {
		L l;
		if(idl)
			for(const_iterator it=m_idle_insts.begin();it!=m_idle_insts.end();++it)
				l.append(it->value());
		else
			for(const_iterator it=this->begin();it!=this->end();++it)
				l.append(it->value());
		return l;
	}
	
	void updatelazy() {this->refresh_update();}
	
protected:
	element_serie	m_idle_insts;
	element_serie	m_used_insts;
	qdate			m_date;
	
	composite_rate(){}
	composite_rate(const qdate& dte):m_date(dte){}
	
	void refresh_update();
	
	virtual bool addtoinstruments(const key_type& key, const ELEMENT& el) = 0;

	/// \brief clean the used instruments
	///
	/// This function loop over the instrument used for building the composite rate
	/// and eliminate the one which are not valid
	bool clean();
	
	/// \brief Add an element to the composite rate
	void addelement(const ELEMENT& el)  {
		if(!el) return;
		try  {
			key_type k = element_wrap::keyval(el,m_date);
			if(element_wrap::valid(el))  {
				if(this->addtoinstruments(k,el))
					this->rebuild();
			}
			else
				m_idle_insts.addkeyval(k,el);
			this->registerWith(el);
		}
		catch(...){}
	}
};


template<class C>
inline bool composite_rate<C>::clean()  {
	ELEMENT el;
	key_type k;
	bool changed = false;
	for(iterator it=this->begin();it!=this->end();++it)  {
		el = it->value();
		if(!element_wrap::valid(el))  {
			changed = true;
			k = element_wrap::keyval(el,m_date);
			m_idle_insts.addkeyval(k,el);
			it = m_used_insts.erase(it);
			if(it == this->end()) break;
		}
	}
	return changed;
}

template<class C>
inline void composite_rate<C>::refresh_update()  {
	ELEMENT el;
	key_type k;
	bool ch = this->clean();
	for(iterator it=m_idle_insts.begin();it!=m_idle_insts.end();++it)  {
		el = it->value();
		k  = element_wrap::keyval(el,m_date);
		if(!element_wrap::valid(el)) continue;
		if(this->addtoinstruments(k,el))  {
			ch = true;
			it = m_idle_insts.erase(it);
			if(it == m_idle_insts.end()) break;
		}
	}
	if(ch) this->rebuild();
	else this->refresh();
}



QM_NAMESPACE_END2



#endif  //  __COMPOSITE_RATE_QM_HPP__

