#ifndef dslMessageContainerH
#define dslMessageContainerH
#include "dslObject.h"
#include "Poco/Condition.h"
#include "Poco/Mutex.h"
#include <deque>
//---------------------------------------------------------------------------

namespace dsl
{

using std::deque;
class MessageProcessor;

//!A threadsafe container
class DSL_COMMON MessageContainer : public DSLObject
{
	//Friends can access our mutexes
	friend                                  MessageProcessor;

    public:
                                                MessageContainer();
		virtual                                 ~MessageContainer();
		virtual unsigned int                    count();

                                                //Post a message to the message list
		virtual void                            postMessage(const string& msg);
		string                                  pop();
		string                                  peek();

        Poco::Mutex                             mListMutex;
        Poco::Condition                    		mGotMessage;

	protected:
		unsigned int                            mNrOfProcessedMessages;
		deque<string>                           mMessages;
};

}
#endif
