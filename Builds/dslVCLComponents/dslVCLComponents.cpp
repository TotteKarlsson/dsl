#include <System.hpp>
#pragma hdrstop
USEFORM("..\..\VCL\Frames\dslTLogMemoFrame.cpp", LogMemoFrame); /* TFrame: File Type */
USEFORM("..\..\VCL\Forms\dslTRegistryForm.cpp", RegistryForm);
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma argsused

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

//Link
#pragma comment(lib, "dslFoundation")
#pragma comment(lib, "dslVCLCommon")
#pragma comment(lib, "poco_foundation")

#pragma link "rtl.bpi"
#pragma link "vcl.bpi"
#pragma link "vclx.bpi"

