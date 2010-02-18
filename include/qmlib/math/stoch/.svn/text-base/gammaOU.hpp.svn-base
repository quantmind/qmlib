

#ifndef __GAMMAOU_PROCESS_QM_HPP__
#define __GAMMAOU_PROCESS_QM_HPP__



#include <qmlib/math/stoch/poisson.hpp>


/* \file
 * \ingroup stoch
 * 
 * \brief Poisson and Poisson Compound processes
 */


QM_NAMESPACE2(math)

class ngou;
typedef QM_SMART_PTR(ngou)	NGOU;


/** \brief Non-Gaussian OU process
 * \ingroup stoch
 */
class ngou: public JumpChar<1u>  {
public:
	bool  ispositive()		   const {return true;}
	void  simula(montecarlo* monte, unsigned numpaths, unsigned& stdim);

	POISSON driver() const {return m_driver;}
	void updateFactors() {m_c_factors[0] = p_v0->get_value();}
protected:
	POISSON	      m_driver;
	iparameter*	  p_v0;
	poisson_base* p_driver;
	iparameter*	  p_kappa;

	ngou(POISSON po, PARAMETER kappa, PARAMETER v0);
};

/** \brief Gamma OU process
 * \ingroup stoch
 */
class gammaOU: public ngou  {
public:
	gammaOU(PARAMETER kappa, PARAMETER lambda, PARAMETER beta, PARAMETER v0);
    bool analytical_exponent() const {return true;}
    void rcumulant(const rvec& u, REXPONENT& expo) const {cumulant(u[0],expo.get());}
    void ccumulant(const cvec& u, CEXPONENT& expo) const {cumulant(u[0],expo.get());}
    static NGOU make(qm_real kappa, qm_real lambjumpcontainerda, qm_real beta, qm_real v0);
    qm_string code() const {return "Gamma OU";}
protected:
	iparameter* p_lambda;
	iparameter* p_beta;
	template<typename T>
	void cumulant(const T& u, affine_exponent<T,1u>* expo) const;
};

//______________________________________________________________________________
//		IMPLEMENTATION


template<typename T>
inline void gammaOU::cumulant(const T& c, affine_exponent<T,1u>* expo) const {
	qm_real tau    = expo->t1 - expo->t0;
   	qm_real la     = p_lambda->get_value();
   	qm_real k      = p_kappa->get_value();
   	qm_real a      = p_beta->get_value();
   	T 		bt     = c*std::exp(-k*tau);
   	expo->a =-la*std::log((a - c)/(a - bt));
   	expo->b[0] = bt;
}


    
QM_NAMESPACE_END2


#endif // __GAMMAOU_PROCESS_QM_HPP__
