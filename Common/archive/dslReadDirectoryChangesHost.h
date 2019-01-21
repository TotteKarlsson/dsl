#ifndef dslReadDirectoryChangesHostH
#define dslReadDirectoryChangesHostH
#include <windows.h>
#include <vector>
#include "dslObject.h"
//---------------------------------------------------------------------------
using std::vector;
class DirectoryNotifier;
class ReadDirectoryChangesWorker;

// This class is responsible for thread startup, orderly thread shutdown, and shimming
// the various C++ member functions with C-style Win32 functions.
class DSL_COMMON ReadDirectoryChangesHost : public dsl::DSLObject
{
    public:
        								        ReadDirectoryChangesHost(DirectoryNotifier* pParent);
        static unsigned int WINAPI 		        threadStartProc(void* arg);

        								        // Called by QueueUserAPC to start orderly shutdown.
        static void CALLBACK 			        terminateProc(ULONG_PTR arg);

        								        // Called by QueueUserAPC to add another directory.
        static void CALLBACK 			        addDirectoryProc(ULONG_PTR arg);

        DirectoryNotifier* 				        mTheNotifier;
        long 							        mOutstandingRequests;

    protected:

        void                                    run();
        void                                    addDirectory( ReadDirectoryChangesWorker* pBlock );
        void                                    requestTermination();

        vector<ReadDirectoryChangesWorker*> 	mBlocks;
        bool 									mTerminate;
};

#endif
