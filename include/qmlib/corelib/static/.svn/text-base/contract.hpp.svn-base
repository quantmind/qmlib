//
//
#ifndef   __CONTRACT_QM_HPP__
#define   __CONTRACT_QM_HPP__
//

#include <qmlib/corelib/templates/containers.hpp>
#include <qmlib/corelib/static/tc.hpp>




QM_NAMESPACE



class ccy;
typedef QM_SMART_PTR(ccy)		CCY;

class contract;
class exchange;
typedef QM_SMART_PTR(contract)	CONTRACT;
typedef QM_SMART_PTR(exchange)	EXCHANGE;

typedef inlinedb<qm_string,contract>  contracts;


static const char monthcodes[12] = {'F','G','H','J','K','M','N','Q','U','V','X','Z'};


/// \brief Base class for securities and exchange traded contracts
/// \ingroup finance
class contract : public codename {
public:
    contract(const qm_string& cod,
             const qm_string& nam,
             const qm_string& cur,
             const qm_string& deftc,
             security_type typ):codename(cod,nam),m_cur(cur),m_defaultTC(deftc),m_type(typ){}
	
	CCY               currency() const;
	const qm_string&  holiday()  const {return m_defaultTC;}
	security_type     type()     const {return m_type;}
	
	/// \brief Fetch a contract from the inline database
	static CONTRACT   get(const qm_string& cod);
	
	/// \brief Return a list containing the names of all ccys objects
	template<class L>
	static L keys();
    
protected:
    qm_string         m_cur;
 	qm_string         m_defaultTC;
 	security_type	  m_type;
};


/// \brief Exchange Contract
/// \ingroup finance
class exchange: public contract  {
public:
    qm_real           tradingUnit() const {return m_tradingUnit;}
    qm_real           tickSize()    const {return m_tickSize;}
    qm_real           tickValue()   const {return m_tickValue;}
    qm_uns_char       delay()       const {return m_delay;}
    const qm_string&  exchplace()   const {return m_exchange;}
    
    exchange(const qm_string& code_,
             const qm_string& name_,
             const qm_string& cur,
             const qm_string& tcs,
             security_type typ,
             const qm_string& exchange,
             qm_real          tradingUnit,
             qm_real          tickSize,
             qm_real          tickValue,
             qm_uns_char      delay):contract(code_,name_,cur,tcs,typ),m_exchange(exchange),
             m_tradingUnit(tradingUnit),m_tickSize(tickSize),m_tickValue(tickValue),m_delay(delay){}

protected:
    qm_string    m_exchange;
    qm_real      m_tradingUnit;
    qm_real      m_tickSize;
    qm_real      m_tickValue;
    qm_uns_char  m_delay;
};


/*
template<class G>
class FutureOptionContract: public exchange  {
      friend class Exchanges;
    public:
      EXCHANGE_INSTS generate_instruments(const qm_date& start, qm_uns_int num, bool skip_first_if_start);
      //
    private:
      EXCHANGE  m_fuex;
      //
      FutureOptionContract(const qm_string& code,
                           const qm_string& name,
                           const EXCHANGE&  futc,
                           qm_real          tradingUnit,
                           qm_real          tickSize,
                           qm_real          tickValue):
      Exchanges(code,name,futc->ccy(),futuredategenerator::dayrule(),futc->setType(),tradingUnit,tickSize,tickValue,futc->setDelay()){}
    };
    */
    //
    /*
    template<class futuredategenerator, class expirydategenerator, class dimension>
    EXCHANGE_INSTS FutureOptionContract<FutureOptionContract,expirydategenerator,dimension>::
      generate_instruments(const qm_date& start, qm_uns_int num, bool skip_first_if_start)
    {
      expirydategenerator exp_gen(start);
      futuredategenerator fut_gen(
      qm_date st = gen.date();
      if(skip_first_if_start && this->expiry(st) == st) st = gen.NextDate();
      EXCHANGE_INSTS insts;
      qm_uns_int     n = 0;
      qm_uns_int     nstop = std::max<qm_uns_int>(1,num);
      timeserie<qm_date,EXCHANGE_INST>::iterator it = s_ts.find(st);
      //
      qm_date stg = st;
      while(it!=s_ts.end())
      {
        insts.push_back(it->value());
        stg = it->date();
        ++it;
        ++n;
        if(n==nstop) return insts;
      }
      //
      EXCHANGE ex(this);
      EXCHANGE_INST  inst;
      if(stg > st) st = gen.NextValidDate(stg);
      for(;n<nstop;n++)
      {
        inst = EXCHANGE_INST(new future<dategenerator,dimension>(ex,this->future_code(st),st));
        s_ts.add(st,inst);
        insts.push_back(inst);
        st = gen.NextDate();
      }
      return insts;
    }
    */
    //
    //typedef FutureContract<IMM3generator,QM_FROM_NAMESPACE2(meta)fixedincome>
    //  Imm3mInterestRateFutureContract;
    //
    //
    //
QM_NAMESPACE_END


#endif  //  __CONTRACT_QM_HPP__


