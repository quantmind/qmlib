//
/// \file
/// \brief Definition of currency objects
/// \ingroup finance
//
#ifndef   __CCY_QM_HPP__
#define   __CCY_QM_HPP__




#include <qmlib/corelib/static/index.hpp>
#include <qmlib/corelib/static/contract.hpp>




QM_NAMESPACE


typedef inlinedb<qm_string,ccy>  ccys;


period parsefrequency(const qm_string& freq, const period& tenure);



/// \brief Currency
/// \ingroup finance
class ccy : public codename {
public:
    const qm_string& twolettercode() const;
    const qm_string& fixedCoupFred() const;
    const qm_string& floatCoupFred() const;
    const qm_string& iso()           const {return m_isocode;}
    BizDayConv		 bizConv()       const {return m_bizConv;}
    qm_uns_char      order()         const;
    qm_uns_char      rounding()      const;
    qm_uns_char      cashDelay()     const;
    qm_uns_char      swapDelay()     const;
    const qm_string& isocode()       const;
    DC        		 floatDC()       const;
    DC        		 fixedDC()       const;
    INDEX			 rateIndex()	 const;
    bool             iscurrency()    const;
    const qm_string& defaultTC()     const;
    const qm_string& defIndex()      const {return m_defIndex;}
    bool             same(const CCY& rhs) const {return this->order() == rhs->order();}
    qm_uns_char      USD()           const {return 5;}
    qm_string		 tostring()		 const {return this->code();}
    
	/// \brief Retrive a ccy object from inline database
	static CCY       get(const qm_string& cod);
	
	/// \brief Return a list containing the names of all ccys objects
	template<class L>
	static L keys();
	
	ccy(const qm_string& code_,
		const qm_string& name_,
        const qm_string& twolettercode_,
        const qm_string& defTradingCentre,
        const qm_string& fixedCoupFreq_,
        const qm_string& floatCoupFreq_,
        BizDayConv		 bizConv,
        qm_uns_char      order_,
        qm_uns_char      rounding_,
        qm_uns_char      cashdelay_,
        qm_uns_char      swapdelay_,
        qm_string   	 fixedDC,
        qm_string	     floatDC,
        qm_string        isocode = "",
        qm_string        indexname = "",
        bool             iscurrency_ = true):codename(code_,name_),
      m_twolettercode(twolettercode_),
      m_fixedCoupFreq(fixedCoupFreq_),m_floatCoupFreq(floatCoupFreq_),
      m_order(order_),m_rounding(rounding_),m_cashdelay(cashdelay_),
      m_swapdelay(swapdelay_),m_isocode(isocode),m_bizConv(bizConv),
      m_iscurrency(iscurrency_)
      {
        m_fixedDC   = fixedDC;
        m_floatDC   = floatDC;
        m_defaultTC = defTradingCentre;
        m_defIndex  = indexname;
      }
    //
 private:
	qm_string      m_twolettercode;
	qm_string      m_fixedCoupFreq;
	qm_string      m_floatCoupFreq;
	qm_uns_char    m_order;
	qm_uns_char    m_rounding;
	qm_uns_char    m_cashdelay;
	qm_uns_char    m_swapdelay;
	qm_string      m_isocode;
	qm_string      m_fixedDC;
	qm_string      m_floatDC;
	BizDayConv	   m_bizConv;
	bool           m_iscurrency;
	qm_string      m_defaultTC;
	qm_string      m_defIndex;
 };

 
QM_NAMESPACE_END


#endif  //  __CCY_QM_HPP__
//


