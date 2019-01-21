#ifndef dslFileWatcherH
#define dslFileWatcherH
#include "dslObject.h"
#include "dslThread.h"
#include <boost/function.hpp>
#include <string>
//---------------------------------------------------------------------------

using std::string;


//!Class that notify changes to a file
class FileWatcher : public dsl::Thread
{
	typedef boost::function<void(double)> FileWatcherCallback;
	public:
                        			FileWatcher(const string& fName);
        void                        assignCallback(FileWatcherCallback cb);
	    virtual bool                start(bool inThread = true);
        void                        run();

    protected:
        string                      mFileName;
        FileWatcherCallback         notifier;

};
#endif
