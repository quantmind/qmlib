//
/// @defgroup python
/// @defgroup python_bloomberg
/// \file
/// \brief Configuration file for python wrappers
//
#ifndef   __WRAP_PYTHON_CONFIG_QM_H__
#define   __WRAP_PYTHON_CONFIG_QM_H__
//
/// \brief Boost Python Pure Virtual overaload flag for Microsoft Visual Studio
#define BOOST_PYTHON_MSVS_VIRTUAL         1300
//
/// \brief Boost Python Pure Virtual overaload flag for Microsoft Visual Studio
#define BOOST_PYTHON_MSVS_VIRTUAL_BASE    1500
//
//
//
//
#include <qmlib/definitions.hpp>
#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/wrapper.hpp>
#include <boost/python/detail/prefix.hpp>
#include <boost/python/converter/return_from_python.hpp>
#include <boost/python/call.hpp>
//
//

//#define qm_list                 boost::python::list
//#define qm_info_dict			boost::python::dict

//
//
//
#endif // __WRAP_PYTHON_CONFIG_QM_H__
//
