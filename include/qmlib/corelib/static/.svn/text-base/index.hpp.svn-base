//
//
#ifndef   __INDEX_QM_HPP__
#define   __INDEX_QM_HPP__
//
//
#include <qmlib/corelib/static/tc.hpp>
//
//
QM_NAMESPACE

class index;
typedef QM_SMART_PTR(index) INDEX;
typedef inlinedb<qm_string,index>  indices;


/// \brief Currency
/// \ingroup finance
class index : public codename  {
public:
	const qm_string&  holidays()    const {return m_tcs;}

    index(const qm_string& code_,
          const qm_string& name_,
          const qm_string& defTradingCentre):codename(code_,name_),m_tcs(defTradingCentre){}
    
	/// \brief Retrive a ccy object from inline database
	static INDEX       get(const qm_string& cod);
	
	/// \brief Return a list containing the names of all ccys objects
	template<class L>
	static L keys();
	
private:
	qm_string        m_tcs;
};


QM_NAMESPACE_END


#endif  //  __INDEX_QM_HPP__



