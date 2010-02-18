
/// \file Standard structured grid operators



#ifndef __STRUCTURED_GRID_OPERATORS_QM_HPP__
#define __STRUCTURED_GRID_OPERATORS_QM_HPP__


#ifndef __STRUCTURED_GRID_QM_HPP__
 #error <qmlib/pde/grid_operators.hpp> must be included via <qmlib/pde/structured_grid.hpp>
#endif



QM_NAMESPACE2(math)


template<typename T, unsigned D, unsigned d, unsigned O>
class first_centered {private: first_centered(){}};
template<typename T, unsigned D, unsigned d, unsigned O>
class second_centered 	{private: second_centered(){}};
template<typename T, unsigned D, unsigned d, unsigned O>
class first_forward 	{private: first_forward(){}};
template<typename T, unsigned D, unsigned d, unsigned O>
class first_backward 	{private: first_backward(){}};
template<typename T, unsigned D, unsigned d, unsigned O>
class second_forward 	{private: second_forward(){}};
template<typename T, unsigned D, unsigned d, unsigned O>
class second_backward 	{private: second_backward(){}};




/// \brief Standard Second Order First central difference operator for sructured grids
///
/// Revert to first order forward and backward operators at boundaries
template<typename T, unsigned D, unsigned d>
class first_centered<T,D,d,2> {
public:
	typedef T							numtype;
	typedef structured_grid<D>			gridtype;
	typedef QM_SMART_PTR(gridtype)		GRIDTYPE;
	typedef qmatrix_ref<T>				unknowns_ref;
	typedef first_centered<T,D,d,2>		myself;
	
	static const unsigned dim = d;
	static qm_string tostring() {return "First Partial Derivative (central difference second order accurate)";}
	
	first_centered(){}
	first_centered(const GRIDTYPE& gr, unsigned i)  {
		qm_real h;
		unsigned di = dim - 1;
		unsigned one = gr->_one(di);
		unsigned N   = gr->npoints(di);
		
		if(i == 0)  {
			h = gr->coor(di,i+1) - gr->coor(di,i);
			m_mone = 0;
			m_pone = one;
		}
		else if(i==N-1)  {
			h = gr->coor(di,i) - gr->coor(di,i-1);
			m_mone = one;
			m_pone = 0;
		}
		else  {
			h = gr->coor(di,i+1) - gr->coor(di,i-1);
			m_mone = one;
			m_pone = one;
		}
		m_c0  = 1.0/h;
	}
	
	
	first_centered(const first_centered& rhs):m_c0(rhs.m_c0),m_pone(rhs.m_pone),m_mone(rhs.m_mone){}
	first_centered& operator = (const first_centered& rhs) {
		m_c0 = rhs.m_c0; m_pone = rhs.m_pone; m_mone = rhs.m_mone;
		return *this;
	}
	
	numtype apply(const unknowns_ref& unk, unsigned i, qm_real t) const  {
		return m_c0 * (unk(i+m_pone) - unk(i-m_mone));
	}
	
	numtype apply(const unknowns_ref& unk, unsigned i, unsigned v, qm_real t) const  {
		return m_c0 * (unk(i+m_pone,v) - unk(i-m_mone,v));
	}
	
	template<class expr>
	numtype apply(const matrix_expr<expr>& unk, unsigned i, qm_real t) const {
		return m_c0 * (unk(i+m_pone) - unk(i-m_mone));
	}
	
	template<class expr>
	numtype apply(const matrix_expr<expr>& unk, unsigned i, unsigned v, qm_real t) const {
		return m_c0 * (unk(i+m_pone,v) - unk(i-m_mone,v));
	}
	template<class expr, class S>
	void lhs(const matrix_expr<expr>& unk, qmatrix<numtype,S>& A, unsigned i) const {
		A(i,i-m_mone) += m_c0*unk(i);
		A(i,i+m_pone) -= m_c0*unk(i);
	}
	template<class expr, class S>
	void lhs(const matrix_expr<expr>& unk, qmatrix<numtype,S>& A, unsigned i, unsigned j, qm_real mul) const {
		qm_real c = mul*m_c0;
		A(i,i-m_mone) += c*unk(j);
		A(i,i+m_pone) -= c*unk(j);
	}
	template<class expr, class op, class S>
	void lhs(const matrix_expr<expr>& unk, const op& ope, qmatrix<numtype,S>& A, unsigned i) const {
		ope(i-m_mone).lhs(unk,A,i-m_mone,i,m_c0);
		ope(i+m_pone).lhs(unk,A,i+m_pone,i,-m_c0);
	}
private:
	qm_real m_c0;
	unsigned m_pone;
	unsigned m_mone;
};






/// \brief Standard Second Order Second central difference operator
///
/// Revert to zero at boundary
template<typename T, unsigned D, unsigned d>
class second_centered<T,D,d,2> {
public:
	typedef T							numtype;
	typedef structured_grid<D>			gridtype;
	typedef QM_SMART_PTR(gridtype)		GRIDTYPE;
	typedef qmatrix_ref<T>				unknowns_ref;
	typedef second_centered<T,D,d,2>	myself;
	
	static const unsigned dim = d;
	static qm_string tostring() {return "Second Partial Derivative (central difference second order accurate)";}
	
	second_centered(){}
	second_centered(const GRIDTYPE& gr, unsigned i)  {
		unsigned di = dim - 1;
		if(i > 0 && i < gr->npoints(di)-1)  {
			qm_real h0 = gr->coor(di,i)   - gr->coor(di,i-1);
			qm_real h1 = gr->coor(di,i+1) - gr->coor(di,i);
			m_c0  = 2.0/((h0+h1)*h0);
			m_c1  =-2.0/(h0*h1);
			m_c2  = 2.0/((h0+h1)*h1);
			m_one = gr->_one(di);
		}
		else  {
			m_one = 0;
			m_c0  = 0;
			m_c1  = 0;
			m_c2  = 0;
		}
	}
	
	second_centered(const second_centered& rhs):m_c0(rhs.m_c0),m_c1(rhs.m_c1),m_c2(rhs.m_c2),m_one(rhs.m_one){}
	second_centered& operator = (const second_centered& rhs) {
		m_c0  = rhs.m_c0;
		m_c1  = rhs.m_c1;
		m_c2  = rhs.m_c2;
		m_one = rhs.m_one;
		return *this;
	}
	
	numtype apply(const unknowns_ref& unk, unsigned i, qm_real t) const  {
		return m_c0 * unk(i-m_one) + m_c1 * unk(i) + m_c2 * unk(i+m_one);
	}
	
	numtype apply(const unknowns_ref& unk, unsigned i, unsigned v, qm_real t) const  {
		return m_c0 * unk(i-m_one,v) + m_c1 * unk(i,v) + m_c2 * unk(i+m_one,v);
	}
	
	template<class expr>
	numtype apply(const matrix_expr<expr>& unk, unsigned i, qm_real t) const {
		return m_c0 * unk(i-m_one) + m_c1 * unk(i) + m_c2 * unk(i+m_one);
	}
	
	template<class expr>
	numtype apply(const matrix_expr<expr>& unk, unsigned i, unsigned v, qm_real t) const {
		return m_c0 * unk(i-m_one,v) + m_c1 * unk(i,v) + m_c2 * unk(i+m_one,v);
	}

	template<class expr, class S>
	void lhs(const matrix_expr<expr>& unk, qmatrix<numtype,S>& A, unsigned i) const {
		A(i,i-m_one) 	-= m_c0*unk(i);
		A(i,i) 			-= m_c1*unk(i);
		A(i,i+m_one) 	-= m_c2*unk(i);
	}
private:
	qm_real m_c0,m_c1,m_c2;
	unsigned m_one;
};







/*
/// \brief Standard Second Order Second central difference operator
///
/// Revert to zero at boundary
template<typename T, unsigned D, unsigned d>
class mixed_centered<T,D,d1,d2,2> {
public:
	typedef T							numtype;
	typedef structured_grid<D>			gridtype;
	typedef QM_SMART_PTR(gridtype)		GRIDTYPE;
	typedef qmatrix_ref<T>				unknowns_ref;
	typedef mixed_centered<T,D,d,2>		myself;
	
	static const unsigned dim = d;
	static qm_string tostring() {return "Second Partial Derivative (central difference second order accurate)";}
	
	mixed_centered(){}
	mixed_centered(const GRIDTYPE& gr, unsigned i)  {
		unsigned di = dim - 1;
		if(i > 0 && i < gr->npoints(di)-1)  {
			qm_real h0 = gr->coor(di,i)   - gr->coor(di,i-1);
			qm_real h1 = gr->coor(di,i+1) - gr->coor(di,i);
			m_c0  = 2.0/((h0+h1)*h0);
			m_c1  =-2.0/(h0*h1);
			m_c2  = 2.0/((h0+h1)*h1);
			m_one = gr->_one(di);
		}
		else  {
			m_one = 0;
			m_c0  = 0;
			m_c1  = 0;
			m_c2  = 0;
		}
	}
	
	second_centered(const second_centered& rhs):m_c0(rhs.m_c0),m_c1(rhs.m_c1),m_c2(rhs.m_c2),m_one(rhs.m_one){}
	second_centered& operator = (const second_centered& rhs) {
		m_c0  = rhs.m_c0;
		m_c1  = rhs.m_c1;
		m_c2  = rhs.m_c2;
		m_one = rhs.m_one;
		return *this;
	}
	
	numtype apply(const unknowns_ref& unk, unsigned i, qm_real t) const  {
		return m_c0 * unk(i-m_one) + m_c1 * unk(i) + m_c2 * unk(i+m_one);
	}
	
	numtype apply(const unknowns_ref& unk, unsigned i, unsigned v, qm_real t) const  {
		return m_c0 * unk(i-m_one,v) + m_c1 * unk(i,v) + m_c2 * unk(i+m_one,v);
	}
	
	template<class expr>
	numtype apply(const matrix_expr<expr>& unk, unsigned i, qm_real t) const {
		return m_c0 * unk(i-m_one) + m_c1 * unk(i) + m_c2 * unk(i+m_one);
	}
	
	template<class expr>
	numtype apply(const matrix_expr<expr>& unk, unsigned i, unsigned v, qm_real t) const {
		return m_c0 * unk(i-m_one,v) + m_c1 * unk(i,v) + m_c2 * unk(i+m_one,v);
	}

	template<class expr, class S>
	void lhs(const matrix_expr<expr>& unk, qmatrix<numtype,S>& A, unsigned i) const {
		A(i,i-m_one) 	-= m_c0*unk(i);
		A(i,i) 			-= m_c1*unk(i);
		A(i,i+m_one) 	-= m_c2*unk(i);
	}
private:
	qm_real m_c0,m_c1,m_c2;
	unsigned m_one;
};
*/


/*
template<typename T, unsigned D>
class first_forward<T,D,1> {
public:
	typedef T					numtype;
	typedef structured_grid<D>	grid_type;
	typedef qmatrix_ref<T>		unknowns_ref;
	
	first_forward(const grid_type& gr, unsigned dim, unsigned i)  {
		qm_real h  = gr.coor(dim,i+1)   - gr.coor(dim,i);
		m_c0  = 1.0/h;
		m_one = gr.index().one(dim);
	}
	
	numtype apply(const unknowns_ref& unk, unsigned i) const  {
		return m_c0 * (unk(i+m_one) - unk(i));
	}
	
	numtype apply(const unknowns_ref& unk, unsigned i, unsigned v) const  {
		return m_c0 * (unk(i+m_one,v) - unk(i,v));
	}
	
	template<class expr>
	numtype apply(const matrix_expr<expr>& unk, unsigned i) const {
		return m_c0 * (unk(i+m_one) - unk(i));
	}
	
	template<class expr>
	numtype apply(const matrix_expr<expr>& unk, unsigned i, unsigned v) const {
		return m_c0 * (unk(i+m_one,v) - unk(i,v));
	}
private:
	qm_real m_c0;
	unsigned m_one;
};


template<typename T, unsigned D>
class first_backward<T,D,1> {
public:
	typedef T					numtype;
	typedef structured_grid<D>	grid_type;
	typedef qmatrix_ref<T>		unknowns_ref;
	
	first_backward(const grid_type& gr, unsigned dim, unsigned i)  {
		qm_real h  = gr.coor(dim,i)   - gr.coor(dim,i-1);
		m_c0  = 1.0/h;
		m_one = gr.index().one(dim);
	}
	
	numtype apply(const unknowns_ref& unk, unsigned i) const  {
		return m_c0 * (unk(i) - unk(i-m_one));
	}
	
	numtype apply(const unknowns_ref& unk, unsigned i, unsigned v) const  {
		return m_c0 * (unk(i,v) - unk(i-m_one,v));
	}
	
	template<class expr>
	numtype apply(const matrix_expr<expr>& unk, unsigned i) const {
		return m_c0 * (unk(i) - unk(i-m_one));
	}
	
	template<class expr>
	numtype apply(const matrix_expr<expr>& unk, unsigned i, unsigned v) const {
		return m_c0 * (unk(i,v) - unk(i-m_one,v));
	}
private:
	qm_real m_c0;
	unsigned m_one;
};

*/
/*


inline void non_centered_second_derivative(qm_real h0, qm_real h1, qm_real h2,
										   qm_real& c0, qm_real& c1, qm_real& c2, qm_real& c3)  {
	qm_real h01    = h0 + h1;
	qm_real h012   = h01 + h2;
	qm_real h0_2   = h0*h0;
	qm_real h01_2  = h01*h01;
	qm_real h012_2 = h012*h012;
	qm_real a      =-h0*(h012_2 - h0_2)/(h01*(h012_2 - h01_2));
	qm_real b      =-(h0 + a*h01)/h012;
	qm_real c      = 2.0/(h0_2 + a*h01_2 + b*h012_2);
	c0 =-c*(1.0 + a + b);
	c1 = c;
	c2 = c*a;
	c3 = c*b;
}


// \brief This is always of order >= 2
template<unsigned order = 2>
struct first_centered_operator  {
	static structured_grid_point_operator get(const standard_structured_grid& gr, unsigned dim, unsigned i) {
		QM_TRACE_ENTER_FUNCTION
		qm_real h  = 1.0/(gr.coor(dim,i+1)   - gr.coor(dim,i-1));
		structured_grid_point_operator op;
		op.c[0] =-h;
		op.c[1] = h;
		op.i[0] = i-1;
		op.i[1] = i+1;
		QM_TRACE_EXIT_FUNCTION
		return op;
	}
};

template<unsigned order = 1>
struct first_forward_operator  {
	static structured_grid_point_operator get(const standard_structured_grid& gr, unsigned dim, unsigned i) {
		QM_TRACE_ENTER_FUNCTION
		qm_real h0  = gr.coor(dim,i+1)   - gr.coor(dim,i);
		structured_grid_point_operator op;
		op.i[0] = i;
		op.i[1] = i+1;
		
		if(order<= 1)  {
			op.c[0] =-1.0/h0;
			op.c[1] = 1.0/h0;
		}
		else  {
			qm_real h1  = gr.coor(dim,i+2) - gr.coor(dim,i+1);
			qm_real h01 = h0 + h1;
			qm_real hr  = h01/h0;
			qm_real hr2 = hr*hr;
			qm_real m   = 1.0/(h01*(1.0 - hr));
			op.c[0]     = m*(hr2 - 1);
			op.c[1]     =-m*hr2;
			op.c[2]     = m;
			op.i[2] 	= i+2;
		}
		QM_TRACE_EXIT_FUNCTION
		return op;
	}
};


template<unsigned order = 1>
struct first_backward_operator  {
	static structured_grid_point_operator get(const standard_structured_grid& gr, unsigned dim, unsigned i) {
		QM_TRACE_ENTER_FUNCTION
		qm_real h0  = gr.coor(dim,i)   - gr.coor(dim,i-1);
		structured_grid_point_operator op;
		op.i[0] = i;
		op.i[1] = i-1;
		
		if(order<= 1)  {
			op.c[0] = 1.0/h0;
			op.c[1] =-1.0/h0;
		}
		else  {
			qm_real h1  = gr.coor(dim,i-1) - gr.coor(dim,i-2);
			qm_real h01 = h0 + h1;
			qm_real hr  = h01/h0;
			qm_real hr2 = hr*hr;
			qm_real m   =-1.0/(h01*(1.0 - hr));
			op.c[0]     = m*(hr2 - 1);
			op.c[1]     =-m*hr2;
			op.c[2]     = m;
			op.i[2] 	= i-2;
		}
		QM_TRACE_EXIT_FUNCTION
		return op;
	}
};


template<unsigned order = 1>
struct second_centered_operator  {
	static structured_grid_point_operator get(const standard_structured_grid& gr, unsigned dim, unsigned i) {
		qm_real h0 = gr.coor(dim,i)   - gr.coor(dim,i-1);
		qm_real h1 = gr.coor(dim,i+1) - gr.coor(dim,i);
		structured_grid_point_operator op;
		op.c[0] = 2.0/((h0+h1)*h0);
		op.c[1] =-2.0/(h0*h1);
		op.c[2] = 2.0/((h0+h1)*h1);
		op.i[0] = i-1;
		op.i[1] = i;
		op.i[2] = i+1;
		op.i[3] = i;
		return op;
	}
};


template<unsigned order = 1>
struct second_forward_operator  {
	static structured_grid_point_operator get(const standard_structured_grid& gr, unsigned dim, unsigned i) {
		qm_real h0 = gr.coor(dim,i+1) - gr.coor(dim,i);
		qm_real h1 = gr.coor(dim,i+2) - gr.coor(dim,i+1);
		qm_real h2 = gr.coor(dim,i+3) - gr.coor(dim,i+2);
		structured_grid_point_operator op;
		non_centered_second_derivative(h0,h1,h2,op.c[0],op.c[1],op.c[2],op.c[3]);
		op.i[0] = i;
		op.i[1] = i+1;
		op.i[2] = i+2;
		op.i[3] = i+3;
		return op;
	}
};

template<unsigned order = 1>
struct zero_operator  {
	static structured_grid_point_operator get(const standard_structured_grid& gr, unsigned dim, unsigned i) {
		return structured_grid_point_operator();
	}
};

template<unsigned order = 1>
struct second_forward_linearfirst_operator  {
	static structured_grid_point_operator get(const standard_structured_grid& gr, unsigned dim, unsigned i) {
		qm_real h0 = gr.coor(dim,i+1) - gr.coor(dim,i);
		qm_real h1 = gr.coor(dim,i+2) - gr.coor(dim,i+1);
		qm_real h01 = h0/h1;
		qm_real hi  = 1.0/(h0*h0);
		structured_grid_point_operator op;
		op.c[0] =-hi;
		op.c[1] = (1.0-h01)*hi;
		op.c[2] = h01*hi;
		op.i[0] = i;
		op.i[1] = i+1;
		op.i[2] = i+2;
		return op;
	}
};


template<unsigned order = 1>
struct second_backward_operator  {
	static structured_grid_point_operator get(const standard_structured_grid& gr, unsigned dim, unsigned i) {
		QM_TRACE_ENTER_FUNCTION
		qm_real h0 = gr.coor(dim,i)   - gr.coor(dim,i-1);
		qm_real h1 = gr.coor(dim,i-1) - gr.coor(dim,i-2);
		qm_real h2 = gr.coor(dim,i-2) - gr.coor(dim,i-3);
		structured_grid_point_operator op;
		non_centered_second_derivative(h0,h1,h2,op.c[0],op.c[1],op.c[2],op.c[3]);
		op.i[0] = i;
		op.i[1] = i-1;
		op.i[2] = i-2;
		op.i[3] = i-3;
		QM_TRACE_EXIT_FUNCTION
		return op;
	}
};



template<class Center, class Lower, class Lower1, class Upper1, class Upper>
inline structured_grid_operator buildoperator(const standard_structured_grid& gr, unsigned dim)  {
	structured_grid_operator go(gr.npoints(dim));
	unsigned N = go.length();
	for(unsigned i=2;i<N-2;++i)
		go[i] = Center::get(gr,dim,i);
	go[0]   = Lower::get(gr,dim,0);
	go[1]   = Lower1::get(gr,dim,1);
	go[N-2] = Upper1::get(gr,dim,N-2);
	go[N-1] = Upper::get(gr,dim,N-1);
	return go;
}

inline structured_grid_operator stable_centered_first(const standard_structured_grid& gr, unsigned dim)  {
	return buildoperator<first_centered_operator<2>,
						 first_forward_operator<1>,		// 1st order forward operator at lower boundary
						 first_centered_operator<2>,
						 first_centered_operator<2>,
						 first_backward_operator<1>		// 1st order backward operator at upper boundary
						 >(gr,dim);
}

inline structured_grid_operator stable_forward_first(const standard_structured_grid& gr, unsigned dim)  {
	return buildoperator<first_forward_operator<2>,
						 first_forward_operator<2>,
						 first_forward_operator<2>,
						 first_forward_operator<1>,
						 first_backward_operator<1>
						 >(gr,dim);
}

inline structured_grid_operator stable_backward_first(const standard_structured_grid& gr, unsigned dim)  {
	return buildoperator<first_backward_operator<2>,
						 first_forward_operator<1>,
						 first_backward_operator<1>,
						 first_backward_operator<2>,
						 first_backward_operator<2>
						 >(gr,dim);
}

inline structured_grid_operator full2o_centered_first(const standard_structured_grid& gr, unsigned dim)  {
	return buildoperator<first_centered_operator<2>,
						 first_forward_operator<2>,		// 1st order forward operator at lower boundary
						 first_centered_operator<2>,
						 first_centered_operator<2>,
						 first_backward_operator<2>		// 1st order backward operator at upper boundary
						 >(gr,dim);
}




inline structured_grid_operator full2o_centered_second(const standard_structured_grid& gr, unsigned dim)  {
	return buildoperator<second_centered_operator<2>,
						 second_forward_operator<2>,		// 1st order forward operator at lower boundary
						 second_centered_operator<2>,
						 second_centered_operator<2>,
						 second_backward_operator<2>		// 1st order backward operator at upper boundary
						 >(gr,dim);
}

inline structured_grid_operator stable_centered_second(const standard_structured_grid& gr, unsigned dim)  {
	return buildoperator<second_centered_operator<2>,
						 zero_operator<>,		// 1st order forward operator at lower boundary
						 second_centered_operator<2>,
						 second_centered_operator<2>,
						 zero_operator<>		// 1st order backward operator at upper boundary
						 >(gr,dim);
}

*/



QM_NAMESPACE_END2

#endif	//	__STRUCTURED_GRID_OPERATORS_QM_HPP__
