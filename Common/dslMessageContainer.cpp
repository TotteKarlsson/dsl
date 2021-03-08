#pragma hdrstop
#include "dslMessageContainer.h"
#include "dslStringUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

namespace dsl
{

MessageContainer::MessageContainer()
:
mNrOfProcessedMessages(0)
{}

MessageContainer::~MessageContainer()
{}

void MessageContainer::postMessage(const string& msg)
{
    //The message list are accessed by threads
    {
        Poco::ScopedLock<Poco::Mutex> lock(mListMutex);
        mMessages.push_back(msg);
    }
    mGotMessage.signal();
}

string MessageContainer::pop()
{
    string msg("");
    {
    	//Scoped lock
        Poco::ScopedLock<Poco::Mutex> lock(mListMutex);
        if(mMessages.size())
        {
            msg = mMessages.front();
            mMessages.pop_front();
        }
    }

    return msg;
}

string MessageContainer::peek()
{
    string msg("");
    {
    	//Scoped lock
        Poco::ScopedLock<Poco::Mutex> lock(mListMutex);
        if(mMessages.size())
        {
            msg = mMessages.front();
        }
    }

    return msg;
}

unsigned int MessageContainer::count()
{
    {
	    //Scoped lock
    	Poco::ScopedLock<Poco::Mutex> lock(mListMutex);
	    unsigned int sz = (unsigned int) mMessages.size();
    	return sz;
	}
}
}
