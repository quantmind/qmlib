


#ifndef   __SENSITIVITY_RESULTS_QM_HPP__
#define   __SENSITIVITY_RESULTS_QM_HPP__


#include <qmlib/qmat/qmatrix.hpp>
#include <qmlib/corelib/dates/all.hpp>
#include <qmlib/corelib/templates/stdwrap.hpp>
#include <boost/serialization/base_object.hpp>



/**\file
 * \brief Results classes for analytic option pricing calculation
 */ 



QM_NAMESPACE


class sensitivity;
class tinysens;
typedef QM_SMART_PTR(sensitivity)  		SENSITIVITY;
typedef QM_SMART_PTR(tinysens)  		TINYSENS;


/** \brief Valuation methods for pricing
 */
enum pricingValuationMethod  {
	/// Analytical valuation. This is is the fastest valuation method (when it is available).
	/// The valuation is obtained solving a closed form formula.
	analytical_ = 0,
	/// Valuation obtained by inverse Fourier transform. This is a quasi-anlytical valuation
	/// method since inverse Fourier transform are quite efficient.
	fourier_,
	/// If neither of the above method are available, than solving a PDE system numerically
	/// is the next choice. However dimensionality can be a problem since anything bigger than two
	/// is not available in this library.
	pde_,
	/// Brute force valuation. This method should be able to price anythig.
	/// However performance is poor.
	montecarlo_,
};



/** \base class for sensitivities
 */
class sensitivity : public icodename {
public:
	typedef qmlib::math::qmatrix<qm_real>									container_type;
	typedef qmlib::math::qmatrix<qm_real>									delta_type;
	typedef qmlib::math::qmatrix<qm_real,qmlib::math::symmetric_matrix>		gamma_type;
	
	sensitivity(){}
	sensitivity(const qdate& dte, const qm_string& code,  unsigned dim, unsigned d2 = 5);
	sensitivity(const sensitivity& rhs);
	
	const delta_type& deltas() const {return m_deltas;}
	const gamma_type& gammas() const {return m_gammas;}
	const container_type& values() const {return m_vals;}
	
	/// Fast access/set methods
	qm_real&	operator [] (unsigned i)       {return m_vals[i];}
	qm_real		operator [] (unsigned i) const {return m_vals[i];}
	
	void    	 set_val(unsigned i, qm_real v)  {m_vals.set1(i,0,v);}
	qm_real		 get_val(unsigned i) const 		{return m_vals.get1(i,0);}
	const qdate& date() const {return m_date;}
	qm_string	 code() const {return m_code;}

	qm_real value()  const {return m_vals[0];}
	void set_value(qm_real v)   {m_vals[0]	   = v;}
	qm_real theta()  const {return m_vals[1];}
	void set_theta(qm_real v)   {m_vals[1]	   = v;}
	qm_real delta()  const {return m_vals[2];}
	void set_delta(qm_real v)   {m_vals[2]	   = v;}
	qm_real gamma()  const {return m_vals[3];}
	void set_gamma(qm_real v)   {m_vals[3]	   = v;}
	qm_real rate()  const {return m_vals[4];}
	void set_rate(qm_real v)   {m_vals[4]	   = v;}

	sensitivity& operator *= (qm_real c);
	unsigned size() const {return m_deltas.size();}
	
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & m_date & m_code & m_vals & m_deltas & m_gammas;
	}
protected:
	sensitivity(unsigned dim, unsigned d2);
	qdate	  				m_date;
	qm_string				m_code;
	delta_type				m_deltas;
	gamma_type				m_gammas;
	container_type 			m_vals;
};



class tinysens: public sensitivity  {
public:
	tinysens(const qdate& dte, const qm_string& code,
	qm_real va = 0,
	qm_real de = 0,
	qm_real ga = 0,
	qm_real ra = 0):sensitivity(dte,code,0){
		this->set_value(va);
		this->set_delta(de);
		this->set_gamma(ga);
		this->set_rate(ra);
	}
};




/** \brief The sensitivity aggregator
 * 
 * Aggregate sensitivities over asset classes and models
 */
class sensitivities: public icodename, public dictionaryBase<qm_string,SENSITIVITY>  {
public:
	typedef dictionaryBase<qm_string,SENSITIVITY>	base_class;
	sensitivities(){}
	sensitivities(const SENSITIVITY& se);
	sensitivities(const sensitivities& rhs):base_class(rhs){}
	
	qm_string code() const {return "sensitivity agglomerator";}
	bool update(const sensitivities& se)  {return base_class::update(se);}
	const qdate& date() const;
	
	template<class S>
	bool add(const QM_SMART_PTR(S)& se) {
		data_type v = smart_cast<data_type::value_type,S>(se);
		if(v) return this->insert(value_type(v->code(),v)).second;
		else return false;
	}
	
	/// \brief serialization
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
	}
	
	template<class L>
	L tolist() const  {
		L l;
		for(const_iterator it=this->begin();it!=this->end();++it)  {
			l.append(it->second);
		}
		return l;
	}
	insert_type	 insert(const value_type& vt);
protected:
};



inline sensitivity::sensitivity(const qdate& dte, const qm_string& code, unsigned dim, unsigned d2):
	m_date(dte),m_code(code),m_deltas(dim),m_gammas(dim,dim),m_vals(std::max(d2,5u)) {
	m_deltas = 0;
	m_gammas = 0;
	m_vals   = 0;
}

inline sensitivity::sensitivity(const sensitivity& rhs):
	m_date(rhs.m_date),m_code(rhs.m_code),m_deltas(rhs.m_deltas),m_gammas(rhs.m_gammas),m_vals(rhs.m_vals){}

inline sensitivity& sensitivity::operator *= (qm_real c)  {
	m_deltas *= c;
	m_gammas *= c;
	m_vals   *= c;
	return *this;
}


inline sensitivities::sensitivities(const SENSITIVITY& se)  {
	if(se) this->insert(value_type(se->code(),se));
}


inline sensitivities::insert_type	sensitivities::insert(const sensitivities::value_type& vt) {
	if(this->size())
		QM_REQUIRE(vt.second->date() == this->date(),"Adding a sensitivity with different date");
	return p_data->insert(vt);
}

inline const qdate& sensitivities::date() const  {
	QM_REQUIRE(this->size(),"No sensitivities available");
	const_iterator it = this->begin();
	return it->second->date();
}



QM_NAMESPACE_END




#endif  //  __ANALYTIC_OPTION_RESULTS_QM_HPP__

