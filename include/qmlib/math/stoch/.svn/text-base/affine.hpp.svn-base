/********************************************************************************
 * qmlib/rndgen/affine.hpp
 *
 * Copyright (C) 2007-2008 Luca Sbardella <luca.sbardella@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Suggestions:          quant.mind@gmail.com
 * Bugs:                 quant.mind@gmail.com
 *
 * For more information, please see the quantmind Home Page:
 *    http://www.quantmind.com
 *
 *******************************************************************************/


#ifndef   __AFFINE_MODELS_QM_HPP__
#define   __AFFINE_MODELS_QM_HPP__



#include <qmlib/math/monte/all.hpp>
#include <qmlib/timeserie.hpp>
#include <qmlib/params.hpp>



/// \file
/// \brief Affine stochastic process
/// \ingroup rndgen



QM_NAMESPACE2(math)


template<class Im> 				class affine_model;
template<class, class, bool> 	class affine_advance;


/// \brief Traits for Affine Models
/// @param C the numtype (real or complex)
/// @param M the model implementation type
/// \ingroup rndgen
template<class C, class M>
struct affine_traits  {
	typedef C													numtype;
	typedef M													params_type;
	typedef affine_model<params_type>							model_type;
	typedef affine_exponent<numtype,params_type::dimensions>	exponent_type;
	typedef QM_SMART_PTR(exponent_type)							EXPONENT_TYPE;
	typedef typename exponent_type::tvec						tvec;
	typedef typename exponent_type::tmat						tmat;
};




/// \brief Base class for Affine models
/// \ingroup rndgen
///
/// Base class for Affine models. An affine models admit analytical
/// solutions (up to a system of ODEs) for two different transforms.
template<class P>
class affine_model : public pii_process<P>  {
public:
	typedef pii_process<P>										base_class;
	typedef P													params_type;
	typedef typename base_class::PARAMS_TYPE					PARAMS_TYPE;
	typedef affine_model<params_type>							model_type;
	typedef affine_traits<qm_real,params_type>					real_affine_traits;
	typedef affine_traits<qm_complex,params_type>				cplx_affine_traits;
	typedef typename real_affine_traits::tvec			    	tvec;
	typedef typename real_affine_traits::tmat			    	tmat;
	typedef typename cplx_affine_traits::tvec			    	cvec;
	typedef typename cplx_affine_traits::tmat			    	cmat;
	typedef typename real_affine_traits::exponent_type			rexp;
	typedef typename cplx_affine_traits::exponent_type			cexp;
	typedef typename real_affine_traits::EXPONENT_TYPE			REXP;
	typedef typename cplx_affine_traits::EXPONENT_TYPE			CEXP;
	
	affine_model():m_pi(model_type::dimensions),m_dt(0.1){init();}
	
	//bool				linear()     	const 	{ return m_model->linear();}

	// \f$\f$\chi^0_{{\bf x}_t}(T,{\bf c},m) = {\tt E}_t[\exp{(m\int_t^T r_s ds + {\bf c}\cdot{\bf x}_t})]\f = \exp{[a_t(T,{\bf c},m)+{\bf b}_t(T,{\bf c},m) \cdot {\bf x}_t$
	
    /// \brief The Simple Transform. Return the simple transform \f$\chi^0_{{\bf x}_t}(T,{\bf c},m)\f$
	///
    /// Defined the simple transform 
	/// @param c The value of \f${\bf b}\f$ at \f$t = T\f$.
	/// @param m The discounting flag.
	/// @param t The initial time.
	/// @param T The time requested. \f$T > t\f$.
	/// @return Pointer to affine_exponent
	template<class C>
	typename affine_traits<C,params_type>::EXPONENT_TYPE
	transform(const typename affine_traits<C,params_type>::tvec& c, qm_real m, qm_real t, qm_real T) const {
		if(this->analyticalcalc())
			return this->m_param->template analytical_simple<C>(c,m,t,T);
		else
			return simple<C>(c,m,t,T);
	}
	
	qm_real		get_rho0(qm_real t)						const {rho0 = this->m_param->rho0(t);   				return rho0;}
	const tvec& get_rho1(qm_real t)   					const {this->m_param->rho1(rho1,t);   				return rho1;}
	const tvec& get_theta(qm_real t)   					const {this->m_param->theta(theta,t);   				return theta;}
	const tmat& get_Kappa(qm_real t)   					const {this->m_param->Kappa(Kappa,t);   				return Kappa;}
	const tmat& get_KappaT(qm_real t)  					const {this->m_param->KappaT(KappaT,t); 				return KappaT;}
	const tmat& get_Theta(qm_real t)   					const {this->m_param->Theta(Theta,t);   				return Theta;}
	const tmat& get_Beta(qm_real t)   					const {this->m_param->Betas(Beta,t);   				return Beta;}
	const tvec& get_alpha(qm_real t)   					const {this->m_param->alphas(alpha,t);   				return alpha;}
	
	const tvec& get_kappa_theta(qm_real t)  			const {this->m_param->kappa_theta(ktheta,t);  		return ktheta;}
	//const tvec& get_Sigma(const tvec& bt, qm_real t)	const {this->m_param->Sigma(tmp,bt,this->factors,t);        return tmp;}
	
	qm_real		gets_rho0()					const {return get_rho0(0);}
	const tvec& gets_rho1()   				const {return get_rho1(0);}
	const tvec& gets_theta()   				const {return get_theta(0);}
	const tmat& gets_Kappa()   				const {return get_Kappa(0);}
	const tmat& gets_KappaT()  				const {return get_KappaT(0);}
	const tmat& gets_Theta()   				const {return get_Theta(0);}
	const tmat& gets_Beta()  				const {return get_Beta(0);}
	const tvec& gets_alpha()   				const {return get_alpha(0);}
	
	//PARAMETER   get_mktrisk(unsigned i)	    const {QM_REQUIRE(i<dimensions,"Out of bound"); return m_pi[i];}
	
	qm_real get_dt() const {return m_dt;}
	void    set_dt(qm_real val) {QM_REQUIRE(val>0,"Time step must be positive"); m_dt = val;}
	
	/// \brief Set up the model for a calculation. Only used when the model is time homogeneous
	void    setup(qm_real t = 0) const;
	
	void    simula(montecarlo* monte, unsigned numpaths) const;
	
	mutable tmat    Kappa, KappaT, Theta, Sigma, Beta;
	mutable tvec    theta, ktheta, alpha, rho1, tmp, pi;
	mutable qm_real rho0;
protected:
	parameter_list<model_type::time_homogeneous>	m_pi;		//	The market price of risk parameters
	qm_real			 								m_dt;
	
	tmat m_tmp,m_tmp2;
	tvec m_kappa0, m_sigb, m_tp;
	
	model_type& noConst() const { return const_cast<model_type&>(*this);}
	
	/// \brief The Numerical Simple Transform
	///
	/// @param c The vector of initial conditions
	/// @param m The discounting flag
	/// @param t The time for which we need the transform
	/// @param T The maturity \f$T \ge t\f$
	/// @return the affine coefficient 
	template<class C>
	typename affine_traits<C,params_type>::EXPONENT_TYPE
	simple(const typename affine_traits<C,params_type>::tvec& c, qm_real m, qm_real t, qm_real T) const;
	
	void init();
};


QM_NAMESPACE_END2


#endif  //  __AFFINE_MODELS_QM_HPP__
