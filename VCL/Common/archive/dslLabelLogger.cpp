#pragma hdrstop
#include <vector>
#include "dslLabelLogger.h"
#include "dslUtils.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace std;
using namespace dsl;

TLabel* LabelLogger::mLogLabel = nullptr;
//Minimalistic logger to a memo...
LabelLogger::LabelLogger(TLabel* aLbl)

{
    if(!mLogLabel)
    {
        mLogLabel = aLbl;
    }
}

LabelLogger::~LabelLogger()
{
    vector<string> lines = dsl::splitString(mStream.str(), "\n");

    for(int i = 0; i < lines.size(); i++)
    {
        mLogLabel->Caption = vclstr(lines[i]);
    }
}

std::ostringstream& LabelLogger::Get()
{
    return mStream;
}

