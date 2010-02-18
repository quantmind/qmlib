

#ifndef __STRUCTURED_GRID_IMPL_QM_HH__
#define __STRUCTURED_GRID_IMPL_QM_HH__


#ifndef __STRUCTURED_GRID_QM_HPP__
 #error <qmlib/pde/impl/structured_grid.hh> must be included via <qmlib/pde/structured_grid.hpp>
#endif



QM_NAMESPACE2(math)



template<unsigned D>
inline structured_grid<D>::structured_grid(qm_real s0, qm_real s1, unsigned npoints):m_coor(D)  {
	QM_REQUIRE(structured_grid::dimens == 1,"This constructor is valid for 1 dimensional grids only")
	QM_REQUIRE(npoints > 3,"Too few grid points in structured grid");
	QM_REQUIRE(s0<s1,"Bad domain in structured grid");
	qm_real dx = (s1 - s0)/npoints;
	rqmat x(npoints);
	for(unsigned i=0;i<npoints;++i) x(i) = s0 + i*dx;
	m_coor[0].copy(x);
	m_idx.set(*this);
}

template<unsigned D>
inline structured_grid<D>::structured_grid(qm_real x0, qm_real x1, unsigned npoints_x,
							 			   qm_real y0, qm_real y1, unsigned npoints_y):m_coor(D)  {
	QM_REQUIRE(structured_grid::dimens == 2,"This constructor is valid for 2 dimensional grids only")
	QM_REQUIRE(npoints_x > 3&& npoints_y > 3,"Too few grid points in structured grid");
	QM_REQUIRE(x0<x1 && y0<y1,"Bad domain in structured grid");
	qm_real dx = (x1 - x0)/npoints_x;
	qm_real dy = (y1 - y0)/npoints_y;
	rqmat x(npoints_x);
	rqmat y(npoints_y);
	for(unsigned i=0;i<npoints_x;i++) x(i) = x0 + i*dx;
	for(unsigned j=0;j<npoints_y;j++) y(j) = y0 + j*dy;
	m_coor[0].copy(x);
	m_coor[1].copy(y);
	m_idx.set(*this);
}

template<unsigned D>
inline rqmat structured_grid<D>::volumes(unsigned dim) const  {
	unsigned N = this->npoints(dim);
	rqmat d(N);
	d = 0;
	qm_real h;
	for(unsigned i=1;i<N;i++)  {
		h = 0.5*(this->coor(dim,i) - this->coor(dim,i-1));
		d(i-1) += h;
		d(i)   += h;
	}
	return d;
}

template<unsigned D>
inline unsigned structured_grid<D>::points() const  {
	unsigned np = 1;
	for(unsigned i=0;i<D;i++) np *= m_coor[i].rows();
	return np;
}

template<unsigned D>
inline qm_real structured_grid<D>::coordinate(unsigned d, unsigned idx) const  {
	return this->coor(d,m_idx(idx)[d]);
}

template<unsigned D>
inline qm_real structured_grid<D>::volume(unsigned i) const  {
	QM_REQUIRE(i < this->points(), "Out of bound in accessing volume");
	return m_idx.volume(i,*this);
}

template<unsigned D>
inline qm_real structured_grid<D>::volume_fast(unsigned i) const  {
	return m_idx.volume(i,*this);
}

template<unsigned D>
inline qm_real structured_grid<D>::minvolume() const  {
	qm_real v = 1;
	for(unsigned i=0;i<structured_grid::dimens;i++)
		v *= min(this->volumes(i));
	return std::pow(v,1.0/structured_grid::dimens);
}


template<unsigned D>
inline const typename structured_grid<D>::gridpoint& structured_grid<D>::point(unsigned i) const  {
	return m_idx(i,*this);
}







///////////////////// STRUCTURED GRID FACTORY



template<unsigned N>
inline QM_SMART_PTR(structured_grid<N>) structured_grid_factory<N>::make0()  {
	typedef structured_grid<N> 			gridtype;
	typedef QM_SMART_PTR(gridtype)		GRIDTYPE;
	if(N == 1) return GRIDTYPE(new gridtype(0,1,50));
	else if(N == 2) return GRIDTYPE(new gridtype(0,1,50,0,1,50));
	else QM_FAIL("dimension not available yet. Ask the developer");
}
template<unsigned N>
inline QM_SMART_PTR(structured_grid<N>) structured_grid_factory<N>::make1(qm_real x0, qm_real x1, unsigned nx)  {
	typedef structured_grid<N> 			gridtype;
	typedef QM_SMART_PTR(gridtype)		GRIDTYPE;
	if(N == 1) return GRIDTYPE(new gridtype(x0,x1,nx));
	else if(N == 2) return GRIDTYPE(new gridtype(x0,x1,nx,x0,x1,nx));
	else QM_FAIL("dimension not available yet. Ask the developer");	
}
template<unsigned N>
inline QM_SMART_PTR(structured_grid<N>) structured_grid_factory<N>::make2(qm_real x0, qm_real x1, unsigned nx,
		                                                                  qm_real y0, qm_real y1, unsigned ny)  {
	typedef structured_grid<N> 			gridtype;
	typedef QM_SMART_PTR(gridtype)		GRIDTYPE;
	if(N == 1) return GRIDTYPE(new gridtype(x0,x1,nx));
	else if(N == 2) return GRIDTYPE(new gridtype(x0,x1,nx,y0,y1,ny));
	else QM_FAIL("dimension not available yet. Ask the developer");
}




QM_NAMESPACE_END2






QM_NAMESPACE


/// \brief object_to_string_o specialization for structured_grid<1>
template<>
struct object_to_string_o<QM_FROM_NAMESPACE2(math)structured_grid<1> >  {
	static qm_string get(const QM_FROM_NAMESPACE2(math)structured_grid<1>& obj)  {
		return "1D PDE grid (" + object_to_string(obj.points()) + " points)";
	}
};


/// \brief object_to_string_o specialization for structured_grid<2>
template<>
struct object_to_string_o<QM_FROM_NAMESPACE2(math)structured_grid<2> >  {
	static qm_string get(const QM_FROM_NAMESPACE2(math)structured_grid<2>& obj)  {
		return "2D orthogonal structured PDE grid ( " + object_to_string(obj.npoints(0)) + " x " +
														object_to_string(obj.npoints(1)) + " )";
	}
};

QM_NAMESPACE_END





#endif // __STRUCTURED_GRID_IMPL_QM_HH__


