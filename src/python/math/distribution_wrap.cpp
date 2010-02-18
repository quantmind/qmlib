

#include <qmlib/python/converters.hpp>
#include <qmlib/math/stat/all.hpp>



QM_NAMESPACE2(python)


template<unsigned N>
void export_distrib()  {
	using namespace boost::python;
   	QM_USING_NAMESPACE2(math);
    
    typedef idistribution<N> idistributionN;
    qm_string na = "distribution" + object_to_string(N);
    
    register_ptr_to_python<QM_SMART_PTR(idistributionN)>();
    
   	class_<idistribution<1u>, boost::noncopyable, bases<icodename> >(na.c_str(),"base class for distributions",no_init)
   		.add_property("mean",			&idistributionN::mean,"Mean value")
   		.add_property("variance",		&idistributionN::variance,"Variance")
   		.add_property("skewness",		&idistributionN::skewness,"Skewness")
   		.add_property("kurt",			&idistributionN::excessKurtosis,"Excess Kurtosis")
   		.add_property("stdev",			&idistributionN::stdev,"Standard deviation")
   		.add_property("params",			&idistributionN::params)
   		.def("cumulative",				&idistributionN::cumulative)
   		.def("icumulative",				&idistributionN::icumulative)
   		.def("lndensity",				&idistributionN::lndensity)
   		.def("density",					&idistributionN::density)
   		.def("characteristic_exp", 		&idistributionN::characteristic_exp)
   		.def("characteristic_func", 	&idistributionN::characteristic_func)
   		;
}


void distribution_wrap()  {
  	
  	using namespace boost::python;
   	QM_USING_NAMESPACE2(math);
    
   	export_distrib<1u>();
    	
   	/*
   	class_<normal_dist, bases<idistributionN> >("normal_dist", "Normal distribution for a given mean and standard deviation", init< optional<qm_real, qm_real> >())
   		.add_property("mu",				&normal_dist::get_mu)
   		.add_property("sigma",			&normal_dist::get_sigma)
   	    ;
   	class_<lognormal_dist, bases<idistributionN> >("lognormal_dist", "Normal distribution for a given mean and standard deviation", init< optional<qm_real, qm_real> >())
   		.add_property("mu",				&lognormal_dist::get_mu)
   		.add_property("sigma",			&lognormal_dist::get_sigma)
   	    ;
   	class_<exponential_dist, bases<idistributionN> >("exponential_dist", "Exponential distribution for a given rate parameter", init< optional<qm_real> >())
   		;
   	class_<gamma_dist, bases<distribution_root> >("gamma_dist", "Gamma distribution for a given shape and scale parameter.", init< optional<qm_real,qm_real> >())
   		.add_property("shape",				&gamma_dist::get_shape)
   		.add_property("scale",				&gamma_dist::get_scale)
   	    ;
   	class_<poisson_dist, bases<idistributionN> >("poisson_dist", "Poisson distribution for a given intensity parameter.", init< optional<qm_real> >())
   	    ;
   	
   	class_<binomial_dist, bases<idistributionN> >("binomial_dist",
   	 "Binomial distribution for a given numer of trial and success probability parameter.",
   	  init< optional<qm_uns_long,qm_real> >())
   	    ;
   	*/
   	
   	def("normald",normal_dist::make,"Create a normal distribution");
   	def("chi2",chi2_distribution::make,"Create a Chi-square distribution");
   	def("chi2nc",chi2nc_distribution::make,"Create a non-central chi-square distribution");
}

QM_NAMESPACE_END2

