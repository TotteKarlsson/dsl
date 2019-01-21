#pragma hdrstop
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslWin32Utils.h"
#include "dslFileUtils.h"
#include <string>
//---------------------------------------------------------------------------

USEFORM("..\..\..\VCL\Frames\dslTPluginInfoFrame.cpp", PluginInfoFrame); /* TFrame: File Type */
USEFORM("..\..\..\VCL\Frames\dslTLogMemoFrame.cpp", LogMemoFrame); /* TFrame: File Type */
USEFORM("TMainForm.cpp", MainForm);
//---------------------------------------------------------------------------
using namespace dsl;
using namespace std;

void setupLogging();
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		setupLogging();
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Carbon");
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}

//---------------------------------------------------------------------------
#pragma comment(lib, "dslFoundation")
#pragma comment(lib, "dslVCLCommon")
#pragma comment(lib, "dslPythonPlugins")
#pragma comment(lib, "poco_foundation")
#pragma comment(lib, "Python37_CG")
#pragma comment(lib, "dslVCLComponents.bpi")
#pragma comment(lib, "dslVCLVisualComponents.bpi")


void setupLogging()
{
	//Get Application folder
	string fldr =  joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), "PluginManager");

	if(!folderExists(fldr))
	{
		createFolder(fldr);
	}

	string fullLogFileName(joinPath(fldr, "Log.txt"));
	clearFile(fullLogFileName);
	dsl::gLogger.logToFile(fullLogFileName);
	dsl::gLogger.setLogLevel(lDebug5);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = false;
	LogOutput::mUseLogTabs 	= false;
	Log(lInfo) << "Logger was setup";
}
