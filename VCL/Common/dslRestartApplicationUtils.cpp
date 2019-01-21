#pragma hdrstop
#include <string>
#include "dslRestartApplicationUtils.h"
#include "dslVCLUtils.h"
#include "dslStringUtils.h"
#pragma package(smart_init)

using namespace std;
using namespace dsl;
namespace dsl
{

// Global Variables
bool  			gWasApplicationRestarted  = false;		// Restarted Flag

bool checkForCommandLineFlag(const string& flag)
{
	// Simple find substring in command line
	string cmdLine(stdstr(GetCommandLineA()));
	return contains(flag, cmdLine);
}

bool WaitForPreviousProcessToFinish(const string& mutexName, HANDLE applicationRestartMutex)
{
	// Try to Create Mutex
	applicationRestartMutex = ::CreateMutexA( nullptr, FALSE, mutexName.c_str());
	DWORD dwLastError = GetLastError();
	bool AlreadyRunning = (dwLastError == ERROR_ALREADY_EXISTS || dwLastError == ERROR_ACCESS_DENIED);

	if(AlreadyRunning)
	{
		// Waiting for previous instance release mutex
		WaitForSingleObject(applicationRestartMutex, INFINITE);
		ReleaseMutex(applicationRestartMutex);
		gWasApplicationRestarted = TRUE;
	}

	::CloseHandle(applicationRestartMutex);
	applicationRestartMutex = nullptr;
	return TRUE;
}

bool RestartProcessFinished(HANDLE applicationRestartMutex)
{
	// Releasing mutex signal that process finished
	DWORD dwWaitResult = WaitForSingleObject(applicationRestartMutex, 0);
	if (dwWaitResult == WAIT_TIMEOUT)
    {
		ReleaseMutex(applicationRestartMutex);
    }

	CloseHandle(applicationRestartMutex);
	applicationRestartMutex = nullptr;
	return (dwWaitResult == WAIT_TIMEOUT);
}

bool ActivateApplicationStyleChange(const string& mutexName, HANDLE applicationRestartMutex, const string& newStyleName)
{
	string cmdLineParameter("--Theme=" + newStyleName);
    return ActivateRestartProcess(mutexName, applicationRestartMutex, cmdLineParameter);
}

bool ActivateRestartProcess(const string& mutexName, HANDLE applicationRestartMutex, const string& cmdLineParameter)
{
	// Restart App
	applicationRestartMutex = ::CreateMutexA( nullptr, TRUE, mutexName.c_str());
	DWORD dwLastError = ::GetLastError();
	bool AlreadyRunning = (dwLastError == ERROR_ALREADY_EXISTS || dwLastError == ERROR_ACCESS_DENIED);

	if(AlreadyRunning)
	{
		WaitForSingleObject(applicationRestartMutex, INFINITE);
		ReleaseMutex(applicationRestartMutex);
		CloseHandle(applicationRestartMutex);
		return FALSE;
	}

	char appPath[MAX_PATH] = {0};
	GetModuleFileNameA(nullptr, appPath, MAX_PATH);

	// Create New Instance command line
	strcat(appPath, (" "));
	strcat(appPath, ("--Restart=true")); // Add command line key for restart

    if(cmdLineParameter.size())
    {
    	lstrcatA(appPath, stdstr(cmdLineParameter).c_str()); // Add command line key for restart
    }

	STARTUPINFOA			si = {0};
	PROCESS_INFORMATION		pi = {0};
	si.cb = sizeof(STARTUPINFO);

	// Create another copy of process
	return CreateProcessA(nullptr, appPath, nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi);
}

}
