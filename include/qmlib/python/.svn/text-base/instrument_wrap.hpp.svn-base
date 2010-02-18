/*******************************************************************************
 * qmlib/finance/base_rates.hpp
 * 
 * Copyright (C) 2007-2008 Luca Sbardella <luca.sbardella@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Suggestions:          quant.mind@gmail.com
 * Bugs:                 quant.mind@gmail.com
 *
 * For more information, please see the quantmind Home Page:
 *    http://www.quantmind.com
 *
 *******************************************************************************/

#ifndef __INSTRUMENT_WRAP_QM_HPP__
#define __INSTRUMENT_WRAP_QM_HPP__



#include <qmlib/python/converters.hpp>
#include <qmlib/finance/derivative.hpp>



QM_NAMESPACE2(python)

template<class U>
inline void export_derivative(const std::string& name, const std::string& info)  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(finance);
    
    typedef derivative<U>     deri;
    typedef option_base<U>    optb;
    typedef vanilla_option<U> vopt;
    
    qm_string na1 = name + "DerivativeBase";
    qm_string na2 = name + "OptionBase";
    qm_string na3 = name + "VanillaOptionBase";
    	
    class_<deri, bases<instrument_base> >(na1.c_str(),info.c_str(),no_init)
       	.add_property("underlying",      &deri::underlying)
       	;
    
    class_<optb, bases<deri> >(na2.c_str(),info.c_str(),no_init)
       	.add_property("expirytype",      &optb::expiry_type)
       	;
    
    class_<vopt, bases<optb> >(na3.c_str(),info.c_str(),no_init)
    	.add_property("otype",      	 &vopt::type)
       	.add_property("strike",      	 &vopt::get_strike, &vopt::set_strike)
       	;
}

template<class U, bool EA>
inline void export_portfolio(const std::string& name, const std::string& info)  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(finance);
    
    typedef portfolio<U>     port;
    
    qm_string na1 = name + "PortfolioBase";
    
    if(EA)  {
    	class_<port, bases<U> >(na1.c_str(),info.c_str(),no_init)
       		.def("add",      			&port::add)
       		.def("__len__",      		&port::size)
       		.add_property("front",      &port::front)
       		.add_property("back",      	&port::back)
       		.def("__iter__",            boost::python::iterator<port>())
       		.def("__getitem__",         &port::get)
       		;
    }
    else  {
    	class_<port, bases<U> >(na1.c_str(),info.c_str(),no_init)
       		.def("__len__",      		&port::size)
       		.add_property("front",      &port::front)
       		.add_property("back",      	&port::back)
       		.def("__iter__",            boost::python::iterator<port>())
       		.def("__getitem__",         &port::get)
       		;
    }
}



QM_NAMESPACE_END2



#endif // __INSTRUMENT_WRAP_QM_HPP__

