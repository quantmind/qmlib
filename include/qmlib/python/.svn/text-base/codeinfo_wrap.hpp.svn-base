//
//
#ifndef __CODEINFO_WRAP_QM_H__
#define __CODEINFO_WRAP_QM_H__
//
//
#include <qmlib/python/pyconfig.hpp>
//
//
//
QM_NAMESPACE2(python)
    //
    //
    //
    /// \brief icodeinfo wrapper template for python
    /// \ingroup python
    template<class iT>
    class codeinfo_wrapper : public iT, public boost::python::wrapper<iT>
    {
    public:
      codeinfo_wrapper(){}
      //
      qm_info_dict get_info() const
      {
        if(boost::python::override f = this->get_override("get_info"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL)
          return boost::python::call<qm_info_dict>(f.ptr());
#       else 
          return f();
#       endif
        return iT::get_info();
      }
      //
      qm_string code() const
      {
        if(boost::python::override f = this->get_override("code"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL_BASE)
          return boost::python::call<qm_string>(f.ptr());
#       else 
          return ret_string(f);
#       endif
        return iT::code();
      }
      //
      qm_string name() const
      {
        if(boost::python::override f = this->get_override("name"))
        {
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL_BASE)
          return boost::python::call<qm_string>(f.ptr());
#       else
          return f();
#       endif
        }
        return iT::name();
      }
      //
      //qm_string    default_code() const {return this->iT::code();}
      //qm_string    default_name() const {return this->iT::name();}
      //qm_info_dict default_info() const {return this->iT::get_info();}
    };
    //
    //
}}
//
//
//
#endif // __CODEINFO_WRAP_QM_H__
//
//