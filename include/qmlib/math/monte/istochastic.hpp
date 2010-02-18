



#ifndef __ISTOCHASTIC_PROCESS_QM_HPP__
#define __ISTOCHASTIC_PROCESS_QM_HPP__


#include <qmlib/math/monte/path.hpp>

/*! \defgroup stoch Stochastic process library

    @{
*/


/**\file
 * \brief Stochastic processes Interface
 */


QM_NAMESPACE2(math)

class istochastic;
typedef QM_SMART_PTR(istochastic) 		STOCHASTIC;



/** \brief Interface class for a general multivariate stochastic process
 */
class istochastic: public icodename  {
public:
	typedef tinyvec<qm_real,4>	momentstype;
    //
    /// true if the process has an analytical probability density function
    /// @return true if the stochastic process has an analytical formula for the probability density function
    virtual bool has_analytical_density()    const {return false;}
    //
    /// true if the process has an analytical cumulative probability function
    /// @return true if the stochastic process has an analytical formula for the cumulatice probability function
    virtual bool has_analytical_cumulative() const {return false;}
    //
    /// @return the analytical probability density function if has_analytical_density is true
    virtual qm_real analytical_density(qm_real, qm_real) const  {return 0;}
    //
    /// @return the analytical cumulative probability function if has_analytical_cumulative is true 
    virtual qm_real analytical_cumulative(qm_real, qm_real) const {return 0;}
    //
    /// @return the number of stochastic process for path generation
    virtual unsigned count() const  {return 1;}
    
    virtual bool isdiffusion() 		  const {return false;}
    virtual bool isexponential()	  const {return false;}
    virtual bool ispositive()		  const {return false;}
    virtual bool has_characteristic() const {return false;}
    virtual bool has_analyticals() 	  const {return false;}
    
    virtual void simula(montecarlo* monte, unsigned numpaths, unsigned& stdim) {}
    
    /// The parameters of the stochastic process
    virtual parameters params()  {QM_FAIL("Not implemented");}
    
    /// The stochastic factors
    virtual parameters factors() {QM_FAIL("Not implemented");}
    
    /// The market price of risk parameters
    virtual parameters mktrisks() {QM_FAIL("Not implemented");}
    
    virtual qm_real	exponential_convexity(qm_real t, qm_real t1) const {QM_FAIL("Cannot evaluate exponential convexity");}
    
    qm_string  name()    const {return this->code() + " stochastic process";}
    //
    const Paths&	get_paths() const {return m_paths;}
    //virtual PATH generatePath(PathGenerator gen) const;
    virtual momentstype moments(unsigned i, qm_real t1, qm_real t2) const {QM_FAIL("Could not evaluate moments");}
    
    qm_real rateDiscount(qm_real T) const {return 1;}
    qm_real convDiscount(qm_real T) const {return 1;}
    
    virtual DIST1 marginal(unsigned i, qm_real t1, qm_real t2) const {QM_FAIL("Analytical marginal distribution not available");}
protected:
	Paths	m_paths;
	
	istochastic(){}
	virtual void precalc() {}
};

QM_NAMESPACE_END2

/*! @} */



#endif // __ISTOCHASTIC_PROCESS_QM_HPP__


