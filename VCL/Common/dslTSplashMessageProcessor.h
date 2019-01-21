#ifndef dslTSplashMessageProcessorH
#define dslTSplashMessageProcessorH
#include <Classes.hpp>
#include "dslVCLCommonExporter.h"
#include "dslMessageProcessor.h"

//---------------------------------------------------------------------------

//This class need a TSplashForm in order to work
//Setup the callback function TOnWritingMessage on creation

typedef void __fastcall (__closure *TOnWritingMessage)();
class TSplashForm;

namespace dsl
{
	class MessageContainer;
}

using dsl::MessageContainer;

class VCLCOMMON SplashMessageProcessor : public dsl::MessageProcessor
{
    public:
                                                    SplashMessageProcessor(TSplashForm* f, MessageContainer& messageContainer);
        void                                        worker();
        virtual void                                processMessages();
        TOnWritingMessage                           FOnWritingMessage;


    private:
        TSplashForm*                                mParent;
};

#endif
