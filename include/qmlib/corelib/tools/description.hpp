//
//
#ifndef __DESCRIPTION_QM_HPP__
#define __DESCRIPTION_QM_HPP__
//
//
//
#include <qmlib/string.hpp>


QM_NAMESPACE

class description;
typedef QM_SMART_PTR(description) DESCRIPTION;

/**
 * \brief description class
 */ 
class description {
public:
	description(const qm_string& nam, const qm_string& descr):
		m_name(nam),m_description(descr){}
	/// \brief name
	const qm_string&  name()	const   {return m_name;}
	/// \description
	const qm_string&  descr()	const   {return m_description;}
protected:
	qm_string   m_name;
	qm_string   m_description;
};


/** \brief 
 * 
 */



class tool_descr  {
public:
	tool_descr(){}
	virtual ~tool_descr() {}
	
	virtual unsigned size() const = 0;
	virtual DESCRIPTION get_descr(unsigned) const = 0;
	
	template<class D>
	D get_dict(unsigned i) const {
		QM_REQUIRE(i<this->size(),"Out of bound");
		D d;
		DESCRIPTION des  = this->get_descr(i);
		d["name"] 		 = des->name();
		d["description"] = des->descr();
		d["value"]		 = (*this)[i];
		return d;
	}
	
	/// \brief Return a list dictionaries
	template<class L, class D>
	L tolist() const {
		L co;
		for(unsigned i=0;i<this->size();++i)
			co.append(this->get_dict<D>(i));
		return co;
	}
};




QM_NAMESPACE_END


/*! @} */


#endif  //  __DESCRIPTION_QM_HPP__

