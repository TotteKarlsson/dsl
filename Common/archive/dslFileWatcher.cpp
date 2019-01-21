#pragma hdrstop
#include "dslFileWatcher.h"
#include "dslLogger.h"
#include "dslWin32Utils.h"
//---------------------------------------------------------------------------

using namespace dsl;
FileWatcher::FileWatcher(const string& fName)
:
mFileName(fName)
{

}

void FileWatcher::assignCallback(FileWatcherCallback cb)
{
    notifier = cb;
}

bool FileWatcher::start(bool inThread)
{
    if(inThread)
    {
    	Thread::run();
    }else
    {
        run();
    }
    return true;
}

void FileWatcher::run()
{
    mIsStarted = true;

    //Start watching the file

    const char* Dir = mFileName.c_str();
    HANDLE hDir = CreateFileA(
        Dir,
        FILE_LIST_DIRECTORY,
        FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        NULL);

    int nCounter = 0;
    FILE_NOTIFY_INFORMATION strFileNotifyInfo[1024];
    FILE_NOTIFY_INFORMATION *fni = NULL;

    while (TRUE)
    {
        //strFileNotifyInfo = NULL;

        DWORD dwBytesReturned = 0;
        //This one is blocking..
        if (ReadDirectoryChangesW(hDir,
        	(LPVOID)&strFileNotifyInfo,
            sizeof(strFileNotifyInfo),
            TRUE,
            FILE_NOTIFY_CHANGE_FILE_NAME |
            FILE_NOTIFY_CHANGE_DIR_NAME |
            FILE_NOTIFY_CHANGE_LAST_WRITE,
            &dwBytesReturned,
            NULL,
            NULL) == 0)
        {
            Log(lError) << "File watcher failed: " << getLastWin32Error();
        }
        else
        {
            char fileName[MAX_PATH] = "";
            DWORD offset = 0;
            do
            {
            	fni = (FILE_NOTIFY_INFORMATION*)(&strFileNotifyInfo[offset]);
                int ret = ::WideCharToMultiByte(CP_ACP, 0, fni->FileName, fni->FileNameLength / sizeof(WCHAR), fileName, sizeof(fileName), NULL, NULL);
                string Test = Dir;
                Test += "\\";
                Test += fileName;

                switch (fni->Action)
                {
                    case FILE_ACTION_ADDED:
                    break;

                    case FILE_ACTION_MODIFIED:
//                        if (boost::filesystem::is_directory(Test)) {
//                            cout << "Directory modified: " << Dir << "\\" << fileName << endl;
//                            }
//                        else {
//                            cout << "File modified: " << Dir << "\\" << fileName << endl;
//                            }
                        break;
                    case FILE_ACTION_REMOVED:
//                        if (boost::filesystem::is_directory(Test)) {
//                            cout << "Directory removed: " << Dir << "\\" << fileName << endl;
//                            }
//                        else {
//                            cout << "File removed: " << Dir << "\\" << fileName << endl;
//                            }
                        break;
                    case FILE_ACTION_RENAMED_NEW_NAME:
//                        if (boost::filesystem::is_directory(Test)) {
//                            cout << "Directory renamend (NEW): " << Dir << "\\" << fileName << endl;
//                            }
//                        else {
//                            cout << "File renamed (NEW): " << Dir << "\\" << fileName << endl;
//                            }
                        break;
                    case FILE_ACTION_RENAMED_OLD_NAME:
//                        if (boost::filesystem::is_directory(Test)) {
//                            cout << "Directory renamed (OLD): " << Dir << "\\" << fileName << endl;
//                            }
//                        else {
//                            cout << "File renamed (OLD): " << Dir << "\\" << fileName << endl;
//                            }
                        break;
                    default:
//                        if (boost::filesystem::is_directory(Test)) {
//                            cout << "Directory UNDISCOVERED ACTION: " << Dir << "\\" << fileName << endl;
//                            }
//                        else {
//                            cout << "File UNDISCOVERED ACTION: " << Dir << "\\" << fileName << endl;
//                            }
                        break;
                    }
            }

        }
	}





    mIsFinished = true;
}
