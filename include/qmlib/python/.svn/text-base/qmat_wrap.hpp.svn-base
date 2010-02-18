
/// \file
///
/// Template function to export the qmat library to python




#ifndef		__QMAT_WRAP_QM_HPP__
#define		__QMAT_WRAP_QM_HPP__



#include <qmlib/python/numpy.hpp>
#include <qmlib/python/serialize.hpp>
#include <qmlib/qmat/linalg.hpp>



QM_NAMESPACE


/// Specialize the convert From python list to qmatrix
//template<>
template<class N, class S>
struct convert<boost::python::list,QM_FROM_NAMESPACE2(math)qmatrix<N,S> >  {
	
	convert(const boost::python::list& from, QM_FROM_NAMESPACE2(math)qmatrix<N,S>& to)  {
	    using namespace boost::python;
	    typedef QM_FROM_NAMESPACE2(math)qmatrix<N,S> qmat;
	    unsigned n = extract<unsigned>(from.attr("__len__")());
	    if(!n) return;
	    //
	    qmat vec(n);
	    try  {
	      for(unsigned i=0;i<n;++i)
	        vec(i) = extract<N>(from[i]);
	      to.copy(vec);
	    }
	    catch(...)  {
	      QM_FAIL("could not convert python list to qmatrix array");
	    }
	}
};


/// Specialize the convert From qmatrix to python list
//template<>
template<class N, class S>
struct convert<QM_FROM_NAMESPACE2(math)qmatrix<N,S>, boost::python::list >  {
	
	convert(const QM_FROM_NAMESPACE2(math)qmatrix<N,S>& from, boost::python::list& to)  {
	    for(unsigned i=0;i<from.rows();++i)
	      to.append(from(i));
	}
};

QM_NAMESPACE_END


QM_NAMESPACE2(math)


/// \brief Convert a Python tuple into a tinyvec
/// \ingroup python
template<typename T, unsigned N>
struct tinyvec_make<T,N,boost::python::tuple>  {
	typedef tinyvec<T,N> vtype;
	 static void make(const boost::python::tuple& tup, vtype& vec)  {
		 unsigned M = len(tup);
		 if(M != N) QM_FAIL("Bad number of indices");
		 for(unsigned i=0;i<N;i++)  {
			 try  {
				 vec[i] = boost::python::extract<T>(tup[i]);
			 }
			 catch(...)  {
				 QM_FAIL("Bad indices value");
			 }
		 }
	 }
};


template<class T>
struct matrix_access<T,boost::python::tuple>  {
	typedef T							mattype;
	typedef typename mattype::numtype	numtype;
	typedef boost::python::tuple		idxtype;
	
	static numtype get(const mattype& rhs, const idxtype& idx)  {
		unsigned N = len(idx);
		if(N > 2) QM_FAIL("too many indexes");
		unsigned i0 = boost::python::extract<unsigned>(idx[0]);
		if(N == 1) return rhs.get1(i0,0);
		else  {
			unsigned i1 = boost::python::extract<unsigned>(idx[1]);
			return rhs.get1(i0,i1);
		}
	}
	static void set(mattype& rhs, const idxtype& idx, const numtype& val)  {
		unsigned N = len(idx);
		if(N > 2) QM_FAIL("too many indexes");
		unsigned i0 = boost::python::extract<unsigned>(idx[0]);
		if(N == 1) rhs.set1(i0,0,val);
		else  {
			unsigned i1 = boost::python::extract<unsigned>(idx[1]);
			rhs.set1(i0,i1,val);
		}
	}
};


QM_NAMESPACE_END2




QM_NAMESPACE2(python)



/// \brief Export tinyvec class templates to Python
template<class T, unsigned N>
inline void export_tinyvec(const std::string& name, const std::string& info)  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    	
    typedef tinyvec<T,N> tvec;

#	ifdef	QM_SERIALIZE
    typedef qmlib_pickle_suite<tvec> my_pickle;
#	endif	//	QM_SERIALIZE
    	
    class_<tvec>(name.c_str(),info.c_str())
    	.def(init<T>())
       	.def("__str__",				 &tvec::tostring)
       	.def("__repr__",			 &tvec::tostring)
       	.def("__len__",				 &tvec::length)
       	.add_property("size",      	 &tvec::length)
       	.add_property("norm2",       &tvec::norm2)
       	.def("__getitem__",          &tvec::get)
       	.def("__setitem__",			 &tvec::set)
       	.def("tolist",				 &tvec::template tolist<qm_list>)
       	.def("fill",				 &tvec::fill)
       	.def("fill",				 &tvec::copydata)
		.def("copy",				 &tvec::copy)
#		ifdef	QM_SERIALIZE
       	.def_pickle(my_pickle())
#		endif	//	QM_SERIALIZE
       	;
}

/// \brief Export tinyvec template to Python
template<class T, unsigned Nr, unsigned Nc>
inline void export_tinymat(const std::string& name, const std::string& info)  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    	
    typedef tinymat<T,Nr,Nc>    		 tvec;
    typedef matrix_access<tvec,tuple>	 atype;
    	
    class_<tvec>(name.c_str(),info.c_str())
    	.def(init<T>())
       	.def("__str__",				 &tvec::tostring)
       	.def("__repr__",			 &tvec::tostring)
       	.def("__len__",				 &tvec::length)
       	.add_property("rows",      	 &tvec::rows)
		.add_property("cols",      	 &tvec::cols)
       	.add_property("size",      	 &tvec::length)
       	.def("__getitem__",          &atype::get)
       	.def("__setitem__",			 &atype::set)
       	.def("inverse",  			 &tvec::inverse)	
       	//.def("tolist",				 &tvec::template tolist<qm_list>)
       	;
}



template<class T, class S>
inline void export_qmatrix(const std::string& name, const std::string& info)  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    	
    typedef qmatrixwrap<T,S> 			 tvec;
    typedef matrix_access<tvec,tuple>	 atype;
    typedef matrix_access<tvec,unsigned> utype;

#	ifdef	QM_SERIALIZE
    typedef qmlib_pickle_suite<tvec>     my_pickle;
#	endif	//	QM_SERIALIZE

    //return_value_policy<copy_const_reference> ccr;
    	
    class_<tvec>(name.c_str(),info.c_str(),init<optional<unsigned> >())
    	.def(init<unsigned,unsigned>())
       	.def("__str__",				 &tvec::tostring)
       	.def("__repr__",			 &tvec::tostring)
       	.def("__len__",				 &tvec::size)
		.add_property("owndata",	 &tvec::get_owndata)
       	.add_property("size",      	 &tvec::size)
       	.add_property("rows",      	 &tvec::rows)
		.add_property("cols",      	 &tvec::cols)
		.add_property("numpy",		 &tvec::numpy)
		//.add_property("is_vector",   &tvec::is_vector)
		//.add_property("is_matrix",   &tvec::is_matrix)
		//.add_property("is_square",   &tvec::is_square)
       	.def("__getitem__",          &atype::get)
       	.def("__getitem__",          &utype::get)
       	.def("__setitem__",			 &atype::set)
       	.def("__setitem__",			 &utype::set)
       	//.def("fill",				 &tvec::fill)
       	//.def("fillrandom",			 &tvec::fill_random)
       	//.def("fill_normal",			 &tvec::fill_normal)
       	//.add_property("numrefs",	 &tvec::numReferences)
       	//.add_property("is_locked",   &tvec::is_locked)
       	//.def("transpose", 			 &tvec::transpose)
       	//.def("resize",				 &tvec::resize1)
       	//.def("resize",				 &tvec::resize)
       	//.def("tolist",				 &tvec::template tolist<list>)
#		ifdef	QM_SERIALIZE
       	//.def_pickle(my_pickle())
#		endif	//	QM_SERIALIZE
       	;
    
}


template<class T>
inline void export_ludecomp(const std::string& name, const std::string& info)  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    	
    typedef LUdecomp<T> lud;
    //return_value_policy<copy_const_reference> ccr;
    	
    class_<lud>(name.c_str(),info.c_str(),init<const qmatrix<T>& >())
       	.def("__str__",				 &lud::tostring)
       	.def("__repr__",			 &lud::tostring)
       	.def("__len__",				 &lud::size)
       	.add_property("size",      	 &lud::size)
		.add_property("L",   		 &lud::L)
		.add_property("U",   		 &lud::U)
		.add_property("permutation", &lud::template permutation_list<qm_list>)
       	;
    
}


QM_NAMESPACE_END2



#endif	//	__QMAT_WRAP_QM_HPP__

