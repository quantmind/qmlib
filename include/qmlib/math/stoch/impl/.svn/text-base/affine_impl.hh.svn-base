


#ifndef   __AFFINE_IMPL_TERM_STRUCTURE_MODELS_QM_HPP__
#define   __AFFINE_IMPL_TERM_STRUCTURE_MODELS_QM_HPP__



QM_NAMESPACE2(math)


template<class C, class M>
class affine_advance<C,M,true>  {
public:
	typedef affine_traits<C,M>								affine_traits_type;
	typedef typename affine_traits_type::numtype			numtype;
	typedef typename affine_traits_type::params_type		params_type;
	typedef typename affine_traits_type::tvec				tvec;
	typedef typename affine_traits_type::tmat				tmat;
	typedef typename affine_traits_type::model_type			model_type;
	typedef typename affine_traits_type::exponent_type		exponent_type;
	
	static void bval(const model_type& model, exponent_type* expo, tvec& rhs, tmat& lhs, qm_real dti)  {
		static tvec tp0,tp1;
		qm_real dm =-expo->d;
		qm_real mu =-1;
		rhs = dm*model.rho1 - mmult(model.KappaT,expo->b);
		lhs = mu*model.KappaT;
		model.model()->template addvolb<C>(rhs,lhs,expo);
		lhs *=-0.5;
		for(unsigned i=0;i<params_type::dimensions;i++) lhs(i,i) += dti;
		lhs.inv();
	}

	static void aval(const model_type& model, exponent_type* expo0, exponent_type* expo1)  {
		qm_real dt  = expo0->t - expo1->t;
		numtype rhs = 0.5 * model.ktheta.inner(expo0->b + expo1->b) - expo0->d*model.rho0;
		model.model()->addvola(rhs,expo0,expo1);
		expo1->a = expo0->a + dt*rhs;
	}
};






//  Calculate the simple transform exponent
template<class P>
template<class C>
inline typename affine_traits<C,P>::EXPONENT_TYPE
affine_model<P>::simple(const typename affine_traits<C,P>::tvec& c, qm_real m, qm_real t, qm_real T) const {
	typedef typename affine_traits<C,P>::exponent_type					exponent_type;
	typedef typename affine_traits<C,P>::EXPONENT_TYPE					EXPONENT_TYPE;
	typedef typename affine_traits<C,P>::tvec							cvec;
	typedef typename affine_traits<C,P>::tmat							cmat;
	typedef affine_advance<C,params_type,model_type::time_homogeneous>	advance_type;
	
	static const qm_real tole = 1.0E-07;
	static const unsigned itemax = 20;
	qm_real tau = T - t;
	EXPONENT_TYPE expo1(new exponent_type(m,T,T));
	expo1->b = c;
	if(tau <= 0.0) return expo1;
	EXPONENT_TYPE expo0(new exponent_type(m,T,T));
	exponent_type* ex0 = expo0.get();
	exponent_type* ex1 = expo1.get();
		
	unsigned NN  = std::max((int)(tau/m_dt) + 1, 1);
	qm_real  dd	 = tau/NN;
	qm_real  ddi = 1.0/dd;
	cvec     rhs0, db;
	cmat     lhs(0);
		
	// Setup a time homogeneous model
	if(model_type::time_homogeneous) this->setup();
			
	if(this->linear())  {
		for(unsigned n = 0; n < NN; n++)  {
			ex0->assign(ex1);
			ex1->t -= dd;
			advance_type::bval(this->noConst(),ex1,rhs0,lhs,ddi);
			ex1->b += mmult(lhs,rhs0);
			ex1->n  = n+1;
			advance_type::aval(this->noConst(),ex0,ex1);
		}
	}
	else  {
		cvec     b0,rhs;
		qm_real  nrm;
		unsigned ite;
		unsigned totite = 0;
		for(unsigned n = 0; n < NN; n++)  {
			ex0->assign(ex1);
			ex1->t -= dd;
			// Get the first guess and store the rhs in rhs0
			advance_type::bval(this->noConst(),ex1,rhs0,lhs,ddi);
			db 		= mmult(lhs,rhs0);
			ex1->b += db;
			ite = 1;
			totite++;
			nrm = 1;
			while(std::sqrt(nrm) > tole)  {
				ite++;
				totite++;
				QM_REQUIRE(ite<itemax,"Affine integration failed. Too many iterations.")
				advance_type::bval(this->noConst(),ex1,rhs,lhs,ddi);
				rhs = 0.5*(rhs + rhs0) - ddi*(ex1->b - ex0->b);
				db  = mmult(lhs,rhs);
				ex1->b += db;
				nrm = db.norm2();
			}
			ex1->n  = n+1;
			advance_type::aval(this->noConst(),ex0,ex1);
		}
		ex1->itern = totite;
	}
	return expo1;
}


/// \brief Montecarlo simulation
template<class Im>
void affine_model<Im>::simula(montecarlo* monte, unsigned numpaths) const  {
	// Setup a time homogeneous model
	if(model_type::time_homogeneous) this->setup();
	TIMEGRID tg = monte->grid();
	//m_paths.set(tg,numpaths);
	/*
	montecarlo::paths_type pats = monte->diffusion(tg,numpaths,dimensions,0);
	tvec x,dw,dww,dx;
	typedef typename affine_paths::data_type	data_type;
	
	m_paths.set_numpaths(numpaths);
	
	data_type cross(numpaths);
	for(unsigned p=0;p<numpaths;p++)  {
		cross[p] = this->factors;
	}
	m_paths.addkeyval(0,cross);
	
	for(unsigned t=1;t<tg->length();t++)  {
		data_type cross1(numpaths);
		qm_real dt  = tg->dt(t,1);
		qm_real tim = tg->time(t);
		for(unsigned p=0;p<numpaths;p++)  {
			for(unsigned n=0;n<dimensions;n++)  {
				dw[n] = pats[n](t,p);
			}
			x   = m_paths(t-1,p);
			dww = mmult(Theta,m_model->diffusion(tim-dt,x,dw));
			dx  = dt*(ktheta - mmult(Kappa,x)) + dww;
			//dx  = dt*(ktheta - mmult(Kappa,x)) + dww;
			cross1[p] = x + dx;
		}
		m_paths.addkeyval(tim,cross);
	}
	*/
}







template<class Im>
void affine_model<Im>::init() {
	rho0    = 0;
	rho1    = 0;
	Kappa   = 0;
	KappaT  = 0;
	Theta   = 0;
	ktheta  = 0;
	Beta	= 0;
	alpha	= 0;
	for(unsigned i=0;i<model_type::dimensions;i++)  {
		//PARAMETER pa = m_model->namefactor(i);
		//m_pi[i] = PARAMETER(new parameter_type(pa->description() + " market-price-of-risk", "pi_" + pa->name(), 0));
		Theta(i,i) = 1;
	}
}


template<class Im>
void affine_model<Im>::setup(qm_real t) const {
	get_rho0(t);
	get_rho1(t);
	get_KappaT(t);
	get_kappa_theta(t);
}




QM_NAMESPACE_END2


#endif  //  __AFFINE_IMPL_TERM_STRUCTURE_MODELS_QM_HPP__
