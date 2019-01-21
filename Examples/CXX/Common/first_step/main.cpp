#pragma hdrstop

#include "dslLogger.h"
#include "dslCommon.h"
#include "dslUtils.h"

#include <iostream>
using namespace dsl;
using namespace std;

int main()
{
    LogOutput::mLogToConsole = true;

    Log(lInfo) << "Hello";
    cout<<"API Version: "	<< getVersion()	<<endl;
    cout<<"Copyright: "		<< getCopyright() <<endl;

    cout<<"Time is: "<<getTime() << endl;
    sleep(4000);
    cout<<"Exiting..\n";

    return 0;
}


