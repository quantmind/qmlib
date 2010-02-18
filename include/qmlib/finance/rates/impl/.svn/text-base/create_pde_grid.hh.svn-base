
QM_NAMESPACE2(finance)

template<unsigned N, payofftype pt>
struct create_pde_grid  {
	
};


template<payofftype pt>
struct create_pde_grid<1u,pt>  {
	typedef option_base<1u>::pderatetype	ratetype;
	typedef Payoff<1u,pt>					payofftype;
	typedef QM_SMART_PTR(payofftype)		PAYOFFTYPE;
	
	static pdegridtraits<1u>::GRIDTYPE
	doit(const ratetype& rate, const PAYOFFTYPE& po, DTIMEGRID tg)  {
		QM_USING_NAMESPACE2(math);
		typedef diffusion<1u>						diffusiontype;
		typedef QM_SMART_PTR(diffusiontype)			DIFFUSIONTYPE;
		DIFFUSIONTYPE diff = smart_cast<diffusiontype,istochastic>(rate.stoch());
		QM_REQUIRE(diff,"Stochastic diffusion not available. Cannot price with PDEs");
		qm_real  sig   = diff->sigma(1,0);
		qm_real  T	   = tg->horizon();
		qm_real  dtmax = tg->dtmax();
		qm_real  DX	   = 3*sig*std::sqrt(T);
		qm_real  dxmin = sig*std::sqrt(dtmax);
		unsigned M	   = unsigned(2*DX/dxmin);
		return po->grid(DX,M);
	}
};


QM_NAMESPACE_END2

