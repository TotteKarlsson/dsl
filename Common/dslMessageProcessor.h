#ifndef dslMessageProcessorH
#define dslMessageProcessorH
#include "dslThread.h"
#include <string>

//----------------------------------------------------------------

namespace dsl
{

class MessageContainer;

class DSL_COMMON MessageProcessor : public Thread
{
    public:
                                                    MessageProcessor(MessageContainer& mMessageContainer, const string& threadName=gEmptyString);
                                                    ~MessageProcessor();

                                                    // overridden from Thread
        virtual void                                worker();
        void                                        run();
        void                                        stop();
        bool                                        start(bool in_thread = true);


        virtual void                                processMessages() = 0;
        void                                        pauseProcessing();
        void                                        resumeProcessing();

	protected:

        bool                                        mAllowProcessing;
        MessageContainer&                           mMessageContainer;

};

}
#endif
