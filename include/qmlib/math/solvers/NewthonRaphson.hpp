//
//
#ifndef   __NEWTHON_RAPHSON_QM_HPP__
#define   __NEWTHON_RAPHSON_QM_HPP__
//
//
#include <qmlib/definitions.hpp>



QM_NAMESPACE2(math)


template<typename T = qm_real>
class root_finder_result  {
public:
	typedef T	numtype;
	root_finder_result(unsigned dim, unsigned iter, qm_real tol, bool suc):m_parameters(dim),m_iterations(iter),m_tolerance(tol),m_success(suc){}
	
	unsigned dimension() const {return m_parameters.size();}
	numtype  get(unsigned i) const {QM_REQUIRE(i < this->dimension(),"Out of dimension"); return m_parameters[i];}
	void     set(unsigned i, numtype v) {QM_REQUIRE(i < this->dimension(),"Out of dimension"); m_parameters[i] = v;}
	
	unsigned iterations() const {return	m_iterations;}
	bool     success()    const {return m_success;}
	qm_real  tolerance()  const {return m_tolerance;}
	
	qm_string tostring()  const {return "root_finder_result";}
	
	operator bool () {return m_success;}
	
private:
	std::vector<numtype> 	m_parameters;
	unsigned      			m_iterations;
	qm_real					m_tolerance;
	bool					m_success;
};


template<class T>
class NewthonRaphson1D  {
public:
	typedef T									implementation;
	typedef typename implementation::numtype	numtype;
	typedef root_finder_result<numtype>			result_type;
	typedef QM_SMART_PTR(result_type)			result_type_ptr;
	
	NewthonRaphson1D(const implementation& impl):m_impl(impl){}
	
	result_type_ptr solve(numtype initial_parameter, unsigned iterMax = 100, qm_real tolerance = 1.E-07) const {
		numtype p     = initial_parameter;
		unsigned iter = 0;
		qm_real  tole = 1;
		numtype  dp,F,der;
		
		while(tole > tolerance && iter < iterMax)  {
			F    = m_impl.values(p,der);
			dp   = F/der;
			p   -= dp;
			tole = std::fabs(dp);
			iter++;
		}
		result_type_ptr res(new result_type(1,iter,tole,iter == iterMax ? false : true));
		res->set(0,p);
		return res;
	}
	
private:
	implementation m_impl;
};
	
QM_NAMESPACE_END2


QM_NAMESPACE

typedef QM_SMART_PTR(QM_FROM_NAMESPACE2(math)root_finder_result<qm_real>)  ROOT_RESULT;

QM_NAMESPACE_END


#endif	//	__NEWTHON_RAPHSON_QM_HPP__

