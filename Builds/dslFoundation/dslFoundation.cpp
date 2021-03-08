#pragma hdrstop
#pragma argsused

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

#if defined(__BORLANDC__)
    #pragma comment(lib, "sqlite.lib")
    #pragma comment(lib, "PocoFoundation.lib")
    #pragma comment(lib, "tinyxml2.lib")
    #pragma comment(lib, "shell32.lib")
#endif
