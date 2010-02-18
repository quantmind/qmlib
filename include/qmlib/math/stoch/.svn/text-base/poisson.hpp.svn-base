

#ifndef __POISSON_PROCESS_QM_HPP__
#define __POISSON_PROCESS_QM_HPP__



#include <qmlib/math/stoch/stochastic.hpp>
#include <qmlib/math/stoch/characteristic.hpp>


/* \file
 * \ingroup stoch
 * 
 * \brief Poisson and Poisson Compound processes
 */


QM_NAMESPACE2(math)

class poisson_base;
typedef QM_SMART_PTR(poisson_base)	POISSON;


template<unsigned N>
class JumpChar: public stochastic, public characteristic<N>  {
public:
	typedef stochastic::momentstype	 momentstype;

	momentstype moments(unsigned i, qm_real t1, qm_real t2) const  {
		momentstype m(0,0,0,0);
		this->calcmoments(i,t1,t2,m);
		return m;
	}
	bool    ispositive_characteristic() const {return this->ispositive();}
protected:
	JumpChar(){}
};



class poisson_base: public JumpChar<1u>  {
public:
	poisson_base(PARAMETER lambda);

    void    simula(montecarlo* monte, unsigned numpaths, unsigned& stdim);

    virtual qm_real sample_jump(RNDGEN gen, unsigned idx, unsigned& dim) const {return 0;}

    bool analytical_exponent() const {return true;}
    bool ispositive()		   const {return true;}
    
	momentstype moments(unsigned i, qm_real t1, qm_real t2) const  {
		momentstype m(0,0,0,0);
		this->calcmoments(i,t1,t2,m);
		return m;
	}
protected:
	iparameter* p_lambda;
};



class poisson: public poisson_base  {
public:
	poisson(PARAMETER lambda, PARAMETER jump);

    qm_real sample_jump(RNDGEN gen, unsigned idx, unsigned& dim) const {return p_jump->get_value();}
    qm_string code() const {return "Poisson";}
    qm_real	characteristic_period() const {return p_jump->get_value();}

    void rcumulant(const rvec& u, REXPONENT& expo) const {cumulant(u[0],expo.get());}
    void ccumulant(const cvec& u, CEXPONENT& expo) const {cumulant(u[0],expo.get());}
protected:
	iparameter* p_jump;

	template<typename T>
	void cumulant(const T& u, affine_exponent<T,1u>* expo) const {
		qm_real la = p_lambda->get_integrated(expo->t0,expo->t1);
		expo->a = la*(std::exp(u*p_jump->get_value()) - 1.0);
		expo->b[0] = 0;
	}
};

class exppoisson: public poisson_base  {
public:
	exppoisson(PARAMETER lambda, PARAMETER decay);

    qm_real sample_jump(RNDGEN gen, unsigned idx, unsigned& dim) const;

    qm_string code() const {return "Exponential Poisson";}

    void rcumulant(const rvec& u, REXPONENT& expo) const {cumulant(u[0],expo.get());}
    void ccumulant(const cvec& u, CEXPONENT& expo) const {cumulant(u[0],expo.get());}
protected:
	iparameter* p_decay;

	template<typename T>
	void cumulant(const T& u, affine_exponent<T,1u>* expo) const {
		qm_real la = p_lambda->get_integrated(expo->t0,expo->t1);
		expo->a    = -u*la/(u - p_decay->get_value());
		expo->b[0] = 0;
	}
};


inline qm_real exppoisson::sample_jump(RNDGEN gen, unsigned idx, unsigned& dim) const  {
	qm_real u = gen->nextUniform(idx,dim);
	dim++;
	return -std::log(1.0 - u)/p_decay->get_value();
}


QM_NAMESPACE_END2


#endif // __POISSON_PROCESS_QM_HPP__
