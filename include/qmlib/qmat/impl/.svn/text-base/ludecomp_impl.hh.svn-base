


#ifndef		__LUDECOMP_IMPL_QMAT_HPP__
#define		__LUDECOMP_IMPL_QMAT_HPP__


QM_NAMESPACE2(math)



template<typename T>
inline void LUdecomp<T>::doit()  {
	if(!m_lu.is_square())  {
		m_ret = linalg_return(false,"LU decomposition failed because matrix is not square");
		return;
	}
	unsigned N = m_lu.rows();
	if(!N)  {
		m_ret = linalg_return(false,"Nothing to do");
		return;
	}
	m_indx.resize(N,1);
	qmat pivot(N);
	T big,dum,sum,temp;
	unsigned i,j,k,imax=0;
	
	for(i=0;i<N;i++)  {
		big = 0.0;
		for(j=0;j<N;j++)
			if((temp=std::fabs(m_lu(i,j))) > big) big = temp;
		if(big == 0.0)  {
			m_ret = linalg_return(false,"LU decomposition: singular matrix");
			return;
		}
		pivot[i] = 1.0/big;
	}
	
	// Loop over the columns, Crout's method
	for(j=0;j<N;j++)  {
		for(i=0;i<j;i++)  {
			sum = m_lu(i,j);
			for(k=0;k<i;k++) sum -= m_lu(i,k)*m_lu(k,j);
			m_lu(i,j) = sum;
		}
		
		// Initialize the search for largest pivot element
		big = 0.0;
		for(i=j;i<N;i++)  {
			sum = m_lu(i,j);
			for(k=0;k<j;k++)
				sum -= m_lu(i,k)*m_lu(k,j);
			m_lu(i,j) = sum;
			if((dum=pivot[i]*std::fabs(sum)) >= big)  {
				big  = dum;
				imax = i;
			}
		}
		
		// We need to change the rows
		if(j != imax)  {
			for(k=0;k<N;k++)  {
				dum = m_lu(imax,k);
				m_lu(imax,k) = m_lu(j,k);
				m_lu(j,k)    = dum;
			}
			//d = -d;
			pivot[imax] = pivot[j];
		}
		m_indx[j] = imax;
		if(j != N-1)  {
			dum = 1.0/m_lu(j,j);
			for(i=j+1;i<N;i++)  m_lu(i,j) *= dum;
		}
	}
	m_ret = linalg_return();
}


template<typename T>
inline void LUdecomp<T>::backsub(typename LUdecomp<T>::qmat& x) const  {
	int N = m_lu.rows();
	int i,j,ip;
	int ii=-1;
	qm_real  sum;
	
	// when ii is non-negative, it will become the
	// index of the first nonvaniscing element of x.
	
	// Forward substitution, and unscramble the permutation
	for(i=0;i<N;i++)  {
		ip    = m_indx(i);
		sum   = x[ip];
		x[ip] = x[i];
		if(ii>=0)
			for(j=ii;j<i;j++) sum -= m_lu(i,j)*x[j];
		else if(sum) ii=i;
		x[i] = sum;
	}
	
	//backward substitution
	for(i=N-1;i>=0;i--)  {
		sum = x[i];
		for(j=i+1;j<N;j++) sum -= m_lu(i,j)*x(j);
		x(i) = sum/m_lu(i,i);
	}
}


template<typename T>
inline linalg_return LUdecomp<T>::solve(qmat& x) const  {
	if(!m_ret) return m_ret;
	this->backsub(x);
	return m_ret;
}


template<typename T>
inline linalg_return LUdecomp<T>::inverse(typename LUdecomp<T>::qmat& Ai) const  {
	if(!m_ret) return m_ret;
	unsigned N = m_lu.rows();
	qmat col(N);
	for(unsigned j=0;j<N;j++)  {
		col.fill(0);
		col[j] = 1;
		this->backsub(col);
		for(unsigned i=0;i<N;i++) Ai(i,j) = col(i);
	}
	return m_ret;
}




template<typename T>
inline typename LUdecomp<T>::ltriang LUdecomp<T>::L() const {
	unsigned N = m_lu.rows();
	ltriang  lt(N);
	for(unsigned i=0;i<N;i++)  {
		for(unsigned j=0;j<i;j++)
			lt(i,j) = m_lu(i,j);
		lt(i,i) = 1;
	}
	return lt;
}


template<typename T>
inline typename LUdecomp<T>::utriang LUdecomp<T>::U() const {
	unsigned N = m_lu.rows();
	utriang  ut(N);
	for(unsigned i=0;i<N;i++)
		for(unsigned j=i;j<N;j++)
			ut(i,j) = m_lu(i,j);
	return ut;
}


QM_NAMESPACE_END2


#endif	//	__LUDECOMP_IMPL_QMAT_HPP__
