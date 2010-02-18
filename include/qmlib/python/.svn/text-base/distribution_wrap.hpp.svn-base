//
/// \file
/// \ingroup python
//
#ifndef __DISTRIBUTION_WRAP_QM_HPP__
#define __DISTRIBUTION_WRAP_QM_HPP__
//
//
#include <qmlib/python/converters.hpp>
#include <qmlib/math/distributions/distribution_base.hpp>
//
//
//
QM_NAMESPACE2(python)
    //
	//
    //
    //
    /// \brief Helper function which exposes to python the timeserie class template
    /// \ingroup python
    //
    // @param name The python class name
    // @param info The python information string of class name
    // @param D The date class used in timeserie
    // @param T The value class used in timeserie
    template<class dist>
    inline void export_distribution(const std::string& name, const std::string& info)  {
    	
    	using namespace boost::python;
    	QM_USING_NAMESPACE2(math);

    	class_<dist>(name.c_str(), info.c_str(), no_init)
    		.def("mean",			&dist::mean)
    		.def("stdev",			&dist::stdev)
    		.def("variance",		&dist::variance)
    		.def("skewness",		&dist::skewness)
    		.def("excessKurtosis",	&dist::excessKurtosis)
    		.def("density",			&dist::density)
        ;
    }

}}
//
//
//
#endif // __DISTRIBUTION_WRAP_QM_HPP__
