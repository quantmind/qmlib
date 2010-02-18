



#ifndef __STOCHASTIC_PROCESS_QM_HPP__
#define __STOCHASTIC_PROCESS_QM_HPP__


#include <qmlib/math/monte/all.hpp>

/*! \defgroup stoch Stochastic process library

    @{
*/


/**\file
 * \brief Interface and Base class for stochastic processes
 */


QM_NAMESPACE2(math)


/** \brief Interface class for a general multivariate stochastic process
 */
class stochastic: public istochastic, public observer, public observable  {
public:
	typedef istochastic					basestoch;
	typedef basestoch::momentstype		momentstype;
	
    parameters params()   {return m_params;}
protected:
	parameters		m_params;
	void add(PARAMETER p) {QM_REQUIRE(p,"Parameter not defined"); m_params.push_back(p);}
	stochastic(){}
};


QM_NAMESPACE_END2

/*! @} */



#endif // __STOCHASTIC_PROCESS_QM_HPP__


