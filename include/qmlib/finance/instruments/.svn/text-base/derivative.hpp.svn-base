

#ifndef   __DERIVATIVE_TEMPLATES_QM_HPP__
#define   __DERIVATIVE_TEMPLATES_QM_HPP__


#include <qmlib/corelib/tools/meta.hpp>
#include <qmlib/finance/instrument.hpp>

QM_NAMESPACE2(finance)


template<class U>
class derivative : public instrument  {
public:
	typedef U				underlying_type;
	typedef QM_SMART_PTR(U)	UNDERLYING;

	UNDERLYING	underlying() const {return m_underlying;}
protected:
	UNDERLYING	m_underlying;
};

/*
template<class U, >
class option: public derivative<U>  {
public:
	typedef O							option_type;
	typedef QM_SMART_PTR(option_type)	OPTION_TYPE;
protected:
	OPTION_TYPE m_opt;
};
*/

QM_NAMESPACE_END2

/*! @} */

#endif	//	__DERIVATIVE_TEMPLATES_QM_HPP__

