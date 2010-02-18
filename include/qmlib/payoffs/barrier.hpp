
#ifndef   __BARRIERE_QM_HPP__
#define   __BARRIERE_QM_HPP__


#include <qmlib/payoffs/payoffinfo.hpp>


/** \file
 * \brief Barrier definitions
 * 
 * \ingroup finins
 */



QM_NAMESPACE


class BarrierBase;
typedef QM_SMART_PTR(BarrierBase) BARRIER;


/** \brief Barrier base class
 * \ingroup finins
 * 
 * A class containg
 *  - barrier level
 *  - the rebate
 *  - The direction of the barrier (up or down)
 *  - The type of barrier (in or out)
 */ 
class BarrierBase : public icodename {
public:
	qm_real get_barrier() const {return m_barrier;}
	void    set_barrier(qm_real b)   {m_barrier = b;}
	qm_real get_rebate() const {return m_rebate;}
	void    set_rebate(qm_real r)   {m_rebate = r;}
	
	qm_string   name() const {return this->code() + " barrier";}
	
	virtual barriertype type() const {return KnockOut_;}
	
	/// \brief check if barrier has been knocked
	///
	///@return true if the barrier has been knocked
	///@param x value to check
	virtual bool		knocked(qm_real x) const {return false;}
	
	/// \brief check direction of barrier
	///
	///@return true if this is an up barrier, false for a down barrier
	virtual bool		up() const {return true;}
	
	qm_string tostring() const {return this->name();}
protected:
	qm_real m_barrier;
	qm_real m_rebate;
	BarrierBase(){}
	BarrierBase(qm_real barrier_, qm_real rebate_ = 0):m_barrier(barrier_),m_rebate(rebate_){}
};


/** \brief Barrier implementation via template
 * \ingroup finins
 */
template<bool U, barriertype T>
class Barrier : public BarrierBase  {
public:
	typedef BarrierTalk<U,T>	barrier_traits;
	static const bool			up_type 	 = U;
	static const barriertype	barrier_type = T;
	Barrier(qm_real barrier_, qm_real rebate_ = 0):BarrierBase(barrier_,rebate_){}
	
	barriertype type() const {return barrier_type;}
	bool		up()   const {return up_type;}
	qm_string   code() const {return barrier_traits::tostring();}
	bool		knocked(qm_real x) const {return barrier_traits::knocked(x,this->get_barrier());}
};


/** \brief Barrier factory
 * \ingroup finins
 */
struct BarrierFactory  {
	static BARRIER UpAndOut(qm_real b, qm_real r)   {return BARRIER(new Barrier<true,KnockOut_>(b,r));}
	static BARRIER DownAndOut(qm_real b, qm_real r) {return BARRIER(new Barrier<false,KnockOut_>(b,r));}
	static BARRIER UpAndIn(qm_real b, qm_real r)    {return BARRIER(new Barrier<true,KnockIn_>(b,r));}
	static BARRIER DownAndIn(qm_real b, qm_real r)  {return BARRIER(new Barrier<false,KnockIn_>(b,r));}
};


QM_NAMESPACE_END


#endif	//	__BARRIERE_QM_HPP__

