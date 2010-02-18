

#ifndef __TRAPEZOIDAL_TIME_MARCHING_QM_HPP__
#define __TRAPEZOIDAL_TIME_MARCHING_QM_HPP__



/**\file
 * \brief Trapezoidal time marching algorithms
 * \ingroup pde
 */


QM_NAMESPACE2(math)



/** \brief Trapezoidal scheme for linear trapezoidal systems
 * \ingroup pde
 * 
 * Given a semi-discrete system of ODE \f$ \frac{d v_t}{d t} =-R_t\,v_t\f$,
 * where \f$L\f$ is a tridiagonal matrix, the linear trapezoidal scheme
 * is given by
 * 
 * \f$\left[\frac{1}{\Delta t} + \frac {1}{2} R_{t+\Delta t}\right] v_{t+\Delta t} = \frac{v_t}{\Delta t}-\frac{1}{2}R_t\,v_t\f$
 */
template<class M>
class timemarching<_trapezoidal,M>  {
public:
	typedef M								model_type;
	typedef typename model_type::numtype	numtype;
	typedef typename model_type::lhstype	lhstype;
	typedef qmatrix<numtype>				qmat;
	
	timemarching(const model_type& model){
		unsigned N = model.points();
		m_tmp.resize1(N);
		m_rhs.resize1(N);
	}

	/// \brief Prepare the left-hand side
	///
	/// @param model The PDE model
	/// @param t time level
	/// @param dt time step
	/// @return a matrix representing the left-hand side
	/// \f$ L_{t+\Delta t} = \frac{1}{\Delta t} + \frac {1}{2} R_{t+\Delta t}\f$
	lhstype lhs(model_type& model, unsigned t)  {
		unsigned  N = model.points();
		qm_real  dt = model.get_timegrid()->dt(t,1);
		qm_real dti = 1.0/dt;
		lhstype  lh = model.lhs(t);
		lh *= 0.5;
		for(unsigned i=0;i<N;i++) lh(i,i) += dti;
		return lh;
	}
	/// \brief advance one time-step, from t to t+dt
	///
	/// @param dt time step
	/// @param t time level
	/// @param unk unknowns at time t
	/// @param unk1 unknown at time t + dt (output of the function)
	/// @param model the pde model
	void advance(unsigned t, const qmat& unk, qmat& unk1, M& model) {
		lhstype  lh = this->lhs(model,t);
		qm_real  dt = model.get_timegrid()->dt(t,1);
		qm_real dti = 1.0/dt;
		m_rhs = model.rhs(unk,t-1) + dti*unk;
		linalg<numtype>::solve(lh, m_rhs, unk1);
		//unk1 = unk + m_tmp;
	}
	
	bool implicit() const {return true;}
	qm_string tostring() const {return "Trapezoidal time-marching algorithm";}
private:
	qmat	m_tmp,m_rhs;
}; 


QM_NAMESPACE_END2


#endif // __TRAPEZOIDAL_TIME_MARCHING_QM_HPP__

