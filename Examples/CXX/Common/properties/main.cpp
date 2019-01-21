#pragma hdrstop
#include "dslProperties.h"
#include "dslLogger.h"

ToNarrow
using namespace dsl;

int main()
{
    try
    {
        gLogger.logToConsole(true);
        gLogger.setLogLevel(lDebug5);
        Log(lInfo) << "Logging... ";
        gLogger.showLogTime(false);
        string propName("Prop1");
        Properties props;
        props.add(new Property<int>(4254, propName));

        auto  s = props.getPropertyValue<int>("Prop1");
        Log(lInfo) << "Property value: " << s;

    }
    catch(const DSLException& e)
    {
        Log(lError) << "Exception: " << e.what();
    }

    return 0;
}

#pragma comment(lib, "dslFoundation")
