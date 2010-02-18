


#ifndef   __YIELD_COMPOSITE_IMPL_QM_HPP__
#define   __YIELD_COMPOSITE_IMPL_QM_HPP__


#include <qmlib/qmat/linalg.hpp>


QM_NAMESPACE2(finance)


template<class B, discount_type T>
inline qm_real
yieldcomposite<B,T>::dft(qm_real t)	const {
	return disc_func::df(m_support->value(t),t);
}


template<class B, discount_type T>
inline bool 
yieldcomposite<B,T>::addtoinstruments(const typename yieldcomposite<B,T>::key_type& key,
									  const typename yieldcomposite<B,T>::ELEMENT& el) {
	m_used_insts.addkeyval(key,el);
	return true;
	/*
	if(!this->size())  {
		m_used_insts.addkeyval(key,el);
		return true;
	}
	CASHFLOW cf = el->cashflow(this->date());
	
	if(el->curvepriority())
	return false;
	*/
}


template<class B, discount_type T>
inline void yieldcomposite<B,T>::build()  {
	unsigned N = this->size();
	if(N == 0) return;
	
	int      j,idx;
	qdate    dte;
	CASHFLOW cf;
	element_type* el;
	qm_real    ra,t1;
	qdate	   anchor = this->date();
	m_support 		  = SUPPORT(new support_type);
	support_type* sup = m_support.get();
	sup->add(0,disc_func::fun(1,0));
	
	ycsuptraits::dates_type		dates;
	
	qm_real t0  = 0;
	qm_real df1 = 1;
	// First loop over instruments
	// Find non-support dates
	
	m_odte.clear();
	for(const_iterator it = this->begin(); it!=this->end(); ++it)  {
		el   = it->value().get();
		ra   = el->internalccr();
		t1   = this->dcf(it->key());
		df1 *= std::exp(-ra*(t1-t0));
		t0   = t1;
		// add to support object
		sup->add(t1,disc_func::fun(df1,t1));
		
		cf = el->cashflow(anchor);
		dates.add(it->key());
		for(CASHFLOW::const_iterator ir = cf.begin();ir!=cf.end();++ir)  {
			dte = ir->key();
			j = dates.search(dte);
			if(j >= 0) continue;
			if(!m_odte.contains(dte))
				m_odte.add(dte);
		}
	}

	unsigned K = m_odte.size();
	QM_REQUIRE(K,"Zero non support points. Cannot solve system");

	multcash m;
	m_matrix.resize(N,N);
	m_offmat.resize(N,K);
	m_matrix.fill(m);
	m_offmat.fill(m);
	
	// Fill cash flow matrices
	unsigned i = 0;
	for(const_iterator it = this->begin(); it!= this->end(); ++it)  {
		el = it->value().get();
		cf = el->cashflow(this->date());
		for(CASHFLOW::const_iterator ir = cf.begin();ir!=cf.end();++ir)  {
			j = dates.search(ir->key());
			if(j >= 0)  {
				m_matrix(i,j).add(ir->value());
			}
			else  {
				idx = m_odte.search(ir->key());
				m_offmat(i,idx).add(ir->value());
			}
		}
		i++;
	}
	
	this->build_offsens();
}



template<class B, discount_type T>
inline void yieldcomposite<B,T>::refresh()  {
	QM_USING_NAMESPACE2(math);
	
	unsigned N = m_offmat.rows();
	unsigned K = m_offmat.cols();
	if(!N || !K) return;

	// Get the matrices
	this->build_cfmat();
	this->build_cfoff();
		
	rmat F(N),b(N),bt(K),OJ(N,K),J(N,N),dx(N);
	qmatrix<qm_real,diagonal> db(N),dbt(K);

	qm_real x,t,nb,cb;
	qm_real tol = 1;
	unsigned ite = 0;
	qm_real  tole   = this->solver().tolerance();
	unsigned itemax = this->solver().maxiter();
	support_type* sup = m_support.get();
	
	// Now lets get cracking.. bootstrap!!!
	while(tol > tole)  {
		ite++;
		QM_REQUIRE(ite<=itemax,"Boostrapping algorithm failed. Too many iterations.");
		
		// Fill the discount factor and first derivative with respect the spline variable
		// at the off nodes points
		for(unsigned i=0;i<m_odte.size();i++)  {
			t      = this->dcf(m_odte[i]);
			x      = sup->value(t);
			bt[i]  = disc_func::df(x,t);
			dbt[i] = disc_func::dfdx(x,t);
		}
		
		// Fill the discount factor and first derivative with respect the spline variable
		// at nodes points
		for(unsigned i=0;i<N;i++)  {
			b[i]  = disc_func::df(sup->yval(i+1),sup->xval(i+1));
			db[i] = disc_func::dfdx(sup->yval(i+1),sup->xval(i+1));
		}
		F  = mmult(m_cflow,b) + mmult(m_cfoff,bt);
		OJ = mmult(m_cfoff,dbt);
		
		// This doesn't work because it access zero elements in the lower_triangular.
		// It could be fixed easily introducing non-optimal code.
		//J  = mmult(cflow,db) + mmult(OJ,m_offsens);
		
		// I restor to Ctran for the time beeing...
		J  = mmult(OJ,m_offsens);
		for(unsigned i=0;i<N;i++)
			for(unsigned j=0;j<=i;j++)
				J(i,j) += m_cflow(i,j)*db[j];
	
		linalg<qm_real>::solve(J,F,dx);
		tol = 0;
		for(unsigned i=0;i<N;i++)  {
			x    = sup->yval(i+1)-dx[i];
			nb   = disc_func::df(x,sup->xval(i+1));
			cb   = nb - b[i];
			tol += cb*cb;
			sup->set_yval(i+1,x);
		}
		tol = std::sqrt(tol/N);
	}
	this->m_solve.set_iter(ite);
	this->m_solve.set_tole(tol);
}

template<class B, discount_type T>
inline typename yieldcomposite<B,T>::cfmat_type
yieldcomposite<B,T>::cfmat()  {
	this->build_cfmat();
	return cfmat_type(m_cflow,true);
}

template<class B, discount_type T>
inline typename yieldcomposite<B,T>::rmat
yieldcomposite<B,T>::cfoff()  {
	this->build_cfoff();
	return rmat(m_cfoff,true);
}

template<class B, discount_type T>
inline typename yieldcomposite<B,T>::rmat
yieldcomposite<B,T>::offsens()  {
	this->build_offsens();
	return rmat(m_offsens,true);
}

template<class B, discount_type T>
inline void yieldcomposite<B,T>::build_cfmat()  {
	unsigned N = m_matrix.rows();
	m_cflow.resize(N,N);
	for(unsigned i=0;i<m_matrix.size();i++)
		m_cflow[i]  = m_matrix[i].cash();
}

template<class B, discount_type T>
inline void yieldcomposite<B,T>::build_cfoff()  {
	unsigned N = m_offmat.rows();
	unsigned M = m_offmat.cols();
	m_cfoff.resize(N,M);
	for(unsigned i=0;i<m_offmat.size();i++)
		m_cfoff[i]  = m_offmat[i].cash();
}

template<class B, discount_type T>
inline void yieldcomposite<B,T>::build_offsens()  {
	typedef ycsuptraits::dates_type::const_iterator date_iterator;
	unsigned N = m_offmat.rows();
	unsigned M = m_offmat.cols();
	m_offsens.resize(M,N);
	support_type* sup = m_support.get();
	unsigned i = 0;
	m_dd.resize(N+1,1);
	for(date_iterator it = m_odte.begin(); it!= m_odte.end(); ++it)  {
		m_dd.fill(0);
		sup->dvdy(this->dcf(*it),m_dd);
		for(unsigned j=0;j<N;j++)
			m_offsens(i,j) = m_dd(j+1);
		i++;
	}
}



QM_NAMESPACE_END2


//
#endif  //  __YIELD_COMPOSITE_IMPL_QM_HPP__
//
