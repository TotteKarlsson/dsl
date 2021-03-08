#pragma hdrstop
#include "dslIPCMessageBuilder.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------


namespace dsl
{

IPCMessageBuilder::IPCMessageBuilder(const char& lDel, const char& rDel)
 :
mLeftDelimiter(lDel),
mRightDelimiter(rDel),
mIsBuilding(false),
mMessage(""),
mHasMessage(false),
mNrOfLeftDel(0),
mNrOfRightDel(0)
{}

bool IPCMessageBuilder::isBuilding()
{
	return mIsBuilding;
}

bool IPCMessageBuilder::isComplete()
{
	return mHasMessage;
}

size_t IPCMessageBuilder::getMessageSize()
{
	return mMessage.size();
}

void IPCMessageBuilder::reset()
{
    mIsBuilding = false;
    mHasMessage = false;
    mNrOfLeftDel = 0;
    mNrOfRightDel = 0;
    mMessage.clear();
}

void IPCMessageBuilder::setDelimiters(const char& lDel, const char& rDel)
{
    mLeftDelimiter = (lDel);
    mRightDelimiter = (rDel);
}

bool IPCMessageBuilder::build(const char& ch)
{
    //If we are looking for end of lines, we are "always" building
    if(mRightDelimiter == '\n')
    {
        if(ch == '\n')
        {
            mHasMessage = true;
            mIsBuilding = false;
            return true;
        }

        mIsBuilding = true;
        mMessage += ch;
        return true;
    }

    //Start building only when a left delimiter is received
    if(!mIsBuilding && ch != mLeftDelimiter)
    {
        return false;
    }

    //Initiate building
    if(!mIsBuilding && ch == mLeftDelimiter)
    {
        reset();
        mIsBuilding = true;
    }

    if(ch == mLeftDelimiter)
    {
        mNrOfLeftDel++;
    }

    if(ch == mRightDelimiter)
    {
        mNrOfRightDel++;
    }

    if(ch == mRightDelimiter && mNrOfLeftDel == 0)
    {
    	//This is an error...
        Log(lError) << "Message builder read inconsistent data: Right delimiter occured before left delimiter.";
        Log(lError) << "Current buffer is: "<<mMessage;
		Log(lError) << "Resetting message builder";
        reset();
        return false;
    }

    if(mNrOfLeftDel > 1)
    {
    	//This is an error...
        Log(lError) << "Message builder read inconsistent data: Two left delimiters present";
        Log(lError) << "Current buffer is: "<<mMessage;
		Log(lError) << "Resetting message builder";
        reset();
        return false;
    }

    if(mNrOfLeftDel == mNrOfRightDel && mNrOfLeftDel > 0)
    {
        mHasMessage = true;
        mIsBuilding = false;
        return true;
    }

    //Insert the character, discard irrelevant ones
    if(!(ch == '\r' || ch == '\n' || ch == mLeftDelimiter || ch == mRightDelimiter))
    {
    	mMessage += ch;
    }
    return true;
}

string IPCMessageBuilder::getMessage()
{
    return mMessage;
}

}
