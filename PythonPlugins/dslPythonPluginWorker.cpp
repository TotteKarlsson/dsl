#pragma hdrstop
#include "dslPythonPluginWorker.h"
#include "dslPythonPlugin.h"
#include "dslPythonInterpreter.h"
#include "dslLogger.h"
#include "dslUtils.h"
#include "dslException.h"
//---------------------------------------------------------------------------

namespace dsl
{

PythonPluginWorker::PythonPluginWorker(PythonPlugin& host)
:
mTheHost(host)
{}

bool PythonPluginWorker::start(bool runInThread)
{
    if(runInThread)
    {
        if(mThread.isRunning())
        {
            Log(lError)<<"Tried to start a working thread!";
            return false;
        }

        //Run the worker in a thread
        mThread.start(*this);
    }
    else
    {
        run(); //Not running worker in a thread
    }
    return true;
}

bool PythonPluginWorker::isRunning() const
{
    return mThread.isRunning();
}

void PythonPluginWorker::run()
{
    mTheHost.mIsWorking = true;
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();


    if(mTheHost.mWorkStartedEvent)
    {
        mTheHost.mWorkStartedEvent(mTheHost.mWorkStartedData1, NULL);
    }

    try
    {
        //Call python plugins execute..
        PythonInterpreter* pi 		= const_cast<PythonInterpreter*>(mTheHost.getPythonInterpreter());
        PyObject* result 			= pi->executePlugin(&mTheHost);

        //We can check the result here, typically a boolean
        Py_DECREF(result);
    }
    catch(const DSLException& e)
    {
        Log(lError) << "Exception: "<<e.what();
    }
    catch(...)
    {
        Log(lError) << "Python worker throw an exception..";
    }

    if(mTheHost.mWorkFinishedEvent)
    {
        mTheHost.mWorkFinishedEvent(mTheHost.mWorkFinishedData1, NULL);
    }

   	PyGILState_Release(gstate);
    mTheHost.mIsWorking = false;
    mTheHost.mTerminate = false;
}

}
