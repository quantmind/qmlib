

#ifndef __DIFFUSION_PROCESS_IMPL_QM_HPP__
#define __DIFFUSION_PROCESS_IMPL_QM_HPP__


QM_NAMESPACE2(math)


// A general implementation of a 1D diffusion path
template<>
void diffusion<1u>::createPaths() {
	timegrid* tg = m_paths.grid().get();
	path::holder pas = m_paths[0]->pathholder();
	qm_real dt,x0,tim,mu,sig;
	unsigned T = m_paths.timedim();
	unsigned P = m_paths.numpaths();
	
	// Loop over time
	for(unsigned t=1; t<T; ++t)  {
		tim   = tg->time(t-1);
		dt    = tg->dt(t,1);
		for(unsigned p=0; p<P; ++p)  {
			x0       = pas(t-1,p);
			mu       = this->drift(x0,tim)*dt;
			sig      = std::sqrt(this->sigma2(x0,tim)*dt);
			pas(t,p) = x0 + mu + sig*pas(t,p);
		}
	}
}


template<unsigned N>
void diffusion<N>::simula(montecarlo* monte, unsigned numpaths, unsigned& stdim) {
	m_paths.set(monte->grid(),numpaths);
	timegrid* tg = m_paths.grid().get();
	PATH pa;

	// Generate the diffusion shocks
	for(unsigned i=0;i<N;++i)  {
		PATH pa = m_paths.add_diffusion();
		monte->diffusion(pa,stdim);
	}
	this->precalc();
	this->createPaths();
}


template<unsigned N>
inline qm_real
CharacteristicDiffusion<N>::exponential_convexity(qm_real t, qm_real t1) const  {
	return 0;
}

template<unsigned N>
void ExponentialCharacteristicDiffusion<N>::simula(montecarlo* monte, unsigned numpaths, unsigned& stdim) {
	p_proc->simula(monte,numpaths,stdim);
	this->m_paths = p_proc->get_paths();
	Paths paths   = this->m_paths;
	this->exp_path_correction(paths);
}


template<typename T, typename U>
inline void square_root_exponent(const T& k, const T& m, qm_real eta, qm_real tau,
								 const U& c, typename QM_PROMOTE(T,U)& a,
								 typename QM_PROMOTE(T,U)& b)  {
	typedef typename QM_PROMOTE(T,U)	out_type;
	qm_real et2    = eta*eta;
	T 		phi    = std::sqrt(k*k + 2.*et2*m);
	T	    c1     = (k-phi)/et2;
	T	    c2     = (k+phi)/et2;
	T	    pt     = std::exp(phi*tau);
	out_type cc1   = c - c1;
	out_type cc2   = c - c2;
	a = c2*tau + (c1-c2)*std::log((c1 - c2*pt + c*(pt - 1.))/(c1-c2))/phi;
	b = (c2*cc1 - pt*c1*cc2)/(cc1 - cc2*pt);
}

inline DIST1 squareroot_marginal(qm_real t, qm_real ka, qm_real th, qm_real et, qm_real v0)  {
	qm_real s2  = et*et;
	qm_real ekt = std::exp(-ka*t);
	qm_real c   = 4.*ka/(s2*(1. - ekt));
	qm_real v   = 4.*ka*th/s2;
	qm_real la  = c*v0*ekt;
	return chi2nc_shifted_distribution::make(v,la,c);
}

    
QM_NAMESPACE_END2


#endif // __DIFFUSION_PROCESS_IMPL_QM_HPP__

