///////////////////////////////////////////////////////////////////////////////
/// \file time_series_base.hpp
/// CRTP base class for all series
//

#ifndef QMLIB_TIMESERIES_BASE_HPP_
#define QMLIB_TIMESERIES_BASE_HPP_


namespace qmlib { namespace timeseries
{
    struct timeseries_root {};

    template<typename Derived>
    struct timeseries_base: timeseries_root   {
        typedef Derived derived_type;

        Derived &cast()  {
            return *static_cast<Derived *>(this);
        }

        Derived const &cast() const  {
            return *static_cast<Derived const *>(this);
        }
    };
}}

#endif	//	QMLIB_TIMESERIES_BASE_HPP_