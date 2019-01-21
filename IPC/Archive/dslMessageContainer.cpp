#pragma hdrstop
#include "dslStringUtils.h"
#include "dslMessageContainer.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

#undef GetMessage;

using boost::mutex;
typedef mutex::scoped_lock ScopedLock;

namespace dsl
{
MessageContainer::MessageContainer()
: mNrOfProcessedMessages(0)
{}


void MessageContainer::PostLogMessage(const string& msg)
{
    //The message list are accessed by child threads
    mutex::scoped_lock lock(mListMutex);
        mMessages.push_back(msg);
    lock.unlock();

    if(mMessages.size())
    {
        mListDataArrived.notify_one();
    }
}

string MessageContainer::PopMessage()
{
    string msg = "";
    ScopedLock lock(mListMutex);
    if(mMessages.size())
    {
        msg = mMessages.front();
        mMessages.pop_front();
    }
    return msg;
}

}
