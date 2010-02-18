
#ifndef   __OPTION_INTERFACES_QM_HPP__
#define   __OPTION_INTERFACES_QM_HPP__


#include <qmlib/payoffs/factory.hpp>
#include <qmlib/finance/instruments/exercise.hpp>
#include <qmlib/finance/instrument.hpp>
#include <qmlib/math/pde/models/lrcd.hpp>
#include <qmlib/math/stoch/diffusion.hpp>


/** \file
 * \brief Interfaces for derivatives
 * 
 * \ingroup finins
 */



QM_NAMESPACE2(finance)


template<unsigned N, pricingValuationMethod V> class optionmodel;


typedef QM_FROM_NAMESPACE2(math)STOCHASTIC STOCHASTIC;


/** \brief base class template for options
 * \ingroup finins
 * 
 * @param N the number of underlyings. This is the number of
 * instrument the option depends on. This is not a basket of options,
 * this is a single option on N underlyings (therefore an option on a basket).
 */
template<unsigned N>
class option_base {
public:
	//typedef optionmodel<N,pde_>									pderatetype;
	//typedef QM_FROM_NAMESPACE2(math)pdemodel_base<qm_real,N>	pdetype;
	//typedef QM_SMART_PTR(pdetype)								PDETYPE;
	
	static const unsigned     dim			 = N;
	
	virtual ~option_base(){}
	unsigned     num_underlyings() 			  const {return dim;}
	virtual      exercisetype exerciseType()  const = 0;
	virtual      payofftype   payoffType()    const = 0;
	
	/// \brief build a model for PDE pricing
	///
	///@param pe The time step
	///@param diff The stochastic diffusion process
	///@return a pde_model
	//PDETYPE	  	 get_pde(const pderatetype& rate) const;
	//PDETYPE	  	 get_pde0() const {return m_pde;}
protected:
	//PDETYPE		m_pde;
	option_base(){}
	//virtual void create_pde(const pderatetype& rate) const {}
};




/** \brief Option class template
 *  \ingroup finins
 * 
 * Simply stated, an %option is a choice.
 * The buyer of an option acquires the right and not the obligation,
 * to buy or sell an underlying asset under specific conditions
 * in %exchange for the payment of a premium.
 * It is entirely up to the buyer whether or not to exercise that right;
 * only the seller of the %option is obligated to perform.
 * 
 * This class template exposes:
 * @param N the number of underlyings. This is the number of
 * instrument the option depends on. This is not a basket of options,
 * this is a single option on N underlyings.
 * @param et The exercisetype
 * @param pt The payofftype
 * \ingroup finins
 */
template<unsigned N, exercisetype et, payofftype pt>
class option : public option_base<N> {
public:
	typedef option_base<N>										basetype;
	typedef Exercise<et>										exercise_type;
	typedef Payoff<N,pt>										payoff_type;
	typedef typename payoff_type::input_type					input_type;
	typedef QM_SMART_PTR(payoff_type)							PAYOFF_TYPE;
	//typedef typename basetype::pderatetype						pderatetype;
	//typedef typename basetype::pdetype							pdetype;
	//typedef typename basetype::PDETYPE							PDETYPE;
	
	static const exercisetype ExpiryType 	 = et;
	static const payofftype   PayoffType 	 = pt;
	
	// \brief Option expiry type
	// 
	// @return expirytype The type of expiration, european_, american_, bermudan_
	exercisetype exerciseType()    			const {return exercise_type::type;}
	payofftype   payoffType() 	 			const {return PayoffType;}
	
	///\brief Get the Payoff object
	///
	///@return a Payoff smart pointer
	PAYOFF_TYPE	 payoff() const {return m_payoff;}
	///\brief Get the exercise schedule
	///
	///@return the exercise schedule
	//const exercise_type& exercise() const {return m_exercise;}
	exercise_type exercise() const {return m_exercise;}
	
protected:
	PAYOFF_TYPE		m_payoff;
	exercise_type 	m_exercise;
	
	option(const PAYOFF_TYPE po, const exercise_type& ex):m_payoff(po),m_exercise(ex){
		QM_REQUIRE(m_payoff,"Payoff is null");
		QM_REQUIRE(m_exercise.size()>0,"No dates in exercise");
	}
	
	//void create_pde(const pderatetype& rate) const;
};







template<instrumentype typ, unsigned N, exercisetype et, payofftype pt>
class optioninst: public Instrument<typ>, public option<N,et,pt>  {
public:
	typedef option<N,et,pt> 					option_base;
	typedef optioninst<typ,N,et,pt>				option_type;
	typedef QM_SMART_PTR(option_type)			OPTION_TYPE;
	typedef typename option_base::PAYOFF_TYPE	PAYOFF_TYPE;
	typedef typename option_base::exercise_type	exercise_type;
	
	static OPTION_TYPE make(const PAYOFF_TYPE po, const exercise_type& ex) {
		return OPTION_TYPE(new option_type(po,ex));
	}
	
	qm_string    name() const {return this->code() + this->exercise().code() + " " + this->payoff()->code();}
protected:
	optioninst(const PAYOFF_TYPE po, const exercise_type& ex):option_base(po,ex){}
};


/*
template<unsigned N> inline typename option_base<N>::PDETYPE
option_base<N>::get_pde(const typename option_base<N>::pderatetype& rate) const  {
	if(!m_pde)
		this->create_pde(rate);
	return m_pde;
}
*/

QM_NAMESPACE_END2

/*! @} */

#endif	//	__OPTION_INTERFACES_QM_HPP__





