

#ifndef __ILOG_QM_HPP__
#define __ILOG_QM_HPP__

#include <qmlib/definitions.hpp>



QM_NAMESPACE



class ilog  {
public:
	void info(const qm_string& msg)		{m_msg = "Info:     " + msg; this->fire();}
	void critical(const qm_string& msg) {m_msg = "CRITICAL: " + msg; this->fire();}
	void warning(const qm_string& msg)	{m_msg = "Warning:  " + msg; this->fire();}
	void error(const qm_string& msg)	{m_msg = "ERROR:    " + msg; this->fire();}
	void debug(const qm_string& msg)	{m_msg = "Debug:    " + msg; this->fire();}
	const qm_string& msg() const		{return m_msg;}

	virtual void fire() {}
protected:
	qm_string m_msg;
};


QM_NAMESPACE_END


#endif	//	__ILOG_QM_HPP__
