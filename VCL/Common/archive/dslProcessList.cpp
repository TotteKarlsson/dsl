
#pragma hdrstop
#include <windows.h>
#include <algorithm>
#include <string>
#include "dslStringUtils.h"
#include "dslVCLUtils.h"
#include "dslProcessList.h"
#pragma package(smart_init)

using namespace dsl;
//---------------------------------------------------------------------------
dslProcessList::dslProcessList(bool updateOnCreation)
{

#define ModuleCast (HINSTANCE__*)

    // Dynamically link to the functions.
    mKernelHandle = LoadLibraryW(L"KERNEL32");
    if((int) mKernelHandle < 32 &&(int) mKernelHandle >= 0)
        return;

     //Get function in the Library
    mCreateToolhelp32Snapshot =
       (SnapshotFunction *) GetProcAddress(ModuleCast mKernelHandle, "CreateToolhelp32Snapshot");

    mProcess32First  =(ProcessFunction *) GetProcAddress(ModuleCast mKernelHandle, "Process32FirstW");
    mProcess32Next   =(ProcessFunction *) GetProcAddress(ModuleCast mKernelHandle, "Process32NextW");

    if(mCreateToolhelp32Snapshot == nullptr
         || mProcess32First == nullptr
         || mProcess32Next == nullptr)
    {
        return;
    }

    if(updateOnCreation)
    {
        Update();    //Calls TakeSnapShot and updates the process list
    }
}

dslProcessList::~dslProcessList()
{
    FreeLibrary(ModuleCast mKernelHandle);
      CloseHandle(mSnapShot);
}

bool dslProcessList::Update()
{
    if(!TakeSnapShot())
    {
        return false;
    }

    //Populate the list with processes
    mProcessList.clear();
    do
    {
        dslProcessInfo aProcess;
        aProcess.SetProcessID(ProcessID());
        aProcess.SetParentProcessID(ParentProcessID());

        String exeName = GetExeFileName();
        aProcess.SetProgramName(stdstr(exeName));

        mProcessList.push_back(aProcess);
    } while(FetchNextProcess());

    return true;
}

bool dslProcessList::FetchNextProcess()
{
    return !mProcess32Next(mSnapShot, &mCurrentProcess) ? false : true;
}

bool dslProcessList::TakeSnapShot()
{
    mSnapShot = mCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if(mSnapShot == 0)
    {
        return false;
    }

    mCurrentProcess.dwSize = sizeof(mCurrentProcess);
    return (!mProcess32First(mSnapShot, &mCurrentProcess)) ? false : true;
}

dslProcessInfo* dslProcessList::GetProcess(const string& name)
{
    for(list<dslProcessInfo>::iterator it = Begin(); it != End(); ++it)
    {
        dslProcessInfo aProcess = *(it);
        string inStr         = toLowerCase(name);
        string nameInList     = toLowerCase(aProcess.GetProgramName());

        if(inStr == nameInList)
        {
            return &(*it);
        }
    }

    return nullptr;
}

dslProcessInfo* dslProcessList::GetProcess(DWORD pid)
{
    for(list<dslProcessInfo>::iterator it = Begin(); it != End(); ++it)
    {
        dslProcessInfo& aProcess = (*it);
        if(aProcess.GetProcessID() == pid)
        {
            return &(*it);
        }
    }

    return nullptr;
}

bool dslProcessList::ContainsProcess(const string& name)
{
    for(list<dslProcessInfo>::iterator it = Begin(); it != End(); ++it)
    {
        dslProcessInfo aProcess = *(it);
        string inStr         = toLowerCase(name);
        string nameInList     = toLowerCase(aProcess.GetProgramName());

        if(inStr == nameInList)
        {
            return true;
        }
    }

    return false;
}

bool dslProcessList::KillProcess(const string& name)
{
    dslProcessInfo* proc = GetProcess(name);
    return (proc) ? proc->Terminate() : false;
}

bool dslProcessList::KillProcess(DWORD PID)
{
    dslProcessInfo* proc = GetProcess(PID);
    return (proc) ? proc->Terminate() : false;
}

bool dslProcessList::ShutDownProcess(const string& name)
{
    dslProcessInfo* proc = GetProcess(name);
    return (proc) ? proc->ShutDown() : false;
}

bool dslProcessList::ShutDownProcess(DWORD PID)
{
    dslProcessInfo* proc = GetProcess(PID);
    return (proc) ? proc->ShutDown() : false;
}

//string StrToLower(const string& inStr)
//{
//    string tmpStr = inStr;
//    std::transform(tmpStr.begin(), tmpStr.end(), tmpStr.begin(), tolower);
//    return tmpStr;
//}
