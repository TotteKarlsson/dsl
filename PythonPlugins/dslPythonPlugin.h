#ifndef dslPythonPluginH
#define dslPythonPluginH
#include "dslPluginWithEvents.h"
#include "dslProperty.h"
#include "dslPythonPluginWorker.h"
#include "dslPythonInterpreter.h"
#include "dslPythonPluginManager.h"
#include "Python.h"
//---------------------------------------------------------------------------


namespace dsl
{

//A Python plugin loads a pytho interpreter and executes a python script in a thread
class DSL_PYTHONPLUGINS PythonPlugin : public PluginWithEvents
{
    friend class PythonPluginWorker;
    friend class PythonInterpreterDSL;
    public:
                                        PythonPlugin(PluginManager* manager);
    	virtual                         ~PythonPlugin();

                                        //!The first argument allow the client to set
                                        //the initial value of the property, anInt
        bool                            execute(DSLObject* obj, bool inThread);
        const PythonInterpreter*        getPythonInterpreter();
        PyObject*                       getModule(){return mPyModule;}
        void                            assignExecuteFunction(PyObject* f);
        void                            assignPyModule(PyObject* f);


    protected:
                                        //!The worker is doing the work..
        PythonPluginWorker     			mWorker;
        PyObject*                       mExecuteFunction;
        PyObject*                       mPyModule;

};

DSL_PYTHONPLUGINS extern int gPluginCount;
DSL_PYTHONPLUGINS Plugin* createPlugin(void* manager);

// Plugin factory function
DSL_PYTHONPLUGINS bool destroyPlugin(Plugin* p);
}
#endif
