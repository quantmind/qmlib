

#ifndef __TRACING_QM_H__
#define __TRACING_QM_H__


#include <qmlib/corelib/templates/patterns.hpp>


#ifdef	QM_ENABLE_TRACING

#include <iostream>


QM_NAMESPACE


class tracing : public singleton<tracing> {
	friend class singleton<tracing>;
public:
	void setStream(std::ostream& stream) { out_ = &stream; }
	bool enabled() const { return enabled_; }
	std::ostream& stream() { return *out_; }
	int depth() const { return depth_; }
	void down() { depth_++; }
	void up() { depth_--; }
private:
	std::ostream* out_;
	bool enabled_;
	int depth_;        
    tracing();
};

inline tracing::tracing(): out_(&std::cerr), enabled_(false), depth_(0) {}


#define QM_DEFAULT_TRACER   qmlib::tracing::instance()


#define QM_TRACE_ON(out) QM_DEFAULT_TRACER.setStream(out)

#define QM_TRACE(message) 													\
    try { 																	\
        QM_DEFAULT_TRACER.stream() << "trace[" << QM_DEFAULT_TRACER.depth() \
                                   << "]: " << message << std::endl; 		\
    } catch (...) {}

#define QM_TRACE_ENTER_FUNCTION 											\
    try { 																	\
        QM_DEFAULT_TRACER.down(); 											\
        QM_DEFAULT_TRACER.stream() << "trace[" << QM_DEFAULT_TRACER.depth() \
                                   << "]: " 								\
                                   << "Entering " << BOOST_CURRENT_FUNCTION \
                                   << std::endl; 							\
    } catch (...) {}

#define QM_TRACE_EXIT_FUNCTION 												\
    try { 																	\
        QM_DEFAULT_TRACER.stream() << "trace[" << QM_DEFAULT_TRACER.depth() \
                                   << "]: " 								\
                                   << "Exiting " << BOOST_CURRENT_FUNCTION 	\
                                   << std::endl; 							\
        QM_DEFAULT_TRACER.up(); 											\
    } catch (...) { QM_DEFAULT_TRACER.up(); }

#define QM_TRACE_LOCATION QM_TRACE("At line " << __LINE__ << " in " << __FILE__)

#define QM_TRACE_VARIABLE(variable) QM_TRACE(#variable << " = " << variable)

QM_NAMESPACE_END

#else

QM_NAMESPACE

#define QM_DEFAULT_TRACER
#define QM_TRACE_ON(out)
#define QM_TRACE(message)
#define QM_TRACE_ENTER_FUNCTION
#define QM_TRACE_EXIT_FUNCTION
#define QM_TRACE_LOCATION
#define QM_TRACE_VARIABLE(variable)

QM_NAMESPACE_END

#endif	//	QM_ENABLE_TRACING


#endif	//	__TRACING_QM_H__

