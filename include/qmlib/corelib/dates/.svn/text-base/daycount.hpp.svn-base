//
/// \file
/// \brief Definition of DayCounter objects
/// \ingroup finance
//
//
//
#ifndef __DAYCOUNT_QM_HPP__
#define __DAYCOUNT_QM_HPP__


#include <qmlib/corelib/templates/inlinedb.hpp>
#include <qmlib/corelib/dates/date.hpp>


/**\file
 * \brief implementatuion of daycount
 * \ingroup dates
 * 
 */



QM_NAMESPACE
	
class daycounter;
typedef QM_SMART_PTR(daycounter)  		DC;
typedef inlinedb<qm_string,daycounter>  daycounters;

    
    
/** \brief Base class for daycounter object
 *  \ingroup dates
 * 
 */
class daycounter : public codename {
public:
  	virtual qm_long  daycount(const qdate& start, const qdate& end) const    {return qdate::daydiff(start,end);}
   	virtual qm_real  dcf(const qdate& start, const qdate& end) const         {return this->daycount(start,end)/360.0;}
   	
   	/// \brief Retrive a daycounter object from inline database
   	static DC        get(const qm_string& cod);
   	
   	/// \brief Return a list containing the names of all daycounter objects
   	template<class L>
   	static L keys();
   	//
protected:
   	daycounter(const qm_string& code, const qm_string& name):codename(code,name){}
};

    
QM_NAMESPACE_END
    
    
#include <qmlib/corelib/dates/impl/daycount_impl.hh>

    

#endif // __DAYCOUNT_QM_HPP__

