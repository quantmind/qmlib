


#ifndef		__QMATRIX_IMPL_QMAT_HPP__
#define		__QMATRIX_IMPL_QMAT_HPP__


//#ifndef __QMATRIX_QMAT_HPP__
// #error <qmlib/qmat/impl/qmatrix_impl.hpp> must be included via <qmlib/qmat/qmatrix.hpp>
//#endif

//#include<qmlib/math/random/rndgen.hpp>


QM_NAMESPACE2(math)

template<typename T, class S>
inline qmatrix<T,S>::qmatrix(unsigned rows):m_structure(rows),m_lock(false)  {
	unsigned siz = this->size();
	if(siz) this->initialblock(siz);
}

template<typename T, class S>
inline qmatrix<T,S>::qmatrix(unsigned rows, unsigned cols):m_structure(rows,cols),m_lock(false)  {
	unsigned siz = this->size();
	if(siz) this->initialblock(siz);
}

// Copy costructor
template<typename T, class S>
inline qmatrix<T,S>::qmatrix(const qmatrix<T,S>& rhs):m_structure(rhs.m_structure),m_lock(rhs.m_lock)  {
	if(this->size() > 0) this->initialblock(rhs.noConst());
}


template<typename T, class S>
inline qmatrix<T,S>::qmatrix(const qmatrix<T,S>& rhs, bool copycontent):m_structure(rhs.m_structure),m_lock(false)  {
	unsigned siz = this->size();
	if(siz)  {
		this->initialblock(siz);
	}
	if(copycontent)
		for(unsigned i=0;i<this->size();++i) this->m_data[i] = rhs[i];
}


template<typename T, class S>
inline qmatrix<T,S>::qmatrix(const structure& str):m_structure(str),m_lock(false)  {
	unsigned siz = this->size();
	if(siz)  {
		this->initialblock(siz);
	}
}


/*
template<typename T, class S>
inline qmatrix<T,S>::qmatrix(const std::vector<unsigned>& shape):m_structure(shape),m_lock(false)  {
	unsigned siz = this->size();
	if(siz) this->initialblock(siz);
}



template<typename T, class S>
inline qmatrix<T,S>::qmatrix(const structure& str):m_structure(str),m_lock(false)  {
	unsigned siz = this->size();
	if(siz)  {
		this->initialblock(siz);
	}
}
*/

// Costructor from a data pointer
template<typename T, class S>
inline qmatrix<T,S>::qmatrix(unsigned rows, unsigned cols, numtype* data):
memoryblockRef<T>(data),m_structure(rows,cols),m_lock(true)  {}

/*
template<typename T, class S>
template<class S2>
qmatrix(const qm_matrix<T,S2& rhs):m_structure(rhs.structure())  {
	if(this->size() > 0)
	{
		if(copy_structure<S2,S>::has_same_structure)
			this->initialblock(rhs.noConst());
		else  {
			this->initialblock(size);
			for(unsigned r=0;r<this->rows();r++)
				for(unsigned c=0;c<this->cols();c++)
					(*this)(r,c) = rhs(r,c);
		}
	}
}
*/



template<typename T, class S>
template<class S2>
inline qmatrix<T,S>::qmatrix(const qmatrix<T,S2>& rhs, const S& structur):m_structure(structur),m_lock(false)  {
	QMAT_PRECONDITION(this->size() == rhs.size(),"Matrices with different dimensions");
	if(this->size() > 0)  {
		this->initialblock(rhs.noConst());
	}
}

/*
template<typename T, class S>
inline qmatrix<T,S>::qmatrix(const qmatrix<T,S>& rhs, const range& r0):m_structure(rhs.m_structure)  {
	if(this->length() > 0) this->initialblock(rhs.noConst());
	QMAT_PRECONDITION(this->checkrange(0,r0),"X-Range not compatible");
	m_rx   = r0;
	m_ry.setup(0,this->cols());
	m_rz.setup(0,this->deps());
}

template<typename T, class S>
inline qmatrix<T,S>::qmatrix(const qmatrix<T,S>& rhs, const range& r0, const range& r1):m_structure(rhs.m_structure)  {
	if(this->length() > 0) this->initialblock(rhs.noConst());
	QMAT_PRECONDITION(this->checkrange(0,r0) && this->checkrange(1,r1),"Ranges not compatibles");
	m_rx   = r0;
	m_ry   = r1;
	m_rz.setup(0,this->deps());
}
*/



template<typename T, class S>
inline void qmatrix<T,S>::resize1(unsigned r) {
	QM_REQUIRE(!this->is_locked(),"Matrix is locked. Cannot resize");
	if(!m_structure.resize1(r)) return;
	unsigned siz = this->size();
	this->newblock(siz);
}
template<typename T, class S>
inline void qmatrix<T,S>::resize(unsigned r, unsigned c) {
	QM_REQUIRE(!this->is_locked(),"Matrix is locked. Cannot resize");
	if(!m_structure.resize(r,c)) return;
	unsigned siz = this->size();
	this->newblock(siz);
}

template<typename T, class S>
inline bool qmatrix<T,S>::is_same(const qmatrix<T,S>& rhs) const {
	if(this == &rhs) return true;
	return false;
}

template<typename T, class S>
inline void qmatrix<T,S>::copy(const qmatrix<T,S>& rhs)  {
	if(this->is_same(rhs)) return;
	m_structure = rhs.m_structure;
	this->changeblock(rhs.noConst());
	//m_rx.setup(0,this->rows());
	//m_ry.setup(0,this->cols());
	//m_rz.setup(0,this->deps());
}

template<typename T, class S>
inline qmatrix<T,S> qmatrix<T,S>::duplicate(bool copycontent) const  {
	qmatrix<T,S> dup(m_structure);
	if(copycontent)
		for(unsigned i=0;i<this->size();++i) dup.m_data[i] = this->m_data[i];
	return dup;
}

/*
template<typename T,class S>
inline bool qmatrix<T,S>::checkrange(unsigned r, const range& rang) const {
	if(rang.first() >= 0 && rang.first() < this->length(r) &&
	   rang.last() >= 0 && rang.last() < this->length(r)) return true;
	return false;
}
*/

template<typename T, class S>
inline qmatrix<T,S>& qmatrix<T,S>::operator = (numtype x)  {
	for(unsigned i=0;i<this->size();++i) this->m_data[i] = x;
	return *this;
}

template<typename T, class S>
inline qmatrix<T,S>& qmatrix<T,S>::operator *= (numtype x)  {
	for(unsigned i=0;i<this->size();++i) this->m_data[i] *= x;
	return *this;
}




template<typename N, class S>
inline qmatrix<N,S>& qmatrix<N,S>::operator = (const qmatrix<N,S>& mat)  {
	QM_REQUIRE(m_structure == mat.m_structure,"Matrices with different dimensions");
	for(unsigned i = 0; i<m_structure.size(); i++) this->m_data[i] = mat.m_data[i];
	return *this;
}

template<typename N, class S>
template<class S2>
void qmatrix<N,S>::add_to_diagonal(const qmatrix<N,S2>& rhs)  {
	BOOST_STATIC_ASSERT(structureinfo<S>::Square);
	for(unsigned i=0;i<this->rows();i++)
		(*this)(i,i) += rhs(i);
}
template<typename N, class S>
template<class S2>
void qmatrix<N,S>::subtract_from_diagonal(const qmatrix<N,S2>& rhs)  {
	BOOST_STATIC_ASSERT(structureinfo<S>::Square);
	for(unsigned i=0;i<this->rows();i++)
		(*this)(i,i) -= rhs(i);
}

template<typename N, class S>
template<class R, bool F>
void qmatrix<N,S>::add_to_diagonal(const matrix_expr<R,F>& rhs)  {
	BOOST_STATIC_ASSERT(structureinfo<S>::Square);
	for(unsigned i=0;i<this->rows();i++)
		(*this)(i,i) += rhs(i);
}

/*
template<typename T, class S>
inline qmatrix<T,S>& qmatrix<T,S>::operator = (const qmatrix<T,S>& x)  {
	QMAT_PRECONDITION(m_structure == x.m_structure,"qmatrix = operator failed. Matrices with different dimensions.");
	for(unsigned i=0;i<this->size();++i) this->m_data[i] = x.m_data[i];
	return *this;
}
*/

template<typename T,class S>
template<typename R,bool F>
inline qmatrix<T,S>& qmatrix<T,S>::operator = (const matrix_expr<R,F>& x)  {
	matrix_assign<T,S,R,F>(*this,x);
	return *this;
}


template<typename T,class S> template<class N2, class S2>
bool qmatrix<T,S>::is_same_shape(const qmatrix<N2,S2>& rhs) const  {
	return structure_compare<S,S2>::same_shape(m_structure, rhs.structur());
}


///////////////////////////////////////////////////////////////////////////////


template<typename T, class S>
inline bool qmatrix<T,S>::is_symmetric(unsigned tole) const  {
	if(m_structure.is_symmetric()) return true;
	if(!m_structure.can_be_symmetric()) return false;
	if(!m_structure.is_square()) return false;
	//
	// Now we have a square matrix that could be symmetric. Need tocheck!
	numtype aij,aji;
	for(unsigned i=0;i<this->rows();++i)  {
		for(unsigned j=0;j<i;++j) {
			aij = (*this)(i,j);
			aji = (*this)(j,i);
			if(!close_enough(aij,aji,tole)) return false;
		}
	}
	return true;
}


template<typename T, class S>
inline qmatrix<T,symmetric_matrix> qmatrix<T,S>::get_symmetric(unsigned tole) const  {
	QM_REQUIRE(this->is_symmetric(tole),"Matric is not symmetric");
	unsigned R = this->rows();
	qmatrix<T,symmetric_matrix> sy(R);
	for(unsigned i=0;i<this->rows();++i)
		for(unsigned j=0;j<=i;++j) sy(i,j) = (*this)(i,j);
	return sy;
}

template<typename T, class S>
inline T qmatrix<T,S>::min() const  {
	numtype t = std::numeric_limits<numtype>::max();
	for(unsigned i=0;i<this->size();++i) t = std::min(t,this->m_data[i]);
	return t;
}

template<typename T, class S>
inline T qmatrix<T,S>::norm2() const  {
	numtype t = 0;
	for(unsigned i=0;i<this->size();++i) t = this->m_data[i]*this->m_data[i];
	return std::sqrt(t);
}

template<typename numtype, class S>
inline typename qmatrix<numtype,S>::transpos qmatrix<numtype,S>::transpose() const {
	return transpos(*this,m_structure.transpose());
}


template<class numtype, class S>
inline qmatrix<numtype,typename qmatrix<numtype,S>::square_structure>
qmatrix<numtype,S>::square() const  {
	QMAT_PRECONDITION(this->is_matrix(),"Qmatrix is not a matrix. Cannot square it");
	typedef qmatrix<numtype,square_structure> qmat; 
	unsigned R = this->rows();
	unsigned C = this->cols();
	qmat rs(C,C);
	if(!rs.size()) return rs;
	
	// Outer loop on column
	for(unsigned c = 0; c < C; ++c)
		// Inner loop at to column c
		for(unsigned k = 0; k <= c; ++k)  {
			numtype v = 0;
			// Row multiplication
			for(unsigned r = 0; r < R; ++r) v += (*this)(r,c)*(*this)(r,k);
			rs(c,k) = v;
		}
	return rs;
}

/*
template<class numtype, class S>
inline void qmatrix<numtype,S>::fill_random()  {
	MersenneTwister rnd;
	for(unsigned i=0;i<this->size();i++) this->m_data[i] = rnd.nextUniform();
}

template<class numtype, class S>
inline void qmatrix<numtype,S>::fill_normal(qm_real mu, qm_real sigma)  {
	MersenneTwister rnd;
	for(unsigned i=0;i<this->size();i++)
		this->m_data[i] = mu + sigma*rnd.nextNormalVariate();
}
*/




///////////////////////////////////////////////////////////////////////////////////////////


template<class numtype, class S>
inline qm_string qmatrix<numtype,S>::tostring()	const   {
	qm_string str = m_structure.tostring() + "\n";
	if(this->size() == 0) return str;
	if(this->is_vector())  {
		str += "["+object_to_string((*this)(0));
		for(unsigned i=1;i<this->rows();i++)
			str += ","+object_to_string((*this)(i));
		str += "]";
	}
	else if(this->is_matrix())  {
		str += "[";
		for(unsigned i=0;i<this->rows();i++)  {
			str += "["+object_to_string(this->get1(i,0));
			for(unsigned j=1;j<this->cols();j++)
				str += "," + object_to_string(this->get1(i,j));
			str += "]";
			if(i < this->rows()-1) str += "\n";
		}
		str += "]";
	}
	return str;
}




	
QM_NAMESPACE_END2


#endif	//	__QMATRIX_IMPL_QMAT_HPP__


