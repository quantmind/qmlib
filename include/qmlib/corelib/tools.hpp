
#ifndef   __TOOLS_LIGHT_QM_HPP__
#define   __TOOLS_LIGHT_QM_HPP__

#include<qmlib/corelib/tools/string.hpp>

QM_NAMESPACE


class itersolver: public basedes  {
public:
	itersolver(unsigned itemax = 20, qm_real tole = 1.0e-10):m_tole(tole),m_tol(0),m_maxiter(itemax),m_iterations(0){}
	itersolver(const itersolver& rhs):m_tole(rhs.m_tole),m_tol(rhs.m_tol),m_maxiter(rhs.m_maxiter),m_iterations(rhs.m_iterations){}
	
	unsigned maxiter() 	 const {return m_maxiter;}
	void set_maxiter(unsigned mi) {m_maxiter = mi;}
	
	qm_real tolerance() const {return m_tole;}
	void set_tolerance(qm_real mi) {m_tole = mi;}

	unsigned iter() 	 const {return m_iterations;}
	void set_iter(unsigned mi) {m_iterations = mi;}
	
	qm_real tole() const {return m_tol;}
	void set_tole(qm_real mi) {m_tol = mi;}
	
	qm_string tostring() const {
		return "max iter " + object_to_string(m_maxiter) + 
			   ", tolerance " + object_to_string(m_tole);
	}
protected:
	qm_real  m_tole,m_tol;
	unsigned m_maxiter;
	unsigned m_iterations;
};

QM_NAMESPACE_END


#endif  //  __TOOLS_LIGHT_QM_HPP__
