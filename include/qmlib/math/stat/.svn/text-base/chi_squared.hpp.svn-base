

#ifndef   __CHI_SQUARED_DISTRIBUTION_QM_HPP__
#define   __CHI_SQUARED_DISTRIBUTION_QM_HPP__


#include <qmlib/math/stat/distribution_base.hpp>

/**\file
 * \brief Chi-square distributions
 * \ingroup distributions
 */


QM_NAMESPACE2(math)

class chi2dist  {
public:
	chi2dist(){}
	chi2dist(qm_real k){init(k);}
	chi2dist(const chi2dist& rhs):m_k(rhs.m_k),m_he(rhs.m_he){}
	qm_real lndensity(qm_real x) const;
	qm_real density(qm_real x) const {return std::exp(this->lndensity(x));}
	void init(qm_real k);
protected:
	qm_real	m_k;
	qm_real m_he;
};

/** \brief the Chi-square distribution
 * \ingroup distributions
 * 
 */
class chi2_distribution: public distribution_root  {
public:
	static DIST1 make(qm_real k);
	qm_real lndensity(qm_real x) const {return m_chi2.lndensity(x);}
	qm_real density(qm_real x)   const {return m_chi2.density(x);}
	qm_real mean()     		     const {return kappa();}
	qm_real variance() 		     const {return 2*kappa();}
	qm_real skewness() 			 const {return std::sqrt(8*kappa());}
	qm_real excessKurtosis() 	 const {return 12./kappa();}
	qm_real kappa() const {return m_parameters[0]->get_value();}
	qm_string	code()		     const {return "Chi-square distribution";}
protected:
	chi2dist m_chi2;
	chi2_distribution(const parameters& pa):distribution_root(pa){precalc();}
	void precalc() {m_chi2.init(kappa());}
};


/** \brief the Noncentral chi-square distribution
 * \ingroup distributions
 * 
 */
class chi2nc_distribution: public distribution_root  {
public:
	typedef std::pair<qm_real,chi2dist>	 serie_elem;
	typedef std::vector<serie_elem>		 serie_type;
	static DIST1 make(qm_real k, qm_real lambda);
	
	qm_real density(qm_real x)   const;
	qm_real mean()     		     const {return kappa() + lambda();}
	qm_real variance() 		     const {return 2.*(kappa() + 2.*lambda());}
	qm_real skewness() 			 const;
	qm_real excessKurtosis() 	 const;
		
	qm_string	code()		     const {return "Noncentral Chi-square distribution";}
	qm_real kappa()  const {return m_parameters[0]->get_value();}
	qm_real lambda() const {return m_parameters[1]->get_value();}
protected:
	serie_type m_chi2s;
	chi2nc_distribution(const parameters& pa):distribution_root(pa){precalc();}
	void precalc();
};

/** \brief the Shifted Noncentral chi-square distribution
 * \ingroup distributions
 * 
 * \f$ p(x) = c \chi^2(c x, \kappa, \lambda)\f$
 */
class chi2nc_shifted_distribution: public idistribution<1u>  {
public:
	static DIST1 make(qm_real k, qm_real lambda, qm_real c) {
		return DIST1(new chi2nc_shifted_distribution(k,lambda,c));
	}
	
	qm_real density(qm_real x)   const {return m_c*m_dist->density(m_c*x);}
	qm_real mean()     		     const {return m_dist->mean()/m_c;}
	qm_real variance() 		     const {return m_dist->variance()/(m_c*m_c);}
	qm_real skewness() 			 const {return m_dist->skewness();}
	qm_real excessKurtosis() 	 const {return m_dist->excessKurtosis();}
	
	qm_string	code()		     const {return "Shifted Noncentral Chi-square distribution";}
protected:
	qm_real				m_c;
	DIST1				m_dist;
	chi2nc_shifted_distribution(qm_real k, qm_real lambda, qm_real c);
};




inline void chi2dist::init(qm_real k) {
	m_k = k;
	qm_real lg = boost::math::lgamma(0.5*m_k);
	m_he = -0.5*m_k*std::log(2.) - lg;
}

inline qm_real chi2dist::lndensity(qm_real x) const  {
	return m_he + (0.5*m_k - 1.0)*std::log(x) - 0.5*x;
}




inline DIST1 chi2_distribution::make(qm_real k)  {
	parameters pa;
	pa.push_back(parameter::make("kappa","Degrees of freedom",k,0));
	return DIST1(new chi2_distribution(pa));
}
inline DIST1 chi2nc_distribution::make(qm_real k, qm_real lambda)  {
	parameters pa;
	pa.push_back(parameter::make("kappa","Degrees of freedom",k,0));
	pa.push_back(parameter::make("lambda","Non centrality parameter",lambda,0));
	return DIST1(new chi2nc_distribution(pa));
}

inline void chi2nc_distribution::precalc()  {
	qm_real tole =-33;
	m_chi2s.clear();
	qm_real la  = 0.5*lambda();
	qm_real  k  = kappa();
	qm_real lla = std::log(la);
	qm_real el  =-la;
	qm_real  i  = 0;
	qm_real ad;
	for(;;) {
		if(el > tole) m_chi2s.push_back(serie_elem(std::exp(el),chi2dist(k+2.*i)));
		i  += 1.;
		ad  = lla - std::log(i);
		el += ad;
		if(el < tole && ad < 0.) break;
	}
}

inline qm_real chi2nc_distribution::density(qm_real x) const {
	if(x <= 0) return 0;
	qm_real d = 0;
	for(serie_type::const_iterator it=m_chi2s.begin();it!=m_chi2s.end();++it)  {
		d += it->first*it->second.density(x);
	}
	return d;
}

inline qm_real chi2nc_distribution::skewness() const  {
	qm_real k = kappa();
	qm_real l = lambda();
	qm_real s = 2.*(k+3.*l)/(k+2.*l);
	return s*std::sqrt(2./(k+2.*l));
}
inline qm_real chi2nc_distribution::excessKurtosis() const  {
	qm_real k = kappa();
	qm_real l = lambda();
	qm_real kl = 1./(k+2.*l);
	return 12*(k+4.*l)*kl*kl;	
}

inline chi2nc_shifted_distribution::chi2nc_shifted_distribution(qm_real k, qm_real lambda, qm_real c):m_c(c)  {
	m_dist = chi2nc_distribution::make(k,lambda);
}



QM_NAMESPACE_END2


#endif  //  __CHI_SQUARED_DISTRIBUTION_QM_HPP__


