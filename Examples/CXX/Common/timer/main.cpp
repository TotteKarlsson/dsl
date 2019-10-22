#pragma hdrstop
#include "dslUtils.h"
#include "dslStringUtils.h"
#include "dslTimer.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>

using namespace dsl;
using namespace std;


class MyClass
{
public:
    void timerCallback()
    {
        cout << "Timer calback" << endl;
    }
};

int main(int argc, char* argv[])
{
    int seconds(5);
    if(argc == 2)
    {
        seconds = toInt(argv[1]);
    }

    MyClass a;
    Timer aTimer(Timespan(1000 * Timespan::MILLISECONDS), boost::bind(&MyClass::timerCallback, a), "MyTimer");

    //aTimer.assignTimerFunction(boost::bind(&MyClass::timerCallback, a));
    cout << "Starting\n" << endl;
    aTimer.start();

    do
    {
        sleep(250);
        cout<<"Lapsed time since start: " <<aTimer.getElapsedTime().seconds()<<":"<<aTimer.getElapsedTime().milliseconds()<<endl;
    }
    while(seconds > aTimer.getElapsedTime().seconds());

    cout <<"Done..\n"<<endl;
    return 0;
}


//#pragma comment(lib, "dslFoundation")
//#pragma comment(lib, "poco_foundation")
