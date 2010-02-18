//
//  errors.h
//  Classes and functions for error handling
//
#ifndef __ERROR_QM_HPP__
#define __ERROR_QM_HPP__


#include <qmlib/corelib/tools/tracing.hpp>
#include <exception>
#include <sstream>
#include <stdexcept>

/*! \defgroup utility Utilities

    Several classes for general usage

    @{
*/



QM_NAMESPACE


/// \brief Base error class
class Error: public std::exception  {
public:
	Error(const qm_string& file, long line, const qm_string& function, const qm_string& message = "");
    ~Error() throw() {}
    
    const char* what() const throw ();
private:
    QM_SMART_PTR(qm_string) m_message;
};


///  \brief throw an error (possibly with file and line information)
#define QM_FAIL(message) \
do { \
    std::ostringstream _qm_msg_stream; \
    _qm_msg_stream << message; \
    throw Error(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION,_qm_msg_stream.str()); \
} while (false)
//
//
/// \brief throw an error if the given condition is not verified
#define QM_ASSERT(condition,message) \
if (!(condition)) { \
    std::ostringstream _qm_msg_stream; \
    _qm_msg_stream << message; \
    throw Error(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION,_qm_msg_stream.str()); \
} else
//
//
/// \brief throw an error if the given pre-condition is not verified
#define QM_REQUIRE(condition,message) \
if (!(condition)) { \
    std::ostringstream _qm_msg_stream; \
    _qm_msg_stream << message; \
    throw Error(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION,_qm_msg_stream.str()); \
} else
//
//
/// \brief throw an error if the given post-condition is not verified
#define QM_ENSURE(condition,message) \
if (!(condition)) { \
    std::ostringstream _qm_msg_stream; \
    _qm_msg_stream << message; \
    throw Error(__FILE__,__LINE__,BOOST_CURRENT_FUNCTION,_qm_msg_stream.str()); \
} else


#ifdef	_DEBUG_

#	define	QMIND_PRECONDITION(X,Y)	QM_ASSERT(X,Y)

#else

#	define	QMIND_PRECONDITION(X,Y)

#endif





QM_NAMESPACE_END


/*! @} */


#include  <qmlib/corelib/impl/error_impl.hh>



#endif	//	__ERROR_QM_HPP__

