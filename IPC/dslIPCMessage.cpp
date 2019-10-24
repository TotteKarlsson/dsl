#pragma hdrstop
#include "dslIPCMessage.h"
#include "dslIPCMessageEnums.h"
#include "dslStringUtils.h"

namespace dsl
{

typedef unsigned int uint;

#undef GetMessage

IPCMessage::IPCMessage(int msgID, const string& msgData, int from_socket)
:
IPCData(msgData),
mSocketID(from_socket),
mIsProcessed(false)
{
    if(mRecords.size())
    {
        mMessageID = (msgID == -1) ? getIPCMessageID(mRecords[0]) : msgID;
    }
}

IPCMessage::IPCMessage(const IPCMessage& rhs)
:
IPCData(rhs)
{
    mSocketID         = rhs.mSocketID;
    mMessageID        = rhs.mMessageID;
    mIsProcessed    = rhs.mIsProcessed;
}

void IPCMessage::Empty()
{
    mMessageID = -1;
    mRecords.clear();
    mData.clear();
}

string IPCMessage::GetMessageName() const
{
    return getIPCMessageName(mMessageID);
}

string IPCMessage::GetRecord(const unsigned int& rec) const
{
    //record 0 is the 'command'
    return (rec <= mRecords.size()) ? mRecords[rec] : string("");
}

string IPCMessage::GetMessage()
{
    bool unPack;
    if(!mIsPacked)
    {
        Pack();
        unPack = true;
    }

    string msg = mData;
    if(unPack)
    {
        UnPack();
    }

    return msg;
}

string IPCMessage::GetMessageBody()
{    
    string msgBody;
    if(mIsPacked)
    {
        vector<string> recs = splitString(mData, mSeparator);
        if(recs.size() == 1)
        {
            msgBody = recs[0];
        }
        else
        {
            for(uint i = 1; i < recs.size(); i++)
            {
                msgBody += recs[i];
                if(i != recs.size() - 1)
                {
                    msgBody += mSeparator;
                }
            }
        }
    }
    else
    {
        for(uint i = 1; i < mRecords.size(); i++)
        {
            msgBody += mRecords[i];
            if(i != mRecords.size() -1)
            {
                msgBody += mSeparator;
            }
        }
    }

    return msgBody;
}

string IPCMessage::GetPackedMessage()
{
    if(!mIsPacked)
    {
        Pack();
    }
    return mData;
}

bool IPCMessage::UnPack()
{
    //Remove message delimeters..
    //A hack... messge delimeters should be handled outside message class..
    if(mData.size() && mData[0] == '[')
    {
        mData = mData.substr(1, mData.size() -2);
    }
    
    mRecords = splitString(mData,  mSeparator);

//    if(mRecords.size())
//    {
//        mMessageID = GetIPCMessageID(mRecords[0]);
//    }

    mIsPacked = false;
    return true;
}

bool IPCMessage::Pack()
{
//    mData = GetMessageName();
    mData = "";
    int startRecord = 0;

//    //Make sure first record is not already message name
//    if(mRecords.size() && mRecords[0] == mData)
//    {
//        startRecord = 1;
//    }

    for(uint i = startRecord; i < mRecords.size(); i++)
    {
        string record = mRecords[i];
        mData += record;
        if(i < mRecords.size() - 1)
        {
            mData += mSeparator;
        }
    }
    mRecords.clear();
//      mData = "[" + mData + "]";
    mIsPacked = true;
    return true;
}

 }
