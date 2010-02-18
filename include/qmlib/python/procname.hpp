
//
//
#ifndef __PYTHON_PROCNAME_QM_H__
#define __PYTHON_PROCNAME_QM_H__
//
//
//
#include <qmlib/python/pyconfig.hpp>
#include <sys/prctl.h>
//
//
QM_NAMESPACE2(python)

using namespace boost::python;

class procname  {
public:
	std::string get(tuple args) {
		int argc;
		char **argv;
		Py_GetArgcArgv(&argc, &argv);
		return Py_BuildValue("s", argv[0]);
	}
};
