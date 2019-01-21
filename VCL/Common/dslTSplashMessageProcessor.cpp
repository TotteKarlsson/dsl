#pragma hdrstop
#include "dslTSplashMessageProcessor.h"
#include "dslMessageContainer.h"
#include "dslLogger.h"
#include "Poco/Condition.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;
using namespace Poco;

SplashMessageProcessor::SplashMessageProcessor(TSplashForm* f, MessageContainer& msgContainer)
:
MessageProcessor(msgContainer, "SplashMessages"),
mParent(f)
{}

void SplashMessageProcessor::processMessages()
{}

void SplashMessageProcessor::worker()
{
    Log(lDebug3)<<"Entering SplashMessageProcessor worker function.";
	while(!mIsTimeToDie)
	{
		if(mMessageContainer.count() != 0)
		{
			string msg = mMessageContainer.peek();
			if(FOnWritingMessage && !mIsTimeToDie)
			{
				//Call main VCL thread
				TThread::Synchronize(nullptr, FOnWritingMessage);
			}
		}
		//Show a message for at least 150ms
		Sleep(150);
	}

    Log(lDebug3)<<"Splash Message Process Exiting";
}


