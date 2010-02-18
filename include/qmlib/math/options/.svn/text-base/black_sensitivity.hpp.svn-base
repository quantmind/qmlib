


#ifndef   __ANALYTIC_OPTION_RESULTS_QM_HPP__
#define   __ANALYTIC_OPTION_RESULTS_QM_HPP__


#include <qmlib/sensitivity.hpp>



/**\file
 * \brief Results classes for analytic option pricing calculation
 */ 



QM_NAMESPACE2(math)


class black_analytics;
typedef QM_SMART_PTR(black_analytics)  		BLACK_ANALYTICS;



/** \brief class for Black-Scholes option analytics
 * append
 * We use a dummy factor in the implied volatility.
 * The implied volatility is not e factor in reality but e parameter (it does
 * not have a dynamic).
*/
class black_analytics : public sensitivity  {
public:
	black_analytics(const qdate& dte = qdate::today(), const qm_string& code = "Black-Scholes option sensitivities"):sensitivity(dte,code,2,2){}
	black_analytics(const black_analytics& rhs):sensitivity(rhs){}
	
	qm_real delta()  const {return m_deltas[0];}
	qm_real vega()   const {return m_deltas[1];}
	qm_real gamma()  const {return m_gammas(0,0);}
	qm_real volga()  const {return m_gammas(0,1);}
	qm_real vanna()  const {return m_gammas(1,1);}
	void set_delta(qm_real v)   {m_deltas[0]   = v;}
	void set_vega(qm_real v)    {m_deltas[1]   = v;}
	void set_gamma(qm_real v)   {m_gammas(0,0) = v;}
	void set_volga(qm_real v)   {m_gammas(0,1) = v;}
	void set_vanna(qm_real v)   {m_gammas(1,1) = v;}

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & boost::serialization::base_object<sensitivity>(*this);
	}
	/// \brief Return a description of the value at i
	/// Safe
	//DESCRIPTION	get_descr(unsigned i) const {return desBA[i];}
};



QM_NAMESPACE_END2




#endif  //  __ANALYTIC_OPTION_RESULTS_QM_HPP__

