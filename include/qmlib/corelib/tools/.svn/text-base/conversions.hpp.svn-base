


#ifndef   __CONVERSIONS_QM_HPP__
#define   __CONVERSIONS_QM_HPP__



#include <qmlib/corelib/tools/error.hpp>
#include <qmlib/corelib/tools/string.hpp>


/*! \defgroup conversions Several conversion templates


    @{
*/



/// \file
/// \brief Definition of some generic Containers
/// \ingroup patterns


QM_NAMESPACE


template<class T, class L>
struct extract_from_list_object  {
	static T doit(const L& cv, unsigned idx)  {
		return dynamic_cast<T>(cv[idx]);
	}
};



/// \brief Helper struct used to extract an element from another one
/// @param T element type
/// @param F element to convert
template<class T, class F>
struct object_conversion  {
	static T doit(const F& cv)  {
		return dynamic_cast<T>(cv);
	}
};

/// \brief Helper struct used to extract an element from another one
/// @param T element type
template<class T>
struct extract_from_object  {
	template<class F>
	static T doit(const F& cv)  {
		return object_conversion<T,F>::doit(cv);
	}
};

/// \brief Helper struct used to add element to a list
/// @param T element type
/// @param L list type
template<class T, class L>
struct element_to_list  {
	static const T& doit(const T& el) {
		return el;
	} 
};


template<class L>
inline unsigned length(const L& list)  {
	return list.size();
}





///////////////////////////////// SPECIALIZATIONS



template<class T>
struct object_conversion<T,T>  {
	static const T& doit(const T& cv)  {
		return cv;
	}
};

//template<>
template<class T, class F>
struct object_conversion<QM_SMART_PTR(T), QM_SMART_PTR(F) >  {
	static QM_SMART_PTR(T) doit(const QM_SMART_PTR(F)& cv)  {
		return smart_cast<T,F>(cv);
	}
};


QM_NAMESPACE_END


/*! @} */


#endif  // __CONVERSIONS_QM_HPP__


