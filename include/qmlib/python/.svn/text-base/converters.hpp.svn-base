//
//
#ifndef __CONVERTERS_PYTHON_QM_H__
#define __CONVERTERS_PYTHON_QM_H__
//
//
//
#include <qmlib/python/pyconfig.hpp>
#include <qmlib/corelib/dates/date.hpp>
#include <datetime.h>



//
//
QM_NAMESPACE2(python)




template<class T, class TfromPy>
struct ObjFromPy  {
	ObjFromPy()  {
		boost::python::converter::registry::push_back(&TfromPy::convertible,
                                                      &TfromPy::construct,
                                                       boost::python::type_id<T>());
	}
};


/// \brief template class for automatic python conversion
/// @param T The C++ class subject of automatic conversion
/// @param TtoPy The class used for implementing the conversion from T to a python object
/// @param TfromPy The inverse of TtoPy
template<class T, class TtoPy, class TfromPy>
struct register_python_conversion  {
	register_python_conversion()  {
        boost::python::to_python_converter<T,TtoPy>();
        ObjFromPy<T,TfromPy>();
	}
};




struct DateToPy  {
	static PyObject* convert(const qdate& dte)  {
        PyDateTime_IMPORT;
        return PyDate_FromDate(dte.year(), dte.month(), dte.day());
    }
};

/*
template<class A, class B>
struct pairToPy  {
	typedef std::pair<A,B>	pair_type;
	typedef pairToPy<A,B>	pairtopy;
	static PyObject* convert(const pair_type& p)  {
		return boost::python::extract<PyObject*>(boost::python::make_tuple(p.first, p.second));
    }
	static void regist()  {
		boost::python::to_python_converter<pair_type,pairtopy>();
	}
};
*/


    struct DateFromPy  {
      //
      static void* convertible(PyObject* obj_ptr)  {
        PyDateTime_IMPORT;
        if(PyDate_Check(obj_ptr) || PyDateTime_Check(obj_ptr)) return obj_ptr;
        return 0;
      }
      //
      static void construct(PyObject* obj_ptr,
                            boost::python::converter::rvalue_from_python_stage1_data* data)
      {
        PyDateTime_IMPORT;
        int y = PyDateTime_GET_YEAR(obj_ptr);
        int m = PyDateTime_GET_MONTH(obj_ptr);
        int d = PyDateTime_GET_DAY(obj_ptr);
        qdate* dte = new qdate(y,m,d);
        //void* storage = ((boost::python::converter::rvalue_from_python_storage<qm_date>*)dte)->storage.bytes;
        //new (storage) dte;
        data->convertible = (void*)dte;
      }
    };
  //

typedef register_python_conversion<qdate, DateToPy, DateFromPy>  date_python_conversion;


QM_NAMESPACE_END2


#endif // __CONVERTERS_PYTHON_QM_H__

