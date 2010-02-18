
#ifndef   __PAYOFF1_IMPL_QM_HPP__
#define   __PAYOFF1_IMPL_QM_HPP__

#include <qmlib/payoffs/payoff.hpp>
#include <qmlib/math/pde/models/lrcd.hpp>


/** \file
 * \brief class template for an Option Payoff
 * 
 * \ingroup finins
 */


QM_NAMESPACE


template<payoffname pn>
class vanillaPayoffImpl: public Payoff<1u,Vanilla_> {
public:
	typedef Payoff<1u,Vanilla_>					base_payoff;
	typedef payoffinfo<pn>						info_type;
	typedef typename base_payoff::input_type	input_type;
	
	vanillaPayoffImpl(qm_real strike):base_payoff(strike){}
	payoffname id() const {return pn;}
	qm_real value(const input_type& x) const {return info_type::get(this->get_strike(),x[0]);}
	qm_string code() const {return info_type::name();}
};


/** Single barrier payoff implementation
 */
template<bool U, barriertype T, payoffname pid, payoffname pn>
class barrierPayoffImpl: public Payoff<1u,Barrier_>  {
public:
	typedef Payoff<1u,Barrier_>		base_payoff;
	typedef Barrier<U,T>			barrier_type;
	typedef payoffinfo<pn>			info_type;

	barrierPayoffImpl(qm_real strike, qm_real bar, qm_real reb):m_barrier(new barrier_type(bar,reb)) {
		if(U) m_upbarrier = m_barrier;
		else m_dobarrier = m_barrier;
		this->set_strike(strike);
	}
	payoffname id()  const {return pid;}
	qm_string code() const {return m_barrier->code() + " " + info_type::name();}
	void    set_strike(qm_real s)  {
		QM_REQUIRE(!m_barrier->knocked(s)," Invalid strike");
		base_payoff::set_strike(s);
	}
	qm_string name() const {return this->code() + " payoff, strike " + object_to_string(get_strike());}
protected:
	BARRIER m_barrier;
};


template<bool U, barriertype T, payoffname pid>
class OneTouchImpl: public Payoff<1u,Barrier_>  {
public:
	typedef Payoff<1u,Barrier_>		base_payoff;
	typedef Barrier<U,T>			barrier_type;

	OneTouchImpl(qm_real bar, qm_real reb)  {
		BARRIER ba(new barrier_type(bar,reb));
		if(U) m_upbarrier = ba;
		else m_dobarrier = ba;
	}
	void    set_strike(qm_real s)  {QM_FAIL("There is no strike in a digital barrier");}
	payoffname id()  const {return pid;}
	qm_string code() const {
		if(U) return m_upbarrier->code() + " binary";
		else return m_dobarrier->code() + " binary";
	}
};


inline Payoff<1u,Vanilla_>::boundary_type
Payoff<1u,Vanilla_>::boundaries() const  {
	boundary_type b(interval_type(0,Infinity()));
	return b;
}


inline pdegridtraits<1u>::GRIDTYPE
Payoff<1u,Vanilla_>::grid(qm_real DX, unsigned M) const {
	qm_real K = this->get_strike();
	return pdegridtraits<1u>::factory::make1(K-DX,K+DX,M);
}



inline Payoff<1u,Barrier_>::boundary_type
Payoff<1u,Barrier_>::boundaries() const  {
	if(m_upbarrier && !m_dobarrier)
		return boundary_type(interval_type(0,m_upbarrier->get_barrier()));
	else if(!m_upbarrier && m_dobarrier)
		return boundary_type(interval_type(m_dobarrier->get_barrier(),std::numeric_limits<qm_real>::infinity()));
	else
		return boundary_type(interval_type(m_dobarrier->get_barrier(),m_upbarrier->get_barrier()));
}


QM_NAMESPACE_END


#endif	//	__PAYOFF1_IMPL_QM_HPP__

