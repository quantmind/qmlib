

#ifndef   __AFFINE_TERM_STRUCTURE_MODELS_QM_HPP__
#define   __AFFINE_TERM_STRUCTURE_MODELS_QM_HPP__



#include <qmlib/finance/tsmodel/tsmodel.hpp>



/// \file
/// \brief Affine term structure models
/// \ingroup termstructure



QM_NAMESPACE2(math)


class affinefactory;

/// \brief Affine term structure models
/// \ingroup termstructure
///
/// Base class for Affine term structure models. An affine term structure models admit analytical
/// solutions (up to a system of ODEs) for two different transforms.
/// The short rate is an affine function of the state variable vector $\f{\bf x}_t\f$:
///
/// \f$r_t = d_0 + {\bf d_1 \cdot {\bf x}_t + \psi_t\f$
/// \f$\psi_t\f$ is a correttive term which can be used to exactly fit the initial term structure.
template<unsigned N>
class atsmodel : public tsmodel  {
	friend class affinefactory;
public:
	const static unsigned Dimension = N;
	typedef characteristic<N>						chartype;
	typedef typename chartype::rvec					rvec;
	typedef typename chartype::cvec					cvec;
	typedef typename chartype::rexponent			rexponent;
	typedef typename chartype::cexponent			cexponent;
	typedef typename chartype::REXPONENT			REXPONENT;
	typedef typename chartype::CEXPONENT			CEXPONENT;
	typedef std::pair<REXPONENT,REXPONENT>			REXPONENTs;
	
	qm_real	modeldf(qm_real t, qm_real T) const;
	
	qm_real modelfwdt(qm_real t, qm_real T1, qm_real T2) const;
	
	REXPONENT fwdexp(qm_real t, qm_real Te, qm_real Tm, qm_real disc) const;
	
	qm_real future(qm_real t, qm_real T1, qm_real T2, qm_real tau) const;
	
	SENSITIVITY floorlet(qm_real T1, qm_real T2, qm_real tau) const;
	
	tinymat<qm_real,2,2>
	fwdratecovar(qm_real t, qm_real T1, qm_real tau1, qm_real T2, qm_real tau2) const;
protected:
	rvec					m_r0;
	mutable REXPONENT		m_re;
	mutable rvec			m_rr0, m_tmp;
	chartype*				m_model;
	mutable rexponent*		p_re;
	
	atsmodel(STOCHASTIC mo, const qdate& dte);
	
	REXPONENTs fwdexps(qm_real t, qm_real Te, qm_real Tm, qm_real disc) const;
};


//template<>
template<unsigned N>
struct characteristic_process_traits<atsmodel<N> > {
	typedef QM_SMART_PTR(atsmodel<N>)		AFFINETYPE;
	typedef QM_SMART_PTR(characteristic<N>)	CHARTYPE;
	static CHARTYPE getstoch(AFFINETYPE typ) {
		return smart_cast<characteristic<N>,istochastic>(typ->stoch());
	}
};







template<unsigned N>
inline atsmodel<N>::atsmodel(STOCHASTIC mo, const qdate& dte):
		tsmodel(mo,dte),m_r0(0),m_re(new rexponent(0,0,1)) {
	QM_SMART_PTR(chartype) c = smart_cast<chartype,istochastic>(this->stoch());
	QM_REQUIRE(c,"Stochastic model not an affine one");
	p_re	= m_re.get();
	m_model = c.get();
}

template<unsigned N>
inline qm_real
atsmodel<N>::modeldf(qm_real t, qm_real T) const  {
	p_re->set_disc(1.0);
	p_re->t0 = t;
	p_re->t1 = T;
	m_model->rcumulant(m_r0,m_re);
	return std::exp(p_re->value(m_model->charFactors()));
}

template<unsigned N>
inline qm_real
atsmodel<N>::modelfwdt(qm_real t, qm_real T1, qm_real T2) const  {
	REXPONENT re = this->fwdexp(t,T1,T2,1.0);
	return std::exp(re->value(m_model->charFactors()));
}

template<unsigned N>
inline typename atsmodel<N>::REXPONENTs
atsmodel<N>::fwdexps(qm_real t, qm_real Te, qm_real Tm, qm_real disc) const {
	REXPONENT re(new rexponent(t,Te,disc));
	rexponent* rep = re.get();
	m_model->rcumulant(m_r0,re);
	p_re->set_disc(disc);
	p_re->t0 = Te;
	p_re->t1 = Tm;
	m_model->rcumulant(rep->b,m_re);
	return REXPONENTs(re,m_re);
}

template<unsigned N>
inline typename atsmodel<N>::REXPONENT
atsmodel<N>::fwdexp(qm_real t, qm_real Te, qm_real Tm, qm_real disc) const {
	REXPONENTs res  = fwdexps(t,Te,Tm,disc);
	rexponent* rep  = res.first.get();
	rexponent* rep2 = res.second.get();
	rep->a  =-rep2->a;
	rep->b -= rep2->b;
	return res.first;
}


template<unsigned N>
inline tinymat<qm_real,2,2>
atsmodel<N>::fwdratecovar(qm_real t, qm_real T1, qm_real tau1, qm_real T2, qm_real tau2) const {
	tinymat<qm_real,2,2> cov;
	REXPONENT  re1 = this->fwdexp(t,T1,T1+tau1,1.0);
	REXPONENT  re2 = this->fwdexp(t,T2,T2+tau2,1.0);
	qm_real F1  = (std::exp(re1->value(m_model->charFactors())) - 1.0)/tau1;
	qm_real F2  = (std::exp(re2->value(m_model->charFactors())) - 1.0)/tau2;
	qm_real cv  = m_model->affine_covariance(re1->b,re2->b,m_model->charFactors());
	qm_real v1  = m_model->affine_covariance(re1->b,re1->b,m_model->charFactors());
	qm_real v2  = m_model->affine_covariance(re2->b,re2->b,m_model->charFactors());
	qm_real f1  = (tau1*F1 + 1.)/tau1;
	qm_real f2  = (tau2*F2 + 1.)/tau2;
	cov(0,0) = f1*f1*v1;
	cov(1,1) = f2*f2*v2;
	cov(0,1) = f1*f2*cv;
	cov(1,0) = cov(0,1);
	return cov;
}

template<unsigned N>
inline qm_real atsmodel<N>::future(qm_real t, qm_real T1, qm_real T2, qm_real tau) const  {
	REXPONENT  re  = this->fwdexp(t,T1,T2,1.0);
	REXPONENT  re2(new rexponent(t,T1,0));
	m_model->rcumulant(re->b,re2);
	return (std::exp(re->a+re2->value(m_model->charFactors())) - 1.)/tau;
}


class affinefactory  {
public:
	static TSMODEL make(STOCHASTIC mo, const qdate& dte)  {
		QM_REQUIRE(mo,"Stochastic model not available");
		unsigned n = mo->count();
		if(n == 1)
			return TSMODEL(new atsmodel<1u>(mo,dte));
		else if(n==2)
			return TSMODEL(new atsmodel<2u>(mo,dte));
		else if(n==3)
			return TSMODEL(new atsmodel<3u>(mo,dte));
		else
			QM_FAIL("Increase dimension in affinefactory");
	}
};


QM_NAMESPACE_END2


#endif  //  __AFFINE_TERM_STRUCTURE_MODELS_QM_HPP__


