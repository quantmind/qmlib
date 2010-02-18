

#ifndef __STRUCTURED_GRID_QM_HPP__
#define __STRUCTURED_GRID_QM_HPP__


#include <qmlib/math/pde/pde.hpp>

/**\file
 * \ingroup pde
 * \brief Structured grids
 */


QM_NAMESPACE2(math)

template<unsigned N> 				class structured_grid;
template<unsigned N> 				class structured_grid_factory;
template<class G>    				class struct_index;
template<unsigned D, unsigned d> 	class structured_indexer;

typedef QM_SMART_PTR(structured_grid<1>)	GRID1D;
typedef QM_SMART_PTR(structured_grid<2>)	GRID2D;



/** \brief class template for a N dimensional orthogonal structured grid
 * \ingroup pde
 * 
 * @param N dimension of the grid
 */
template<unsigned N>
class structured_grid : public gridN {
public:
	typedef structured_grid<N>				myself;
	typedef struct_index<myself>			indexer;
	typedef typename indexer::gridpoint		gridpoint;
	friend class structured_grid_factory<N>;
	//friend class indexer;
	
	static const unsigned dimens = N;
	
	const rqmat& coor_vector(unsigned dim)  const {this->checkdim(dim); return m_coor[dim];}
	
	qm_real coor(unsigned dim, unsigned i)	const {this->checkdim(dim); return m_coor[dim](i);}
	
	unsigned 			npoints(unsigned dim)	const {this->checkdim(dim); return m_coor[dim].rows();}
	unsigned 			points()	  			const;
	const gridpoint& 	point(unsigned i) 		const;
	unsigned 		 	dimensions() 			const {return dimens;}
	qm_string 			tostring()		   		const {return object_to_string(*this);}
	qm_real				volume(unsigned i)      const;
	qm_real				volume_fast(unsigned i) const;
	qm_real 			coordinate(unsigned d, unsigned idx) const;
	
	qm_real minvolume() const;
	
	template<class L>
	L coors(unsigned dim) const {
		this->checkdim(dim);
		L co;
		for(unsigned i=0;i<m_coor[dim].rows();++i)
			co.append(m_coor[dim](i));
		return co;		
	}
	
	friend std::ostream& operator<<(std::ostream& os, const myself& og)  {os << og.tostring(); return os;}
	
	qm_real volume_(unsigned dim, unsigned i)  const  {
		QMAT_PRECONDITION(dim < dimens,"Out of bound in dimension. It must be between 0 and Dim-1");
		unsigned R = m_coor[dim].rows();
		if(i > 0 && i < R-1) return 0.5*(m_coor[dim](i+1) - m_coor[dim](i-1));
		else if(i == 0) return m_coor[dim](1) - m_coor[dim](0);
		else return m_coor[dim](R-1) - m_coor[dim](R-2);
	}
	
	unsigned _one(unsigned d) const {return m_idx.one(d);}
	
private:
	
	/// \build a 1D equally spaced structured grid
	structured_grid(qm_real s0=0, qm_real s1=1, unsigned npoints=20);
	/// \build a 2D equally spaced structured grid
	structured_grid(qm_real x0, qm_real x1, unsigned npoints_x,
					qm_real y0, qm_real y1, unsigned npoints_y);
	
	std::vector<rqmat> 		m_coor;
	indexer					m_idx;
	rqmat volumes(unsigned dim) const;
};





/// \brief structured grid indexers
template<>
class struct_index<structured_grid<1> >  {
public:
	typedef structured_grid<1>		gridtype;
	typedef tinyvec<qm_real,1>		gridpoint;
	typedef tinyvec<unsigned,1>		holder;
	
	struct_index(){}
	void set(const gridtype& gr){}
	unsigned one(unsigned) const {return 1;}
	const holder& operator () (unsigned idx) const {m_idx[0] = idx; return m_idx;}
	const gridpoint& operator () (unsigned idx, const gridtype& gr) const {m_po[0] = gr.coor(0,idx); return m_po;}
	qm_real volume(unsigned idx, const gridtype& gr) const  {return gr.volume_(0,idx);}
private:
	mutable holder 		m_idx;
	mutable gridpoint 	m_po;
};

template<>
class struct_index<structured_grid<2> >  {
public:
	typedef structured_grid<2>	gridtype;
	typedef tinyvec<qm_real,2>	gridpoint;
	typedef tinyvec<unsigned,2>	holder;
	
	struct_index(){}
	void set(const gridtype& gr) {m_dim1 = gr.npoints(0);}
	unsigned one(unsigned d) const {return d == 0 ? 1 : m_dim1;}
	const holder& operator () (unsigned idx) const {
		m_idx[0] = idx % m_dim1;
		m_idx[1] = idx / m_dim1;
		return m_idx;
	}
	const gridpoint& operator () (unsigned idx, const gridtype& gr) const  {
		(*this)(idx);
		m_po[0] = gr.coor(0,m_idx[0]);
		m_po[1] = gr.coor(1,m_idx[1]);
		return m_po;
	}
	qm_real volume(unsigned idx, const gridtype& gr) const  {
		(*this)(idx);
		return std::sqrt(gr.volume_(0,m_idx[0]) * gr.volume_(1,m_idx[1]));
	}
private:
	mutable holder 		m_idx;
	mutable gridpoint 	m_po;
	unsigned m_dim1;
};












/// \brief structured_grid class factory
template<unsigned N>
class structured_grid_factory  {
public:
	typedef structured_grid<N> 			gridtype;
	typedef QM_SMART_PTR(gridtype)		GRIDTYPE;
	
	static GRIDTYPE make0();
	static GRIDTYPE make1(qm_real,qm_real,unsigned);
	static GRIDTYPE make2(qm_real,qm_real,unsigned,qm_real,qm_real,unsigned);
};





/// \brief A grid matrix expression.
///
/// This template should work even for unstructured grid!!!
template<class U, class T>
class grid_expr  {
public:
	typedef U									unk_expr;
	typedef T									point_operators;
	typedef typename unk_expr::numtype			numtype;
	
	grid_expr(const unk_expr& unk, const point_operators& sgo, qm_real t):m_unk(unk),m_oper(sgo),m_t(t){}
	grid_expr(const grid_expr& rhs):m_unk(rhs.m_unk),m_oper(rhs.m_oper),m_t(rhs.m_t){}
	
	/// access operator for a one equation pde
	numtype operator () (unsigned i) 			 const	{return m_oper(i).apply(m_unk,i,m_t);}
	/// access operator for system of equations pde
	numtype operator () (unsigned i, unsigned v) const	{return m_oper(i).apply(m_unk,i,v,m_t);}
	/// bad access operator.. Does not make sense
	numtype operator () (unsigned i, unsigned v, unsigned k) const	{QM_FAIL("This asssess operator is not valid");}
protected:
	unk_expr			m_unk;
	point_operators 	m_oper;
	qm_real				m_t;
};


template<>
class structured_indexer<1,1>  {
public:
	typedef QM_SMART_PTR(structured_grid<1>) 	GRIDTYPE;
	structured_indexer(const GRIDTYPE& gr){}
	structured_indexer(const structured_indexer& rhs){}
	structured_indexer& operator = (const structured_indexer& rhs){return *this;}
	unsigned operator () (unsigned n)  const {return n;}
};
template<>
class structured_indexer<2,1>  {
public:
	typedef QM_SMART_PTR(structured_grid<2>) 	GRIDTYPE;
	structured_indexer(const GRIDTYPE& gr):m_dim1(gr->npoints(0)){}
	structured_indexer(const structured_indexer& rhs):m_dim1(rhs.m_dim1){}
	structured_indexer& operator = (const structured_indexer& rhs) {m_dim1 = rhs.m_dim1; return *this;}
	unsigned operator () (unsigned n) const {return n % m_dim1;}
private:
	unsigned m_dim1;
};
template<>
class structured_indexer<2,2>  {
public:
	typedef QM_SMART_PTR(structured_grid<2>) 	GRIDTYPE;
	structured_indexer(const GRIDTYPE& gr):m_dim1(gr->npoints(0)){}
	structured_indexer(const structured_indexer& rhs):m_dim1(rhs.m_dim1){}
	structured_indexer& operator = (const structured_indexer& rhs) {m_dim1 = rhs.m_dim1; return *this;}
	unsigned operator () (unsigned n) const {return n / m_dim1;}
private:
	unsigned m_dim1;
};




template<class C, unsigned D, unsigned d>
class structured_grid_operator {
public:
	typedef C									holder;
	typedef typename holder::numtype			point_operator;
	typedef typename point_operator::gridtype	gridtype;
	typedef QM_SMART_PTR(gridtype)				GRIDTYPE;
	typedef typename holder::reference			reference;
	typedef structured_indexer<D,d>				indexer;
	
	structured_grid_operator(const holder& rhs, const GRIDTYPE& gr):m_oper(rhs),m_idx(gr){}
	structured_grid_operator(const structured_grid_operator& rhs):m_oper(rhs.m_oper),m_idx(rhs.m_idx){}
	const point_operator& operator () (unsigned i) const {return m_oper(m_idx(i));}
private:
	reference	m_oper;
	indexer		m_idx;
};



/// \brief Template class for structured grid operators
///
/// This template defined the operations and type traits for a structured grid.
/// The operator can be any user defined operator such as first difference,
/// second difference upwind first difference or any other specialized algorithm.
template<class Op>
class structured_operator  {
public:
	typedef Op										point_operator;
	typedef typename point_operator::numtype		numtype;
	typedef typename point_operator::gridtype		gridtype;
	typedef QM_SMART_PTR(gridtype)					GRIDTYPE;
	typedef qmatrix<numtype>						qmat;
	typedef typename qmat::reference				qmat_ref;
	typedef qmatrix<point_operator>		  			container;
	typedef typename container::reference			container_ref;

	// grid dimension
	static const unsigned dimens = gridtype::dimens;
	/// The dimension to which the operator apply. Must be dim <= dimens
	static const unsigned dim	 = point_operator::dim;
	
	typedef structured_grid_operator<container,dimens,dim>	grid_operator;

	/// \brief type trais helper struct
	template<class expr> struct traits  {
		typedef matrix_traits<expr>							mtraits;
		typedef typename mtraits::arg						arg;
		typedef grid_expr<arg, grid_operator>				oper;
		typedef matrix_expr<oper>                           ret_type;
	};
	
	structured_operator(const GRIDTYPE& gr = GRIDTYPE()):m_gr(gr) {
		QM_REQUIRE(m_gr,"Structured grid not available. You need to pass a grid object as argument");
		m_opers.resize1(m_gr->npoints(dim-1));
		for(unsigned i=0;i<m_opers.rows();i++)
			m_opers(i) = point_operator(m_gr,i);
	}
	
	structured_operator(const structured_operator& rhs):m_gr(rhs.m_gr),m_opers(rhs.m_opers){}
	
	unsigned  points()    const {return m_opers.rows();}
	unsigned  direction() const {return dim;}
	GRIDTYPE  grid()      const {return m_gr;}
	qm_string tostring()  const {return m_gr->tostring() + " operator " + point_operator::tostring();}
	
	//structured_operator(const myself& rhs):m_opers(rhs.m_opers){}
	structured_operator& operator = (const structured_operator& rhs) {
		m_gr = rhs.m_gr;
		m_opers.copy(rhs.m_mat);
		return *this;
	}
	
	template<class expr>
	typename traits<expr>::ret_type
	operator () (const matrix_expr<expr>& unk, qm_real t) const {
		typedef matrix_traits<expr>					mtraits;
		typedef typename traits<expr>::oper			oper;
		typedef typename traits<expr>::ret_type 	ret_type;
		return ret_type(oper(unk,grid_operator(m_opers,m_gr),t));
	}
	
	typename traits<qmat>::ret_type
	operator () (const qmat& unk, qm_real t) const {
		typedef traits<qmat> 			tr;
		typedef typename tr::oper       oper;
		typedef typename tr::ret_type 	ret_type;
		return ret_type(oper(unk.getref(),grid_operator(m_opers,m_gr),t));
	}
	
	template<class expr, class S>
	void lhs(const matrix_expr<expr>& unk, qmatrix<numtype,S>& A) const  {
		unsigned num = A.rows();
		grid_operator ope(m_opers,m_gr);
		for(unsigned i=0;i<num;i++) ope(i).lhs(unk,A,i);
	}
private:
	GRIDTYPE		m_gr;
	container 		m_opers;
};


QM_NAMESPACE_END2


QM_NAMESPACE

/**\brief PDE structured grid traits
 * \ingroup pde
 */
template<unsigned N>
struct pdegridtraits  {
	typedef QM_FROM_NAMESPACE2(math)structured_grid_factory<N>	factory;
	typedef typename factory::gridtype							gridtype;
	typedef typename factory::GRIDTYPE							GRIDTYPE;
	typedef typename gridtype::gridpoint  						gridpoint;
};



QM_NAMESPACE_END




#include <qmlib/math/pde/impl/grid_operators.hh>
#include <qmlib/math/pde/impl/structured_grid.hh>

#endif // __STRUCTURED_GRID_QM_HPP__

