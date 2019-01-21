#pragma hdrstop
#include "dslPythonInterpreter.h"
#include <sstream>
#include "dslLogger.h"
#include "dslStringUtils.h"
#include "dslPythonPlugin.h"
#include "dslException.h"
//---------------------------------------------------------------------------

using namespace std;
namespace dsl
{

PythonInterpreter::PythonInterpreter(const string& scriptName, const string& sf)
:
//mModuleP(NULL),
mModuleName(scriptName),
mScriptFolder(sf),
mMainThreadState(NULL)
{}

bool PythonInterpreter::isInitialized()
{
	return Py_IsInitialized() == 0 ? false : true;
}

PythonInterpreter::~PythonInterpreter()
{
	finalize();
}

void PythonInterpreter::initialize()
{
	Py_Initialize();
    PyEval_InitThreads();
}

void PythonInterpreter::finalize()
{
	// shut down the interpreter
	//PyEval_AcquireLock();
	//Py_Finalize();
}

PyObject* PythonInterpreter::loadModule(const string& moduleName, const string& scriptFolder)
{
    if(moduleName.size())
    {
        mModuleName = moduleName;
    }

    if(scriptFolder.size())
    {
        mScriptFolder = scriptFolder;
    }

    PyObject* pm = PyUnicode_DecodeFSDefault(mModuleName.c_str());

    string logFile = gLogger.getLogFileName();
    logFile = replaceCharacter('\\', '/', logFile);

    //Prepare the Python interpreter
    stringstream cmd;
    cmd << "import sys" << endl
    	<< "sys.path.append(\"" << mScriptFolder << "\")" << endl;

    //Have Python log to the applications (C++) logfile
    cmd <<"sys.stdout = sys.stderr = open('" << logFile << "', 'a')" << endl;
    cmd <<"print ('PY_DEBUG: Entering the Python')" << endl;
    cmd <<"sys.stdout.flush()" << endl;

	Log(lDebug5) << "Executing Python Code: " << cmd.str();
	PyRun_SimpleString(cmd.str().c_str());

    PyObject* pyM = PyImport_Import(pm);
    Py_DECREF(pm);


    if (!pyM)
    {
        PyErr_Print();
        stringstream msg;
        msg << "Failed to load the python module: "<< mModuleName;
        Log(lError) << msg.str();
        throw(DSLException (msg.str()));
    }
    return pyM;
}

PyObject* PythonInterpreter::setupFunction(PyObject* pyModule, const string& fName)
{
    PyObject* pFunc = PyObject_GetAttrString(pyModule, fName.c_str());

    if (!pFunc || !PyCallable_Check(pFunc))
    {
        if (PyErr_Occurred())
        {
            PyErr_Print();
        }

        stringstream msg;
        msg << "Failed to setup Python function: "<<fName;
        throw(DSLException(msg.str()));
    }

    return pFunc;
}

PyObject* PythonInterpreter::executeFunction(PyObject* pFunc, const StringList& args)
{
    PyObject* pArgs = PyTuple_New(args.size());

    for (int i = 0; i < args.size(); ++i)
    {
        PyObject* pValue = PyLong_FromLong(atoi(args[i].c_str()));
        if (!pValue)
        {
            Py_DECREF(pArgs);
//            Py_DECREF(mModuleP);
	        stringstream msg;
    	    msg<<"Failure converting python function argument";
            throw(msg.str());
        }

        /* pValue reference stolen here: */
        PyTuple_SetItem(pArgs, i, pValue);
    }

	PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    /***** Calling python here *****/
    PyObject *pValue= PyObject_CallObject(pFunc, NULL);

   	PyGILState_Release(gstate);

    Py_DECREF(pArgs);
    if (pValue)
    {
        return pValue;
    }
    else
    {
        Py_DECREF(pFunc);
//        Py_DECREF(mModuleP);
        stringstream msg;
        msg<<"Failure calling python function";
        throw(DSLException(msg.str()));
    }
    return NULL;
}

}
