

#include <qmlib/python/converters.hpp>
#include <qmlib/math/fourier/fftchar.hpp>



QM_NAMESPACE2(python)

template<unsigned N, typename T>
void export_fft_array(const qm_string& name)  {
	using namespace boost::python;
	QM_USING_NAMESPACE2(math);
	typedef fftarray<N,T> vtype;
	
  	class_<vtype, bases<basedes> >(name.c_str(), "Fourier transform array",no_init)
  		.add_property("size",		&vtype::size)
  		.def("__getitem__",			&vtype::get_slow)
  		.def("__setitem__",			&vtype::set_slow)
  		.def("tolist",				&vtype::template tolist<qm_list>)
  		;
}

template<unsigned N, typename T>
void export_fft(const qm_string& s)  {
	using namespace boost::python;
	QM_USING_NAMESPACE2(math);
	
	return_value_policy<copy_const_reference> ccr;
	return_value_policy<copy_non_const_reference> cncr;
	
	typedef fourier<N,T> vtype;
	register_ptr_to_python<QM_SMART_PTR(vtype)>();
	qm_string na = s + "fft";
	class_<vtype, bases<basedes> >(na.c_str(), "Fourier transform in one dimension",
			init<unsigned>())
		.add_property("size",		&vtype::size,"Size of inverse data, which can be used in the direct transform")
		.add_property("dsize",		&vtype::dsize,"Size of direct data, used in the inversion")
		.add_property("idata",		make_function(&vtype::idata,cncr))
		.add_property("ddata",		make_function(&vtype::ddata,cncr))
		.def("inverse",				&vtype::inverse)
		.def("direct",				&vtype::direct)
		;
	
	typedef frfft<N,T> rtype;
	register_ptr_to_python<QM_SMART_PTR(rtype)>();
	na = s + "frfft";
   	class_<rtype, bases<basedes> >(na.c_str(), "Fractional Fast Fourier Transform in one dimension",
   			init<unsigned,unsigned,unsigned>())
   		.def("__len__",					&rtype::dim,"Number of transforms")
   		.add_property("size",			&rtype::size,"Size of inverse data, which can be used in the direct transform")
   		.add_property("dsize",			&rtype::dsize,"Size of direct data, used in the inversion")
   		.add_property("method",			&rtype::method, &rtype::set_method,"Integration method")
   		.add_property("weights",		make_function(&rtype::weights,ccr),"Integration weights")
   		.add_property("frft",			&rtype::frft,"True if calculation method is the Fractional FFT")
   		.def("zdft",					&rtype::zdft,args("beta","transform"),"Fourier transform of z vector")
   		.def("ydft",					&rtype::ydft,"Fourier transform of z vector")
   		.def("__iter__",	            boost::python::iterator<rtype>())
   		.def("__getitem__",				&rtype::get_slow,"Direct access to ffts")
   		.def("inverse",					&rtype::invert,arg("beta"))
   		;
}

template<typename T>
void export_charfft(const qm_string& s)  {
	using namespace boost::python;
	QM_USING_NAMESPACE2(math);
		
	typedef ifftchar<T> vtype;
	register_ptr_to_python<QM_SMART_PTR(vtype)>();
	qm_string na = s + "fftchar";
   	
   	class_<vtype, bases<basedes> >(na.c_str(),"FFT transform of characteristic functions",no_init)
   		.add_property("size",				&vtype::size,"Size of transforms")
   		.add_property("alpha",				&vtype::alpha, &vtype::set_alpha,"Smoothing factor for option transforms")		
   		.add_property("process",			&vtype::process,"The stochastic process used for calculation")
   		.add_property("stdmul",				&vtype::stdmul, &vtype::set_stdmul,"Multiplicator for standard deviation. Used to evaluate the state domain size")	
   		.add_property("dumin", 				&vtype::dumin, &vtype::set_dumin,"Minimum frequency spacing")
   		.add_property("method", 			&vtype::method, &vtype::set_method,"FFT method for integration")
   		.add_property("disc",				&vtype::disc,"Discounting flag")
   		.add_property("fourier",			&vtype::get_fourier,"The fourier class used to invert characteristic transforms")
   		.def("clear",						&vtype::clear,"Empty the cache")
   		.def("calculate",					&vtype::calculate,args("T0","T1","T2","tau"),"Perform calculation")
		.def("calculate",					&vtype::calculate1,args("T"),"Perform calculation")
   		.def("characteristic",				&vtype::characteristicfun,args("T0","T1","T2","tau"),"Characteristic transform")
		.def("characteristic",				&vtype::characteristicfun1,args("T"),"Perform calculation")
   		;
   	
   	typedef fftcharresult<T> rtype;
   	register_ptr_to_python<QM_SMART_PTR(rtype)>();
   	na = s + "fftcharresult";
    class_<rtype, bases<basedes> >(na.c_str(),"Result from inverse FFT of characteristic transform",no_init)
    	.add_property("size",				&rtype::size,"size of transform")
    	.add_property("dim",				&rtype::dim,"number of transforms")
    	.add_property("b",					&rtype::bval,"Initial value of state domain")
    	.add_property("L",					&rtype::Lval,"half length of domain")
    	.add_property("dx",					&rtype::dx,"domain discretization step")
    	.add_property("du",					&rtype::du,"Circular frequency discretization step")
    	.add_property("beta",				&rtype::beta,"beta coefficient in FRFTT")
    	.def("__getitem__",					&rtype::value,arg("x"),"Value at x")
    	.def("value",						&rtype::value,arg("x"),"Value at x")
    	.def("xvalues",						&rtype::template xlist<qm_list>,arg("i"),"transformed domain discretization")
    	.def("uvalues",						&rtype::template ulist<qm_list>,arg("i"),"transformed domain discretization")
    	.def("dvalues",						&rtype::template dlist<qm_list>,arg("i"),"domain discretization")
    	.def("yvalues",						&rtype::template ylist<qm_list>,args("i","n"),"list of all values")
    	.def("multiplier",					&rtype::multiplier,arg("i"),"Return the transform multiplier at node i")
    	.add_property("expiry",				&rtype::expiry,"Time to expiry")
    	.add_property("settle",				&rtype::settle,"Time to settlement")
    	.add_property("maturi",				&rtype::maturi,"Time to maturity")
    	.add_property("tenure",				&rtype::tau,"tenure")
    	.def("impliedblack",				&rtype::impliedblack,arg("Strike"),"Calculate the implied black volatility.")
    	.def("sens",						&rtype::sens,args("date","code","dval"),"Calculate value and sensitivities")
    	;
   	
   	na = s + "fftdensity";
   	def(na.c_str(),	fftdensity<T,characteristic<1u> >::make);
   	def(na.c_str(),	fftdensity<T,characteristic<2u> >::make);
   	def(na.c_str(),	fftdensity<T,characteristic<3u> >::make);
   	def(na.c_str(),	fftdensity<T,atsmodel<1u> >::make);
   	def(na.c_str(),	fftdensity<T,atsmodel<2u> >::make);
   	def(na.c_str(),	fftdensity<T,atsmodel<3u> >::make);
   	na = s + "fftoption";
   	def(na.c_str(),	fftoption<T,ExponentialCharacteristicDiffusion<1u>,false>::make);
   	def(na.c_str(),	fftoption<T,ExponentialCharacteristicDiffusion<2u>,false>::make);
}


void fourier_wrap()  {
  	
  	using namespace boost::python;
  	QM_USING_NAMESPACE2(math);
  	
    enum_<fftmethod>("fftmethod")
    	.value("fft_trapezoidal",	fft_trapezoidal)
        .value("fft_simpson",		fft_simpson)
        .value("frft_trapezoidal",	frft_trapezoidal)
        .value("frft_simpson",		frft_simpson)
        .export_values()
        ;

    typedef fftcharresult<qm_real> 	  fftcharresultr;
    typedef fftcharresult<qm_complex> fftcharresultc;
    
  	export_fft_array<1u,double>("rfourier1darray");
  	export_fft_array<1u,qm_complex>("cfourier1darray");
  	export_fft<1u,double>("r");
  	export_fft<1u,qm_complex>("c");
  	export_charfft<double>("r");
  	export_charfft<qm_complex>("c");
}

QM_NAMESPACE_END2

