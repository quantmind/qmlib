//
/// \file
/// \ingroup config
/// \brief definitions for qmlib library
//
#ifndef __DEFINITIONS_QM_H__
#define __DEFINITIONS_QM_H__
//
//
// Uncomment if building with Visual Studio
//#define		__BUILD_VISUAL_STUDIO__

#include <qmlib/qmconfig.hpp>
#include <vector>
#include <map>
#include <list>
#include <cstddef>
#include <cmath>

#include <boost/assert.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/current_function.hpp>
//#include <boost/numeric/ublas/matrix.hpp>

#define PI 3.14159265358979323846

//
#ifdef  __QM_BUILD_LIBRARY__
  #ifdef	__QM_EXPORT_LIBRARY__
		#define QMDLL __declspec(dllexport)
  #else
    #define QMDLL __declspec(dllimport)
  #endif
#else
	#define QMDLL
#endif  // __QM_BUILD_LIBRARY__
//
/*! \defgroup macros qmlib macros

    Global definitions and a few macros which help porting the
    code to different compilers.

    @{
*/
//
/*! \def QM_NAMESPACEsensitivity

    Define the root namespace for qmlib library
*/
#define QM_NAMESPACE                   namespace qmlib  {

/*! \def QM_NAMESPACE2(X)

    Define a subnamespace of name X for qmlib library
*/
#define QM_NAMESPACE2(X)               namespace qmlib { namespace X  {
#define QM_NAMESPACE3(X,Y)             namespace qmlib { namespace X  { namespace Y  {
#define QM_USING_NAMESPACE		       using namespace qmlib
#define QM_USING_NAMESPACE2(X)         using namespace qmlib::X
#define QM_USING_NAMESPACE3(X,Y)       using namespace qmlib::X::Y
#define QM_FROM_NAMESPACE2(X)          qmlib::X::
#define QM_FROM_NAMESPACE3(X,Y)        qmlib::X::Y::
#define QM_NAMESPACE_END				}
#define QM_NAMESPACE_END2				}}
#define QM_NAMESPACE_END3				}}}
#define QM_ERROR_LINES
#define QM_ERROR_FUNCTIONS
//#define QM_ENABLE_TRACING_IN_DEBUG
//sensitivity
//
#define qm_list                 boost::python::list
#define qm_info_dict			boost::python::dict
//
//
#define QM_SMART_PTR(T)         boost::shared_ptr<T >
#define QM_DICTIONARY(T)        std::map<std::string,T >
#define QM_HASH_TABLE(K,T)      std::map<K,T>
//
#define QM_LIST(T)          	std::list<QM_SMART_PTR(T) >
#define QM_VECTOR_PTR(T)    	std::vector<QM_SMART_PTR(T) >
#define QM_LIST_OBJ(T)      	std::list<T>
#define QM_SET(T)           	std::set<T>
//
/*! @} */
//
//
//
/// \brief short integersensitivity
typedef short                     qm_short;
/// \brief integer
typedef int		                  qm_int;
/// \brief long integer
typedef long	                  qm_long;
/// \brief unsigned short integer
typedef unsigned char             qm_uns_char;
/// \brief unsigned integer
typedef unsigned int        	  qm_uns_int;
/// \brief unsigned long integer
typedef unsigned long	          qm_uns_long;
/// \brief real value
typedef double	                  qm_real;
/// the size of a container
typedef std::size_t               qm_Size;
/// \brief a string object
typedef std::string               qm_string;
/// \brief vector of strings
typedef std::vector<qm_string>    qm_strings;


template<class T, class U>
inline QM_SMART_PTR(T) smart_cast(QM_SMART_PTR(U) const & inst)  {
	return boost::dynamic_pointer_cast<T,U>(inst);
}

/// \brief Template class for shape information
template<class C, class S>
struct arrayinfo  {
};


struct Nil {};

//
#ifdef	_DEBUG_
#	ifdef	QM_ENABLE_TRACING_IN_DEBUG
#		define	QM_ENABLE_TRACING	1
#	endif
#endif


//
//
//
#endif // __DEFINITIONS_QM_H__
//
