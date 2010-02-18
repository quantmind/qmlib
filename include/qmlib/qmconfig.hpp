//
/// @defgroup config
//
#ifndef __CONFIG_QM_H__
#define __CONFIG_QM_H__
//
//#include <qmlib/boost_user_config.h>
#include <boost/config.hpp>
#include <boost/version.hpp>
//
//
#if BOOST_VERSION < 103100
    #error using an old version of Boost, please update.
#endif
//
#if !defined(BOOST_ENABLE_ASSERT_HANDLER)
    #define BOOST_ENABLE_ASSERT_HANDLER
#endif
//
//
#endif  //  __CONFIG_QM_H__
