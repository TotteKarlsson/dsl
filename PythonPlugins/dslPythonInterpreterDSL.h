#ifndef dslPythonInterpreterDSLH
#define dslPythonInterpreterDSLH
#include "dslPythonInterpreter.h"
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_PYTHONPLUGINS PythonInterpreterDSL : public PythonInterpreter
{
    friend class PythonPlugin;
    public:
					                PythonInterpreterDSL(const string& pModuleName, const string& scriptFolder);
					                ~PythonInterpreterDSL();
		PyObject* 					executePlugin(PythonPlugin* pl);
		PyObject* 					executeFunction(PyObject* func, PythonPlugin* pl);
};

}

#endif
