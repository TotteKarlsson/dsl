#pragma hdrstop
#pragma argsused

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

#pragma comment(lib, "sqlite.lib")
#pragma comment(lib, "poco_foundation.lib")
#pragma comment(lib, "tinyxml2.lib")


