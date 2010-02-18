

#include <qmlib/python/rndgen_wrap.hpp>
#include <qmlib/math/stoch/gammaOU.hpp>
//#include <qmlib/math/stoch/quadratic.hpp>
#include <qmlib/math/stoch/corr.hpp>
#include <qmlib/math/stoch/heston.hpp>
#include <qmlib/math/stoch/wiener.hpp>
#include <qmlib/math/stoch/meanrev.hpp>
//#include <qmlib/math/stoch/a13.hpp>


QM_NAMESPACE2(python)


void stochastic_wrap()  {
	using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    
    return_value_policy<copy_const_reference> ccr;
    
    register_ptr_to_python<STOCHASTIC>();
    register_ptr_to_python<POISSON>();
    register_ptr_to_python<NGOU>();
    
    class_<istochastic, bases<icodename> >("istochastic",no_init)
    	.def("__len__",					 &istochastic::count,"Number of stochastic driving processes")
    	.add_property("params",			 &istochastic::params,"List of the parameters which define the process")
    	.add_property("factors",	     &istochastic::factors,"List of free-factors in the stochastic process")
    	.add_property("mktrisks",	     &istochastic::mktrisks,"List of market price of risk parameters")
    	.add_property("isdiffusion",     &istochastic::isdiffusion,"Check if process is a diffusion")
    	.add_property("ispositive",		 &istochastic::ispositive,"Check if process is positive")
    	.add_property("isexponential",	 &istochastic::isexponential,"Check if the process is exponential")
    	.def("moments",					 &istochastic::moments,args("i","T1","T2"),"Calculate mean,standard deviation,skewness and excess kurtosis")
    	.def("marginal",				 &istochastic::marginal,args("i","T1","T2"),"Analytical marginal distribution for process i at time T2, from time T1")
    	.add_property("paths",			 make_function(&istochastic::get_paths,ccr),"Montecarlo paths")
    	;
    
    export_processes<1u>();
    export_processes<2u>();
    export_processes<3u>();
    
    class_<poisson_base, bases<istochastic, characteristic<1u> > >("poisson_base","Generalized Poisson process",no_init)
    	;
    class_<ngou, bases<istochastic, characteristic<1u> > >("ngou","Generalized Non-gaussian OU process",no_init)
    	.add_property("driver",			 &ngou::driver)
    	;
    
    //class_<meanreverting>("meanreverting","Mean reverting process",no_init)
    //	.add_property("kappa", 	 		&meanreverting::get_kappa)
    //	;
    	
    //class_<gaussian_meanreverting, bases<meanreverting> >("gaussian_meanreverting","Mean reverting process",no_init)
	//	.add_property("theta", 	 		&gaussian_meanreverting::get_mean)
	//	.add_property("sigma", 	 		&gaussian_meanreverting::get_sigma)
	//	;
    
    //class_<stochcorr, bases<istochastic, gaussian_meanreverting> >("stochcorr","Mean reverting process",
    //	init<optional<qm_real,qm_real,qm_real> >())
    //	;
    
    class_<wiener, bases<istochastic, characteristic<1u> > >("wiener",init<PARAMETER,PARAMETER>())
    	;
	class_<gaussianOU, bases<istochastic, characteristic<1u> > >("gaussianOU",init<PARAMETER,PARAMETER,PARAMETER,PARAMETER>())
    	;
	class_<squareroot, bases<gaussianOU > >("squareroot",init<PARAMETER,PARAMETER,PARAMETER,PARAMETER>())
    	;
	class_<stochcorr, bases<istochastic > >("stochcorr",init<PARAMETER,PARAMETER,PARAMETER,PARAMETER>())
    	;
	class_<poisson, bases<poisson_base> >("poisson",init<PARAMETER,PARAMETER>())
    	;
	class_<exppoisson, bases<poisson_base> >("exppoisson",init<PARAMETER,PARAMETER>())
    	;
	
    //class_<poisson, bases<pii<1> > >("poisson",init<POISSON_PARAMS >())
    //	;
    //def("poisson",poisson_base::make_simple);
    //def("epoisson",poisson_base::make_exponential);
    //def("wiener",wiener::make,"mu,sigma.  A generalized Wiener Process");
    //def("heston",heston_exponent::make,"kappa,theta,eta,rho.  Heston stochastic volatility model");
    //def("stochcorr",stochcorr::make,"kappa,theta,sigma.  A stochastic correlation process");
    //def("quadraticvol",quadraticvol::make,"gamma,m,d.  A quadratic volatility diffusion process");
    //def("gaussianou",gaussianOU::make<gaussianOU>);
    //def("squareroot",gaussianOU::make<squareroot>);
    //def("gammaou",gammaOU::make);
    //def("a13",a13::make);
}


QM_NAMESPACE_END2
