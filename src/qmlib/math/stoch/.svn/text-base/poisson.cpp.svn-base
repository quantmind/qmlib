
#include <qmlib/math/stoch/poisson.hpp>


QM_NAMESPACE2(math)


poisson_base::poisson_base(PARAMETER lambda)  {
	p_lambda = lambda.get();
	this->add(lambda);
}

poisson::poisson(PARAMETER lambda, PARAMETER jump):poisson_base(lambda) {
	p_jump = jump.get();
	this->add(jump);
}

exppoisson::exppoisson(PARAMETER lambda, PARAMETER decay):poisson_base(lambda) {
	p_decay = decay.get();
	this->add(decay);
}


void poisson_base::simula(montecarlo* monte, unsigned numpaths, unsigned& startdim) {
	this->precalc();
	QM_REQUIRE(monte,"Montecarlo method is null");
	m_paths.set(monte->grid(),numpaths);
	PATH pa = m_paths.add_jumping();
	jumping_path::jump_paths ph = pa->jumpcontainer();

	RNDGEN  gen = monte->get_generator();
	qm_real T   = monte->grid()->horizon();
	qm_real lam = p_lambda->get_integrated(0,T);
	qm_real tl  = T/lam;
	unsigned dimens;
	unsigned maxdim = 0;
	
	for(unsigned p=0;p<numpaths;p++)  {
		dimens = startdim;
		path::jump_container pap(ph[p]);
		
		qm_real jv = 0;
		pap.addkeyval(0.0,jv);
		dimens++;
		qm_real ar = gen->nextArrival(p,dimens);
		
		while(ar<lam)  {
			dimens++;
			jv += this->sample_jump(gen,p+1,dimens);
			pap.addkeyval(ar*tl,jv);
			ar += gen->nextArrival(p+1,dimens);
		}
		maxdim = std::max(maxdim,dimens-startdim);
	}
	//pap->togrid();
	//ret.set_dim(maxdim);
	//startdim = ret.enddim();
}



QM_NAMESPACE_END2