
#ifndef   __EQUITY_INSTRUMENT_QM_H__
#define   __EQUITY_INSTRUMENT_QM_H__

#include <boost/static_assert.hpp>
#include <qmlib/finance/instrument.hpp>
#include <qmlib/finance/ccyinst.hpp>


/** \brief Vanilla fixed income instrument
 * \ingroup finins
 * 
 * This file contains the definition for common fixed income
 * otc instruments such as
 * 	- deposit
 *  - fra
 *  - vanillaswap
 *  - cms
 */

QM_NAMESPACE2(finance)



template<instrumentype typ>
class asset: public ccyplug, public instrate  {
public:
	static finins make(const name& name, const qm_string& currency);
protected:
	asset(const CCY& ccy, qm_real notional):ccyplug(ccy,notional),instrate(new simple_value){}
};



template<instrumentype typ>
inline finins asset<typ>::make(const name& name, const qm_string& currency) {
	CCY ccy = ccy::get(currency);
	INST inst(new asset<typ>(ccy,notional));
	return finins(inst);
}



QM_NAMESPACE_END2



#include	<qmlib/finance/instruments/impl/otcir_impl.hh>

    
#endif  //  __EQUITY_INSTRUMENT_QM_H__
//
