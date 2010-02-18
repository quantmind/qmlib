//
/// @defgroup patterns
/// \file
/// \brief Definition of some generic Patterns
/// \ingroup patterns
//
//
#ifndef   __PATTERNS_QM_H__
#define   __PATTERNS_QM_H__




#include <qmlib/definitions.hpp>


QM_NAMESPACE


/** \brief The Curiously Recurring Template Pattern (CRTP).
 * 
 * A class T has, as a base class, a template specialization of CRTP, taking T itself
 * as an argument.
 * \ingroup patterns
 */
template<typename T>
class CRTP { 
public:
	CRTP() { }
	CRTP(const CRTP<T>&) { }
	T& unwrap() { return static_cast<T&>(*this); }
	const T& unwrap() const { return static_cast<const T&>(*this); }
};
    
/**
 * \ingroup patterns
 */
template<class T>
class singleton : private boost::noncopyable {
public:
	/// \brief access to the unique instance
    static T& instance();
protected:
    singleton() {}
    static QM_SMART_PTR(T) m_instance;
};


template <class T>
QM_SMART_PTR(T) singleton<T>::m_instance;


template <class T>
T& singleton<T>::instance() {
	if(!m_instance)
		m_instance = QM_SMART_PTR(T)(new T);
    return *m_instance;
}

/// \brief Visitor for a specific class T
/// \ingroup patterns
template <class T>
class visitor {
public:
  virtual ~visitor() {};
  //
  /// \brief Visit the "visited" class T
  /// @param pointer to T
  virtual void visit(T&) const {}
};



/// \brief Reference counter class
template<class T>
class refCount : public T {
public:
	refCount():m_references(0){}
    	
   	int reference() const { return m_references;}

   	int addReference()  {++m_references; return m_references;}
    	
   	int removeReference()  {
   		--m_references;
   		return m_references;
   	}
   	
	T& 		 cast() 		{ return static_cast<T&>(*this); }
	const T& cast() const 	{ return static_cast<const T&>(*this); }
private:
   	int m_references;
};

template<class S>
class simple_smart  {
	typedef	S		elementtype;
	simple_smart():m_ptr(0){}
private:
	refCount<S>*	m_ptr;
};




    /*
    //
    class acyclicVisitor {
    public:
      virtual ~acyclicVisitor() {}
    };
    //
    //
#   include<qmlib/impl/patterns_impl.hpp>
    //
    */
QM_NAMESPACE_END
//
#endif  // __PATTERNS_QM_H__
//
