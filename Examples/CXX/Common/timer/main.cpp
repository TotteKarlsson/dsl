#pragma hdrstop
#include "dslUtils.h"
#include "dslStringUtils.h"
#include "dslTimer.h"
using namespace dsl;

int main(int argc, char* argv[])
{
    int seconds(5);
    if(argc == 2)
    {
        seconds = toInt(argv[1]);
    }

    Timer aTimer;
    cout << "Starting\n" << endl;
    aTimer.start();

    do
    {
        sleep(250);
        cout<<"Lapsed time since start: "			<<aTimer.getElapsedTime().seconds()<<":"<<aTimer.getElapsedTime().milliseconds()<<endl;
    }
    while(seconds > aTimer.getElapsedTime().seconds());

    cout <<"Done..\n"<<endl;
    return 0;
}


//#pragma comment(lib, "dslFoundation")
//#pragma comment(lib, "poco_foundation")
