

#ifndef		__OBSERVER_QM_HPP__
#define		__OBSERVER_QM_HPP__

/*! \defgroup patterns Design Patterns

    \brief Implementation of several well-known design patters.
    
    For more information on design patterns check the book
    
    Design Patterns - Element of Reusable Object-Oriented Software
    
    by Gamma, Helm, Johnson, Vlissides

    @{
*/



/** \file
 * \brief observer / observable behavioral design pattern.
 * 
 * observer and observable objects define a many-to-many dependency between objects so that when
 * one object changes state, all its obervers are notified and updated automatically.
 */

#include <qmlib/corelib/tools/error.hpp>


QM_NAMESPACE

class observer;

/** \brief The observable pattern.
 * 
 * The observable contains a list of observer.
 * The observer will notify its observers when its status changes.
 * It provides an interface for attaching/detaching observer objects.
 * 
 * \note observable object should be created using QM_SMART_PTR
 */
class observable  {
	friend class observer;
public:
	typedef observer* 	            			  observer_type;
    typedef std::list<observer_type>   			  observers_container;
    typedef observers_container::iterator         iterator;
    typedef observers_container::const_iterator   const_iterator;
    //
    observable() {}
    virtual ~observable(){}
    
    /** \brief The notify method.
     * The %observable interface
     */
    virtual void notify_observers();
    
    /// \brief Count the number of observer monitoring the object
    unsigned  count_observers() const {return m_observers.size();}
    
private:
	observers_container   m_observers;
    
    void attachObserver(observer_type);
    void detachObserver(observer_type);
};


/** \brief The observer pattern
 * 
 *  \ingroup patterns
 */
class observer  {
public:
	typedef QM_SMART_PTR(observable)             subject_type;
    typedef std::list<subject_type>              subjects_container;
    typedef subjects_container::iterator         iterator;
    typedef subjects_container::const_iterator   const_iterator;
    
    observer() {}
    virtual ~observer();
    
    // \brief the observer interface
    // observable objects will use this method to notify this observer
    virtual void update() {QM_FAIL("update method needs to be implemented in observer");}
    
    /// \brief Register with an obervable
    ///
    ///@param subj The observable to register with
    ///@return true is the registration was succesful
    template<class T>
    bool registerWith(const QM_SMART_PTR(T)& subj);
    
    /// \brief Unregister with an obervable
    ///
    ///@param subj The observable to unregister with
    ///@return true is the unregistration was succesful
    bool unregisterWith(const subject_type& subj);
    
    unsigned  count_subjects() const {return m_subjects.size();}
private:
  	subjects_container     m_subjects;
};



/** \brief A lazy object pattern
 * 
 * A lazy object is an object which receives and sends updates on demand.
 * A lazy object is both observer and subject.
 * \ingroup patterns
 */
class lazy: public observer, public observable  {
public:
	lazy():m_frozen(false){}
    
    /// \brief Freeze the object. No updating and notification is performed
    bool frozen()         {return m_frozen;}
 
    /// \brief Unfreeze the object.
    void set_frozen(bool val)       {m_frozen = val; update();}
    
    //
    void update();
    //
    /// \brief Update the object
    ///
    /// This method is the only method which needs to be implemented by lazy
    /// object implementations
	virtual void updatelazy() {QM_FAIL("Updatelazy not implemented");}
	
private:
    mutable bool  m_frozen;
};



inline void observable::notify_observers() {
    bool successful = true;
    for(observers_container::iterator i=m_observers.begin(); i!=m_observers.end(); ++i) {
        try {
            (*i)->update();
        } catch (...) {
            successful = false;
        }
    }
    QM_REQUIRE(successful, "could not notify one or more observers");
}


inline void observable::attachObserver(observable::observer_type o) {
	m_observers.push_front(o);
}


inline void observable::detachObserver(observable::observer_type o) {
    iterator i = std::find(m_observers.begin(),m_observers.end(),o);
    if (i != m_observers.end())
    	m_observers.erase(i);
}


inline observer::~observer() {
    for (iterator i=m_subjects.begin(); i!=m_subjects.end(); ++i)
        (*i)->detachObserver(this);
}

template<class T>
inline bool observer::registerWith(const QM_SMART_PTR(T)& obj) {
	subject_type subj = smart_cast<observable,T>(obj);
	if (subj) {
		// check if it is already attached
		iterator i = std::find(m_subjects.begin(),m_subjects.end(),subj);
		if(i!= m_subjects.end()) return false;
		//
		m_subjects.push_front(subj);
	    subj->attachObserver(this);
	    return true;
	}
	return false;
}


inline bool observer::unregisterWith(const observer::subject_type& subj) {
	if (subj) {
		iterator i = std::find(m_subjects.begin(),m_subjects.end(),subj);
		if(i!= m_subjects.end()) {
			(*i)->detachObserver(this);
			m_subjects.erase(i);
		    return true;
		}
		return false;
	}
	return false;
}


inline void lazy::update() {
	if(!m_frozen)  {
		this->updatelazy();
		this->notify_observers();
	}
}

QM_NAMESPACE_END

/*! @} */

#endif	//	__OBSERVER_QM_HPP__
