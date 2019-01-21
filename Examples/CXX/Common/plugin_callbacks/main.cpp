#pragma hdrstop
#pragma argsused
#include "dslPluginWithEvents.h"
#include <iostream>
using namespace dsl;
using namespace std;

class MyPlugin : public PluginWithEvents
{
    public:
        bool execute(DSLObject* obj = nullptr, bool inThread = false){return true;}
        int  getAnInt(){return 42;}
};

void c1(void* _v1, void* _v2)
{
    MyPlugin* v1 = (MyPlugin*) _v1;
    int* v2 = (int*) _v2;
    cout << "Hello" << v1->getAnInt() <<" " << * v2;
}

int main()

{
    MyPlugin pl;
    pl.assignOnStartedEvent(c1, &pl);


    //Call the callback
    for(int i = 0; i < 10; i++)
    {
    	pl.workStartedEvent(&pl, &i);
    }

	return 0;
}

#pragma comment(lib, "dslFoundation.lib")



