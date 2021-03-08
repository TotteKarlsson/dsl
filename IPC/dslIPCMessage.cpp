#pragma hdrstop
#include "dslIPCMessage.h"
#include "dslIPCMessageEnums.h"
#include "dslStringUtils.h"

namespace dsl
{

IPCMessage::IPCMessage(int msgID, const string& msgData, int from_socket)
:
IPCData(msgData),
mSocketID(from_socket),
mIsProcessed(false)
{
    if(mRecords.size())
    {
        mMessageID = (msgID == -1) ? dsl::getMessageID(mRecords[0]) : msgID;
    }
}

IPCMessage::IPCMessage(const IPCMessage& rhs)
:
IPCData(rhs)
{
    mSocketID    = rhs.mSocketID;
    mMessageID   = rhs.mMessageID;
    mIsProcessed = rhs.mIsProcessed;
}

void IPCMessage::setMessageID(int id)
{
    mMessageID = id;
}

IPCMessage::operator const string() const
{
	return mData;
}

ostream& operator<<(ostream& stream, IPCMessage& rhs)
{
    stream << rhs.getMessage();
    return stream;
}

string operator+(const string& lhs, IPCMessage& rhs)
{
    string temp = lhs + rhs.getMessage();
    return temp;
}

IPCMessage& IPCMessage::operator+(const string& rhs)
{
	mData = mData + rhs;
    return *this;
}

IPCMessage& IPCMessage::operator=(const string& rhs)
{
	mData = rhs;
    return *this;
}

int IPCMessage::getCommand()
{
	return mMessageID;
}

int IPCMessage::getID() const
{
	return mMessageID;
}

int IPCMessage::getMessageID() const
{
	return mMessageID;
}

int IPCMessage::getSocketID() const
{
	return mSocketID;
}

void IPCMessage::setSocketID(int id)
{
	mSocketID = id;
}

int IPCMessage::getOrigin() const
{
	return mSocketID;
}

char IPCMessage::getSeparator() const
{
	return mSeparator;
}

bool IPCMessage::isProcessed() const
{
	return mIsProcessed;
}

void IPCMessage::isProcessed(bool isIt)
{
	mIsProcessed = isIt;
}

void IPCMessage::insertRecord(const string& record)
{
	mRecords.push_back(record);
}

void IPCMessage::empty()
{
    mMessageID = -1;
    mRecords.clear();
    mData.clear();
}

string IPCMessage::getMessageName() const
{
    return getRecord(0);
}

string IPCMessage::getRecord(int rec) const
{
    //record 0 is the 'command'
    return (rec <= mRecords.size()) ? trim(mRecords[rec]) : string("");
}

string IPCMessage::getMessage()
{
    bool unPacked;
    if(!mIsPacked)
    {
        pack();
        unPacked = true;
    }

    string msg = mData;
    if(unPacked)
    {
        unPack();
    }

    return msg;
}

string IPCMessage::getMessageBody()
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
            for(dsluint i = 1; i < recs.size(); i++)
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
        for(dsluint i = 1; i < mRecords.size(); i++)
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

string IPCMessage::getPackedMessage()
{
    if(!mIsPacked)
    {
        pack();
    }
    return mData;
}

bool IPCMessage::unPack()
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

bool IPCMessage::pack()
{
//    mData = GetMessageName();
    mData = "";
    int startRecord = 0;

//    //Make sure first record is not already message name
//    if(mRecords.size() && mRecords[0] == mData)
//    {
//        startRecord = 1;
//    }

    for(dsluint i = startRecord; i < mRecords.size(); i++)
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
