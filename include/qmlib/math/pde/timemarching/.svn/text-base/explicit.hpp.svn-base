




/*

/// \brief Euler method. A simple 1st order Euler method
template<typename T>
class EulerMethod : public timemarching {
public:
	EulerMethod():timemarching("Euler 1st order time integration",false){}
	
	template<class M>
	void setup(const M& model, qm_real dt)  {}
	
	template<class M>
	void advance(qm_real dt, qm_real t, const qmatrix<typename M::numtype>& unk, qmatrix<typename M::numtype>& unk1, M& m) {
		unk1 = unk + dt * m.rhs(unk,t);
	}
	
};

/// \brief Henn's method. A predictor corrector with theta = 1/2
template<typename T>
class HennMethod : public timemarching {
public:
	typedef T					numtype;
	typedef qmatrix<numtype>	qmat;
	HennMethod():timemarching("Henn Method",false){}
	
	template<class M>
	void setup(const M& model, qm_real dt)  {
		m_tmp.resize1(model.points());
	}
	
	template<class M>
	void advance(qm_real dt, qm_real t, const qmat& unk, qmat& unk1, M& m) {
		m_tmp  = unk + dt * m.rhs(unk,t);
		unk1   = unk + dt * m.rhs(m_tmp, t);
	}
private:
	qmat	m_tmp;
};

*/
