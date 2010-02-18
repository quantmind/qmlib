



#ifndef   __PARAMETERS_MODELS_QM_HPP__
#define   __PARAMETERS_MODELS_QM_HPP__


#include <qmlib/corelib/tools/json.hpp>
#include <qmlib/corelib/templates/observer.hpp>
#include <qmlib/corelib/templates/stdwrap.hpp>

/*! \ingroup parameter Parameter definitions

	Definitions of classes for parameter definition

    @{
*/

/// \file
/// \brief Model base classes
/// \ingroup utility


QM_NAMESPACE

class iparameter;
typedef QM_SMART_PTR(iparameter)	PARAMETER;
typedef hashVector<qm_string,iparameter>  parameters;


/** \brief Parameter interface class
 */
class iparameter : public icodename, public lazy {
public:	
	iparameter(){}
	json			   tojson()				 const;
	qm_string		   tostring()			 const   	{return this->tojson().tostring();}
	virtual void       set_value(qm_real val) 			{QM_FAIL("Value cannot be set");}
	virtual qm_real    get_value() 			 const 		{QM_FAIL("Value not available");}
	virtual qm_real    get_valuet(qm_real t) const 		{QM_FAIL("Not implemented");}
	virtual bool	   get_const()			 const		{return true;}
	virtual void	   set_active(bool val) 			{QM_FAIL("Not implemented");}
	virtual bool	   get_active() 		 const 	    {QM_FAIL("Not implemented");}
	virtual qm_real	   get_integrated(qm_real t0, qm_real t1) const {QM_FAIL("Not implemented");}
	virtual qm_real	   get_square_integrated(qm_real t0, qm_real t1) const {QM_FAIL("Not implemented");}
	virtual bool       positive()			 const   	{return this->lower_bound() >= 0;}
	virtual bool       negative()			 const   	{return !(this->lower_bound() >= -smallreal());}
	virtual qm_real    lower_bound()	 	 const   	{return -maxreal();}
	virtual qm_real    upper_bound()		 const   	{return maxreal();}
	virtual parameters params()				 const		{QM_FAIL("No parameters available");}
	
	void updatelazy() {}
};


/** A simple constant parameter
 */
class parameter : public iparameter {
public:
	static PARAMETER make(const qm_string& code, const qm_string& name, qm_real val,
			  	   		  qm_real lower = -maxreal(),
			  	   		  qm_real upper = maxreal(),
			  	   		  bool act = true){return PARAMETER(new parameter(code,name,val,lower,upper,act));}
	qm_string  code()	const   {return m_code;}
	qm_string  name()	const   {return m_name;}
	void      set_value(qm_real val);
	qm_real   get_value() 			const 	{return m_value;}
	qm_real   get_valuet(qm_real t)	const 	{return m_value;}
	qm_real	  get_integrated(qm_real t0, qm_real t1) const {return m_value*(t1 - t0);}
	qm_real	  get_square_integrated(qm_real t0, qm_real t1) const {return m_value*m_value*(t1 - t0);}
	qm_real   lower_bound()			const   {return m_lower;}
	qm_real   upper_bound()			const   {return m_upper;}
	void	  set_active(bool val) 			{m_active = val;}
	bool      get_active() 			const 	{return m_active;}
protected:
	parameter(const qm_string& code, const qm_string& name,  qm_real val,
			  qm_real lower, qm_real upper, bool act);
	qm_string   m_code;
	qm_string   m_name;
	qm_real 	m_value;
	qm_real 	m_lower;
	qm_real 	m_upper;
	bool		m_active;
};




//______________________________________________________________________________________
//		IMPLEMENTATION

inline json iparameter::tojson() const  {
	json js;
	js.insert("code",this->code());
	js.insert("name",this->name());
	js.insert("value",this->get_value());
	if(this->lower_bound() ==-smallreal())
		js.insert("lower_bound",qm_string("non-negative"));
	else if(this->lower_bound() != -maxreal())
		js.insert("lower_bound",this->lower_bound());
	if(this->upper_bound() != maxreal())
		js.insert("upper_bound",this->upper_bound());
	return js;
}

inline parameter::parameter(const qm_string& code,  const qm_string& name,  qm_real val,
		  					qm_real lower,  qm_real upper,  bool act):
		  			m_code(code),m_name(name),m_lower(lower),m_upper(upper) {
	QM_REQUIRE(m_upper>m_lower,"Upper bound lower than lower bound");
	m_active = true;
	this->set_value(val);
	m_active = act;
}

inline void parameter::set_value(qm_real val) {
	if(m_active && val > m_lower && val <m_upper)  {
		m_value = val;
		this->update();
	}
	else {
		if(!m_active) QM_FAIL("Trying to set a parameter which is non-active");
		QM_FAIL("Out of bound");
	}
}





/*



/// \brief The model factors
///
/// Model factors
class factor : public model_parameter {
public:
	factor(const qm_string& descr = "", const qm_string& nam = "", qm_real val = 0.0):
		model_parameter(descr,nam,true),m_value(val){}
	
	qm_string tostring() 	const 	{
		qm_string str = "Factor " + m_name + " : " + pretty_print(m_value);
		str += " ("+m_description+")";
		return str;
	}
	
	void      		  set_value(qm_real val) 		{m_value = val;}
	qm_real   		  get_value() 			const 	{return m_value;}
	qm_real   		  get_valuet(qm_real t)	const 	{return m_value;}
	void    		  set_active(bool val) 			{QM_FAIL("Factor are always active");}
protected:
	qm_real 	m_value;
};


/// \brief A list of parameters
///
/// Used from classes which contains several parameters
template<bool Co = true>
class parameter_list {
public:
	typedef model_parameter						parameter_type;
	typedef QM_SMART_PTR(parameter_type)		PARAMETER;	
	typedef std::vector<PARAMETER>				parameters_type;
	typedef parameters_type::iterator			iterator;
	typedef parameters_type::const_iterator		const_iterator;
	
	static const bool	  time_homogeneous = Co;
	
	parameter_list():m_parameters(new parameters_type){}
	virtual ~parameter_list(){}
	//
	unsigned 			numparams() 	const 	{return m_parameters->size();}
	iterator			begin()	 				{return m_parameters->begin();}
	iterator			end()	 				{return m_parameters->end();}
	const_iterator		begin()	 		const 	{return m_parameters->begin();}
	const_iterator		end()	 		const 	{return m_parameters->end();}
	bool		    	get_timehomo() 	const   {return time_homogeneous;}
	const PARAMETER&	get(unsigned i) const 	{return (*m_parameters)[i];}
	
	void			set(unsigned i, PARAMETER pa)   	  {if(pa) (*m_parameters)[i] = pa;}
	PARAMETER		get_slow(unsigned i)    			  {QM_REQUIRE(i<this->numparams(),"Out of bound"); return (*m_parameters)[i];}
	void			push_back(PARAMETER pa);
	void 			set_full();
	unsigned		active()	 const;
protected:
	QM_SMART_PTR(parameters_type)  m_parameters;
};



/// \brief Base time function class
///
/// This should be used as base class for time function implementation
class time_function  {
public:
	friend class time_parameter;
	time_function(){}
	virtual ~time_function(){}
	virtual  qm_real value(qm_real t) const {return 0;}
protected:
	TIME_PARAMETER	m_pa;
	void set(TIME_PARAMETER pa){m_pa = pa;}
};


/// \brief A time dependent parameter.
///
/// This parameter is composed by one or more parameters
class time_parameter : public model_parameter, public parameter_list<false> {
public:
	typedef parameter_list<false>	plist;
	
	static TIME_PARAMETER create0(const qm_string& descr, const qm_string& nam, TIME_FUNCTION fun)  {
		return create(descr,nam,fun,true);
	}
	static TIME_PARAMETER create(const qm_string& descr, const qm_string& nam,
			                     TIME_FUNCTION fun, bool act)  {
		TIME_PARAMETER pa = TIME_PARAMETER(new time_parameter(descr,nam,fun,act));
		fun->set(pa);
		return pa;
	}
	
	bool	  get_const()	const	{return this->get_timehomo();}
	qm_real   get_value() 			const 	{return this->get_valuet(0);}
	qm_real   get_valuet(qm_real t)	const 	{return m_function->value(t);}
	qm_string tostring() 			const 	{
		return "Time-dependent Parameter";
	}
protected:
	TIME_FUNCTION	m_function;
	time_parameter& noconst() const {return const_cast<time_parameter&>(*this);}
	time_parameter(const qm_string& descr, const qm_string& nam, TIME_FUNCTION fun, bool act):
		model_parameter(descr,nam,act),m_function(fun){QM_REQUIRE(m_function,"Function not specified");}
};

template<bool Co>
inline void parameter_list<Co>::set_full() {
	for(typename parameter_list<Co>::iterator it = this->begin();it!=this->end();++it)
		(*it)->set_active(true);
}

template<bool Co>
inline unsigned parameter_list<Co>::active() const  {
	unsigned n = 0;
	for(typename parameter_list<Co>::const_iterator it = this->begin();it!=this->end();++it)
		if((*it)->get_active()) n++;
	return n;
}

template<bool Co>
inline void	parameter_list<Co>::push_back(PARAMETER pa) {
	QM_REQUIRE(!time_homogeneous || pa->get_const(),"Adding a time dependent parameter to a time-homogeneous model");
	m_parameters->push_back(pa);
}
*/

QM_NAMESPACE_END


/*! @} */


#endif	//	__PARAMETERS_MODELS_QM_HPP__

