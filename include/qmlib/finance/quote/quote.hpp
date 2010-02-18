



#ifndef	__QUOTE_QM_HPP__
#define	__QUOTE_QM_HPP__

#include <qmlib/finance/iquote.hpp>
#include <qmlib/finance/instrument.hpp>

QM_NAMESPACE2(finance)

template<class,class> class quote;

template<class T, class I> struct quoteInstrument {};



/** \brief Class template which provate a template implementation of iquote
 * \ingroup quote
 * 
 * This class template provides a template implementation of iquote
 * 
 * @param T	ticker type
 * @param I financial instrument associated with ticker (optional)
 */
template<class T, class I = instrument>
class quote: public iquote  {
public:
	typedef quote<T,I>							self_type;
	typedef T									ticker_type;
	typedef I									inst_type;
	typedef QM_SMART_PTR(self_type)				SELF_TYPE;
	typedef QM_SMART_PTR(ticker_type)			TICKER_TYPE;
	typedef QM_SMART_PTR(ticker_type)			INST_TYPE;
	
	QM_SMART_PTR(self_type) create(ticker_type t, const qdate& dte) {return SELF_TYPE(new self_type(t,dte));}
	
	// Overrides
	TICKER           ticker()      const {return smart_cast<iticker,ticker_type>(m_ticker);}
	qm_real			 value()       const {return m_inst->rate()->get_value();}
	bool 			 isValid() 	   const {return m_inst->rate()->validvalue();}
	qdate            date()        const {return m_date;}
	qm_string		 code()        const {return m_ticker->code();}
	qm_string		 name()        const {return m_ticker->name();}
	qm_string		 Short()       const {return m_ticker->Short();}
	qm_string		 tostring()    const {return m_ticker->tostring();}
	
	// New property
	inst_type        instrument()  const {return m_inst;}
protected:
	TICKER_TYPE  m_ticker;
	qdate		 m_date;
	INST_TYPE	 m_inst;
	
	quote(ticker_type t, const qdate& dte):
		m_ticker(t),m_date(dte) {
		QM_REQUIRE(m_ticker,"Null ticker");
		m_inst = quoteInstrument<ticker_type,inst_type>::make(m_ticker,m_date);
	}
	bool set_value_changed(qm_real val) {
		qm_real vo = this->value();
		if(val != vo)  {
			m_inst->rate()->set_value(val);
			if(this->isValid()) return true;
			else {
				m_inst->rate()->set_value(vo);
				return false;
			}
		}
		else return false;
	}
};



QM_NAMESPACE_END2


#endif	//	__QUOTE_QM_HPP__

