


#ifndef   __PAYOFF_BARRIER_ANALYTIC_QM_HPP__
#define   __PAYOFF_BARRIER_ANALYTIC_QM_HPP__



#include <boost/numeric/interval.hpp>
#include <qmlib/qmat/tiny.hpp>
#include <qmlib/finance/payoffs/barrier.hpp>


/** \file
 * \brief Analytic pricing of barrier options
 * \ingroup payoff
 */



QM_NAMESPACE2(finance)



/** \brief class template for analytic pricing of barrier options
 * \ingroup payoff
 */
template<bool U, barriertype T, class V>
class barrier_analytic {};






inline qm_real barrier_AB(qm_real S, qm_real X, qm_real H, qm_real T, qm_real sigma, qm_real r, qm_real b, qm_real psi)  {
	qm_real s2 = sigma*sigma;
	qm_real st = sigma*std::sqrt(T);
	qm_real mu = (b - 0.5*s2)/s2;
	qm_real x1 = std::log(S/H)/st + (1.0 + mu)*st;
	QM_USING_NAMESPACE2(math);
	normal_dist no;
	return psi*std::exp(-r*T) * (std::exp(b*T)*S*no.cumulative(psi*x1) - X*no.cumulative(psi*(x1 - st)));
}


inline qm_real barrier_CD(qm_real S, qm_real X, qm_real H, qm_real Ha, qm_real T, qm_real sigma, qm_real r, qm_real b, qm_real eta, qm_real psi)  {
	qm_real s2 	= sigma*sigma;
	qm_real st 	= sigma*std::sqrt(T);
	qm_real mu 	= (b - 0.5*s2)/s2;
	qm_real hs 	= H/S;
	qm_real hs2 = std::pow(hs,2*mu);
	qm_real y1 	= std::log(H*hs/Ha)/st + (1.0 + mu)*st;
	QM_USING_NAMESPACE2(math);
	normal_dist no;
	return psi*std::exp(-r*T)*hs2 * (std::exp(b*T)*S*hs*hs*no.cumulative(eta*y1) - X*no.cumulative(eta*(y1 - st)));
}

inline qm_real barrier_A(qm_real S, qm_real X, qm_real H, qm_real T, qm_real sigma, qm_real r, qm_real b, qm_real psi)  {
	return barrier_AB(S,X,X,T,sigma,r,b,psi);
}
inline qm_real barrier_B(qm_real S, qm_real X, qm_real H, qm_real T, qm_real sigma, qm_real r, qm_real b, qm_real psi)  {
	return barrier_AB(S,X,H,T,sigma,r,b,psi);
}
inline qm_real barrier_C(qm_real S, qm_real X, qm_real H, qm_real T, qm_real sigma, qm_real r, qm_real b, qm_real psi, qm_real eta)  {
	return barrier_CD(S,X,H,X,T,sigma,r,b,psi,eta);
}
inline qm_real barrier_D(qm_real S, qm_real X, qm_real H, qm_real T, qm_real sigma, qm_real r, qm_real b, qm_real psi, qm_real eta)  {
	return barrier_CD(S,X,H,H,T,sigma,r,b,psi,eta);
}
inline qm_real barrier_F(qm_real S, qm_real H, qm_real T, qm_real sigma, qm_real r, qm_real b, qm_real eta)  {
	qm_real s2 	= sigma*sigma;
	qm_real st 	= sigma*std::sqrt(T);
	qm_real mu 	= (b - 0.5*s2)/s2;
	qm_real la  = std::sqrt(mu*mu + 2.0*r/s2);
	qm_real hs 	= H/S;
	qm_real hs1 = std::pow(hs,mu);
	qm_real hs2 = std::pow(hs,la);
	qm_real z 	= std::log(hs)/st + la*st;
	QM_USING_NAMESPACE2(math);
	normal_dist no;
	return hs1 * (hs2*no.cumulative(eta*z) + no.cumulative(eta*(z - 2*la*st))/hs2);
}




template<true, KnockOut, _CALL_>
struct barrier_analytic {
	static qm_real value(qm_real S, qm_real K, qm_real H, qm_real R, qm_real ra, qm_real rb, qm_real T, qm_real vol)  {
		if(S >= H) return R;  // we are over the barrier. You get the rebate
		return 	barrier_A(S,K,H,T,vol,ra,rb,1.0) - 
				barrier_B(S,K,H,T,vol,ra,rb,1.0) +
				barrier_C(S,K,H,T,vol,ra,rb,1.0,-1.0) -
				barrier_D(S,K,H,T,vol,ra,rb,1.0,-1.0) +
				barrier_F(S,H,T,vol,ra,rb,-1.0)*R;
	}
};

template<false, KnockOut, _CALL_>
struct barrier_analytic {
	static qm_real value(qm_real S, qm_real K, qm_real H, qm_real R, qm_real ra, qm_real rb, qm_real T, qm_real vol)  {
		if(S < H) return R;  // we are over the barrier. You get the rebate
		return 	barrier_A(S,K,H,T,vol,ra,rb,1.0) - 
				barrier_C(S,K,H,T,vol,ra,rb,1.0,1.0) +
				barrier_F(S,H,T,vol,ra,m_rb,1.0)*R;
	}
};

template<true, KnockOut, _PUT_>
struct barrier_analytic {
	static qm_real value(qm_real S, qm_real K, qm_real H, qm_real R, qm_real ra, qm_real rb, qm_real T, qm_real vol)  {
		if(S >= H) return R;
		return 	barrier_A(S,K,H,T,vol,ra,rb,-1.0) - 
				barrier_C(S,K,H,T,vol,ra,rb,-1.0,-1.0) +
				barrier_F(S,H,T,vol,ra,rb,-1.0)*R;
	}
};

template<false, KnockOut, _PUT_>
struct barrier_analytic {
	static qm_real value(qm_real S, qm_real K, qm_real H, qm_real R, qm_real ra, qm_real rb, qm_real T, qm_real vol)  {
		if(m_S <= m_H) return m_R;  // we are over the barrier. You get the rebate
		return 	barrier_A(S,K,H,T,vol,ra,rb,-1.0) - 
				barrier_B(S,K,H,T,vol,ra,rb,-1.0) +
				barrier_C(S,K,H,T,vol,ra,rb,-1.0,1.0) -
				barrier_D(S,K,H,T,vol,ra,rb,-1.0,1.0) +
				barrier_F(S,H,T,vol,ra,rb,1.0)*R;
	}
};






QM_NAMESPACE_END2



#endif	//	__PAYOFF_BARRIER_ANALYTIC_QM_HPP__

