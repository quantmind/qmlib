
#include <qmlib/math/stoch/meanrev.hpp>


QM_NAMESPACE2(math)


gaussianOU::gaussianOU(PARAMETER kappa, PARAMETER theta, PARAMETER var, PARAMETER v0) {
	p_kappa = kappa.get();
	p_theta = theta.get();
	p_var   = var.get();
	p_v0    = v0.get();
	QM_REQUIRE(p_kappa && p_theta && p_var && p_v0,"Parameters not properly defined");
	this->add(kappa);
	this->add(theta);
	this->add(var);
	this->add(v0);
}

// Advance the square root process. Euler scheme
qm_real square_root_advance(qm_real ka, qm_real th, qm_real et,
								   qm_real v0, qm_real dt, qm_real sdt,
								   qm_real nv)  {
	qm_real u2 = v0;
	qm_real u  = std::sqrt(u2);
	qm_real b  = 0.5*et*nv*sdt;
	qm_real a  = 0.5*(ka*(th - u2) - 0.25*et*et)/u;
	qm_real un = u + a*dt + b;
	return un*un;
}

qm_real gaussianOU::advance(qm_real ka, qm_real th, qm_real eta, qm_real x0,
			     				   qm_real dt, qm_real sdt, qm_real nv) const {
	return x0*sdt + th*(1.0 - sdt) + eta*std::sqrt(0.5*(1.0 - sdt*sdt)/ka)*nv;
}

qm_real squareroot::advance(qm_real ka, qm_real th, qm_real eta, qm_real x0,
								   qm_real dt, qm_real sdt, qm_real nv) const {
	return square_root_advance(ka,th,eta,x0,dt,sdt,nv);
}


void gaussianOU::createPaths() {
	timegrid* tg = m_paths.grid().get();
	path::holder pas = m_paths[0]->pathholder();

	qm_real dt,x0,sdt;
	qm_real v0  = m_c_factors[0];
	double ka    = p_kappa->get_value();
	double th    = p_theta->get_value();
	double eta   = std::sqrt(p_var->get_value());
	unsigned t,p;
	unsigned P = m_paths.numpaths();

	for(p=0;p<P;++p)  pas(0,p) = v0;

	// Loop over time
	for(t=1;t<pas.rows();++t)  {
		dt    = tg->dt(t,1);
		sdt   = this->sdt(ka,dt);
		//
		// Loop over paths
		for(p=0; p<P; ++p)  {
			x0  = pas(t-1,p);
			pas(t,p)  = this->advance(ka,th,eta,x0,dt,sdt,pas(t,p));
		}
	}
}

QM_NAMESPACE_END2
