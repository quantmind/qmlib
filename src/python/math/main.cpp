

#include <qmlib/python/pyconfig.hpp>

QM_NAMESPACE2(python)

void distribution_wrap();
void fourier_wrap();
void misc_wrap();
void rndgen_wrap();
void timegrid_wrap();
void monte_wrap();
void stochastic_wrap();
//void pde_wrap();
//void dataserie_wrap();
//void payoff_wrap();
//void options_wrap();
//void tsmodel_wrap();
void bootstrap_wrap();

QM_NAMESPACE_END2


#ifdef _DEBUG_
BOOST_PYTHON_MODULE(mathlibdebug)  {
#else
BOOST_PYTHON_MODULE(mathlib)  {
#endif	// _DEBUG_
	QM_USING_NAMESPACE2(python);
	
	rndgen_wrap();
    distribution_wrap();
    fourier_wrap();
    misc_wrap();
    timegrid_wrap();
    monte_wrap();
    stochastic_wrap();
    //pde_wrap();
    //dataserie_wrap();
    //payoff_wrap();
    //options_wrap();
    //tsmodel_wrap();
	bootstrap_wrap();
}
