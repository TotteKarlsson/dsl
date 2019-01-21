#pragma hdrstop
#include <sstream>
#include <iomanip>
#include "dslUtils.h"
#include "dslPluginWithEvents.h"
#include "dslProperty.h"
#include "dslBaseProperty.h"
#include "dslLogger.h"
#include "dslException.h"
//---------------------------------------------------------------------------

namespace dsl
{
using namespace std;

PluginWithEvents::PluginWithEvents(const string& name, const string& category, const PluginManager* pm)
:
Plugin(name, category, pm),
mWorkStartedEvent(nullptr),
mWorkProgressEvent(nullptr),
mWorkFinishedEvent(nullptr)
{}

PluginWithEvents::~PluginWithEvents()
{}

bool PluginWithEvents::hasStartedEvent() const
{
    return (mWorkStartedEvent) ? true : false;
}

bool PluginWithEvents::hasProgressEvent() const
{
    return (mWorkProgressEvent) ? true : false;
}

bool PluginWithEvents::hasFinishedEvent() const
{
    return (mWorkFinishedEvent) ? true : false;
}

void PluginWithEvents::workStartedEvent(void* data1, void* data2)
{
    if(mWorkStartedEvent)
    {
        mWorkStartedEvent(data1, data2);
    }
}

void PluginWithEvents::workProgressEvent(void* data1, void* data2)
{
    if(mWorkProgressEvent)
    {
        mWorkProgressEvent(data1, data2);
    }
}

void PluginWithEvents::workFinishedEvent(void* data1, void* data2)
{
    if(mWorkFinishedEvent)
    {
        mWorkFinishedEvent(data1, data2);
    }
}

pair<void*, void*> PluginWithEvents::getWorkStartedData()
{
    return pair<void*, void*>(mWorkStartedData1, mWorkStartedData2);
}

pair<void*, void*> PluginWithEvents::getWorkProgressData()
{
    return pair<void*, void*>(mWorkProgressData1, mWorkProgressData2);
}

pair<void*, void*> PluginWithEvents::getWorkFinishedData()
{
    return pair<void*, void*>(mWorkFinishedData1, mWorkFinishedData2);
}

bool PluginWithEvents::assignOnStartedEvent(PluginEvent startedFnc, void* userData1, void* userData2)
{
    mWorkStartedEvent = startedFnc;
    mWorkStartedData1 = userData1;
    mWorkStartedData2 = userData2;
    return true;
}

bool PluginWithEvents::assignOnProgressEvent(PluginEvent progress, void* userData1, void* userData2)
{
    mWorkProgressEvent = progress;
    mWorkProgressData1 = userData1;
    mWorkProgressData2 = userData2;
    return true;
}

bool PluginWithEvents::assignOnFinishedEvent(PluginEvent endFnc, void* userData1, void* userData2)
{
    mWorkFinishedEvent = endFnc;
    mWorkFinishedData1 = userData1;
    mWorkFinishedData2 = userData2;
    return true;
}

}

