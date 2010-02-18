
#ifndef   __DISTRIBUTION_BASE_QM_HPP__
#define   __DISTRIBUTION_BASE_QM_HPP__



#include <qmlib/complex.hpp>
#include <qmlib/qmat/tiny.hpp>
#include <qmlib/corelib/info/params.hpp>
#include <qmlib/math/numbers/constants.hpp>
#include <boost/math/special_functions/erf.hpp>
//#include <qmlib/math/SpecialFunctions.h>

/*! \defgroup distributions qmlib distributions

    several distributions with closed form density

    @{
*/

/// \file
/// \brief Interface and base classes for distributions




QM_NAMESPACE2(math)


template<unsigned N> class idistribution;

typedef QM_SMART_PTR(idistribution<1u>) DIST1;


template<unsigned N>
struct distTraits  {
	typedef const tinyvec<qm_real,N>&		inputtype;
	typedef tinyvec<qm_real,N>				outtype;
	typedef tinymat<qm_real,N,N>			covtype;
	typedef const tinyvec<qm_complex,N>&	cplxtype;
};
template<>
struct distTraits<1u>  {
	typedef qm_real		inputtype;
	typedef qm_real		outtype;
	typedef qm_real		covtype;
	typedef qm_complex	cplxtype;
};


template<unsigned N>
class idistribution: public icodename  {
public:
	typedef distTraits<N>						dist_traits;
	typedef typename dist_traits::inputtype		inputtype;
	typedef typename dist_traits::outtype		outtype;
	typedef typename dist_traits::covtype		covtype;
	typedef typename dist_traits::cplxtype		cplxtype;
	static const unsigned dimension = N;
	
	unsigned dim() const {return dimension;}
	virtual outtype     mean()     				const {return 0;}
	virtual covtype     variance() 				const {return 0;}
	virtual qm_real     skewness() 			 	const {return 0;}
	virtual qm_real     excessKurtosis() 		const {return 0;}
	virtual qm_real     cumulative(inputtype x) const {return 1;}
	virtual qm_real     lndensity(inputtype x)	const {return 1;}
	virtual qm_real     density(inputtype x)	const {return exp(this->lndensity(x));}
	
	/// \brief The inverse of the cumulative probability function
	/// @param u The quantile, a number between 0 and 1.
	virtual qm_real     icumulative(qm_real u)  const {QM_FAIL("Not available");}
	
	virtual qm_complex  characteristic_exp(const cplxtype& u) const {QM_FAIL("Not available");}
	
	virtual parameters params()  {QM_FAIL("No parameters");}
	
	qm_complex characteristic_func(const cplxtype& u) const {return std::exp(this->characteristic_exp(u));}
	covtype   stdev() const {return sqrt(this->variance());}
};


	
/// \brief base class for univariate statistical distributions
class distribution_root : public idistribution<1u>, public observer {
public:
	parameters params()     {return m_parameters;}
	void update() {this->precalc();}
protected:
	parameters	m_parameters;
	virtual void precalc() {}
	
	distribution_root(){}
	void check_u(qm_real u) const {
		QM_REQUIRE(u > 0.0 && u < 1.0,"quantile must be between 0 and 1");
	}
	distribution_root(const parameters& pa):m_parameters(pa)  {
		m_parameters.registerObserver(this);
		m_parameters.set_locked(true);
	}
};
	
	
/** \brief The normal distribution. What more to say!
 * 
 * The normal distribution, also called the Gaussian distribution,
 * is an important family of continuous probability distributions.
 * 
 * \see http://en.wikipedia.org/wiki/Normal_distribution for more information and links
 */
class normal_dist: public distribution_root  {
public:
	normal_dist(qm_real mu = 0, qm_real var = 1) {
		QM_REQUIRE(var>0,"normal variance must be positive");
		this->m_parameters.push_back(parameter::make("mu","Mean",mu));
		this->m_parameters.push_back(parameter::make("var","Variance",var,0));
		this->m_parameters.set_locked(true);
		}
	static DIST1 make(qm_real mu, qm_real var) {
		return DIST1(new normal_dist(mu,var));
	}
	qm_real   mu() 		 const {return this->m_parameters[0]->get_value();}
	qm_real   var()		 const {return this->m_parameters[1]->get_value();}
	qm_real   sigma()    const {return std::sqrt(var());}
	PARAMETER get_mu() 		   {return this->m_parameters[0];}
	PARAMETER get_var()        {return this->m_parameters[1];}
	qm_real   standard_variate(qm_real x) const {return (x - mu())/sigma();}
	qm_real   mean()     const {return mu();}
	qm_real   variance() const {return var();}
				
	qm_real   cumulative(qm_real x) const;
	qm_real   icumulative(qm_real u)  const;
	qm_real   lndensity(qm_real x)  const;
	
	qm_string	code()				const {return "Normal Distribution";}
	
	qm_complex  characteristic_exp(const qm_complex& u) const;
};

/// \brief The log-normal distribution.
///
/// See http://en.wikipedia.org/wiki/Normal_distribution for more information and links
class lognormal_dist: public distribution_root  {
public:
	lognormal_dist(qm_real mu = 0, qm_real std = 1) {
		QM_REQUIRE(std>0,"standard deviation must be positive");
		this->m_parameters.push_back(parameter::make("mu","Mean of log parameter",mu));
		this->m_parameters.push_back(parameter::make("sigma","Standard deviation of log parameter",std,0));
		this->m_parameters.set_locked(true);
		}
	qm_real   mu() 		 const {return this->m_parameters[0]->get_value();}
	qm_real   sigma()    const {return this->m_parameters[0]->get_value();}
	PARAMETER get_mu() 		{return this->m_parameters[0];}
	PARAMETER get_sigma()   {return this->m_parameters[1];}
	
	qm_real   standard_variate(qm_real x) const;
	qm_real   mean()     const {return std::exp(mu() + 0.5*sigma()*sigma());}
	qm_real   variance() const {qm_real m = this->mean(); return (std::exp(sigma()*sigma()) - 1)*m*m;}
				
	qm_real   cumulative(qm_real x) const   {QM_FAIL("not available");}
	qm_real   icumulative(qm_real u)  const {QM_FAIL("not available");}
	qm_real   lndensity(qm_real x)  const;
	
	qm_string	code()				const {return "LogNormal Distribution";}
		
	qm_complex  characteristic_exp(const qm_complex& u) const {QM_FAIL("Not available");}
private:
	qm_real	m_mu;
	qm_real m_std;
};

	
	
/// \brief The Gamma distribution
///
/// See http://en.wikipedia.org/wiki/Gamma_distribution
class gamma_dist: public distribution_root  {
public:
	gamma_dist(qm_real shape = 1, qm_real scale = 1) {
		QM_REQUIRE(shape>0,"shape parameter must be positive");
		QM_REQUIRE(scale>0,"scale parameter must be positive");
		this->m_parameters.push_back(parameter::make("shape","Shape parameter",shape,0));
		this->m_parameters.push_back(parameter::make("scale","Scale parameter",scale,0));
		this->m_parameters.set_locked(true);
	}
	qm_real shape() 		const {return this->m_parameters[0]->get_value();}
	qm_real scale()    		const {return this->m_parameters[1]->get_value();}
	PARAMETER get_shape() 		{return this->m_parameters[0];}
	PARAMETER get_scale()   	{return this->m_parameters[1];}
	qm_real   mean()     		const {return shape()*scale();}
	qm_real   variance() 		const {return shape() * scale() * scale();}
	qm_real   skewness() 		const {return 2.0/shape();}
	qm_real   excessKurtosis() 	const {return 6.0/shape();}
		
	qm_real     cumulative(qm_real x) const;
	qm_real     density(qm_real x)  const;
	qm_real     icumulative(qm_real u) const;
	qm_complex  characteristic_exp(const qm_complex& u) const;
	
	qm_real     lndensity(qm_real x)  const {return std::log(this->density(x));}
	
	qm_string	code()		const {return "Gamma Distribution";}
private:
		
	void check_x(qm_real x) const {
		QM_REQUIRE(x>=0.0,"X value must be non-negative");
	}
};
	
/** \brief Exponential distribution
 * 
 * This distribution is a degenerate gamma_dist with shape parameter equal to 1.
 * See http://en.wikipedia.org/wiki/Exponential_distribution for more details.
 */
class exponential_dist: public distribution_root  {
public:
	exponential_dist(qm_real rate = 1.0)  {
		QM_REQUIRE(rate>0,"rate parameter must be positive");
		this->m_parameters.push_back(parameter::make("rate","Exponential decay rate",rate,0));
		this->m_parameters.set_locked(true);
	}
	qm_real     rate() 		 	  const {return this->m_parameters[0]->get_value();}
	qm_string   code()            const {return "exponential distribution";}
	qm_real     mean()     		  const {return 1.0/rate();}
	qm_real     variance() 		  const {return 1.0/ (rate() * rate());}
	qm_real     skewness() 		  const {return 2.0;}
	qm_real     excessKurtosis()  const {return 6.0;}
					
	qm_real     cumulative(qm_real x)  const {check_x(x); return 1.0 - std::exp(-rate()*x);}
	qm_real     lndensity(qm_real x)   const {check_x(x); return std::log(rate()) - rate()*x;}
	qm_real     icumulative(qm_real u) const {check_u(u); return -std::log(1.0-u)/rate();}
	qm_complex  characteristic_exp(const qm_complex& u) const {return std::log(1.0 - mult_i(u)/rate());}
private:
	void check_x(qm_real x) const {
		QM_REQUIRE(x>=0.0,"X value must be non-negative");
	}
};
	
	
/** \brief Base class for discrete distribution such as Poisson and Binomial
 */
class discrete_distribution: public distribution_root  {
public:
	typedef std::pair<qm_real,qm_real> pdist;
	typedef std::vector<pdist>		   container;
		
	qm_real cumulative(qm_real x)  const;
	qm_real density(qm_real x)     const;
	qm_real lndensity(qm_real x)   const {return std::log(density(x));}
protected:
	mutable container	m_distribution;
	
	virtual const pdist& buildist(qm_uns_long k) const = 0;
};
	
/** \brief The Poisson distribution
 * 
 * See http://en.wikipedia.org/wiki/Poisson_distribution for further details
 */
class poisson_dist: public discrete_distribution  {
public:
	poisson_dist(qm_real lambd = 1)   {
		QM_REQUIRE(lambd>0,"lambda parameter must be positive");
		this->m_parameters.push_back(parameter::make("lambda","Poisson jump intensity",lambd,0));
		this->m_parameters.set_locked(true);
		qm_real d = std::exp(-lambda());
		m_distribution.push_back(pdist(d,d));
	}
	qm_real	  lambda()			const {return this->m_parameters[0]->get_value();}
	qm_real   mean()     		const {return lambda();}
	qm_real   variance() 		const {return lambda();}
	qm_real   skewness() 		const {return 1.0/std::sqrt(lambda());}
	qm_real   excessKurtosis() 	const {return 1.0/lambda();}
private:
	const pdist& buildist(qm_uns_long k) const;
};
	
/** \brief The Binomial distribution
 * 
 * In probability theory and statistics, the binomial distribution is the discrete probability
 * distribution of the number of successes in a sequence of n independent yes/no experiments,
 * each of which yields success with probability p. Such a success/failure experiment is also
 * called a Bernoulli experiment or Bernoulli trial. In fact, when n = 1, the binomial distribution
 * is a Bernoulli distribution.
 * /seealso http://en.wikipedia.org/wiki/Binomial_distribution for further details
 */
class binomial_dist: public discrete_distribution  {
public:
	binomial_dist(unsigned nn = 1, qm_real pp = 0.5)  {
		QM_REQUIRE(nn>0,"nn parameter must be positive");
		QM_REQUIRE(pp>0 && pp<1,"pp parameter must be in (0,1)");
		this->m_parameters.push_back(parameter::make("n","Number of trials",nn,0));
		this->m_parameters.push_back(parameter::make("p","Probability of success",pp,0,1));
		this->m_parameters.set_locked(true);
		qm_real d = std::exp(n() * std::log(1.0 - p()));
		m_distribution.push_back(pdist(d,d));
	}
	qm_real	  n()				const {return this->m_parameters[0]->get_value();}
	qm_real	  p()				const {return this->m_parameters[1]->get_value();}
	qm_real   mean()     		const {return n()*p();}
	qm_real   variance() 		const {return mean()*(1.0 - p());}
	qm_real   skewness() 		const {return (1.0- 2*p())/std::sqrt(this->variance());}
	qm_real   excessKurtosis() 	const {return (1.0 - 6*p()*(1.0-p()))/this->variance();}
private:
	const pdist& buildist(qm_uns_long k) const;
};

QM_NAMESPACE_END2


#endif  //  __DISTRIBUTION_BASE_QM_HPP__

/*! @} */

