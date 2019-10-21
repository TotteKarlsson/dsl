#pragma hdrstop
#include "dslStringUtils.h"
#include "dslIPCData.h"

namespace dsl
{

typedef unsigned int uint;

IPCData::IPCData(short id)
:
mIsPacked(true)
{
    mData += toString(id);

}

IPCData::IPCData(const string& data, const char& sep)
:
mIsPacked(true),
mSeparator(sep),
mData(data)
{
    if(mData.size())
    {
        unPack();
    }
}

IPCData::IPCData(const IPCData& rhs)
{
    //copy all data
    mIsPacked     = rhs.mIsPacked;
    mSeparator     = rhs.mSeparator;
    mData       = rhs.mData;
    mRecords    = rhs.mRecords;
}

IPCData::~IPCData(){}

bool IPCData::isPacked() const
{
	return mIsPacked;
}

bool IPCData::unPack()
{
    string sep;
    sep = mSeparator;
    mRecords = splitString(mData,  sep);
    mIsPacked = false;
    return true;
}

bool IPCData::pack()
{
    mData = "[";
    for(uint i = 0; i < mRecords.size(); i++)
    {
        string record = mRecords[0];
        mData += record;
        if(i != mRecords.size())
        {
            mData += mSeparator;
        }
    }
    mRecords.clear();
    mData += "]";
    mIsPacked = true;
    return true;
}

bool IPCData::hasData() const
{
    return (mData.size() > 1) ? true : false;
}

string IPCData::getNextRecord()
{
    mRecordIterator++;
    return (mRecordIterator != end()) ? (*mRecordIterator) : string("");
}

}
