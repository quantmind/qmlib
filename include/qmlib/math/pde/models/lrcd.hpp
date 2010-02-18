

#ifndef __LINEAR1D_PDE_MODELS_QM_HPP__
#define __LINEAR1D_PDE_MODELS_QM_HPP__


#include <qmlib/math/pde/model_coef.hpp>



/**\file
 * \ingroup pde
 * \brief Reaction-convection-diffusion equation.
 * 
 * This type of equations are very common in finance when pricing
 * options.
 * 
 */



QM_NAMESPACE2(math)


template<typename T, unsigned N, bool linear> class ReacConvDiff;
template<class T, unsigned N> struct rcd_operators;


template<class T>
struct rcd_operators<T,1u>  {
	typedef T										numtype;
	typedef first_centered<numtype,1,1,2>			first_der_type;
	typedef second_centered<numtype,1,1,2>			second_der_type;
	typedef structured_operator<first_der_type>		first_der_types;
	typedef structured_operator<second_der_type>	second_der_types;
	typedef qmatrix<numtype,tridiagonal>			lhstype;
};



/** \brief Linear one-dimensional Reaction-Convection-Diffusion PDE
 * \ingroup pde
 * 
 * The classical one dimension linear reaction-convection-diffusion equation.
 * 
 * \f$ \frac{\partial V_t}{\partial t} = c_t(x) \frac{\partial V_t}{\partial x} +
 *  \nu_t(x) \frac{\partial^2 V_t}{\partial x^2} + r_t(x) V_t\f$
 * 
 * where
 * 
 * \f$c_t(x)\f$ is the convection coefficient,
 * \f$\nu_t(x)\f$ is the diffusion coefficient and
 * \f$r_t(x)\f$ is the reaction coefficient.
 * 
 * This equation is linear since the coefficients do not depend on the
 * unknown \f$V_t\f$
 * 
 * @param C the convection coefficent
 * @param D the diffusion coefficent
 * @param R the reaction coefficent
 */
template<typename T, bool lin>
class ReacConvDiff<T,1u,lin>: public pdemodel_base<T,1u>  {
public:
	typedef T										numtype;
	typedef ReacConvDiff<numtype,1u,lin>			selftype;
	typedef pdemodel_base<numtype,1u>				base_class;
	typedef rcd_operators<numtype,1u>				operators;
	typedef typename base_class::gridtype			gridtype;
	typedef typename base_class::GRIDTYPE			GRIDTYPE;
	typedef typename operators::lhstype				lhstype;
	typedef typename operators::first_der_types		first_der_types;
	typedef typename operators::second_der_types	second_der_types;
	typedef qmatrix<numtype>						qmat;
	typedef pde_coefficient<1u,numtype>				coeftype;
	typedef QM_SMART_PTR(coeftype)					COEFTYPE;
	
	static const bool c_linear = lin;
	
	ReacConvDiff(const GRIDTYPE& gr,
				 const COEFTYPE& diffusion,
				 const COEFTYPE& convection,
			 	 const COEFTYPE& reaction):base_class(gr), m_fder(gr),m_sder(gr),
			 						   m_diff(diffusion),m_conv(convection),
			                           m_reac(reaction),m_lhsdone(false)  {
		QM_REQUIRE(m_diff && m_conv && m_reac,"One or more coefficients are null");
		m_diff->set_grid(gr);
		m_conv->set_grid(gr);
		m_reac->set_grid(gr);
		this->setup();
	}
	ReacConvDiff(const GRIDTYPE& gr,
				 numtype diffusion,
				 numtype convection,
			 	 numtype reaction):
			 		 base_class(gr), m_fder(gr),m_sder(gr), m_lhsdone(false) {
		typedef const_pde_coefficient<1u,numtype> const_coef;
		m_diff = COEFTYPE(new const_coef(diffusion,gr));
		m_conv = COEFTYPE(new const_coef(convection,gr));
		m_reac = COEFTYPE(new const_coef(reaction,gr));
		this->setup();
	}
	
	time_marching_result solve(const TIMEGRID& tg)  {
		return time_marching::advance<_trapezoidal,selftype>(*this,tg);
	}
	
	void clear();
	
	bool      islinear() const {return c_linear;}
	bool      timedependent() const {return m_diff->timedependent() || m_conv->timedependent() || m_reac->timedependent();} 
	qm_real   dtmax()  const {return m_dtmax;}
	qm_string tostring() const {return "Linear Reaction-Convection-Diffusion PDE in one dimension";}

	const qmat& rhs(const qmat& unk, unsigned t) {
		this->m_rhs = timecoef(m_reac,t,true)*unk + 
					  timecoef(m_conv,t,true)*m_fder(unk,t) +
					  timecoef(m_diff,t,true)*m_sder(unk,t);
		return this->m_rhs; 
	}
	
	///\brief Evaluate the right hand side from a matrix expression
	template<class expr>
	const qmat& rhs(const matrix_expr<expr>& unk, unsigned t) {
		this->m_rhs = timecoef(m_reac,t,true)*unk +
					  timecoef(m_conv,t,true)*m_fder(unk,t) + 
					  timecoef(m_diff,t,true)*m_sder(unk,t);
		return this->m_rhs;
	}
	
	///\brief get the left-hand-side tridiagonal matrix
	lhstype& lhs(unsigned t) {
		this->LHS(t);
		return m_lhs;
	}
	
	const TIMEGRID& get_timegrid() const {return m_reac->get_timegrid();}
	
	void set_timegrid(const TIMEGRID& tg) {
		m_lhsdone = false;
		m_reac->set_timegrid(tg);
		m_conv->set_timegrid(tg);
		m_diff->set_timegrid(tg);
	}
	
	/// \brief Retrive the diffusion coefficient
	const COEFTYPE& diffusion()  const {return m_diff;}
	/// \brief Retrive the convection coefficient
	const COEFTYPE& convection() const {return m_conv;}
	/// \brief Retrive the reaction coefficient
	const COEFTYPE& reaction()   const {return m_reac;}
	
	/// \brief Return the diffusion coefficients at time t
	qmat get_diffusion(unsigned t)  {this->m_rhs = timecoef(m_diff,t,t); return this->m_rhs;}
	/// \brief Return the convection coefficients at time t
	qmat get_convection(unsigned t) {this->m_rhs = timecoef(m_conv,t,t); return this->m_rhs;}
	/// \brief Return the reaction coefficients at time t
	qmat get_reaction(unsigned t)   {this->m_rhs = timecoef(m_reac,t,t); return this->m_rhs;}
	
protected:
	first_der_types		m_fder;
	second_der_types	m_sder;
	lhstype				m_lhs;
	COEFTYPE 			m_diff, m_conv, m_reac;
	bool				m_lhsdone;
	qm_real 			m_dtmax;
	
	void setup()  {
		unsigned N  = this->points();
		qm_real v,cov,dif,dtc,dtd,dtm;
		qm_real big = std::numeric_limits<qm_real>::max();
		m_dtmax = big;
		GRIDTYPE gr = this->grid();
		for(unsigned i=0;i<N;i++)  {
			v = gr->volume_fast(i);
			cov = std::fabs(m_conv->eval(i,0,true));
			dif = m_diff->eval(i,0,true);
			dtc = cov > 0 ? v/cov 		: big;
			dtd = dif > 0 ? 0.5*v*v/dif : big;
			dtm = std::min(dtc,dtd);
			m_dtmax  = std::min(m_dtmax,dtm);
		}
		if(m_dtmax == big) m_dtmax = 1.0;
	}
	
	void LHS(unsigned t) {
		if(!m_lhsdone)  {
			m_lhs.resize(this->points(),this->points());
			m_lhsdone = true;
		}
		m_lhs = 0;
		m_fder.lhs(timecoef(m_conv,t,false),m_lhs);
		m_sder.lhs(timecoef(m_diff,t,false),m_lhs);
		m_lhs.add_to_diagonal(timecoef(m_reac,t,false));
	}
	
};










//___________________________________________________________________________________
//IMPLEMENTATION
template<typename T, bool lin>
inline void ReacConvDiff<T,1u,lin>::clear()  {
	m_lhsdone = false;
	m_diff->clear();
	m_conv->clear();
	m_reac->clear();
}




QM_NAMESPACE_END2


#endif // __LINEAR1D_PDE_MODELS_QM_HPP__

