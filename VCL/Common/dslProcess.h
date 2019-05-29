#ifndef dslProcessH
#define dslProcessH
#include <vector>
#include <string>
#include <SysUtils.hpp>
#include "dslObject.h"
#include "dslVCLCommonExporter.h"
#include "dslThread.h"
#include "dslStringList.h"
#include <boost/function.hpp>

namespace dsl
{
using std::vector;
using std::string;

class Process;

enum ProcessState {psRunning, psPaused, psTerminated, psFinished, psUndefined};
enum MessageHandling {mhIgnoreMessages = 0, mhCatchMessages, mhShowMessages};

typedef boost::function<void(void* opaque1, void* opaque2)> Callback;
//!This class should be written to use Poco process instead of win32 functions..
class VCLCOMMON Process : public dsl::Thread
{


    public:
                                            Process(const string& exeFName = gEmptyString, const string& wd = gEmptyString);
                                            ~Process();
        void                                assignCallbacks(Callback enter, Callback progress, Callback onExit);
        void                                assignOpaqueData(void* one, void* two);

        bool                                setup(const string& cmd = gEmptyString, MessageHandling mh = mhIgnoreMessages);
        bool                                setExecutable(const string& nameAndPath);
        bool                                setWorkingDirectory(const string& nameAndPath);

		bool 								start(bool inThread = true);
        virtual void	                    run();

        virtual bool                        pause();
        virtual bool                        terminate();
        string                              getProcessStateAsString();
        ProcessState                        getProcessState();
        STARTUPINFOA*                       getStartUpInfo(){return &mSI;}
        PROCESS_INFORMATION*                getProcessInfo(){return &mPI;}
        MessageHandling                     getMessageHandling(){mMessageHandling;}


    protected:
	    Callback 			                onEnter;
	    Callback 			                onProgress;
	    Callback 			                onExit;
        void*                               mOpaqueData1;
        void*                               mOpaqueData2;

        string                              mExeFile;
        string                              mWorkingDirectory;
   		MessageHandling         			mMessageHandling;

        string                              mCommandLine;
        HANDLE                              mReadPipeHandle;
        HANDLE                              mWritePipeHandle;

        STARTUPINFOA                        mSI;
        PROCESS_INFORMATION                 mPI;
        ProcessState                        mProcessState;

        bool                                setupPipe();

        void                                setup(const string& exeFName, ProcessState pState = psUndefined);
        virtual bool                        readFromPipe();
};

}
#endif
