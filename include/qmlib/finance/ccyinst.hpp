
#ifndef   __CCY_PLUGINS_QM_HPP__
#define   __CCY_PLUGINS_QM_HPP__


#include <qmlib/corelib/tools/json.hpp>
#include <qmlib/corelib/static/all.hpp>



QM_NAMESPACE2(finance)

class iccyplug  {
public:
	virtual ~iccyplug(){}
	virtual CCY			currency()	   const {QM_FAIL("Not implemented");}
	virtual qm_real		notional()     const {QM_FAIL("Not implemented");}
	virtual void		set_notional(qm_real notio) {QM_FAIL("Not implemented");}
};



class ccyplug : public iccyplug {
public:
	ccyplug(const CCY& ccy,qm_real notional):m_ccy(ccy),m_notional(notional){}
	CCY			currency()	   const {return m_ccy;}
	qm_real		notional()     const {return m_notional;}
	void		set_notional(qm_real notio) {m_notional = notio; updatenotional();} 
protected:
	virtual void updatenotional(){}
	//void		filljson(json::object& obj) const;
	CCY			m_ccy;
	qm_real		m_notional;
};

QM_NAMESPACE_END2


QM_NAMESPACE

typedef QM_FROM_NAMESPACE2(finance)ccyplug	fccyplug;

template<>
struct  filljson_o<fccyplug>  {
	static void doit(const fccyplug& obj, json& js) {
		js.insert("currency",obj.currency()->code());
		js.insert("notional",obj.notional());
	}
};

QM_NAMESPACE_END


#endif	//	__CCY_PLUGINS_QM_HPP__

