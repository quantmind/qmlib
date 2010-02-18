
#ifndef	__BGM_TENURE_CURVES_HPP__
#define	__BGM_TENURE_CURVES_HPP__

#include	<qmlib/math/options/fwdratevol.hpp>
#include	<qmlib/math/tools/timegrid.hpp>
#include	<qmlib/irates.hpp>


QM_NAMESPACE2(finance)


class tenure;
typedef QM_SMART_PTR(tenure)	TENURE;

typedef QM_FROM_NAMESPACE2(math)fwdratevol		fwdratevol;
typedef QM_FROM_NAMESPACE2(math)FWDRATEVOL		FWDRATEVOL;
typedef QM_FROM_NAMESPACE2(math)date_timegrid	date_timegrid;
typedef QM_FROM_NAMESPACE2(math)DTIMEGRID		DTIMEGRID;

class tenure;


class tenurecode  {
public:
	static qm_string A(unsigned alpha, unsigned M) {
		return "alpha="+object_to_string(alpha)+", M="+object_to_string(M);
	}
	static qm_string B(unsigned alpha, unsigned N, unsigned K) {
		return "alpha="+object_to_string(alpha)+", N="+object_to_string(N)+
			   ", K="+object_to_string(K);
	}
};

class tenure : public basedes {
public:
	typedef QM_FROM_NAMESPACE2(math)qmatrix<qm_real> 		  datatype;
	typedef QM_FROM_NAMESPACE2(math)diagonal 		 		  diagtype;
	typedef QM_FROM_NAMESPACE2(math)qmatrix<qm_real,diagtype> coeftype;
	//
	tenure(DISCOUNTCURVE yc, const period& horizon,
		   const period& cap, const period& swap,
		   ADJ adj, DC floatDC, DC fixedDC,
		   FWDRATEVOL fv);
	const qdate date() const {return m_yc->date();}
	qm_string tostring() const {return "Fra-swap yield curve tenure";}
	
	unsigned 	   capswapratio() const {return m_K;}
	DC		 	   daycount()     const {return m_tg->daycount();}
	DC		 	   swapdc()       const {return m_fixedDC;}
	DISCOUNTCURVE  yc()   		  const {return m_YC;}
	DTIMEGRID      grid()		  const {return m_TG;}
	FWDRATEVOL	   fwdv()		  const {return m_FV;}
	unsigned	   size()		  const {return m_tg->length() - 1;}
	datatype weights(unsigned a, unsigned N, bool full) const;
	datatype weightsK(unsigned a, unsigned N, unsigned K, bool full) const;
	coeftype coefs(unsigned a, unsigned N, bool full) const;
	coeftype coefsK(unsigned a, unsigned N, unsigned K, bool full) const;
protected:
	void create();
	idiscountcurve*	m_yc;
	date_timegrid*  m_tg;
	fwdratevol*		m_fv;
	period 		 	m_horizon,m_cap,m_swp;
	ADJ    		 	m_adj;
	DC     		 	m_fixedDC;
	unsigned     	m_K;
	
	qm_real  B(unsigned m)				const {return m_cache(m,0);}
	qm_real  Aab(unsigned a, unsigned b) const {return m_cache(a,0) - m_cache(b,0);}
	qm_real  tau(unsigned m) 			const {return m_cache(m,1);}
	qm_real  delta(unsigned m)			const;
	qm_real  fwd(unsigned m) 			const {return m_cache(m,2);}
	datatype PV01(unsigned a, unsigned b, unsigned K) const;
private:
	DISCOUNTCURVE   m_YC;
	DTIMEGRID		m_TG;
	FWDRATEVOL  	m_FV;
	datatype		m_cache;
};


QM_NAMESPACE_END2

#include <qmlib/finance/bgm/tenure_impl.hh>

#endif	//	__BGM_TENURE_CURVES_HPP__

