
#ifndef __PDE_WRAP_QM_H__
#define __PDE_WRAP_QM_H__


#include <qmlib/python/pyconfig.hpp>
#include <qmlib/math/pde/model_coef.hpp>

/** \file
 * \ingroup python
 * \brief Expose the pde library to Python
 */




QM_NAMESPACE2(python)


	
template<class Op>
inline void export_pde_operator(const std::string& name, const std::string& info)  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    	
    typedef structured_operator<Op> opera;
    typedef typename Op::GRIDTYPE	GRIDTYPE;
    	
    class_<opera>(name.c_str(),info.c_str(),init<optional<GRIDTYPE> >())
       	.def("__str__",				 &opera::tostring)
       	.def("__repr__",			 &opera::tostring)
       	.def("__len__",				 &opera::points)
       	.add_property("points",      &opera::points)
       	.add_property("direction",   &opera::direction)
       	.add_property("grid",   	 &opera::grid)
       	;
}


// \brief Export a pde model to Python
template<class T, unsigned N>
inline void export_pde_model(const std::string& name, const std::string& info)  {
	
    using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    
    return_value_policy<copy_const_reference> ccr;
    
    typedef pdemodel_base<T,N> pdemod;
    
    class_<pdemod>(name.c_str(),info.c_str(),no_init)
		.def("__str__",					&pdemod::tostring)
		.def("__repr__",				&pdemod::tostring)
		.add_property("dimensions",		&pdemod::dimensions)
		.add_property("grid",			&pdemod::grid)
		.add_property("dtmax",  		&pdemod::dtmax)
		.add_property("timegrid",		make_function(&pdemod::get_timegrid,ccr), &pdemod::set_timegrid)
		.add_property("initial",		make_function(&pdemod::get_initial,ccr), &pdemod::set_initial)
		.add_property("linear",			&pdemod::islinear)
		.add_property("timedependent",	&pdemod::timedependent)
		.add_property("final",			make_function(&pdemod::final,ccr))
		.add_property("store",			&pdemod::get_store, &pdemod::set_store)
		.add_property("isready",		&pdemod::isready,"true if the model is ready for calculation")
		.add_property("stored",			&pdemod::stored,"true if the solution is stored for all time steps")
		.def("rhs", 					make_function(&pdemod::rhs,ccr))
		.def("solve",					&pdemod::solve,"Solve the PDEs given a timegrid")
//
//		Intial conditions... Battery Included
		.def("calloption",		&pdemod::calloption)
		.def("putoption",		&pdemod::putoption)
		.def("worseofcall",		&pdemod::calloption)
		.def("worseofput",		&pdemod::putoption)
		;
    
}


template<unsigned N, class T>
class pde_coefficient_wrapper : public qmlib::math::pde_coefficient<N,T>,
								public boost::python::wrapper<qmlib::math::pde_coefficient<N,T> >  {
public:
	typedef qmlib::math::pde_coefficient<N,T>	base_type;
	typedef typename base_type::numtype			numtype;
	
	pde_coefficient_wrapper(){}
    
    numtype eval(unsigned i, unsigned t, bool explic) const  {
        if(boost::python::override f = this->get_override("eval"))
#       if BOOST_WORKAROUND(BOOST_MSVC, <= BOOST_PYTHON_MSVS_VIRTUAL)
          return boost::python::call<numtype>(f.ptr(i,t,explic));
#       else 
          return f(i,t,explic);
#       endif
        return base_type::eval(i,t,explic);
    }
};

QM_NAMESPACE_END2


#endif // __PDE_WRAP_QM_H__

