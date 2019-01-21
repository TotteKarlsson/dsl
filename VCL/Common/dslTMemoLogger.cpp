#pragma hdrstop
#include <vector>
#include "dslTMemoLogger.h"
#include "dslStringUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;
bool TMemoLogger::mMemoIsEnabled = false;

//Minimalistic logger to a memo...
TMemoLogger::TMemoLogger(TMemo* aMemo)
:
mMemo(aMemo)
{}

TMemoLogger::~TMemoLogger()
{
    //Don't write to memo if app is closing down..
    if(mMemoIsEnabled == true && mMemo != nullptr)
    {
        vector<string> lines = dsl::split(mStream.str(), '\n');
        for(size_t i = 0; i < lines.size(); i++)
        {
			mMemo->Lines->Add(lines[i].c_str());
            //mMemo->Lines->Insert(0, lines[i].c_str());
        }
    }
}

std::ostringstream& TMemoLogger::get()
{
    return mStream;
}

