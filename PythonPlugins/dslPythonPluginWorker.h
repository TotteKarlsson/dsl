#ifndef dslPythonPluginWorkerH
#define dslPythonPluginWorkerH
#include "dslPythonPluginsExporter.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
//---------------------------------------------------------------------------

namespace dsl
{
class PythonPlugin;

class DSL_PYTHONPLUGINS PythonPluginWorker : public Poco::Runnable
{
    protected:
        Poco::Thread            mThread;
        PythonPlugin&   	 	mTheHost;

    public:
                                PythonPluginWorker(PythonPlugin& mTheHost);
        bool                    start(bool useThread = true);
        void                    run();
        bool                    isRunning() const;
};

}
#endif
