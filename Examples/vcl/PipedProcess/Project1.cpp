//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslApplicationInfo.h"
#include "dslFileUtils.h"

#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
using namespace dsl;

string gAppDataLocation(getApplicationPath());
string gLogFileName("testing.log");

//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Form1);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{

	try
	{
        string fullLogFileName(joinPath(gAppDataLocation, gLogFileName));
        clearFile(fullLogFileName);
        dsl::gLogger.logToFile(fullLogFileName);
        LogOutput::mShowLogLevel = true;
        LogOutput::mShowLogTime = false;
        LogOutput::mUseLogTabs = false;
        Log(lInfo) << "Logger was setup";

		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Auric");
		Application->CreateForm(__classid(TForm1), &Form1);
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
#pragma comment(lib, "poco_foundation")
