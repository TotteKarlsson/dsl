#ifndef dslMessageContainerH
#define dslMessageContainerH
#include <deque>

//We are not really using boost threads, only conditions and mutexes
//See http://stackoverflow.com/questions/16443989/warnings-when-compiling-boost-libraries-in-c-builder
//for explanation of the #define
#define BOOST_THREAD_USE_LIB

#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include "dslLogMessageProcessor.h"
//---------------------------------------------------------------------------

namespace dsl
{

class mtkIPCReceiver;
using std::deque;

class MTK_COMMON MessageContainer : public DSLObject
{
    public:
                                            MessageContainer();
		virtual                             ~MessageContainer(){}
		virtual int                         getNrOfMessages(){return mMessages.size();}
		virtual void                        PostLogMessage(const string& msg);            //Post a message to the message list
		bool                                HasMessage(){return mMessages.size() ? true : false;}
		string                              PopMessage();

	protected:
		unsigned int                        mNrOfProcessedMessages;
		deque<string>                       mMessages;

		boost::mutex                        mListMutex;
		boost::condition                    mListDataArrived;

		//Friends can access our mutexes
		friend                     		    LogMessageProcessor;
};

}
#endif
