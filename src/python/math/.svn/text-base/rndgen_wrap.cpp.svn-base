

#include <qmlib/python/converters.hpp>
#include <qmlib/math/random/all.hpp>


QM_NAMESPACE2(math)
qm_int  SOBOL_BITS 	= 8*sizeof(qm_uns_long);
qm_real SOBOL_NFACT 	= 0.5/(1UL<<(SOBOL_BITS-1));

template<int D>
const qm_int SobolGenerator<D>::c_bits = SOBOL_BITS;
template<int D>
const qm_real SobolGenerator<D>::c_normalizationFactor = SOBOL_NFACT;
QM_NAMESPACE_END2


QM_NAMESPACE2(python)




BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(rndgen_nextUniform,       nextUniform, 0, 2)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(rndgen_nextNormalVariate, nextNormalVariate, 0, 2)



void rndgen_wrap()  {
	using namespace boost::python;
    QM_USING_NAMESPACE2(math);
    //return_value_policy<copy_const_reference> ccr;
    
    class_<rndgen, bases<basedes> >("rndgen", "Random Number Generator", no_init)
       .def("next",                       &rndgen::nextUniform, rndgen_nextUniform(args("index", "dimension"),
                                                                "Generate the next random uniform number in [0 1]"))
       .def("nextNormalVariate",          &rndgen::nextNormalVariate, rndgen_nextNormalVariate(args("index", "dimension"),
                                                                "Generate the next random standard normal variate"))
       .add_property("maxdimension",		  &rndgen::maxdimension)
      ;
    
    class_<MersenneTwister, bases<rndgen> >("MersenneTwister", "MersenneTwister 19937 pseudo-random number generator", init< optional<qm_long> >());
    class_<sobol0, bases<rndgen> >("sobol0", "Sobol low-discrepancy sequence",
                              init< optional<qm_long,qm_long> >(args("maxDimension","seed"), "maxDimension"));
    class_<sobol1, bases<rndgen> >("sobol1", "Sobol low-discrepancy sequence",
                       init< optional<qm_long,qm_long> >(args("maxDimension","seed"), "maxDimension"));
    class_<sobol2, bases<rndgen> >("sobol2", "Sobol low-discrepancy sequence",
                        init< optional<qm_long,qm_long> >(args("maxDimension","seed"), "maxDimension"));
    class_<sobol3, bases<rndgen> >("sobol3", "Sobol low-discrepancy sequence",
                        init< optional<qm_long,qm_long> >(args("maxDimension","seed"), "maxDimension"));
    class_<halton, bases<rndgen> >("halton", "Halton low-discrepancy sequence",
    		init<  optional<qm_long> >(args("maxDimension"), "maxDimension"));
    
    def("randomdate",randomdate,"rndgen,start,end");

}

    
QM_NAMESPACE_END2
