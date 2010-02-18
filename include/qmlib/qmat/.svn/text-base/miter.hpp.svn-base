

#ifndef		__MITER_QMAT_HPP__
#define		__MITER_QMAT_HPP__


#ifndef __QMATRIX_QMAT_HPP__
 #error <qmlib/qmat/miter.hpp> must be included via <qmlib/qmat/matrix.hpp>
#endif


QM_NAMESPACE2(math)


template<typename T, class S = default_structure>
class qmatrix_ref  {
public:
    typedef  T 					numtype;
    typedef  qmatrix<T,S>		holder;
    typedef  qmatrix_ref<T,S>	myself;
    typedef  myself				reference;
    
    static const bool can_be_nested	= true;
    
    qmatrix_ref(const holder& m):m_matrix(&m) { }
    qmatrix_ref(const myself& rhs):m_matrix(rhs.m_matrix) { }
    //qmatrix_ref& operator = (const holder& m) {m_matrix = &m; return *this;}

    const numtype& operator()(unsigned i) 							const {return (*m_matrix)(i);}
    const numtype& operator()(unsigned i, unsigned j) 				const {return (*m_matrix)(i,j);}
    unsigned rows() const  { return m_matrix->rows(); }
    unsigned cols() const  { return m_matrix->cols(); }

private:
	qmatrix_ref() { } 

    const holder* m_matrix;
};


/*
template<typename T>
class qmat_iterator_base : public qindex  {
public:
	typedef T                			numtype;
	typedef qmatrix<numtype> 			vector;
	typedef tinyvec<unsigned,2>			dim_holder;
	
	qmat_iterator_base(const vector& mat):qindex(mat.dims()), m_data(mat.data()) {}
	
	~qmat_iterator_base(){}
	
protected:
	qmat_iterator_base(){}
	
	numtype*				m_data;
};




template<typename T>
class const_qmat_iterator : public qmat_iterator_base<T> {
public:
	typedef T                						numtype;
	typedef qmatrix<numtype> 						vector;
	typedef qmat_iterator_base<numtype> 			base_class;
	
	const_qmat_iterator(const vector& mat):base_class(mat){}
	
	numtype  operator () (unsigned r, unsigned c = 0) 	const	{ return this->m_data[this->index(r,c)];}
protected:
};
*/

QM_NAMESPACE_END2


#endif	//	__MITER_QMAT_HPP__


