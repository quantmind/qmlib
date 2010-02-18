
#include <qmlib/math/monte/all.hpp>


QM_NAMESPACE2(math)


void Paths::set(TIMEGRID tg, unsigned numpaths)  {
	m_tg = tg;
	m_numpaths = numpaths;
	QM_REQUIRE(m_tg,"Grid not available");
	this->vector()->clear();
}

PATH Paths::add_diffusion() const  {
	PATH d(new diffusion_path(this->grid(), this->numpaths()));
	p_data->push_back(d);
	return d;
}

PATH Paths::add_jumping() const {
	PATH d(new jumping_path(this->grid(), this->numpaths()));
	p_data->push_back(d);
	return d;
}

void jumping_path::togrid()  {
	for(unsigned p=0;p<this->numpaths();p++)  {
		path::jump_container jp(m_jumpings[p]);
		m_paths(0,p) = jp[0].value();
		index_pair id;
		for(unsigned i=1;i<this->timedim();i++)  {
			id = jp.niceindex(m_tg->time(i));
			m_paths(i,p) = jp[id.first].value();
		}
	}
}


montecarlo::montecarlo(RNDGEN gen, STOCHASTIC p, bool bridge):m_process(p),m_gen(gen),m_brownian(bridge){
	if(!m_gen) m_gen = RNDGEN(new default_rndgen);
}

qm_string montecarlo::tostring() const {
	if(m_process)
		return "Montecarlo method for " + m_process->tostring();
	else
		return "Montecarlo";
}



void montecarlo::simula(unsigned numpaths) {
	QM_REQUIRE(m_process,"Process not available");
	QM_REQUIRE(m_tg,"timegrid not available");
	unsigned stdim = this->setup(numpaths, 0);
	m_process->simula(this,numpaths,stdim);
}

unsigned montecarlo::setup(unsigned numpaths, unsigned startdim) const {
	QM_REQUIRE(numpaths>0,"Number of paths must be positive");
	unsigned dim    = this->grid()->length();
	QM_REQUIRE(dim>1,"time grid with less than two point");
	return startdim;
}


void montecarlo::diffusion(PATH pa, unsigned& startdim)  {
	QM_REQUIRE(pa,"Path not defined");
	QM_REQUIRE(m_gen,"Generator not defined");
	path::holder ph  = pa->pathholder();
	startdim         = std::max(1u,startdim);
	unsigned dim     = m_tg->length();
	unsigned tdim    = dim-1;
	unsigned d,p,dimens;
	rndgen* gen = m_gen.get();
	
	// Build using the brownian bridge
	if(m_brownian)  {
		BrownianBridge* br = m_tg->bridge().get();
		QM_REQUIRE(br->size() == tdim,"Brownian bridge with wrong dimension");
		BrownianBridge::pathtype bpath(tdim);
		
		for(p=0; p<ph.cols(); p++)  {
			dimens = startdim;
			
			// Get the normal variates
			for(d=0; d<tdim; ++d)  {
				dimens++;
				bpath[d] = gen->nextNormalVariate(p,dimens);
			}
			
			// Build an integrated path
			br->buildPath(ph,p,bpath);
			
			// Get changes in normal variates
			for(d=tdim;d>=2;--d)
				ph(d,p) = ph(d-1,p) - ph(d-2,p);
			ph(1,p) = ph(0,p);
			ph(0,p) = 0;
		}
	}
	else  {
		for(p=0;p<ph.cols();p++)  {
			dimens = startdim;
			ph(0,p) = 0;
			for(d=1; d<dim; d++)  {
				dimens++;
				ph(d,p) = gen->nextNormalVariate(p,dimens);
			}
		}
	}
	startdim += pa->totaldim();
}


QM_NAMESPACE_END2

