#ifndef dslPythonInterpreterH
#define dslPythonInterpreterH
#include "dslObject.h"

#define HAVE_ROUND
#ifdef _DEBUG
#define RESTORE_DEBUG
#undef _DEBUG
#endif
#include <Python.h>
#ifdef RESTORE_DEBUG
#define _DEBUG
#undef RESTORE_DEBUG
#endif

#include "dslStringList.h"
#include "dslPythonPluginsExporter.h"
//---------------------------------------------------------------------------

namespace dsl
{

class PythonPlugin;
class DSL_PYTHONPLUGINS PythonInterpreter : public DSLObject
{
    public:
					                PythonInterpreter(const string& pModuleName, const string& scriptFolder);
		virtual 	                ~PythonInterpreter();
        void                        initialize();
        void                        finalize();
        bool                        isInitialized();

        PyObject*                   loadModule(const string& moduleName="", const string& scriptFolder="");
        PyObject*     			    setupFunction(PyObject* pModule, const string& fName);
        PyObject*           		executeFunction(PyObject* func, const StringList& args = StringList());

		virtual PyObject* 			executeFunction(PyObject* func, PythonPlugin* pl) = 0;
		virtual PyObject* 			executePlugin(PythonPlugin* pl) = 0;

    protected:
//		PyObject* 		            mModuleP;
		PyThreadState* 				mMainThreadState;
   		string			            mModuleName;
   		string			            mScriptFolder;
};

}

#endif
