

#include <qmlib/python/pyconfig.hpp>

QM_NAMESPACE2(python)

void quote_wrap();
void interestrate_wrap();
void finance_rates_wrap();
void instrument_wrap();
void instrument_wrap();
void option_wrap();
void pricing_wrap();
void composite_wrap();

QM_NAMESPACE_END2


BOOST_PYTHON_MODULE(financelib)  {
    QM_USING_NAMESPACE2(python);

    quote_wrap();
    interestrate_wrap();
    finance_rates_wrap();
    instrument_wrap();
    option_wrap();
    pricing_wrap();
    composite_wrap();
}
