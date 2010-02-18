//
//
/// \file
/// \brief Expose the rate library to python
///
/// Exposes the main rate object to python in a polymorphic mannar
/// \ingroup python



#ifndef __RATE_WRAP_QM_HPP__
#define __RATE_WRAP_QM_HPP__


#include <qmlib/python/dataserie_wrap.hpp>
#include <qmlib/finance/rates/volsurface.hpp>
#include <qmlib/finance/instruments/cap.hpp>
#include <qmlib/finance/instruments/future.hpp>




QM_NAMESPACE2(python)


/// \brief Python wrapper for general rates
/// \ingroup python
template<class T>
class generalrate_wrapper : public T, public boost::python::wrapper<T>  {
public:
	generalrate_wrapper(){}
	
	qm_string rate_string() const {
        if(boost::python::override overfun = this->get_override("rate_string"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL_BASE)
          return boost::python::call<qm_real>(overfun.ptr());
#       else
          return overfun();
#       endif
        return T::rate_string();		
	}
	
	qdate referenceDate() const  {
        if(boost::python::override overfun = this->get_override("referenceDate"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL_BASE)
          return boost::python::call<qm_real>(overfun.ptr());
#       else
          return overfun();
          //return boost::python::call<qdate>(overfun.ptr());
#       endif
        return T::referenceDate();
	}
};




/// \brief Python wrapper for itermstructure
/// \ingroup python
template<class T>
class itermstructure_wrapper : public generalrate_wrapper<T>  {
public:

	qm_real dcf(const qdate& dte) const  {
        if(boost::python::override overfun = this->get_override("dcf"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL_BASE)
          return boost::python::call<qm_real>(overfun.ptr(),dte);
#       else
          return overfun(dte);
#       endif
        return T::dcf(dte);
	}
};

    
/// \brief Python wrapper for idiscountcurve
/// \ingroup python
template<class T>
class idiscountcurve_wrapper: public itermstructure_wrapper<T>  {
public:
	
	qm_real dft(qm_real t) const  {
        if(boost::python::override overfun = this->get_override("dft"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL_BASE)
          return boost::python::call<qm_real>(overfun.ptr(),t);
#       else
          return overfun(t);
#       endif
        return T::dft(t);
    }

	qm_real df(const qdate& dte) const  {
        if(boost::python::override overfun = this->get_override("df"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL_BASE)
          return boost::python::call<qm_real>(overfun.ptr(),dte);
#       else
          return overfun(dte);
#       endif
        return T::df(dte);
    }
};

template<class T>
class ivolsurface_wrapper: public itermstructure_wrapper<T>  {
public:
	
	qm_real striketomoneyness(qm_real t) const  {
        if(boost::python::override overfun = this->get_override("striketomoneyness"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL_BASE)
          return boost::python::call<qm_real>(overfun.ptr(),t);
#       else
          return overfun(t);
#       endif
        return T::striketomoneyness(t);
    }

	qm_real blackvol(qm_real strike, const dateperiod& dte) const  {
        if(boost::python::override overfun = this->get_override("blackvol"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL_BASE)
          return boost::python::call<qm_real>(overfun.ptr(),strike,dte);
#       else
          return overfun(dte);
#       endif
        return T::blackvol(strike,dte);
    }
	
	qm_real bpvol(qm_real strike, const dateperiod& dte) const  {
        if(boost::python::override overfun = this->get_override("bpvol"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL_BASE)
          return boost::python::call<qm_real>(overfun.ptr(),strike,dte);
#       else
          return overfun(dte);
#       endif
        return T::bpvol(strike,dte);
    }
};


template<class V>
inline void export_compositerate_base(const std::string& name, const std::string& info)  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(finance);
    
    typedef V												rate_type;
    typedef typename rate_type::composite_type				comprates;
    typedef typename comprates::element_type				element_type;
    typedef typename comprates::element_composite_type		element_composite_type;
    typedef typename comprates::key_type					key_type;
    typedef typename comprates::element_composite_wrap		element_composite_wrap;
    
    return_value_policy<copy_const_reference> ccr;
    
    qm_string na1  = name + "_composite_rate_base";
    qm_string nae  = name + "_composite_rate_base_element";
    qm_string naes = nae  + "_serie";
    
    export_dataserie<key_type,true,element_composite_wrap>(naes,info);
    
    class_<comprates>(na1.c_str(),info.c_str(),no_init)
    	.def("append",              &comprates::template add< otcir >)
    	.def("append",              &comprates::template add< irfuture >)
    	.def("append",              &comprates::template add< capfloor >)
    	//.def("append",             &comprates::add< fxvanilla >)
    	.def("append",              &comprates::template add< swaption >)
    	.def("append",              &comprates::template add< vanillaswap >)
    	.def("append",              &comprates::template add< fra >)
    	.def("__getitem__",         &comprates::get)
    	.def("refresh",				&comprates::refresh)
    	.def("__iter__",            iterator<comprates>())
    	.add_property("allinsts",	make_function(&comprates::allinsts,ccr))
       	;
    
   	class_<element_composite_wrap>(nae.c_str(),info.c_str(),no_init)
       	.def("__str__",              &element_composite_wrap::tostring)
       	.def("__repr__",             &element_composite_wrap::tostring)
      	.add_property("keyval",	 	 make_function(&element_composite_wrap::keyval,ccr))
      	.add_property("elem",	 	 &element_composite_wrap::elem)
        ;
    
    register_ptr_to_python<QM_SMART_PTR(V) >();
}


template<class V>
inline void export_volsurfacebases(const std::string& name, const std::string& info)  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(finance);
    
    return_value_policy<copy_const_reference> ccr;
    
    typedef volsurftraits<V>								vol_traits;
    typedef typename vol_traits::base_vol_class				basevol;
    typedef typename vol_traits::composite_type				composite_type;
    typedef typename vol_traits::vanilla_type				vanilla_type;
    typedef typename vol_traits::cross_section_type 		cross_section_type;
    typedef typename cross_section_type::composite_type 	base_cross;
    
    // Export the cross section
    qm_string nac = name + "_cross_section";
    export_compositerate_base<cross_section_type>(nac,info);
    class_<cross_section_type, bases<base_cross, itermstructure > >(nac.c_str(),info.c_str(),no_init)
    	.add_property("maturity",		make_function(&cross_section_type::maturity,ccr))
    	.add_property("ttm",			&cross_section_type::ttm)
       	;
    
    // Export the basevolatility surface
    qm_string na1 = name + "_base_volatility";
    export_compositerate_base<basevol>(na1,info);
    class_<basevol, bases<ivolsurface, composite_type > >(na1.c_str(),info.c_str(),no_init)
       	;
    
    register_ptr_to_python<QM_SMART_PTR(V) >();
}



    
QM_NAMESPACE_END2



#endif // __RATE_WRAP_QM_HPP__


