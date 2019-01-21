#ifndef dslIPCMessageEnumsH
#define dslIPCMessageEnumsH
#include <string>
#include "dslIPCExporter.h"
//---------------------------------------------------------------------------

using std::string;
namespace dsl
{

DSL_IPC int    getIPCMessageID(const string& cs);
DSL_IPC string getIPCMessageName(int cs);

enum IPC_ID
{
        cUnknown            = -1,
        cUsage                  ,
        cFlush                  ,
        cShutDown               ,
        cPause                  ,
        cInitServer             ,
        cGetStatus              ,
        cStart                  ,
        cStop                   ,
        cConnectLogger          ,
        cSetLogLevel            ,
        cGetLogLevel            ,
        cLogMessage
};

}
#endif
