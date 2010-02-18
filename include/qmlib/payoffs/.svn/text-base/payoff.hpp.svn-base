
#ifndef   __PAYOFF_QM_HPP__
#define   __PAYOFF_QM_HPP__


#include <qmlib/payoffs/barrier.hpp>
#include <qmlib/math/pde/structured_grid.hpp>


/** \file
 * \brief Base class templates for an Option Payoff
 * 
 * \ingroup payoff
 */



QM_NAMESPACE


template<unsigned N> 				class PayoffBase;
template<unsigned N, payofftype P>  class Payoff;
template<unsigned N, payofftype P,  class U> class composite_payoff;

template<> class PayoffBase<0u> {};
template<payofftype P, class U> class composite_payoff<1u,P,U> {};


/** \brief Payoff virtual class template
 * \ingroup payoff
 * 
 * @param N dimension of payoff function
 * 
 * A payoff is a function defined in \f$R^N \rightarrow R\f$ and it is used
 * to define option payoffs
 */
template<unsigned N>
class PayoffBase : public icodename {
public:
	typedef boost::numeric::interval<qm_real>				interval_type;
	/// \brief payoff input type
	typedef qmlib::math::tinyvec<qm_real,N>    				input_type;
	typedef qmlib::math::tinyvec<interval_type,N>			boundary_type;
	typedef qm_real							   				value_type;
	
	typedef pdegridtraits<N>								gridtraits;
	typedef typename gridtraits::gridtype					gridtype;
	typedef typename gridtraits::GRIDTYPE					GRIDTYPE;
	
	static const unsigned 	 dim	= N;

	PayoffBase(){}
	virtual ~PayoffBase(){}
	
	/// \brief Payoff implementation
	///
	/// This function should be overwritten by derived classes
	/// @param x a \f$R^N\f$ vector of real values
	/// @return payoff value
	virtual qm_real value(const input_type& x) const {return 0;}
	
	/// \brief another Payoff function
	///
	/// We use an arbitrary object P to access the payoff
	/// @param x an object which can be converted into a \f$R^N\f$ vector of real values
	/// @return payoff value
	template<class P>
	qm_real value2(const P& vec) const {return this->value(input_type::make(vec));}
	
	/// \brief Payoff input type
	///
	/// @return a payoff input type
	input_type input() const {return input_type();}
	
	qm_string name()      const {return this->code() + " payoff";}
	qm_string tostring()  const {return this->name();}
	unsigned  dimension() const {return dim;}
	
	/// \brief Get the payoff domain boundaries
	///
	///@return a tinymat N by 2 which defines the domain boundaries
	virtual boundary_type boundaries() const {QM_FAIL("Not implemented");} 
	
	virtual payofftype Type() const = 0;
	
	virtual payoffname id() const {QM_FAIL("not implemented");}
	
	template<class L>
	L boundarylist()  const  {
		L t;
		boundary_type bo = this->boundaries();
		for(unsigned i=0;i<N;i++)  {
			L li;
			li.append(bo[i].lower());
			li.append(bo[i].upper());
			t.append(li);
		}
		return t;
	}
};





/** \brief A composite Payoff class template
 * \ingroup finins
 * 
 * A composite payoff can be specified by differents payoffs in each dimension
 * and a unary function which combine them all
 * 
 * @param N payoff input dimension
 * @oaram U unary function \f$R \rightarrow R\f$.
 */
/*
template<unsigned N, payofftype P, class U>
class composite_payoff: public Payoff<N,P>  {
public:
	typedef U										  	funtion_type;
	typedef PayoffBase<1u>					  		  	single_payoff_type;
	typedef QM_SMART_PTR(single_payoff_type)  		  	SINGLE_PAYOFF_TYPE;
	typedef qmlib::math::tinyvec<SINGLE_PAYOFF_TYPE,N>  container_type;
	typedef typename PayoffBase<N>::input_type		  	input_type;
	typedef typename PayoffBase<NbarrierPayoff>::boundary_type		boundary_type;
	
	composite_payoff(payoffname id = UNKNOWN_PAYOFF_):Payoff<N,P>(id){}
	
	qm_real value(const input_type& x) const {
		qm_real v = m_payoffs[0]->value(x[0]);
		for(int i=1;i<N;i++)  {
			v = m_fun(v,m_payoffs[i]->value(x[i]));
		}
		return v;
	}
	
	//boundary_type boundaries() const {
	//	boundary_type b; 
	//	for(unsigned i=0;i<N;i++)  {
	//		b[i] = m_payoffs[i]->boundaries();
	//	}
	//	return b;
	//}
	
protected:
	container_type m_payoffs;
	funtion_type   m_fun;
};
*/


QM_NAMESPACE_END


#endif	//	__PAYOFF_QM_HPP__


