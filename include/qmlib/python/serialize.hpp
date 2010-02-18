
#ifndef		__SERIALIZATION_WRAP_QM_HPP__
#define		__SERIALIZATION_WRAP_QM_HPP__

#include <iomanip>
#include <iostream>
#include <fstream>
#include <qmlib/python/pyconfig.hpp>


#ifdef	QM_SERIALIZE


#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>

/** \file
 * \brief Class templates for object serialization in Python
 * \ingroup python
 */



QM_NAMESPACE2(python)


/** \brief Lightweight implementation of pickle support
 * \ingroup python
 * 
 * Class template used to add pickle support to classes.
 * @param T C++ class for wich pickle support is implemented
 * 
 * This implementation assume that a default constructor is
 * available for class T.
 * 
 * @see http://www.boost.org/libs/python/doc/v2/pickle.html for more documentation
 * on Boost.Python Pickle support.
 */
template<class T>
struct qmlib_pickle_suite : boost::python::pickle_suite  {
	
	/** \brief Define the Python __getstate__ method
	 * 
	 * \note This methodhas an important pitfall that
	 * the end user of a Boost.Python extension module might not be aware of.
	 * 
	 * The following possibilities must be taken into consideration:
	 *  - If this class is used in Python as a base class. Most likely the __dict__
	 * of instances of the derived class needs to be pickled in order to restore the instances correctly.
	 *  - the user adds items to the instance's __dict__ directly.
	 * Again, the __dict__ of the instance then needs to be pickled.
	 * 
	 * @see http://www.boost.org/libs/python/doc/v2/pickle.html for more information
	 */ 
	static boost::python::object
	getstate (const T& obj) {
	    std::ostringstream os;
	    boost::archive::binary_oarchive oa(os);
	    oa << obj;
	    return boost::python::str(os.str());
	}
	
	/** \brief Define the Python __setstate__ method
	 * 
	 * When an instance of a Boost.Python extension class is restored by the
	 * unpickler (cPickle.loads), it is first constructed using the result of
	 * __getinitargs__ as arguments.
	 * Subsequently the unpickler tests if the new instance has a
	 * __setstate__  method. If so, this method is called with the result of
	 * __getstate__ (a Python object) as the argument.
	 * 
	 * @see http://www.boost.org/libs/python/doc/v2/pickle.html
	 */
	static void
	setstate(T& obj, boost::python::object entries) {
	    boost::python::str s = boost::python::extract<boost::python::str>(entries)();
	    qm_string st = boost::python::extract<qm_string>(s)();
	    std::istringstream is(st);
	    boost::archive::binary_iarchive ia(is);
	    ia >> obj;
	}
};




QM_NAMESPACE_END2

#endif	//	QM_SERIALIZE


#endif	//	__SERIALIZATION_WRAP_QM_HPP__




