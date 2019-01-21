#pragma hdrstop
#include "dslIPCMessageEnums.h"
#include "dslStringUtils.h"
//---------------------------------------------------------------------------


namespace dsl
{

int getIPCMessageID(const string& cs)
{
    if(compareStrings(cs, "Usage",       csCaseInsensitive))    return cUsage;
    if(compareStrings(cs, "Flush",       csCaseInsensitive))    return cFlush;
    if(compareStrings(cs, "ShutDown",    csCaseInsensitive))    return cShutDown;
    if(compareStrings(cs, "Pause",       csCaseInsensitive))    return cPause;
    if(compareStrings(cs, "LogMessage",  csCaseInsensitive))    return cLogMessage;
    return cUnknown;
}

string getIPCMessageName(int cs)
{
    switch (cs)
    {
        case cUsage:                return  "Usage";
        case cFlush:                return  "Flush";
        case cShutDown:             return  "ShutDown";
        case cPause:                return  "Pause";
        case cLogMessage:           return  "LogMessage";
        default: return "UNKNOWN";
    }
}

}

