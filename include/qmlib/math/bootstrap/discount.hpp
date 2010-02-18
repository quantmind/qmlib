
#ifndef   __BOOTSTRAP_DISCOUNT_QM_HPP__
#define   __BOOTSTRAP_DISCOUNT_QM_HPP__


#include <qmlib/math/bootstrap/bootstrap.hpp>


QM_NAMESPACE2(math)



template<class S, booststrap_type D>
inline void discount_bootstrap<S,D>::build(const typename discount_bootstrap<S,D>::lhstype& lhs,
										   const typename discount_bootstrap<S,D>::rhstype& rhs,
										   const typename discount_bootstrap<S,D>::vectype& trhs)  {

	unsigned N     = lhs.rows();
	unsigned K     = rhs.cols();
	unsigned M     = m_support.size();
	unsigned start = M - N;
	if(!N || !K) return;
	
	vectype					  F(N),b(N),bt(K),dx(N),dd(M),OJ(N,K),J(N,N);
	qmatrix<numtype,diagonal> db(N),dbt(K);
	
	// Fill the off sensitivity matrix.
	// This matrix depends only upon the x-values of the spline
	m_offsens.resize(K,N);
	unsigned i,k;
	for(k=0;k<K;k++)  {
		dd.fill(0);
		m_support.dvdy(trhs[k],dd);
		for(i=0;i<N;i++)
			m_offsens(k,i) = dd(i+start);
	}

	qm_real y,yold,t,nb,cb;
	qm_real tol  = 1;
	unsigned ite = 0;
	qm_real  tole     = m_solver.tolerance();
	unsigned itemax   = m_solver.maxiter();
	
	// Now lets get cracking.. bootstrap!!!
	while(tol > tole)  {
		ite++;
		QM_REQUIRE(ite<=itemax,"Boostrapping algorithm failed. Too many iterations.");
		
		// Fill the discount factor and first derivative with respect the spline variable
		// at the off nodes points
		for(unsigned k=0;k<K;k++)  {
			t      = trhs[k];
			y      = m_support.value(t);
			bt[k]  = function_type::func(y,t);
			dbt[k] = function_type::dfdx(y,t);
		}
		
		// Fill the discount factor and first derivative with respect the spline variable
		// at nodes points
		for(unsigned i=0;i<N;i++)  {
			t     = m_support.xval(i+start);
			y     = m_support.yval(i+start);
			b[i]  = function_type::func(y,t);
			db[i] = function_type::dfdx(y,t);
		}
		F  = mmult(lhs,b) + mmult(rhs,bt);
		OJ = mmult(rhs,dbt);
		
		// This doesn't work because it access zero elements in the lower_triangular.
		// It could be fixed easily introducing non-optimal code.
		//J  = mmult(cflow,db) + mmult(OJ,m_offsens);
		
		// I restor to Ctran for the time beeing...
		J  = mmult(OJ, m_offsens);
		for(unsigned i=0;i<N;i++)
			for(unsigned j=0;j<=i;j++)
				J(i,j) += lhs(i,j)*db[j];
	
		linalg<qm_real>::solve(J,F,dx);
		tol = 0;
		for(unsigned i=0;i<N;i++)  {
			t    = m_support.xval(i+start);
			yold = m_support.yval(i+start);
			y    = yold - dx[i];
			nb   = function_type::func(y,t);
			cb   = nb - b[i];
			tol += cb*cb;
			m_support.set_yval(i+start,y);
		}
		tol = std::sqrt(tol/N);
	}
	m_solver.set_iter(ite);
	m_solver.set_tole(tol);
}


QM_NAMESPACE_END2


//
#endif  //  __BOOTSTRAP_DISCOUNT_QM_HPP__
//
