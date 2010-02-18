



#include<qmlib/finance/rates/impl/create_pde_grid.hh>


QM_NAMESPACE2(finance)


template<unsigned N, exercisetype et, payofftype pt> inline void
option<N,et,pt>::create_pde(const typename option_base<N>::pderatetype& rate) const  {
	QM_USING_NAMESPACE2(math);
	typedef diffusion<1u>						diffusiontype;
	typedef QM_SMART_PTR(diffusiontype)			DIFFUSIONTYPE;
	typedef create_pde_grid<N,pt>				gridmaker;
	typedef typename gridmaker::GRIDTYPE		GRIDTYPE;
	
	//DTIMEGRID tg   = m_exercise.get_timegrid(rate.date(),rate.dt());
	//GRIDTYPE gr    = gridmaker::doit(rate,m_payoff,tg);
}



// PDE pricer for 1d process,
//  - vanilla and barrier payoffs of any exercise type
template<>
template<exercisetype et, payofftype pt> inline SENSITIVITY
optionmodel<1u,pde_>::calculate(const boost::shared_ptr<option<1u,et,pt> > &op) const  {
	typedef option<1u,et,pt> 					option_type;
	typedef typename option_type::PDETYPE		PDETYPE;
	typedef typename option_type::payoff_type	payoff_type;
	typedef typename payoff_type::boundary_type	boundary_type;
	QM_USING_NAMESPACE2(math);
	SENSITIVITY se;
	PDETYPE pde = op->get_pde(*this);
	return se;
}


QM_NAMESPACE_END2

