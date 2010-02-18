//
/// \file
/// \brief Conversion to and from numpy array
//
#ifndef __NUMPY_CONVERTERS_QM_H__
#define __NUMPY_CONVERTERS_QM_H__


#include <qmlib/python/pyconfig.hpp>
#include <qmlib/qmat/qmatrix.hpp>

#ifndef NUMPYCPP_FILE_WITH_INIT
#define NO_IMPORT_ARRAY
#endif

#define PY_ARRAY_UNIQUE_SYMBOL numpycpp_PyArray_API
#include <numpy/arrayobject.h>


QM_NAMESPACE2(python)

using namespace boost::python;
using namespace qmlib::math;

template<typename T> struct numpytype;


#define DECLARE_DTYPE_FOR( type, tk, dtype, numtype)			\
template< > struct numpytype<type> {							\
	static const char type_kind = tk;							\
	static const int  type_num  = numtype;						\
	static std::string name() { return dtype; }					\
	static bool check_type_num(int num) {						\
        return type_num == num;									\
    }															\
};


DECLARE_DTYPE_FOR(float,  'f', "float32", NPY_FLOAT)
DECLARE_DTYPE_FOR(double, 'f', "float64", NPY_DOUBLE)



template<class T, class S>
class qmatrixwrap {
public:
	typedef T									  numtype;
	typedef numpytype<numtype>					  pytype;							  
	typedef QM_FROM_NAMESPACE2(math)qmatrix<T,S>  tvec;
	
	qmatrixwrap(unsigned rows = 0):m_mat(rows){}
	qmatrixwrap(unsigned rows, unsigned cols):m_mat(rows,cols){}
	qmatrixwrap(const tvec& rhs):m_mat(rhs),m_pyo(0){}
	qmatrixwrap(const tvec& rhs, const boost::python::object& pyo):m_mat(rhs),m_pyo(pyo){}
	qmatrixwrap(const boost::python::object& rhs, unsigned rows, unsigned cols, void* data):m_pyo(rhs),m_mat(rows,cols,(T*)data){}
	qmatrixwrap(const qmatrixwrap& rhs):m_mat(rhs.m_mat),m_pyo(rhs.m_pyo){}
	qmatrixwrap& operator = (const qmatrixwrap& rhs) {m_mat = rhs.m_mat; m_pyo = rhs.m_pyo; return *this;}
	qm_string tostring() const {return m_mat.tostring();}
	unsigned  size()	 const {return m_mat.size();}
	unsigned  rows()	 const {return m_mat.rows();}
	unsigned  cols()	 const {return m_mat.cols();}
	bool      get_owndata()	 const {return m_mat.get_owndata();}
	numtype	  get1(unsigned r, unsigned c) const	{return m_mat.get1(r,c);}
	void set1(unsigned r, unsigned c, const numtype& val) {m_mat.set1(r,c,val);}
	object	  numpy()    const {return m_pyo;}
	tvec	  matrix()   const {return m_mat;}
private:
	tvec	m_mat;
	object	m_pyo;
};

	
	
	

/// \brief Implementation of automatic conversion from numpy to a c++ array_type
template<typename T, class S>
class numpy_converter  {
public:
	typedef T							numtype;
	typedef numpytype<numtype>			dtype;
	typedef qmatrixwrap<numtype,S>		qmat;
	typedef typename qmat::tvec			tvec;
	
	static qmat convert(object npa);
	static PyObject* topython(const tvec& mat);
};


template<typename T, class S>
inline typename numpy_converter<T,S>::qmat
numpy_converter<T,S>::convert(boost::python::object npa)  {
	using namespace boost::python;
	std::string ntype;
	tuple shape;
	try {
		object ty = object(npa.attr("dtype"));
		ntype     = std::string(extract<char*>(ty.attr("name")));
		shape     = (tuple)npa.attr("shape");
	}
	catch(...) {
		QM_FAIL("object is not a numpy.ndarray");
	}
	QM_REQUIRE(ntype == dtype::name(), "array of wrong type");
	unsigned N = len(shape);
	QM_REQUIRE(N <= 2, "array must have 2 dimensions");
	void* data = PyArray_DATA(npa.ptr());
	unsigned rows = extract<unsigned>(shape[0]);
	unsigned cols = rows;
	if(N == 1)  {
		rows = 1;
	}
	else {
		cols = extract<unsigned>(shape[1]);
	}
	return qmat(npa,rows,cols,data);
}

template<typename T, class S>
//inline typename numpy_converter<T,S>::qmat
inline PyObject*
numpy_converter<T,S>::topython(const typename numpy_converter<T,S>::tvec& mat)  {
	npy_intp* shape = PyDimMem_NEW(2);
	shape[0]   = mat.rows();
	shape[1]   = mat.cols();
	void* data = (void*)mat.data();
	//PyObject* pobj = PyArray_FromDims(2,shape,dtype::type_num);
	//PyObject* pobj = PyArray_FromDimsAndData(2,shape,dtype::type_num,data);
	PyObject* pobj = PyArray_SimpleNewFromData(2,shape,dtype::type_num,data);
	return pobj;
	//object npy(pobj);
	//return qmat(mat,npy);
}


 
QM_NAMESPACE_END2



#endif // __NUMPY_CONVERTERS_QM_H__

