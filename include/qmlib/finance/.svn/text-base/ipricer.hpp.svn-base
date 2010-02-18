

#ifndef   __PRICER_ENGINE_INTERFACE_QM_HPP__
#define   __PRICER_ENGINE_INTERFACE_QM_HPP__

#include <qmlib/finance/iquote.hpp>
#include <qmlib/finance/instrument.hpp>


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


/** \brief Interface class for pricing engines
 */
class ipricer : public icodename , public listwrap<INST> {
	friend class instrument;
public:
	ipricer(bool fullevaluation):m_full(fullevaluation){}
	bool		    fulleval()   const  {return m_full;}
	
	virtual void    reset()      const {}
	
	/// \brief Perform calculation
	virtual void    calculate()  const {}
	
	/// \brief Reference date
	///
	/// This is the date for which valuation is requested.
	virtual qdate   date()		const {QM_FAIL("not implemented");}
	
	virtual qm_real dcf(const qdate& dte) const {return 0;}
	
	/// \brief Add an instrument to the pricer
	virtual bool    add(const INST& inst) {return false;}
	
	virtual unsigned  numberOfThreads() const {return 0;}
	
	/// \brief Valuation method pricingValuationMethod
	virtual pricingValuationMethod method() const {QM_FAIL("Not implemented");}
	
protected:
	bool		m_full;
};


inline void finins::set_pricer(const PRICER& e)  {
	if(e->add(m_inst))
		m_pricer = e;
}


QM_NAMESPACE_END2

/*! @} */

#endif	//	__PRICER_ENGINE_INTERFACE_QM_HPP__


