


#ifndef	__INTERESTRATE_HELP_QM_HPP__
#define	__INTERESTRATE_HELP_QM_HPP__


#include <qmlib/corelib/static/all.hpp>



QM_NAMESPACE2(finance)


class irhelp;
typedef QM_SMART_PTR(irhelp) IRHELP;


/** \brief Help class for interestrate
 */
class irhelp : public icodename {
public:
	INDEX		   index()	  	  const {return m_idx;}
	const period&  tenure()   	  const {return m_tenure;}
	DC			   daycount() 	  const {return m_dc;}
	const period&  frequency()	  const {return m_freq;}
	ADJ			   adj()   		  const {return m_adj;}
	qm_string	   code()		  const;
	qm_string	   name()		  const {return "interest rate info: " + this->code();}
	
	/// \brief Build a default fixed-rate help object
	///
	/// Each ccy has its default for daycounter, settlement delay,
	/// trading centres and compound frequency.
	///
	/// @param cu Currency code. This is used to get all default values
	/// @param tenure rate tenure. This is used to evaluate the compounding frequency.
	/// @return irhelp smart pointer
	static IRHELP	fixedrate(const qm_string& cu, const qm_string& tenure);
	static IRHELP	floatrate(const qm_string& cu, const qm_string& tenure);
	static IRHELP	general(const qm_string& tenure, DC dc = DC(), const qm_string& freq = "");
protected:
	irhelp(const period& tenure,
		   const ADJ& adj, DC dc,
		   const period& freq, INDEX idx);
	period          m_tenure;
	ADJ 			m_adj;
	DC			   	m_dc;
	period          m_freq;
	INDEX		 	m_idx;
};


QM_NAMESPACE_END2


#include <qmlib/finance/impl/irhelp_impl.hh>


#endif	//	__INTERESTRATE_HELP_QM_HPP__

