
#ifndef   __OPTION_EXERCISE_QM_HPP__
#define   __OPTION_EXERCISE_QM_HPP__


#include <qmlib/corelib/templates/containers.hpp>
#include <qmlib/math/tools/timegrid.hpp>


/** \file
 * \brief Interfaces for derivatives
 * 
 * \ingroup finins
 */


QM_NAMESPACE2(finance)

typedef QM_FROM_NAMESPACE2(math)DTIMEGRID DTIMEGRID;


/** \brief Option exercise style
 * \ingroup finins
 * 
 * In finance, the style or family of an option is a general term denoting the class
 * into which the option falls, usually defined by the dates on which
 * the option may be exercised. The vast majority of options are either European or American (style) options. 
 * \see http://en.wikipedia.org/wiki/Option_style
 */
enum exercisetype  {
	/// %Exercise at maturity only.
	/// A European may be exercised only at the expiry date of the option,
	/// i.e. at a single pre-defined point in time.
	European_ = 0,
	/// Continuous exercise opportunities
	/// An American option may be exercised at any time before the expiry date.
	American_,
	/// Finite set of exercise opportunities.
	/// A Bermudan option is an option where the buyer has the right to exercise at
	/// a set (always discretely spaced) number of times. This is intermediate between
	/// a European_ option and an American_ option (Bermuda is between America and Europe).
	Bermudan_,
};
template<exercisetype> struct exercise_traits;

template<>
struct exercise_traits<European_>  {
	static const bool payoffAtexpiry = true;
	static qm_string tostring() {return "European";}
	static void check(unsigned siz){QM_REQUIRE(siz==0,"European exercise should only contain one date");}
};
template<>
struct exercise_traits<American_>  {
	static const bool payoffAtexpiry = false;
	static qm_string tostring() {return "American";}
	static void check(unsigned siz){}
};
template<>
struct exercise_traits<Bermudan_>  {
	static const bool payoffAtexpiry = false;
	static qm_string tostring() {return "Bermudan";}
	static void check(unsigned siz){}
};


/** \brief Option exercise base class
 * \ingroup finins
 * 
 */
class ExerciseBase : public icodename, public jsonrepr {
public:
	typedef ordered_vector<qdate,qdate,qdate,false>	date_container;
	typedef date_container::iterator		iterator;
	typedef date_container::const_iterator	const_iterator;

    // constructors
	ExerciseBase(){}
    ExerciseBase(const qdate& dte){}
    ExerciseBase(const ExerciseBase& rhs):m_dates(rhs.m_dates){}
    
    const_iterator   begin()       const { return m_dates.begin();}
    const_iterator   end()         const { return m_dates.end();}
    iterator    	 begin()             { return m_dates.begin();}
    iterator    	 end()               { return m_dates.end();}
    void			 add(const qdate& dte);
    
    unsigned  size()             const { return m_dates.size();}
    const qdate& lastDate()      const { return m_dates.back(); }
    const qdate& get(unsigned i) const { QM_REQUIRE(i<this->size(),"Out of bound"); return m_dates[i];}
    
    qm_string name()         	 const { return this->code() + " exercise";}
    virtual exercisetype Type()           const {QM_FAIL("not implemented");}
    virtual bool         payoffatexpiry() const {QM_FAIL("not implemented");}
    
    json	tojson() const;
    qm_string tostring() const {return this->tojson().tostring();}
    
	/// \brief Create a timegrid used for numerical solutions
	///
	///@param pe period fortime discretization
	DTIMEGRID	  get_timegrid(const qdate& start, const period& pe, ADJ adj) const;
    
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar & m_dates;
	}
protected:
	date_container m_dates;
	virtual void check() const {}
};


/** \brief Template class for exercise
 * \ingroup finins
 * 
 * @param et 			 exercisetype Type of exercise
 */
template<exercisetype et>
class Exercise : public ExerciseBase {
public:
	typedef exercise_traits<et>		etraits;
	
	static const exercisetype type 				= et;
	static const bool 		  payoffAtexpiry	= exercise_traits<type>::payoffAtexpiry;
	
    // constructor
	Exercise(){}
    Exercise(const qdate& dte):ExerciseBase(dte){}
    Exercise(const Exercise& rhs):ExerciseBase(rhs){}
    
    qm_string    code() const   {return etraits::tostring();}
    exercisetype Type() const   {return type;}
    bool         payoffatexpiry() const {return payoffAtexpiry;}
protected:
	void check() const {etraits::check(this->size());}
};


inline void ExerciseBase::add(const qdate& dte)  {
	this->check();
	m_dates.add(dte);
}


inline json	ExerciseBase::tojson() const  {
	json js;
	js.insert("style",this->code());
	js.insert("dates",tojsonvec(m_dates));
	return js;
}


inline DTIMEGRID
ExerciseBase::get_timegrid(const qdate& start, const period& pe, ADJ adj) const {
	QM_REQUIRE(this->size() && this->lastDate() > start,"Could not create time grid");
	QM_USING_NAMESPACE2(math);
	DTIMEGRID gr(new date_timegrid);
	gr->add(start);
	for(const_iterator it=m_dates.begin();it!=m_dates.end();++it)  {
		if(*it > start)	gr->add(*it);
	}
	return DTIMEGRID(new date_timegrid(gr,pe,adj));
}


QM_NAMESPACE_END2


#endif	//	__OPTION_EXERCISE_QM_HPP__



