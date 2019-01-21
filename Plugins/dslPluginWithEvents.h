#ifndef dslPluginWithEventsH
#define dslPluginWithEventsH
#include <sstream>
#include <string>
#include "dslPlugin.h"

namespace dsl
{

class PluginManager;
using std::string;
using std::pair;
typedef void (*PluginEvent)(void* data1, void* data2);

class DSL_PLUGINS PluginWithEvents :  public Plugin
{
    friend PluginManager;
    public:
                                                PluginWithEvents(const string& name = gEmptyString, const string& cat = gNoneString, const PluginManager* pm = nullptr);
        virtual                                 ~PluginWithEvents();

        virtual bool                            execute(DSLObject* obj = nullptr, bool inThread = false) = 0;

        virtual bool                            assignOnStartedEvent( PluginEvent   pluginStarted,      void* userData1 = nullptr, void* userData2 = nullptr);
        virtual bool                            assignOnProgressEvent(PluginEvent   pluginsProgress,    void* userData1 = nullptr, void* userData2 = nullptr);
        virtual bool                            assignOnFinishedEvent(PluginEvent   pluginsFinished,    void* userData1 = nullptr, void* userData2 = nullptr);

        bool                                    hasStartedEvent() const;
        bool                                    hasProgressEvent() const;
        bool                                    hasFinishedEvent() const;

        void                                    workStartedEvent(void* data1, void* data2);
        void                                    workProgressEvent(void* data1, void* data2);
        void                                    workFinishedEvent(void* data1, void* data2);

        pair<void*, void*>                      getWorkStartedData();
        pair<void*, void*>                      getWorkProgressData();
        pair<void*, void*>                      getWorkFinishedData();

    protected:

        PluginEvent                             mWorkStartedEvent;
        PluginEvent                             mWorkProgressEvent;
        PluginEvent                             mWorkFinishedEvent;

                                                //!These opaque pointers allow the user to interact with data manipulated
                                                //!with by the plugin, an addition to plugin properties
        void*                                   mWorkStartedData1;
        void*                                   mWorkStartedData2;
        void*                                   mWorkProgressData1;
        void*                                   mWorkProgressData2;
        void*                                   mWorkFinishedData1;
        void*                                   mWorkFinishedData2;
};

}

#endif
