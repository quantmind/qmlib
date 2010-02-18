

#ifndef   __FWDRATE_VOLATILITY_FUNCTION_QM_HPP__
#define   __FWDRATE_VOLATILITY_FUNCTION_QM_HPP__



#include <qmlib/corelib/info/timeparam.hpp>
#include <qmlib/math/tools/integra.hpp>



QM_NAMESPACE2(math)

class fwdratevol;
typedef QM_SMART_PTR(fwdratevol)	FWDRATEVOL;


class fwdratevol: public time_parameter  {
public:
	typedef simpson1d			integrator;
	typedef integrator::funtype	funtype;
	
	fwdratevol():m_Ti(1),m_Tj(1),m_integrator(0.1){m_fun = boost::ref(*this);}
	qm_real    lower_bound() const  {return 0;}
	qm_real T()  const {return m_Ti;}
	qm_real Ti() const {return m_Ti;}
	qm_real Tj() const {return m_Tj;}
	void set_T(qm_real t)   const {m_Ti = t; m_Tj = t;}
	void set_Ti(qm_real ti) const {m_Ti = ti;}
	void set_Tj(qm_real tj) const {m_Tj = tj;}
	
	qm_string name() const {return this->code() + " function for forward rates";}
	
	qm_real operator () (qm_real t) const {return get_valuet(t);}
	
	virtual qm_real correlationfunction(qm_real t, qm_real ti, qm_real tj) const {return 1;} 
	
	qm_real get_integrated(qm_real t0, qm_real t1) const;
	qm_real covariance(qm_real t0, qm_real t1) const {return this->get_integrated(t0,t1);}
	qm_real correlation(qm_real t0, qm_real t1) const;
	qm_real get_valuet(qm_real t) const;
	
	qm_real volatility(qm_real t) const {return this->volatilityT(t,m_Ti);}
protected:
	virtual qm_real volatilityT(qm_real t, qm_real T) const {return 0;}
	mutable qm_real		m_Ti,m_Tj;
	integrator 			m_integrator;
	funtype				m_fun;
}; 




//_________________________________________________________________________


inline qm_real fwdratevol::get_valuet(qm_real t) const {
	qm_real v1 = this->volatilityT(t,m_Ti);
	if(m_Ti == m_Tj) return v1*v1;
	else  {
		qm_real v2 = this->volatilityT(t,m_Tj);
		return v1*v2*this->correlationfunction(t,m_Ti,m_Tj);
	}
}

inline qm_real fwdratevol::get_integrated(qm_real t0, qm_real t1) const  {
	return m_integrator.integra(m_fun,t0,t1);
}

inline qm_real fwdratevol::correlation(qm_real t0, qm_real t1) const  {
	if(t1 <= t0) return 1;
	qm_real cov = this->covariance(t0,t1);
	qm_real ti = m_Ti;
	qm_real tj = m_Tj;
	set_T(ti);
	qm_real vi = this->covariance(t0,t1);
	set_T(tj);
	qm_real vj = this->covariance(t0,t1);
	m_Ti = ti;
	m_Tj = tj;
	return cov/std::sqrt(vi*vj);
}

QM_NAMESPACE_END2


#endif	//	__FWDRATE_VOLATILITY_FUNCTION_QM_HPP__


