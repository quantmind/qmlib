
#ifndef   __TIME_PARAMETERS_MODELS_QM_HPP__
#define   __TIME_PARAMETERS_MODELS_QM_HPP__



#include <qmlib/corelib/info/params.hpp>



QM_NAMESPACE

class time_parameter;
typedef QM_SMART_PTR(time_parameter)  TIME_PARAMETER;


/// \brief A time dependent parameter.
///
/// This parameter is composed by one or more parameters
class time_parameter : public iparameter  {
public:
	time_parameter(){};
	
	qm_real   get_value() 			const 	{return this->get_valuet(0);}
	
	parameters params()				const	{return m_params;}
	
	bool	   get_const()			const	{return false;}
	
	json	   tojson()				const;
	
	void updatelazy() {precalc();}
protected:
	parameters  m_params;
	qm_string   m_code;
	qm_string   m_name;
	void registration();
	virtual void precalc() {}
	time_parameter(const qm_string& code, const qm_string& name):
		m_code(code),m_name(name){}
};

inline void time_parameter::registration()  {
	QM_SMART_PTR(observable) obs;
	for(parameters::iterator it=m_params.begin();it!=m_params.end();++it)  {
		obs = smart_cast<observable,iparameter>(*it);
		this->registerWith(obs);
	}
}

inline json time_parameter::tojson() const  {
	json js;
	js.insert("code",this->code());
	js.insert("name",this->name());
	return js;
}



QM_NAMESPACE_END

#endif	//	__TIME_PARAMETERS_MODELS_QM_HPP__

