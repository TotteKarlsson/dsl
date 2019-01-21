//---------------------------------------------------------------------------
#ifndef dslProcessListH
#define dslProcessListH
//---------------------------------------------------------------------------
#include <windows.h>
#include <tlhelp32.h>
#include <string>
#include <list>
#include "dslProcessInfo.h"
#include <System.hpp>
using std::string;
using std::list;

///using UNICODE!!!
class VCL_COMMON mtkProcessList : dsl::DSLObject
{
    private:
        HANDLE                              mSnapShot;
        PROCESSENTRY32                      mCurrentProcess;
        HANDLE                              mKernelHandle;
        list<mtkProcessInfo>                mProcessList;
        list<mtkProcessInfo>::iterator      mListIter;

        typedef HANDLE                      WINAPI(SnapshotFunction)(DWORD dwFlags, DWORD th32ProcessID);
        typedef BOOL                        WINAPI(ProcessFunction)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe);

        SnapshotFunction                   *mCreateToolhelp32Snapshot;
        ProcessFunction                    *mProcess32First;
        ProcessFunction                    *mProcess32Next;
        bool                                TakeSnapShot();

        String                              GetExeFileName()       {return mCurrentProcess.szExeFile;}             // Returns the name of the EXE file
        DWORD                               Usage()             {return mCurrentProcess.cntUsage; }
        DWORD                               ProcessID()         {return mCurrentProcess.th32ProcessID; }
        DWORD                               DefaultHeapID()     {return mCurrentProcess.th32DefaultHeapID; }
        DWORD                               ModuleID()             {return mCurrentProcess.th32ModuleID; }
        DWORD                               Threads()             {return mCurrentProcess.cntThreads; }
        DWORD                               ParentProcessID()     {return mCurrentProcess.th32ParentProcessID; }
        LONG                                PriClassBase()         {return mCurrentProcess.pcPriClassBase; }
        DWORD                               Flags()             {return mCurrentProcess.dwFlags; }
        bool                                FetchNextProcess();

    public:
                                            mtkProcessList(bool updateOnCreation = false);
        virtual                            ~mtkProcessList();
        list<mtkProcessInfo>::iterator      Begin(){    return mProcessList.begin();}
        list<mtkProcessInfo>::iterator      End(){        return mProcessList.end();}
        int                                 Count(){    return mProcessList.size();}
        bool                                Update();
        bool                                ContainsProcess(const string& name);
        mtkProcessInfo*                     GetProcess(const string& name);
        mtkProcessInfo*                     GetProcess(DWORD pid);
        bool                                ShutDownProcess(const string& name);
        bool                                ShutDownProcess(DWORD PID);
        bool                                KillProcess(const string& name);
        bool                                KillProcess(DWORD PID);
};
#endif
