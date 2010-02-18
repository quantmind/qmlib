
#ifndef   __OPTION_RATE_QM_HPP__
#define   __OPTION_RATE_QM_HPP__


#include <qmlib/finance/instruments/options.hpp>



QM_NAMESPACE2(finance)

typedef QM_FROM_NAMESPACE2(math)STOCHASTIC STOCHASTIC;



template<unsigned N, pricingValuationMethod V>
class optionmodel: public ioptionmodel,
				   public base_container<boost::shared_ptr<optionmodel<1u,V> > >  {
public:
	typedef base_container<boost::shared_ptr<optionmodel<1u,V> > >	base_class;
	typedef typename base_class::value_type							value_type;
	
	template<class L>
	static OPTION_MODEL make(const L& data);
	
	const period&	dt()	  const	 {return (*this)[0].dt();}
	qdate     		date() 	  const  {return (*this)[0].date();}
	unsigned  		length()  const  {return N;}
	
	template<exercisetype et, payofftype pt>
	SENSITIVITY	calculate(const boost::shared_ptr<option<N,et,pt> > &op) const;
protected:
	optionmodel():base_class(N){
		//BOOST_STATIC_ASSERT((V == pde_ && N <= 2) || );
	}
};




/** \brief Specialization of optionmodel for options with 1 underlying
 * \ingroup rates
 */
template<pricingValuationMethod V>
class optionmodel<1u,V>: public ioptionmodel , public discount_curve_holder {
public:
	static OPTION_MODEL make(const STOCHASTIC& p,
							 DISCOUNTCURVE yc,
							 DISCOUNTCURVE cy,
							 const period& dt) {return OPTION_MODEL(new optionmodel(p,yc,cy,dt));}
	qm_string code() const {return "Option model with " + m_process->name();}
	STOCHASTIC  stoch() const {return m_process;}
	pricingValuationMethod method() const {return V;}
	/// \brief Calculate the forward rate
	qm_real     forward(const qdate& dte)  const;
	
	qdate     		date() 	const    {return this->m_yc->date();}
	const period&	dt()	const	 {return m_dt;}
	
	template<exercisetype et, payofftype pt>
	SENSITIVITY	calculate(const boost::shared_ptr<option<1u,et,pt> > &op) const;
protected:
	STOCHASTIC	m_process;
	qm_real		m_spot;
	period		m_dt;
	qm_real		m_cfl;
	bool available() const;
	optionmodel(const STOCHASTIC& p, DISCOUNTCURVE yc, DISCOUNTCURVE cy, const period& pe);
};


/*
template<class L>
static OPTION_MODEL make(const L& data)  {
	unsigned n = extract_length<L>(data);
	QM_REQUIRE(n==N,"wromg number of models");
	value_type mod;
	for(unsigned i=0;i<N;i++)  {
		mod = extract_data<value_type>(data,i);
		(*this)[i] = mod;
	}
}
*/






template<pricingValuationMethod V>
inline optionmodel<1u,V>::optionmodel(const STOCHASTIC& p, DISCOUNTCURVE yc,
									  DISCOUNTCURVE cy, const period& dt):m_process(p),m_dt(dt) {
	QM_REQUIRE(m_process,"Stochastic process not available");
	QM_REQUIRE(yc,"Yield curve not available");
	QM_REQUIRE(this->available(),"Option pricing model not available");
	DISCOUNTCURVE cy_ = cy;
	if(!cy_) cy_ = DISCOUNTCURVE(new dummydiscount);
	this->addcurve(yc);
	this->addcurve(cy_);
}

template<>
inline bool optionmodel<1u,analytical_>::available() const {
	return m_process->has_analyticals();
}
template<>
inline bool optionmodel<1u,pde_>::available() const {
	return m_process->isdiffusion();
}
template<>
inline bool optionmodel<1u,fourier_>::available() const {
	return m_process->has_characteristic();
}
template<>
inline bool optionmodel<1u,montecarlo_>::available() const {
	return true;
}

template<pricingValuationMethod V>
inline qm_real optionmodel<1u,V>::forward(const qdate& dte)  const  {
	qm_real ba = m_yc->df(dte);
	qm_real bb = m_cy->df(dte);
	return bb*m_spot/ba;
}


/*
// PDE pricer for 1d process,
//  - average path dependent payoffs are not priced with a pde method
template<> template<> inline SENSITIVITY
optionmodel<1u,pde_>::calculate(const QM_SMART_PTR(option<1u,European_,Average_>)& op) const  {
	QM_FAIL("Cannot price an average payoff option using a PDE method");
}
template<> template<> inline SENSITIVITY
optionmodel<1u,pde_>::calculate(const QM_SMART_PTR(option<1u,American_,Average_>)& op) const  {
	QM_FAIL("Cannot price an average payoff option using a PDE method");
}
template<> template<> inline SENSITIVITY
optionmodel<1u,pde_>::calculate(const QM_SMART_PTR(option<1u,Bermudan_,Average_>)& op) const  {
	QM_FAIL("Cannot price an average payoff option using a PDE method");
}
*/

/*
struct OptionConvention1d  {
	typedef qm_real	numtype;
	static const bool timedependent = true;
	Convention1d(GRID1D gr):m_grid(gr){}
	qm_real operator () (unsigned i, qm_real t) const {
		return m_grid->coor(0,i);
	}
};
struct OptionDiffusion1d  {
	typedef qm_real	numtype;
	static const bool timedependent = true;
	Convention1d(GRID1D gr, JDP1 di):m_grid(gr),m_diff(di){}
	qm_real operator () (unsigned i, qm_real t) const {
		qm_real sig = m_diff->sigma(m_grid->coor(0,i),t);
		return 0.5*sig*sig;
	}
};
struct OptionReaction1d  {
	typedef qm_real	numtype;
	static const bool timedependent = true;
	Convention1d(DISCOUNTCURVE yc):m_grid(gr),m_diff(di){}
	qm_real operator () (unsigned i, qm_real t) const {
		qm_real sig = m_diff->sigma(m_grid->coor(0,i),t);
		return 0.5*sig*sig;
	}
};
*/



QM_NAMESPACE_END2


#include<qmlib/finance/rates/impl/pderate_impl.hh>


#endif	//	__OPTION_RATE_QM_HPP__
