#ifndef dslIPCMessageEnumsH
#define dslIPCMessageEnumsH
#include <string>
#include "dslIPCExporter.h"
//---------------------------------------------------------------------------

using std::string;
namespace dsl
{

DSL_IPC int    getMessageID(const string& cs);
DSL_IPC string getMessageName(int cs);

enum IPC_ID
{
        cUnknown            = -1,
        cUsage              = 0 ,
        cFlush                  , //1
        cShutDown               , //2
        cPause                  , //3
        cInitServer             , //4
        cGetStatus              , //5
        cStart                  , //6
        cStop                   , //7
        cConnectLogger          , //8
        cSetLogLevel            , //9
        cGetLogLevel            , //10
        cLogMessage               //11
};

}
#endif
