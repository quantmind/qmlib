
#ifndef   __PAYOFF1_QM_HPP__
#define   __PAYOFF1_QM_HPP__

#include <qmlib/payoffs/payoff.hpp>
#include <qmlib/math/pde/models/lrcd.hpp>


/** \file
 * \brief class template for an Option Payoff
 * 
 * \ingroup finins
 */


QM_NAMESPACE


/** \brief Helper class for a payoff with a strike
 * \ingroup payoff
 */
class _striked_payoff {
public:
	virtual ~_striked_payoff(){}

	virtual void    set_strike(qm_real s)  {m_strike = s;}
	qm_real get_strike() const {return m_strike;}
	
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & m_strike;
	}
protected:
	qm_real m_strike;
	_striked_payoff(qm_real strike = std::numeric_limits<qm_real>::quiet_NaN()):m_strike(strike){}
};


/** Base class for Vanilla Payoffs
 * \ingroup payoff
 */
template<>
class Payoff<1u,Vanilla_>: public PayoffBase<1u>, public _striked_payoff {
public:
	static const payofftype  type   = Vanilla_;
	payofftype Type() const {return type;}
	boundary_type boundaries() const;
	qm_string name() const {return this->code() + " payoff, strike " + object_to_string(get_strike());}
	
	/// \brief Create a pde model
	///
	/// Very useful function for creating a standard option pde model on the fly.
	///
	///@param sp a diffusion process
	///@param yc Interest rate idiscountfactor
	///@param cy Convenience yield idiscountfactor
	///@param M number of grid points
	///@param T time horizion for calculation. This is not the time to maturity
	///of the option, it is just a number which is used to get the size of the grid.
	///Ideally one should choose T as close as possible to the option expiry.
	//RCD1D pdemodel(const DIFFP1& sp, DISCOUNTCURVE yc, DISCOUNTCURVE cy,
	//			   unsigned M, qm_real T) const;
	GRIDTYPE grid(qm_real DX, unsigned M) const;
protected:
	Payoff(qm_real strike):_striked_payoff(strike){}
};



/** \brief Base class for one tough Barrier payoffs
 * \ingroup payoff
 */
template<>
class Payoff<1u,Barrier_>: public PayoffBase<1u>, public _striked_payoff  {
public:
	static const payofftype  type   = Barrier_;
	payofftype Type()   const {return type;}
	BARRIER upbarrier() const {return m_upbarrier;}
	BARRIER dobarrier() const {return m_dobarrier;}
	boundary_type boundaries() const;
protected:
	BARRIER m_upbarrier;
	BARRIER m_dobarrier;
	Payoff(){}
};



template<>
class Payoff<1u,Average_>: public PayoffBase<1u>, public _striked_payoff {
public:
	static const payofftype  type   = Average_;
	payofftype Type() const {return type;}
protected:
	Payoff(qm_real strike):_striked_payoff(strike){}
};



QM_NAMESPACE_END


#include <qmlib/payoffs/impl/payoff1_impl.hpp>


#endif	//	__PAYOFF1_QM_HPP__

