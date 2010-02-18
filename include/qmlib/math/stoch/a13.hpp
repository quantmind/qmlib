

#ifndef __A13_PROCESS_QM_HPP__
#define __A13_PROCESS_QM_HPP__



#include <qmlib/math/stoch/diffusion.hpp>
#include <qmlib/math/stoch/impl/a13integra.hh>




QM_NAMESPACE2(math)


/** \brief Gaussian OU process
 * \ingroup stoch
 * 
 * \f$ d x_t = \kappa(\theta - x_t) dt + \sigma d w_t\f$
 */
class a13: public CharacteristicDiffusion<3u> {
public:
	typedef CharacteristicDiffusion<3u> basestoch;
	
	static CDIFFP3 make(qm_real kr,      qm_real km,  qm_real kv,
		  	 			qm_real th,      qm_real vol,
		  	 			qm_real alpha_r, qm_real alpha_m,
		  	 			qm_real eta_r,   qm_real eta_m, qm_real eta_v,
		  	 			qm_real srm,     qm_real smr,
		  	 			qm_real srv, 	 qm_real smv);
	
	void characteristic_exponent(const cvec& u, CEXPONENT& expo) const;
	void rcumulant(const rvec& u, REXPONENT& expo) const {m_it.vals(u,expo.get(),get_dtchar());}
    void ccumulant(const cvec& u, CEXPONENT& expo) const {m_it.vals(u,expo.get(),get_dtchar());}
	
	qm_string code() const {return "Maximal Affine 3 factor (1 stoch vol)";}
	void createPaths() const;
	void updateFactors();
	
	const rmat&	ThetaMat() const;
	rvec S2value(const rvec& fact) const;
	
	DIST1 marginal(unsigned i, qm_real t1, qm_real t2) const;
	
	bool    ispositive_characteristic(unsigned i) const {return i==2;}
protected:
	a13integrator m_it;
	a13(const parameters& pa,const parameters& fa,const parameters& ri):basestoch(pa,fa,ri){m_it.set(this); precalc();}
	void precalc() {m_it.set(this->params()); updateFactors();}
};






inline CDIFFP3 a13::make(qm_real kr,      qm_real km,  qm_real kv,
					  	 qm_real th,   	  qm_real vol,
					  	 qm_real alpha_r, qm_real alpha_m,
					  	 qm_real eta_r,   qm_real eta_m, qm_real eta_v,
						 qm_real srm,     qm_real smr,
						 qm_real srv, 	  qm_real smv)  {
	parameters pa;
	pa.push_back(parameter::make("kappar","Mean-rev speed of short rate",				kr,-smallreal()));
	pa.push_back(parameter::make("kappam","Mean-rev speed of long rate",				km,-smallreal()));
	pa.push_back(parameter::make("kappav","Mean-rev speed of stochastic variance",		kv,-smallreal()));
	pa.push_back(parameter::make("theta","Central tendency of long rate",				th,0));
	pa.push_back(parameter::make("sigma","Central tendency of stochastic volatility",	vol,0));
	pa.push_back(parameter::make("alphar","Vol of short-rate alpha",					alpha_r,-smallreal()));
	pa.push_back(parameter::make("alpham","Vol of long-rate alpha",						alpha_m,-smallreal()));
	pa.push_back(parameter::make("etar","Vol of short-rate eta_r",						eta_r,-smallreal()));
	pa.push_back(parameter::make("etam","Vol of short-rate eta_m",						eta_m,-smallreal()));
	pa.push_back(parameter::make("etav","Vol of vol eta_v",								eta_v,-smallreal()));
	pa.push_back(parameter::make("srm","Covariance short rate-long rate",				srm));
	pa.push_back(parameter::make("smr","Covariance long rate-short rate",				smr));
	pa.push_back(parameter::make("srv","Covariance short rate-volatility",				srv));
	pa.push_back(parameter::make("smv","Covariance long rate-volatility",				smv));
	parameters fa;
	fa.push_back(parameter::make("r","Short rate",th,0));
	fa.push_back(parameter::make("m","Long rate",th,0));
	fa.push_back(parameter::make("v","Stochastic variance",vol*vol,0));
	parameters ris;
	ris.push_back(parameter::make("lambdar","Market price of risk of short rate",0));
	ris.push_back(parameter::make("lambdam","Market price of risk of long rate",0));
	ris.push_back(parameter::make("lambdav","Market price of risk of variance",0));
	return CDIFFP3(new a13(pa,fa,ris));
}


inline const a13::rmat& a13::ThetaMat() const  {
	m_mat(0,0) = 1;
	m_mat(0,1) = m_it.srm;
	m_mat(0,2) = m_it.srv;
	m_mat(1,0) = m_it.smr;
	m_mat(1,1) = 1;
	m_mat(1,2) = m_it.smv;
	m_mat(2,0) = 0;
	m_mat(2,1) = 0;
	m_mat(2,2) = 1;
	return m_mat;
}

inline a13::rvec a13::S2value(const a13::rvec& fact) const {
	rvec s;
	s[0] = m_it.alphar2 + m_it.etar2*fact[2];
	s[1] = m_it.alpham2 + m_it.etam2*fact[2];
	s[2] = 				  m_it.etav2*fact[2];
	return s;
}

inline void a13::updateFactors() {
	m_c_factors[0] = m_factors[0]->get_value();
	m_c_factors[1] = m_factors[1]->get_value();
	m_c_factors[2] = m_factors[2]->get_value();
}


inline void a13::createPaths() const  {
	timegrid*  tg = m_paths.grid().get();
	multipath prs = m_paths[0];
	multipath pms = m_paths[1];
	multipath pvs = m_paths[2];
	qm_real   rr0 = m_factors[0]->get_value();
	qm_real   mm0 = m_factors[1]->get_value();
	qm_real   vv0 = m_factors[2]->get_value();
	unsigned    P = m_paths.numpaths();
	unsigned    T = tg->length();
	qm_real dt,r0,m0,v0,r1,m1,v1,sdt,nr,nm,nv;
	qm_real krt,krt2,dtr,kmt,kmt2,dtm,ar,am,av,mave,vave;
	qm_real kr2   = 2.*m_it.kr;
	qm_real km2   = 2.*m_it.km;
	unsigned p,t;
	path *pr,*pm,*pv;
	
	qm_real srm = m_it.srm;
	qm_real smr = m_it.smr;
	qm_real srv = m_it.srv;
	qm_real smv = m_it.smv;
	qm_real th  = m_it.theta;
	
	for(p=0;p<P;p++)  {
		pr = prs[p].get();
		pm = pms[p].get();
		pv = pvs[p].get();
		r0 = rr0;
		m0 = mm0;
		v0 = vv0;
		pr->set(0,r0);
		pm->set(0,m0);
		pv->set(0,v0);
		for(t=1;t<T;t++)  {
			dt   = tg->dt(t,1);
			sdt  = std::sqrt(dt);
			krt  = std::exp(-m_it.kr*dt);
			krt2 = krt*krt;
			dtr  = std::sqrt((1. - krt2)/kr2);
			kmt  = std::exp(-m_it.km*dt);
			kmt2 = kmt*kmt;
			dtm  = std::sqrt((1. - kmt2)/km2);
			nr   = pr->get(t);
			nm   = pm->get(t);
			nv   = pv->get(t);
			v1   = square_root_advance(m_it.kv,m_it.sig2,m_it.etav,v0,dt,sdt,nv);
			vave = 0.5*(v1+v0);
			ar   = std::sqrt(m_it.alphar2 + m_it.etar2*vave);
			am   = std::sqrt(m_it.alpham2 + m_it.etam2*vave);
			av   = std::sqrt(m_it.etav2*vave);
			m1   = th   + (m0-th)*kmt   + (smr*ar*nr + am*nm + smv*av*nv)*dtm;
			mave = 0.5*(m0+m1);
			r1   = mave + (r0-mave)*krt + (ar*nr + srm*am*nm + srv*av*nv)*dtr;
			pr->set(t,r1);
			pm->set(t,m1);
			pv->set(t,v1);
			r0   = r1;
			m0   = m1;
			v0   = v1;
			//vr   = std::sqrt((v0*(1.-krt2) + (v1-v0)*(1.-(kr2*dt+1.)*krt2)/(kr2*dt))/kr2);
			//vm   = std::sqrt((v0*(1.-kmt2) + (v1-v0)*(1.-(km2*dt+1.)*kmt2)/(km2*dt))/km2);
		}
	}
}


inline DIST1 a13::marginal(unsigned i, qm_real t1, qm_real t2) const  {
	QM_REQUIRE(t1>=0. && t2>t1,"Time must be positive");
	QM_REQUIRE(i==2,"A13 model has analytical marginal anly for factor 2");
	return squareroot_marginal(t2-t1,m_it.kv,m_it.sig2,m_it.etav,m_c_factors[2]);
}


QM_NAMESPACE_END2


#endif // __A13_PROCESS_QM_HPP__
