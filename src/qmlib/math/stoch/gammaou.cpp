
#include <qmlib/math/stoch/gammaOU.hpp>


QM_NAMESPACE2(math)



ngou::ngou(POISSON po, PARAMETER kappa, PARAMETER v0):m_driver(po) {
	p_v0    = v0.get();
	p_kappa = kappa.get();
	this->add(kappa);
	this->add(v0);
}


gammaOU::gammaOU(PARAMETER kappa, PARAMETER lambda, PARAMETER beta, PARAMETER v0):
	ngou(POISSON(new exppoisson(lambda,beta)),kappa,v0)  {
	p_lambda = lambda.get();
	p_beta   = beta.get();
	this->add(lambda);
	this->add(beta);
}


void ngou::simula(montecarlo* monte, unsigned numpaths, unsigned& stdim) {
	this->precalc();
	typedef jumping_path::jump_container jump_container;
	m_driver->simula(monte,numpaths,stdim);
	//m_paths = m_driver->get_paths().copy();
	/*
	multipath pa = m_paths[0];
	unsigned   P = m_paths.numpaths();
	qm_real  v00 = m_factors[0]->get_value();
	qm_real    k = m_params[0]->get_value();
	jumping_path*  pap;
	jump_container jc;
	
	for(multipath::iterator it = pa.begin();it!=pa.end();++it)  {
		pap = static_cast<jumping_path*>(it->get());
		jc  = pap->jumpcontainer();
		v0  = v00;
		t1  = 0;
		for(jump_container::iterator jp=jc.begin();ip!=jc.end();++jp)  {
			t0 = t1;
			t1 = jp->key();
			v1 = v0*std::exp(-k*(t1-t0)) 
		}
			
		J   = pap->
	}
	*/
}


QM_NAMESPACE_END2
