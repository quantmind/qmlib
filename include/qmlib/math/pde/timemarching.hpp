

#ifndef __TIME_MARCHING_QM_HPP__
#define __TIME_MARCHING_QM_HPP__


#include <qmlib/math/pde/structured_grid.hpp>
#include <qmlib/math/tools/timecoef.hpp>
#include <qmlib/qmat/linalg.hpp>
//#include <qmlib/tools.hpp>


/**\file
 * \brief Time marching algorithms
 * \ingroup pde
 */




QM_NAMESPACE2(math)

/**\brief type of timemarching algorithms
 * \ingroup pde
 */
enum timeschemes  {
	_euler = 0,
	_henn,
	_trapezoidal,
	_unknown,
};

template<timeschemes T, class M> class timemarching;



/** \brief Result for time marching algorithm
 * \ingroup pde
 * 
 * This class contains useful informations about the results of
 * a time marching algorithm.
 */
class time_marching_result  {
public:
	time_marching_result(TIMEGRID tg, qm_real dtmax1);
	time_marching_result(const time_marching_result& rhs):m_N(rhs.m_N),m_dt(rhs.m_dt),m_cfl(rhs.m_cfl),m_perf(rhs.m_perf){}
	
	time_marching_result& operator = (const time_marching_result& rhs)  {
		m_N		= rhs.m_N;
		m_dt	= rhs.m_dt;
		m_cfl   = rhs.m_cfl;
		m_perf	= rhs.m_perf;
		return *this;
	}
	
	unsigned  steps() 		const { return m_N;}
	qm_real   dt()	 		const { return m_dt;}
	qm_real   time()  		const { return m_N*m_dt;}
	qm_real   cfl()			const { return m_cfl;}
	qm_real	  performance() const { return m_perf;}
	qm_string tostring()	const { return object_to_string(*this);}
	
	void	 start()  {m_temp = clock();}
	void	 end()    {m_perf = clock() - m_temp;}
	
	friend std::ostream& operator<<(std::ostream& os, const time_marching_result& og)  {
	    os <<  og.tostring() << std::endl;
	    return os;
	}
private:
	unsigned	m_N;
	qm_real		m_dt;
	qm_real     m_cfl;
	qm_real		m_perf;
	qm_real 	m_temp;
};


/** \brief The time marching structure
 * \ingroup pde
 * 
 * This struct advance the solution of a system of PDEs in time.
 * Several time marching algorithms can be used.
 */
struct time_marching  {
	
	/// \brief the general time stepping algorithm
	///
	/// @param tm the time marching algorithm
	/// @param m  the pde model
	/// @param dt time step
	/// @param N  number of time steps to advance solution
	/// @return a time_marching_result object
	template<timeschemes T, class M>
	static time_marching_result advance(M& m, const TIMEGRID& tg)  {
		typedef M							model;
		typedef typename model::numtype		numtype;
		typedef typename model::qmat		qmat;
		
		QM_REQUIRE(m.isready(),"Model not ready for calculation. Need to set initial condition!!!");
		m.set_timegrid(tg);
		
		timemarching<T,M> tm(m);
		m.clear();
		time_marching_result tr(tg,m.dtmax());
		qmat unk0(m.get_initial().duplicate());
		qmat unk1(m.final());
		
		tr.start();
		unsigned N = tg->length();
		if(N > 0)  {
			for(unsigned i=1;i<N-1;++i)  {
				tm.advance(i,unk0,unk1,m);
				swapequal(unk0,unk1);
			}
			tm.advance(N-1,unk0,unk1,m);
		}
		else unk1  = unk0;
		
		tr.end();
		return tr;
	}
};


inline time_marching_result::time_marching_result(TIMEGRID tg, qm_real dtmax1):m_perf(0)  {
	m_N  = tg->length()-1;
	m_dt = tg->dtmax();
	m_cfl = (m_dt/dtmax1);
}







QM_NAMESPACE_END2




QM_NAMESPACE


template<>
struct object_to_string_o<QM_FROM_NAMESPACE2(math)time_marching_result >  {
	static qm_string get(const QM_FROM_NAMESPACE2(math)time_marching_result& tmr)  {
		return "time_marching_result ( steps = " + object_to_string(tmr.steps()) +
									", dt = " + object_to_string(tmr.dt()) +
									", cfl = " + object_to_string(tmr.cfl()) +
									", time = " + object_to_string(tmr.time()) +
									", performance = " + object_to_string(tmr.performance()) +
									" )";
	}
};


QM_NAMESPACE_END


#include<qmlib/math/pde/timemarching/trapezoidal.hpp>


#endif // __TIME_MARCHING_QM_HPP__

