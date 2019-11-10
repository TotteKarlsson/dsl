#include <System.hpp>
#pragma hdrstop
#pragma package(smart_init)
#pragma argsused

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

//Link
#pragma comment(lib, "dslFoundation")
#pragma comment(lib, "dslVCLCommon")
#pragma comment(lib, "PocoFoundation")

#pragma link "rtl.bpi"
#pragma link "vcl.bpi"
#pragma link "vclx.bpi"

