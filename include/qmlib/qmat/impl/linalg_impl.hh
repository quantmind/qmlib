


#ifndef		__LINALG_IMPL_QMAT_HPP__
#define		__LINALG_IMPL_QMAT_HPP__


QM_NAMESPACE2(math)


	
template<typename T>
inline linalg_return linalg<T>::solve_lower_triangular(const ltriang& lhs, const qmat& b, qmat& x)  {
	unsigned R = lhs.rows();
	unsigned C = b.cols();
	QMAT_PRECONDITION(R == b.rows() && R > 0,"Could not use forward subsitution in solving linear system.");
	QMAT_PRECONDITION(R == x.rows() && x.cols() == b.cols(),"Could not use forward subsitution in solving linear system.");
	numtype t;
	for(unsigned c=0;c<C;++c)  {
		x(0,c) = b(0,c)/lhs(0,0);
		for(unsigned r=1;r<R;++r)  {
			t = 0;
			for(unsigned k=0;k<r;++k) t += lhs(r,k)*x(k,c);
			x(r,c) = (b(r,c) - t)/lhs(r,r);
		}
	}
	return linalg_return();
}
	
template<typename T>
inline linalg_return linalg<T>::solve_upper_triangular(const utriang& lhs, const qmat& b, qmat& x)  {
	unsigned N = lhs.rows();
	QM_REQUIRE(N == b.rows() && N == x.rows() && N > 0,"Could not use backward subsitution in solving linear system.");
	numtype sum;
	unsigned k;
	int r;
	x(N-1) = b(N-1)/lhs(N-1,N-1);
	for(r=N-2;r>=0;r--)  {
		sum = 0;
		for(k=r+1;k<N;k++) sum += lhs(r,k)*x(k);
		x(r) = (b(r) - sum)/lhs(r,r);
	}
	return linalg_return();
}
	
template<typename T>
inline linalg_return linalg<T>::cholesky(const symat& A, ltriang& L)  {
	unsigned N = A.rows();
	QMAT_PRECONDITION(N == L.rows(),"Lower triangular matrix with different dimension");
	if(N == 0) return linalg_return("Nothing to do. Zero element matrix.");
	unsigned i,j;
	int k;
	numtype sum = quiet_sqrt(A(0,0));
	if(sum == 0) return linalg_return(false,"Symmetric matrix not positive definite");
	L(0,0) = sum;
	for(j=1;j<N;j++) L(j,0) = A(0,j)/sum;
	
	for(i=1;i<N;i++)  {
		sum = A(i,i);
		for(k=i-1;k>=0;k--) sum -= L(i,k)*L(i,k);
			sum = quiet_sqrt(sum);
		if(sum == 0) return linalg_return(false,"Symmetric matrix not positive definite");
		L(i,i) = sum;
		for(j=i+1;j<N;j++)  {
			for(sum = A(j,i), k=i-1;k>=0;k--) sum -= L(i,k)*L(j,k);
			L(j,i) = sum / L(i,i);
		}
	}
	return linalg_return();
}


template<typename T>
inline linalg_return linalg<T>::QR(const qmat& A, const qmat& Q, utriang& R)  {
	unsigned N = A.rows();
	return linalg_return(false,"QR decomposition not available yet");
}

	
template<typename T>
inline linalg_return linalg<T>::solve(const symat& A, const qmat& b, qmat& x)  {
	unsigned N = A.rows();
	ltriang L(N);
	qmat    y(N);
	linalg_return ret;
	cholesky(A,L);
	ret = solve_lower_triangular(L,b,y);
	ret = solve_upper_triangular(L.transpose(),y,x);
	return ret;
}


/// \brief solve tridiagonal system using Thomas algorithm
template<typename T>
inline linalg_return linalg<T>::solve(const trimat& A, const qmat& b, qmat& x)  {
    //Forward substitution
	unsigned N = A.rows();
	if(N == 0) return linalg_return(true, "Nothing to do");
    T bet = A(0,0);
    if(!bet) return linalg_return(false,"Failed while solving tridiagonal system");
    qmat g(N);
    
    //Forward substitution
    x(0) = b(0)/bet;
    for(unsigned i=1;i<N;i++)  {
    	g(i)  = A(i-1,i)/bet;
    	bet    = A(i,i) - A(i,i-1)*g(i);
    	if(!bet) return linalg_return(false,"Failed while solving tridiagonal system");
    	x(i)   = (b(i) - A(i,i-1)*x(i-1))/bet;
    }
    //
    //..Backward substitution
    for(int i=N-2;i>=0;i--)
    	x(i) -= g(i+1)*x(i+1);
    
    return linalg_return();
}
	
template<typename T>
inline linalg_return linalg<T>::least_square(const qmat& A, const qmat& b, qmat& x)  {
	unsigned N = A.rows();
	unsigned M = A.cols();
	symat sq(M);
	qmat  d(M);
	typename qmat::transpos AT(A.transpose());
	sq = mmult(AT,A);
	d  = mmult(AT,b);
	return linalg<T>::solve(sq,d,x);
}


template<typename T>
inline linalg_return linalg<T>::inverse(const diag_mat& A, diag_mat& Ai)  {
	unsigned N = A.rows();
	if(!N) return linalg_return(false,"Nothing to do");
	for(unsigned i=0;i<N;i++)  {
		T v = A[i];
		if(!v) return linalg_return(false,"Singular matrix. Cannot invert");
		Ai[i] = 1.0/v;
	}
	return linalg_return();
}

QM_NAMESPACE_END2


#endif	//	__LINALG_IMPL_QMAT_HPP__

