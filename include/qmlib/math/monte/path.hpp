//
/// \file
/// \ingroup math
//
//
#ifndef __PATH_QM_HPP__
#define __PATH_QM_HPP__


#include <qmlib/math/random/all.hpp>
#include <qmlib/math/tools/timegrid.hpp>
#include <qmlib/irates.hpp>


/*! \defgroup monte Math MonteCarlo library

    This library handles montecarlo simulation.
    It defines
     - montecarlo class which manage simulation
     - path a class for a single path

    @{
*/


/**\file
 * \brief Monte Carlo path classes
 */


QM_NAMESPACE2(math)


// Some forward declarations for qmlib.math
class montecarlo;
class path;
class diffusion_path;
class jumping_path;
class Paths;
class istochastic;

typedef QM_SMART_PTR(istochastic) 		STOCHASTIC;
typedef QM_SMART_PTR(path)				PATH;
typedef QM_SMART_PTR(jumping_path)		JPATH;


/** \brief Path base class
 */
class path_base : public icodename  {
public:
	path_base(TIMEGRID tg):m_tg(tg){QM_REQUIRE(m_tg && m_tg->length()>1,"No time grid");}
	path_base(const path_base& rhs):m_tg(rhs.m_tg){}
	path_base& operator = (const path_base& rhs) {m_tg = rhs.m_tg; return *this;}
	
	virtual unsigned numvar()	 const  {return 1;}
	virtual unsigned numpaths()	 const  {return 1;}
	virtual unsigned totaldim()  const  {return 0;}
	virtual bool     diffusion() const  {return true;}
	unsigned timedim()   const  {return m_tg->length();}
	TIMEGRID   grid()    const  {return m_tg;}
protected:
	path_base(){}
	TIMEGRID	m_tg;
};



/** \brief Base class for a single process path
 */
class path : public path_base  {
public:
	/// \brief the path holder class
	typedef matrix_struct<column_row>			mstructure;
	typedef qmatrix<qm_real, mstructure >		holder;
	typedef dataserie<qm_real,false,qm_real>	jump_container;
	typedef std::vector<jump_container>			jump_paths;
	
	path(TIMEGRID tg, unsigned numpaths):path_base(tg){
		QM_REQUIRE(numpaths>0,"Number of paths must be positive");
		m_paths.resize(this->timedim(),numpaths);
	}
	
	unsigned numpaths()	 const  {return m_paths.cols();}

	qm_string tostring() const {return this->name();}
	
	const holder& pathholder() const {return m_paths;}
	
	virtual PATH copy() const {QM_FAIL("notimplemented");}

	virtual const jump_paths& jumpcontainer() const {QM_FAIL("not available");}
protected:
	holder m_paths;
};


/// \brief Simple diffusion path
///
/// Building block for diffusion processes
class diffusion_path : public path  {
public:
	diffusion_path(TIMEGRID tg, unsigned numpaths):path(tg,numpaths){}
	unsigned  totaldim()    const    {return this->timedim()-1;}
	qm_string code()        const    {return "diffusion path";}
	//qm_real	  get_loglik()	const;
	//PATH copy() const;
protected:
};

/// \brief Path for a Jump process
///
/// Building block for jump-diffusion processes
class jumping_path : public path  {
public:
	jumping_path(TIMEGRID tg, unsigned numpaths):path(tg,numpaths),m_flag(0){}

	unsigned  totaldim()  const    {return m_flag*m_totaldim;}
	bool      diffusion() const    {return false;}
	//void	 addjump(qm_real arrival, qm_real jump) {m_jumping.addkeyval(arrival,jump);}
	void      togrid();

	const jump_paths& jumpcontainer() const {return m_jumpings;}
	//PATH copy() const;
protected:
	unsigned	   m_totaldim;
	jump_paths	   m_jumpings;
	unsigned	   m_flag;
};



/**\brief class used to create paths for multi factor processs
 * 
 * This class contains a vector of multipath
 */
class Paths : public path_base, public base_container<PATH> {
public:
	typedef base_container<PATH>			base_class;
	
	Paths(){}
	Paths(TIMEGRID tg, unsigned numpath):path_base(tg),m_numpaths(numpath){}
	Paths(const Paths& rhs):path_base(rhs),base_class(rhs),m_numpaths(rhs.m_numpaths){}
	
	Paths& operator = (const Paths& rhs)  {
		path_base::operator = (rhs);
		base_class::operator = (rhs);
		m_numpaths = rhs.m_numpaths;
		return *this;
	}

	//Paths	   copy() const;
	void	   set(TIMEGRID tg, unsigned numpath);

	qm_string  tostring() const {return "Multi Path container for " + object_to_string(this->size()) + " factors processes";}

	PATH	   add_diffusion() const;
	PATH	   add_jumping() const;

	unsigned numpaths()	 const  {return m_numpaths;}
	PATH     get_slow(unsigned i) const {QM_REQUIRE(i<this->size(),"Out of bound"); return this->getd(i);}
private:
	unsigned 		m_numpaths;
};

    
QM_NAMESPACE_END2

/*! @} */


#endif // __PATH_QM_HPP__


