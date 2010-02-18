//
//
#ifndef   __LOG_PYTHON_WRAP_QM__
#define   __LOG_PYTHON_WRAP_QM__


#include <boost/python/wrapper.hpp>
#include <qmlib/ilog.hpp>


QM_NAMESPACE2(python)


/// \brief Exposes the ilog interface polyphormism to python
/// \ingroup python
class ilog_wrapper : public ilog, public boost::python::wrapper<ilog> {
public:
	
    void fire() {
        if(boost::python::override overfun = this->get_override("fire"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL)
          boost::python::call<void>(overfun.ptr());
#       else
          overfun();
#       endif
        ilog::fire();
    }
/*
    void critical(const qm_string& msg) {
        if(boost::python::override overfun = this->get_override("critical"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL)
          boost::python::call<void>(overfun.ptr(),msg);
#       else
          overfun(msg);
#       endif
        ilog::critical(msg);
    }

    void error(const qm_string& msg) {
        if(boost::python::override overfun = this->get_override("error"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL)
          boost::python::call<void>(overfun.ptr(),msg);
#       else
          overfun(msg);
#       endif
        ilog::error(msg);
    }

    void warning(const qm_string& msg) {
        if(boost::python::override overfun = this->get_override("warning"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL)
          boost::python::call<void>(overfun.ptr(),msg);
#       else
          overfun(msg);
#       endif
        ilog::warning(msg);
    }

    void debug(const char* msg) {
        if(boost::python::override overfun = this->get_override("debug"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL)
          boost::python::call<void>(overfun.ptr(),msg);
#       else
          overfun(msg);
#       endif
        ilog::debug(msg);
    }
	*/
};


QM_NAMESPACE_END2


#endif  //  __LOG_PYTHON_WRAP_QM__
//
//