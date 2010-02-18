

#ifndef   __TEMPLATES_PRICER_ENGINE_QM_HPP__
#define   __TEMPLATES_PRICER_ENGINE_QM_HPP__


#include <qmlib/corelib/dates/all.hpp>


/*! \defgroup pricers Pricers library

    The pricers library defines a series of templates for pricing
    different financial instruments. The templates allow to specify:
    
    	- The model to use in the pricing
    	- The valuation method
    	
    For example an option on a given underlying could be priced with
    a standard black-Scholes model using an analytical valuation method or a
    montecarlo valuation method or a pde valuation method.

    @{
*/


/** \file
 *  \brief Base template classes for pricers
 */


QM_NAMESPACE2(finance)



/** \brief Valuation methods for pricing
 */


template<class D>
class : public CRTP<D>
{
public:
};

class EuropeanVanilla: public CRTP<EuropeanVanilla>  {
	
};



/** \brief Base template class for pricers
 * @param It The instrument type which can be priced by the pricer
 * @param R  The type of result object which is return by the pricer
 */
template<class V>
class ipricer : public basedes {
public:
	typedef V											valuation_type;
	typedef typename valuation_type::instrument_type	instrument_type;
	typedef typename valuation_type::result_type		result_type;
	typedef QM_SMART_PTR(instrument_type)				InstType;
	typedef std::list<InstType>							InstTypes;
	typedef typename InstTypes::const_iterator			const_iterator;
	
	ipricer(bool fullevaluation):m_full(fullevaluation){}
	
	template<class G>
	void add(const QM_SMART_PTR(G)& gi)  {
		InstType it = smart_cast<instrument_type,G>(gi);
		if(it) m_insts.push_back(it);
	}
	unsigned       size()     const   {return m_insts.size();}
	const_iterator begin()    const   {return m_insts.begin();}
	const_iterator end()      const   {return m_insts.end();}
	void		   reset()    const   {m_res = ResTyp();}
	bool		   fulleval() const   {return m_full;}
	
	virtual qdate     date()      const {QM_FAIL("pricer date not implemeneted");}
	virtual ResTyp    calculate()       {QM_FAIL("calculate method for pricer not implemeneted");}
protected:
	InstTypes	        m_insts;
	mutable ResTyp		m_res;
	bool			    m_full;
};



template<class It, class R>
class analytical_pricer  {
public:
	typedef It			instrument_type;
	typedef R			result_type;
};




QM_NAMESPACE_END2

/*! @} */

#endif	//	__TEMPLATES_PRICER_ENGINE_QM_HPP__

