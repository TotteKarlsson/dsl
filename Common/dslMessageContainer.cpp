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
        mGotMessage.signal();
    }
}

string MessageContainer::pop()
{
    string msg("");
    {    //Scoped lock
        Poco::ScopedLock<Poco::Mutex> lock(mListMutex);
        if(mMessages.size())
        {
            msg = mMessages.front();
            mMessages.pop_front();
        }
        mListMutex.unlock();
    }

    return msg;
}

string MessageContainer::peek()
{
    string msg("");

    {    //Scoped lock
        Poco::ScopedLock<Poco::Mutex> lock(mListMutex);
        mListMutex.lock();
        if(mMessages.size())
        {
            msg = mMessages.front();
        }
        mListMutex.unlock();
    }

    return msg;
}

int MessageContainer::count()
{
    mListMutex.lock();
    int sz = mMessages.size();
    mListMutex.unlock();
    return sz;
}
}
