


#ifndef   __CCYPAIR_QM_HPP__
#define   __CCYPAIR_QM_HPP__



QM_NAMESPACE

class ccypair;
typedef QM_SMART_PTR(ccypair)		 CCYPAIR;
typedef inlinedb<qm_string,ccypair>  ccypairs;


/// /brief Currency pair such as EURUSD
/// /ingroup finance
class ccypair: public codename {
public:
	CCY           	base()        const {return ccy::get(m_base);}
    CCY           	counter()     const {return ccy::get(m_counter);}
    qm_uns_char   	settDelay()   const {return m_settDelay;}
    TradingCentres  holiday() 	  const {return TradingCentres(m_tcs);}
    
	/// \brief Retrive a ccy object from inline database
	static CCYPAIR  get(const qm_string& cod);
	
	/// \brief Return a list containing the names of all ccys objects
	template<class L>
	static L keys();
	
	ccypair(const qm_string& base,
			const qm_string& counter,
			const qm_string& name_,
			qm_uns_char delay,
			const qm_string& hols,
			SettlementType typ = physical_settlement):codename(base+counter,name_),
			m_base(base),m_counter(counter),m_settDelay(delay),m_tcs(hols),m_sett(typ){}
private:
    qm_string      m_base;
    qm_string      m_counter;
    qm_uns_char    m_settDelay;
    qm_string      m_tcs;
    SettlementType m_sett;
};

CCYPAIR splitfx6(const qm_string& code, bool& inverse);


QM_NAMESPACE_END

#endif  //  __CCYPAIR_QM_HPP__


