///////////////////////////////////////////////////////////////////////////////
/// \file time_series_base.hpp
/// CRTP base class for all series
//

#ifndef QMLIB_TIME_SERIES_BASE_HPP_
#define QMLIB_TIME_SERIES_BASE_HPP_

#include <boost/time_series/time_series_fwd.hpp>

namespace qmlib { namespace timeseries
{
    struct timeseries_root {};

    template<typename Derived>
    struct timeseries_base : timeseries_root   {
        typedef Derived derived_type;

        Derived &cast()  {
            return *static_cast<Derived *>(this);
        }

        Derived const &cast() const  {
            return *static_cast<Derived const *>(this);
        }
    };
}}

#endif