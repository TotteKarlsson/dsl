#pragma hdrstop
#include "dslPythonPlugin.h"
#include "dslLogger.h"
#include "dslException.h"
//---------------------------------------------------------------------------

namespace dsl
{

int gPluginCount = 0;

using Poco::DateTimeFormatter;
using namespace dsl;

//---------------------------------------------------------------------------
PythonPlugin::PythonPlugin(PluginManager* manager)
:
PluginWithEvents( "PythonPlugin",   "Python Test Plugin With Events", manager),
mWorker(*this),
mExecuteFunction(NULL),
mPyModule(NULL)
{
    mMetaData.setVersion("1.0.0");
    mMetaData.setHint("A Python Plugin");
    mMetaData.setDescription("Set this up by running init function in the Python");
    mMetaData.add("Minimum PythonVersion", "3.0");
}

PythonPlugin::~PythonPlugin()
{
    Log(lInfo) << "In PythonPlugin destructor";
}

bool PythonPlugin::execute(DSLObject* subject, bool inThread)
{
    Log(lInfo)<<"Testing Plugin";

    //go away and carry out the work in a thread, or not if inThread is false
    return mWorker.start(inThread);
}

void PythonPlugin::assignExecuteFunction(PyObject* f)
{
	mExecuteFunction = f;
}

void PythonPlugin::assignPyModule(PyObject* f)
{
	mPyModule = f;
}

const PythonInterpreter* PythonPlugin::getPythonInterpreter()
{
    PluginManager* pm = const_cast<PluginManager*>(getPluginManager());
    PythonPluginManager* ppm = dynamic_cast<PythonPluginManager*>(pm);
    if(!ppm)
    {
        throw("Bad stuff..");
    }
    return ppm->getPythonInterpreter();
}

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

// Plugin factory function
Plugin* createPlugin(void* manager)
{
    //allocate a new plugin object and return it
    Plugin* p = new PythonPlugin((PluginManager*) manager);
    if(p)
    {
        gPluginCount++;
    }
    return p;
}

// Plugin factory function
bool destroyPlugin(Plugin* p)
{
    delete p;
    gPluginCount--;
    return true;
}

}

