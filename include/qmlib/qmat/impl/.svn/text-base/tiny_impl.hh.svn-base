

#ifndef		__TINY_IMPL_QMAT_HPP__
#define		__TINY_IMPL_QMAT_HPP__


//#ifndef __QMATRIX_QMAT_HPP__
// #error <qmlib/qmat/impl/qmatrix_impl.hpp> must be included via <qmlib/qmat/qmatrix.hpp>
//#endif

//#include<qmlib/math/random/rndgen.hpp>



QM_NAMESPACE


//template<>
template<class T,unsigned N>
struct object_to_string_o<QM_FROM_NAMESPACE2(math)tinyvec<T,N> >  {
	static qm_string get(const QM_FROM_NAMESPACE2(math)tinyvec<T,N>& vec)  {
		qm_string va = "[" + object_to_string(vec[0]); 
		for(unsigned i=1;i<N;i++) va += ", " + object_to_string(vec[i]);
		va += "]";
		return va;
	}
};

//template<>
template<class T,unsigned Nr,unsigned Nc>
struct object_to_string_o<QM_FROM_NAMESPACE2(math)tinymat<T,Nr,Nc> >  {
	static qm_string get(const QM_FROM_NAMESPACE2(math)tinymat<T,Nr,Nc>& mat)  {
		qm_string va = "[ ";
		for(unsigned r=0;r<Nr;r++)  {
			va += "[ " + object_to_string(mat(r,0));
			for(unsigned i=1;i<Nc;i++) va += " , " + object_to_string(mat(r,i));
			va += " ]";
			if(r<Nr-1) va += "\n";
		}
		va += " ]";
		return va;
	}
};


//template<>
template<class T, unsigned N>
struct qmoper<QM_FROM_NAMESPACE2(math)tinyvec<T,N> >  {
	static qm_real abs(const QM_FROM_NAMESPACE2(math)tinyvec<T,N>& x) {
		T v = std::sqrt(x.inner(x));
		return qmoper<T>::abs(v);
	}
};


QM_NAMESPACE_END




QM_NAMESPACE2(math)


template<typename T, unsigned N_len>
inline tinyvec<T,N_len>::tinyvec(const T x0, const T x1) {
	BOOST_STATIC_ASSERT(N_len==2);
	m_data[0] = x0;
	m_data[1] = x1;
}

template<typename T, unsigned N_len>
inline tinyvec<T,N_len>::tinyvec(const T x0, const T x1, const T x2) {
	BOOST_STATIC_ASSERT(N_len==3);
	m_data[0] = x0;
	m_data[1] = x1;
	m_data[2] = x2;
}

template<typename T, unsigned N_len>
inline tinyvec<T,N_len>::tinyvec(const T x0, const T x1, const T x2, const T x3) {
	BOOST_STATIC_ASSERT(N_len==4);
	m_data[0] = x0;
	m_data[1] = x1;
	m_data[2] = x2;
	m_data[3] = x3;
}

template<typename T, unsigned N_len>
inline tinyvec<T,N_len>::tinyvec(const T x0, const T x1, const T x2, const T x3,
								 const T x4) {
	BOOST_STATIC_ASSERT(N_len==5);
	m_data[0] = x0;
	m_data[1] = x1;
	m_data[2] = x2;
	m_data[3] = x3;
	m_data[4] = x4;
}

template<typename T, unsigned N_len>
inline tinyvec<T,N_len>::tinyvec(const T x0, const T x1, const T x2, const T x3,
								 const T x4, const T x5) {
	BOOST_STATIC_ASSERT(N_len==6);
	m_data[0] = x0;
	m_data[1] = x1;
	m_data[2] = x2;
	m_data[3] = x3;
	m_data[4] = x4;
	m_data[5] = x5;
}

template<typename T, unsigned N_len>
inline tinyvec<T,N_len>::tinyvec(const T x0, const T x1, const T x2, const T x3,
								 const T x4, const T x5, const T x6) {
	BOOST_STATIC_ASSERT(N_len==7);
	m_data[0] = x0;
	m_data[1] = x1;
	m_data[2] = x2;
	m_data[3] = x3;
	m_data[4] = x4;
	m_data[5] = x5;
	m_data[6] = x6;
}

template<typename T, unsigned N_len>
inline bool tinyvec<T,N_len>::operator == (const tinyvec<T,N_len>& rhs) const {
	for(unsigned i=0;i<N_len;i++)
		if((*this)[i] != rhs[i]) return false;
	return true;
}
template<typename T, unsigned N_len>
inline bool tinyvec<T,N_len>::operator != (const tinyvec<T,N_len>& rhs) const {
	return !((*this) == rhs);
}


//___________________________________________________________________________-
//		TINYMAT


template<typename T, unsigned N_rows, unsigned N_cols>
inline tinymat<T,N_rows,N_cols>::tinymat(const numtype v0, const numtype v1,
										 const numtype v2, const numtype v3)  {
	BOOST_STATIC_ASSERT(_size==4);
	m_data[0] = v0;
	m_data[1] = v1;
	m_data[2] = v2;
	m_data[3] = v3;
}



template<typename T, unsigned N_len>
inline qm_string tinyvec<T,N_len>::tostring() const {
	return object_to_string(*this);
}



template<typename T, unsigned Nr, unsigned Nc>
inline qm_string tinymat<T,Nr,Nc>::tostring() const {
	return object_to_string(*this);
}


template<class T>
struct matrix_access<T,unsigned>  {
	typedef T							mattype;
	typedef typename mattype::numtype	numtype;
	
	static numtype get(const mattype& rhs, unsigned idx)  {
		return rhs.get1(idx,0);
	}
	static void set(mattype& rhs, unsigned idx, const numtype& val)  {
		rhs.set1(idx,0,val);
	}
};



QM_NAMESPACE_END2

#endif	// __TINY_IMPL_QMAT_HPP__
