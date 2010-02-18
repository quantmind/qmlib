
#include <qmlib/math/stoch/heston.hpp>


QM_NAMESPACE2(math)



void heston_exponent::createPaths() {
	this->precalc();
	timegrid* tg = m_paths.grid().get();
	qm_real ka  = p_kappa->get_value();
	qm_real th  = p_theta->get_value();
	qm_real eta = std::sqrt(p_eta2->get_value());
	qm_real ro  = p_rho->get_value();
	qm_real r1 = std::sqrt(1. - ro*ro);
	qm_real v1, x, ex, ev, dt, sdt, vm;
	unsigned t,p,i,dim = tg->length();

	path::holder X = m_paths[0]->pathholder();
	path::holder V = m_paths[1]->pathholder();
	qm_real v0 = p_v0->get_value();

	for(p=0; p<m_paths.numpaths(); ++p)  {
		X(0,p) = 0;
		V(0,p) = v0;
	}

	for(t=1;t<m_paths.timedim();i++)  {
		dt  = tg->dt(t,1);
		sdt = std::sqrt(dt);
		for(p=0; p<m_paths.numpaths(); ++p)  {
			ex  = X(t,p);
			ev  = V(t,p);
			v0  = V(t-1,p);
			v1  = square_root_advance(ka,th,eta,v0,dt,sdt,ev);
			vm  = std::sqrt(v1+v0);
			x  += vm*sdt*(r1*ex + ro*ev);
			X(t,p) = x;
			V(t,p) = v1;
		}
	}
}


QM_NAMESPACE_END2

