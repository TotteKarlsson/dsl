#pragma hdrstop
#include "dslPythonInterpreterDSL.h"
#include "dslLogger.h"
#include "dslPythonPlugin.h"
#include "dslException.h"
#include "dsl/dsl_swigpyrun.h"
//---------------------------------------------------------------------------

using namespace std;
namespace dsl
{

PythonInterpreterDSL::PythonInterpreterDSL(const string& scriptName, const string& sf)
:
PythonInterpreter(scriptName, sf)
{}

PythonInterpreterDSL::~PythonInterpreterDSL()
{}

//Excution of a Python plugin function involves calling the function with
//a plugin instance as parameter
PyObject* PythonInterpreterDSL::executeFunction(PyObject* func, PythonPlugin* pythonPluginObj)
{
    if(!pythonPluginObj)
    {
        return NULL;
    }

    //Our C++ PluginClass is "Python\Plugin". Swig info about this type in Swig is obtained by the function
    //SWIG_TypeQuery("namespace::MyClass *")
    swig_type_info* swigTypeInfo = SWIG_TypeQuery("dsl::PythonPlugin *");

	//Create a Python object from our C++ object
	PyObject* pPlugin = SWIG_NewPointerObj((void*)pythonPluginObj, swigTypeInfo,  0);

    if(func)
    {
	    PyObject* pArgs = PyTuple_New(1);

    	/* pValue reference stolen here: */
	    PyTuple_SetItem(pArgs, 0, pPlugin);

    	/***** Calling python here *****/
        PyObject* result = PyObject_CallObject(func, pArgs);
	    Py_DECREF(pArgs);

        if (result)
        {
            Log(lInfo) <<"Result of Python call: " << PyLong_AsLong(result);
            return result;
        }
        else
        {
            stringstream msg;
            msg << "Execution of plugin function for Plugin \"" << pythonPluginObj->getName() << "\" failed";
            Log(lError) << msg.str();
			throw(DSLException(msg.str()));
        }
    }
    return NULL;
}

//Excution of a Python plugin involves calling a Python function named "execute", with
//a plugin instance as parameter
PyObject* PythonInterpreterDSL::executePlugin(PythonPlugin* plugin)
{
    if(!plugin)
    {
        return NULL;
    }

    //Our C++ PluginClass is "Python\Plugin". Swig info about this type in Swig is obtained by the function
    //SWIG_TypeQuery("namespace::MyClass *")
    swig_type_info* swigTypeInfo = SWIG_TypeQuery("dsl::PythonPlugin *");

	//Create a Python object from our C++ object
	PyObject* pPlugin = SWIG_NewPointerObj((void*)plugin, swigTypeInfo,  0 );

    PyObject* f	= setupFunction(plugin->getModule(), "execute");
    if(f)
    {
	    PyObject* pArgs = PyTuple_New(1);

    	/* pValue reference stolen here: */
	    PyTuple_SetItem(pArgs, 0, pPlugin);

    	/***** Calling python here *****/
        PyObject* result = PyObject_CallObject(f, pArgs);
	    Py_DECREF(pArgs);
		Py_DECREF(f);

        if (result)
        {
            Log(lInfo) <<"Result of Python call: " << PyLong_AsLong(result);
            return result;
        }
        else
        {
            stringstream msg;
            msg << "Execution of plugin \"" << plugin->getName() << "\" failed";
            Log(lError) << msg.str();
			throw(DSLException(msg.str()));
        }
    }
    return NULL;
}

}
