
#ifndef __TIMECOEF_QM_HPP__
#define __TIMECOEF_QM_HPP__


#include <qmlib/math/tools/timegrid.hpp>


/// \file
/// \brief Definition of a timecoef
/// \ingroup math


QM_NAMESPACE2(math)


/** \brief Base class for time dependent coefficients
 * with a cache. It can be used in pde or montecarlo methods
 */
template<class T>
class timedependentcoef : public basedes {
public:
	typedef T							numtype;
	typedef std::vector<numtype>  		cachetype;
	typedef timedependentcoef<numtype>	selftype;
	
	timedependentcoef(){}
	
	/// \brief clear the cache
	void clearcache() {m_cache.clear();}
	
	const TIMEGRID& get_timegrid() const {return m_tg;}
	void set_timegrid(const TIMEGRID& tg) {m_tg = tg; QM_REQUIRE(m_tg,"Time grid is null");}
	
	/// \brief return the value at time step t
	///@param t It defined the time-step interval \f$[t,t+1]\f$.
	///@param explic if true will calculate at time[t], otherwise at tim[t+1].
	numtype value(unsigned t, bool explic) const;
	
	virtual qm_real time(unsigned t) const {return m_tg->time(t);} 
protected:
	cachetype	m_cache;
	TIMEGRID 	m_tg;
	selftype& 	noConst() const { return const_cast<selftype&>(*this); }
	
	virtual numtype calcfromcache(unsigned t, bool explic) const {return 0;}
	virtual numtype evaluate(unsigned t) const {return 0;}
};



template<class T>
inline typename timedependentcoef<T>::numtype
timedependentcoef<T>::value(unsigned t, bool explic) const  {
	unsigned t1 = explic ? t+1 : t;
	unsigned S  = m_cache.size();
	if(S <= t1)  {
		for(unsigned i=S;i<=t1;i++)
			noConst().m_cache.push_back(this->evaluate(i));
	}
	return this->calcfromcache(t,explic);	
}


QM_NAMESPACE_END2


#endif	//	__TIMECOEF_QM_HPP__

