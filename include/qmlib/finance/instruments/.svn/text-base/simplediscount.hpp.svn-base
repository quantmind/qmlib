
#ifndef   __SIMPLEDISCOUNT_INSTRUMENTS_QM_HPP__
#define   __SIMPLEDISCOUNT_INSTRUMENTS_QM_HPP__


#include <qmlib/finance/instrument.hpp>


/** \file
 * \brief Simple discount instrument interface
 * 
 * This interface is pluged in instruments which
 * can be priced by simpled discounting on a discountcurve
 */


QM_NAMESPACE2(finance)


class simplediscount: public isimplediscount {
public:
	CASHFLOW cashflow(const qdate& dte) const;
protected:
	simplediscount(){}
	simplediscount(ivalue* ra):isimplediscount(ra){}
	
	void clearcf() {m_cfdate = qdate();}
	mutable	qdate			  m_cfdate;
	mutable CASHFLOW		  m_cfs;
	virtual CASHFLOW build_cashflow(const qdate& dte) const {QM_FAIL("not implemented");}
};


inline CASHFLOW simplediscount::cashflow(const qdate& dte) const {
	if(dte != m_cfdate)  {
		m_cfs    = this->build_cashflow(dte);
		m_cfdate = dte;
	}
	return m_cfs;
}


QM_NAMESPACE_END2

/*! @} */

#endif	//	__SIMPLEDISCOUNT_INSTRUMENTS_QM_HPP__



