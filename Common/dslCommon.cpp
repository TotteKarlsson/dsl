#pragma hdrstop
#pragma argsused
#include "dslCommon.h"
#include <string>

namespace dsl
{

using namespace std;

Version gAPIVersion = Version("0.5.0.0");

Version getVersion()
{
    return gAPIVersion;
}

const char* getCopyright()
{
    return "(c) 1999-2018 M. T. Karlsson - Dune Scientific, LLC";
}

string getCompilerVersion()
{
std::string compiler =
#ifdef __clang__
   "clang++";
#else
   "Compiler not defined";
#endif
    return compiler;
}

}
namespace boost
{
void tss_cleanup_implemented(void) {};
}

extern "C" int _libmain(unsigned long reason)
{
	return 1;
}

