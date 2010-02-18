

#ifndef   __FACTORY_INSTRUMENT_IMPL_QM_HPP__
#define   __FACTORY_INSTRUMENT_IMPL_QM_HPP__


#include <qmlib/finance/instruments/irfuture.hpp>


QM_NAMESPACE2(finance)


struct future_factory  {
	
	static FUTURE make(const qm_string& cod, const qdate& expiry, unsigned n)  {
		EXCHANGE ex(smart_cast<exchange,contract>(contract::get(cod)));
		QM_REQUIRE(ex,"Exchange contract not available");
		return get(ex,expiry,n);
	}
	
	template<class L>
	static L makelist(const qm_string& cod, const qdate& expiry, unsigned n)  {
		EXCHANGE ex(smart_cast<exchange,contract>(contract::get(cod)));
		QM_REQUIRE(ex,"Exchange contract not available");
		L l;
		for(unsigned i=0;i<n;i++)
			l.append(get(ex,expiry,i));
		return l;
	}
	
	template<class L>
	static L makelist2(const qm_string& cod, const qdate& start, const qdate& end)  {
		EXCHANGE ex(smart_cast<exchange,contract>(contract::get(cod)));
		QM_REQUIRE(ex,"Exchange contract not available");
		L l;
		FUTURE fu = get(ex,start,0);
		while(fu->expiry()<end)  {
			l.append(fu);
			fu = get(ex,fu->expiry(),1);
		}
		return l;
	}
	
protected:
	static FUTURE get(const EXCHANGE& ex, const qdate& expiry, unsigned n)  {
		switch(ex->type())  {
			case imm_3m_irfuture: return future_next<irfuture,IMM3generator>::get(ex,expiry,n);
			default: QM_FAIL("not implemented");
		}
	}
	
};

QM_NAMESPACE_END2

    
#endif  //  __FACTORY_INSTRUMENT_IMPL_QM_HPP__
//
