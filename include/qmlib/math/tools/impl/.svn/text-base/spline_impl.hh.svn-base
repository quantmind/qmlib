



QM_NAMESPACE2(math)

inline unsigned cubic_spline::coef(qm_real x, qm_real& u, qm_real& h, qm_real& a, qm_real& b, qm_real& c, qm_real& d) const  {
	if(!m_ready) this->noConst().evaluate(false);
	unsigned i = this->search(x);
	if(i == 0) i = 1;
	else if(i >= this->size()) i = this->size() - 1; 
	h   = xval(i) - xval(i-1);
	qm_real y   = yval(i) - yval(i-1);
    qm_real xm  = x - xval(i-1);
    qm_real h2  = h*h;
    u   = xm/h;
    a   = yval(i-1);
    b   = y - h2*(2*kval(i-1) + kval(i))/6.;
    c   = 0.5*h2*kval(i-1);
    d   = h2*(kval(i) - kval(i-1))/6;
    if(x <= this->front())  {
       	if(m_lower_extrapolation == 1) c = 0;
       	d = 0;
    }
    else if(x >= this->back())  {
       	if(m_upper_extrapolation == 1) {
       		a += b + c + d;
       		b += 2.*c + 3.*d;
       		u  = (x - xval(i))/h;
       		c = 0;
       	}
       	d = 0;
    }
    return i;
}

inline qm_real cubic_spline::value(qm_real x) const  {
	qm_real u,h,a,b,c,d;
	this->coef(x,u,h,a,b,c,d);
	return a + u*(b + u*(c + d*u));
}

inline qm_real cubic_spline::der1(qm_real x) const  {
	qm_real u,h,a,b,c,d;
	this->coef(x,u,h,a,b,c,d);
	return (b + u*(2*c + 3*d*u))/h;
}

inline qm_real cubic_spline::der2(qm_real x) const  {
	qm_real u,h,a,b,c,d;
	this->coef(x,u,h,a,b,c,d);
	return (2*c + 6*d*u)/(h*h);
}

inline const cubic_spline::qmat_type& cubic_spline::sensitivity() const  {
	if(!m_ready || !m_sens_ready) this->noConst().evaluate(true);
	return m_sens;
}


inline void cubic_spline::evaluate_two_points() {
	if(m_lowerBound == definedFirstDerivative && m_upperBound == definedFirstDerivative)  {
		set_kval(0,m_lowerDer);
		set_kval(1,m_upperDer);
	}
	else  {
		qm_real h = xval(1) - xval(0);
		qm_real y = yval(1) - yval(0);
		if(m_lowerBound == definedFirstDerivative)  {
			set_kval(0,m_lowerDer);
			set_kval(1,0.5*(3*y/h - m_lowerDer));
		}
		else if(m_upperBound == definedFirstDerivative)  {
			set_kval(0,0.5*(3*y/h - m_upperDer));
			set_kval(1,m_upperDer);
		}
		else {
			set_kval(0,y/h);
			set_kval(1,y/h);			
		}
	}
}

inline void cubic_spline::evaluate(bool evasens) {
	typedef qmatrix<qm_real,tridiagonal>	triadiag_mat;
    unsigned np  = this->size();
    QM_REQUIRE(np>=2,"There must be at least 2 support points in cubic spline");
    qm_real h2,h1,h2i,h1i,y2,y1,kv,mk;
    
    if(np == 2)  {
    	set_kval(0,0);
    	set_kval(1,0);
    	if(evasens)  {
    		m_sens.resize(2,2);
    	    m_sens.fill(0);
    	}
    	return;
    }
    else if(np == 3)  {
    	h1  = xval(1) - xval(0);
        h2  = xval(2) - xval(1);
        h1i = 1.0/h1;
        h2i = 1.0/h2;
        y1  = (yval(1) - yval(0))*h1i;
        y2  = (yval(2) - yval(1))*h2i;
        mk  = 3./(h1+h2);
        kv  = mk*(y2 - y1);
        set_kval(0,0);
        set_kval(1,kv);
        set_kval(2,0);
        if(evasens)  {
            m_sens.resize(3,3);
            m_sens.fill(0);
            m_sens(1,0) = mk*h1i;
            m_sens(1,1) =-mk*(h2i+h1i);
            m_sens(1,2) = mk*h2i;
        }
        return;
    }
    
    //
    unsigned ist = 0;
    unsigned ien = np-1;
    if(m_lowerBound != definedFirstDerivative) ist++;
    if(m_upperBound != definedFirstDerivative) ien--;
    
    unsigned N  = ien - ist + 1;
    triadiag_mat	A(N),B(np);
    qmatrix<qm_real> bi(N),xv(N);
    unsigned i0,i1,i,j,k;
    
    // Internal domain
    for(i=1;i<np-1;i++)    {
    	j = i - ist;
    	
        h1  = xval(i)   - xval(i-1);
    	h2  = xval(i+1) - xval(i);
    	h1i = 1.0/h1;
    	h2i = 1.0/h2;
    	y1  = (yval(i)   - yval(i-1))*h1i;
    	y2  = (yval(i+1) -   yval(i))*h2i;
        
    	A(j,j)   = 2*(h1 + h2);
    	bi(j)    = 6*(y2 - y1);
    	B(i,i)   =-6*(h1i+h2i);
    	B(i,i-1) = 6*h1i;
    	B(i,i+1) = 6*h2i;
    	
    	if(j>0)
    		A(j,j-1) = h1;
    	if(j<N-1)
    		A(j,j+1) = h2;
    }
    
    /// Lower boundary
    if(m_lowerBound == definedFirstDerivative)  {
    	h1  = xval(1)    - xval(0);
        y1  = (yval(1)   - yval(0))/h1;
    	A(0,0) = 2*h1;
    	A(0,1) = h1;
    	B(0,0) =-6.0/h1;
    	B(0,1) =-B(0,0);
    	bi(0)  = 6*(y1 - m_lowerDer);
    }
    
    /// Upper boundary
    if(m_upperBound == definedFirstDerivative)  {
    	h1  = xval(np-1)    - xval(np-2);
    	y1  = (yval(np-1)   - yval(np-2))/h1;
    	A(N-1,N-1)   = 2*h1;
    	A(N-1,N-2)   = h1;
    	B(np-1,np-1) = 6.0/h1;
    	B(np-1,np-2) =-B(np-1,np-1);
    	bi(N-1)      = 6*(y1 - m_upperDer);
    }
    
    if(!m_ready)  {
    	linalg<qm_real>::solve(A,bi,xv).check();
    	for(j=0;j<N;j++)  {
    		i = j + ist;
    		set_kval(i,xv(j));
    	}
    }
    
    if(evasens)  {
        m_sens.resize(np,np);
        m_sens.fill(0);
        
    	// Evaluate sensitivities of second derivatives at knots point with resepct knot values
        // The ith row of this matrix contains
        // dK_i/d_y_0  dK_i/d_y_1 .....  dK_i/d_y_n  
    	// Loop around the all the support points
    	for(unsigned i=0;i<np;i++)  {
    		i0 = i;
    		i1 = i;
    		if(i>0)    i0--;
    		if(i<np-1) i1++;
    		for(unsigned j=0;j<N;j++)  {
    			k = j + ist;
    			if(k>=i0 && k<=i1)
    				bi(j) = B(k,i);
    			else
    				bi(j) = 0;
    		}
    		linalg<qm_real>::solve(A,bi,xv);
    		for(unsigned j=0;j<N;j++)  {
    			m_sens(j+ist,i) = xv(j);
    		}
    	}
    	m_sens_ready = true;
    }
    
    m_ready = true;
    
}


// Evaluate the sensitivity of the spline value at x with respect the values of knots y_i, i=0,..,n
inline qm_real cubic_spline::dvdy(qm_real x, qmatrix<qm_real>& der) const  {
	this->sensitivity();
	qm_real u,h,a,b,c,d;
	unsigned j = this->coef(x,u,h,a,b,c,d);
	qm_real mm = h*h*u/6;
	qm_real m0 =-mm*(2 + u*(u - 3));
	qm_real m1 =-mm*(1 - u*u);
	der(j-1) += 1 - u;
	der(j)   += u;
	for(unsigned i=0;i<this->size();i++)
		der(i) += m0*m_sens(j-1,i) + m1*m_sens(j,i);
	return a + u*(b + u*(c + d*u));
}








inline qm_real spline1d::value(qm_real x) const  {
	if(!m_ready) this->noConst().evaluate();
	
	qm_real a,b,c,d;
    int n = this->size() - 1;
    if(x >= this->back())  {
        a =  xval(n) - xval(n-1);
        b = (yval(n) - yval(n-1))/a;
        return yval(n) + (b + a*kval(n-1)/6.0 + a*kval(n)/3.0)*(x - xval(n));
    }
    else if(x <= this->front())  {
        a =  xval(1) - xval(0);
        b = (yval(1) - yval(0))/a;
        return yval(0) + (b - a*kval(0)/3.0 - a*kval(1)/6.0)*(x - xval(0));
    }
    int i = this->getCoef(x,a,b,c,d);
    return a*yval(i-1)+b*yval(i)+c*kval(i-1)+d*kval(i);
}

inline qm_real spline1d::der1(qm_real x) const  {
	if(!m_ready) this->noConst().evaluate();
	
	qm_real a,b,c,d;
    int n = this->size() - 1;
    if(x >= this->back())  {
        a =  xval(n) - xval(n-1);
        b = (yval(n) - yval(n-1))/a;
        return b + a*kval(n-1)/6.0 + a*kval(n)/3.0;
    }
    else if(x <= this->front())  {
        a =  xval(1) - xval(0);
        b = (yval(1) - yval(0))/a;
        return b - a*kval(0)/3.0 - a*kval(1)/6.0;
    }
    int i = this->search(x);
    qm_real h = xval(i) - xval(i-1);
    qm_real u = (x - xval(i-1))/h;
    qm_real k0 = kval(i-1);
    qm_real k1 = kval(i);
    b = (yval(i) - yval(i-1))/h - h*(2*k0 + k1)/6;
    c = 0.5*h*k0;
    d = h*(k1 - k0)/6;
    return b + u*(2*c + 3*d*u);
}


inline qm_int spline1d::getCoef(qm_real x, qm_real& a, qm_real& b, qm_real& c, qm_real& d) const   {
	qm_int j = this->search(x);
    this->coef(j,x,a,b,c,d);
    return j;
}


inline void spline1d::coef(qm_int i, qm_real x, qm_real& A, qm_real& B, qm_real& C, qm_real& D) const   {
	qm_real h   = xval(i) - xval(i-1);
    qm_real h0  = x - xval(i-1);
    qm_real b   = h0/h;
    qm_real hs  = h*h/6;
    A = 1 - b;
    B = b;
    C = A * (A * A - 1) * hs;
    D = B * (B * B - 1) * hs;
}


inline unsigned spline1d::dimension(unsigned& ist, unsigned& np) const {
    np  = this->size();
    ist = 0;
    if(!np) return 0;
    //
    unsigned ien = np-1;
    if(m_lowerBound == zeroSecondDerivative || m_lowerBound == zeroThirdDerivative) ist++;
    if(m_upperBound == zeroSecondDerivative || m_upperBound == zeroThirdDerivative) ien--;
    //
    int n  = ien - ist + 1;
    if(n <= 0) return 0;
    else return n;
}

inline spline1d::qmat_type spline1d::lhs() const  {
	unsigned ist,np;
	unsigned N = this->dimension(ist,np);
	qmat_type	A(N);
	qmatrix<qm_real> bi(N);
	evaluate_matrices(A,bi,ist,np);
	return A;
}

inline void spline1d::evaluate(bool evalder)  {
	unsigned ist,np;
	unsigned Nt = this->size();
	QM_REQUIRE(Nt>=2,"Spline must have at least two support points");
	if(Nt == 2)  {
		set_kval(0,0);
		set_kval(1,0);
	}
	else  {
		unsigned N  = this->dimension(ist,np);
		qmat_type	A(N);
		qmatrix<qm_real> bi(N),xv(N);
		evaluate_matrices(A,bi,ist,np);
		linalg<qm_real>::solve(A,bi,xv).check();
		for(unsigned j=0;j<N;j++)  {
			unsigned i = j + ist;
			set_kval(i,xv(j));
		}
		if(m_lowerBound == zeroThirdDerivative) set_kval(0,kval(1));
		if(m_upperBound == zeroThirdDerivative) set_kval(np-1,kval(np-2));
	}
    m_ready = true;
}

inline void spline1d::evaluate_matrices(spline1d::qmat_type& A, qmatrix<qm_real>& bi, unsigned ist, unsigned np) const {
    qm_real h0,h1,y0,y1;
    //
    unsigned N = A.rows();
    for(unsigned j=0;j<N;j++)    {
    	unsigned i = j + ist;
        //
        h0  = 0;
        y0  = 0;
        h1  = 0;
        y1  = 0;
        //
        if(i > 0)  {
        	h0  = xval(i) - xval(i-1);
        	y0  =(yval(i) - yval(i-1))/h0;
        }
        if(i < np - 1)  {
        	h1  = xval(i+1) - xval(i);
        	y1  =(yval(i+1) - yval(i))/h1;
        }
        //
        A(j,j)  = 2.0*(h0 + h1);
        if(j>0) A(j,j-1) = h0;
        if(j < N-1) A(j,j+1) = h1;
        bi(j) = 6.0*(y1 - y0);
        //
        // DefinedFirstDerivative corrections
        if(i == 0    && m_lowerBound == definedFirstDerivative) bi(j) -= 6.0 * m_lowerDer;
        if(i == np-1 && m_upperBound == definedFirstDerivative) bi(j) += 6.0 * m_upperDer;
        //
        // ZeroThirdDerivative corrections
        if(j==0    && m_lowerBound == zeroThirdDerivative) A(j,j) += h0;
        if(j==N-1  && m_upperBound == zeroThirdDerivative) A(j,j) += h1;
    }
      //
      /*
      double a,b,c,d;
      for(int i=1;i<np;i++)
      {
        IntegraCoef(i, m_xval(i), out a, out b, out c, out d);
        m_kval(i, 1) = m_kval(i-1,1) + a * m_yval(i-1) + b * m_yval(i) + c * m_kval(i-1, 0) + d * m_kval(i, 0);
      }
      //
      if(evalDer)
      {
        m_kder = new RealMatrix(np,np);
        //
        for(int i = 0; i < np; i++)
        {
          int j = i - ist;
          Bi.SetValue(0);
          double h0 = 0;
          double h1 = 0;
          if(i > 0)
          {
            h0 = 6.0 / (m_xval(i) - m_xval(i - 1));
            if(j > 0) Bi(j-1) = h0;
          }
          if(i<np-1)
          {
            h1 = 6.0/(m_xval(i+1) - m_xval(i));
            if(j<n-1) Bi(j+1) = h1;
          }
          if(j>=0 && j<n) Bi(j) = - h0 - h1;
          //
          xv    = Tri.Thomas(Bi);
          for(int k=0;k<n;k++) m_kder(k+ist,i) = xv(k); 
        }
      }
      */
      //
}

/*
inline void lspline1d::evaluate(bool evalder)  {
	unsigned np = this->size();
	std::vector<unsigned>  vec;
	vec.push_back(0);
	for(unsigned i=1;i<np-1;i++)  {
		y0 = yval(i) - yval(i-1);
		y1 = yval(i+1) - yval(i);
		if(y0*y1 <= 0) vec.push_back(i);
	}
	vec.push_back(np-1);
	unsigned ist,np;
	unsigned N = this->dimension(ist,np);
	qmat_type	A(N);
	qmatrix<qm_real> bi(N),xv(N);
	evaluate_matrices(A,bi,ist,np);
    linalg<qm_real>::solve(A,bi,xv).check();
    for(unsigned j=0;j<N;j++)  {
    	unsigned i = j + ist;
    	set_kval(i,xv(j));
    }
    if(m_lowerBound == zeroThirdDerivative) set_kval(0,kval(1));
    if(m_upperBound == zeroThirdDerivative) set_kval(np-1,kval(np-2));
    m_ready = true;
}
*/



    
QM_NAMESPACE_END2
    
    
