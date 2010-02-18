

#ifndef __MONTECARLO_QM_HPP__
#define __MONTECARLO_QM_HPP__


#include <qmlib/math/monte/istochastic.hpp>


/// \file
/// \brief Montecarlo class
/// \ingroup random


QM_NAMESPACE2(math)

class montecarlo;
typedef QM_SMART_PTR(montecarlo)	MONTECARLO;


/// \brief base class for montecarlo methods
/// \ingroup monte
class montecarlo : public basedes {
public:
	typedef sobol1		default_rndgen;
	
	montecarlo(RNDGEN gen = RNDGEN(), STOCHASTIC p = STOCHASTIC(), bool bridge = true);
	qm_string tostring() const;
	
	template<class C>
	void set_grid(QM_SMART_PTR(C) grid) {
		m_tg = smart_cast<timegrid,C>(grid);
		QM_REQUIRE(m_tg,"Time grid not set");
	}
	
	void simula(unsigned numpaths);
	
    STOCHASTIC		get_process() 						const  {return m_process;}
    void    		set_process(const STOCHASTIC pr)           {m_process = pr;}
    
    RNDGEN      	get_generator() 			const {return m_gen;}
    void         	set_generator(RNDGEN ge)          {if(ge) m_gen = ge;}
    
    bool	      	get_bridge() 			const {return m_brownian;}
    void         	set_bridge(bool br)           {m_brownian = br;}
    
    void			diffusion(PATH pa, unsigned& startdim);
    TIMEGRID		grid()      const    {return m_tg;}
    TIMEGRID		get_grid()           {return m_tg;}
protected:
	STOCHASTIC  		m_process;
	TIMEGRID			m_tg;
	RNDGEN				m_gen;
	bool			    m_brownian;
	
	unsigned setup(unsigned numpaths, unsigned startdim) const;
};


QM_NAMESPACE_END2


#endif // __MONTECARLO_QM_HPP__

