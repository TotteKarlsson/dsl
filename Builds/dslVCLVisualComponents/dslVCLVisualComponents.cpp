//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
USEFORM("..\..\VCL\Forms\dslTAboutForm.cpp", AboutForm);
USEFORM("..\..\VCL\Forms\dslTRegistryForm.cpp", RegistryForm);
USEFORM("..\..\VCL\Frames\dslTAboutFrame.cpp", AboutFrame); /* TFrame: File Type */
USEFORM("..\..\VCL\Frames\dslTLogMemoFrame.cpp", LogMemoFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------


#pragma argsused
extern "C" int _libmain(unsigned long reason)
{
	return 1;
}
//---------------------------------------------------------------------------

#pragma comment(lib, "dslFoundation.lib")
#pragma comment(lib, "dslVCLCommon.lib")
#pragma comment(lib, "dslVCLComponents.bpi")
#pragma comment(lib, "poco_foundation.lib")

#pragma link "vcl.bpi"
