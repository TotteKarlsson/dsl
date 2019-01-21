#ifndef dslLogMessageClientSenderH
#define dslLogMessageClientSenderH

#include <string>
#include "dslThread.h"
namespace dsl
{

class mtkLogClient;

//----------------------------------------------------------------
class mtkLogMessageClientSender : public mtkThread
{
    private:
        string serverName;
        mtkLogClient* parent;           //This is a pointer to a parent.

    public:
        mtkLogMessageClientSender(mtkLogClient* parent);
        ~mtkLogMessageClientSender();

        // overridden from Thread
        void Worker();
        void ShutDown();
};

#endif 

