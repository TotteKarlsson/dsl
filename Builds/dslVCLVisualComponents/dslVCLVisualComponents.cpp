#include <System.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------

USEFORM("..\..\VCL\Forms\dslTAboutForm.cpp", AboutForm);
USEFORM("..\..\VCL\Forms\dslTRegistryForm.cpp", RegistryForm);
USEFORM("..\..\VCL\Frames\dslTAboutFrame.cpp", AboutFrame); /* TFrame: File Type */
USEFORM("..\..\VCL\Frames\dslTLogMemoFrame.cpp", LogMemoFrame); /* TFrame: File Type */
USEFORM("..\..\VCL\Frames\dslTServerSocketFrame.cpp", ServerSocketFrame); /* TFrame: File Type */
USEFORM("..\..\VCL\Frames\dslTClientSocketFrame.cpp", ClientSocketFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
#pragma package(smart_init)


//   Package source.
//---------------------------------------------------------------------------
#pragma argsused
extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

//---------------------------------------------------------------------------
#pragma comment(lib, "dslFoundation")
#pragma comment(lib, "PocoFoundation")

#pragma comment(lib, "dslVCLCommon")
#pragma comment(lib, "dslVCLComponents")

#pragma link "vcl.bpi"
