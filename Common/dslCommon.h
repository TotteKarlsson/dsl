#ifndef dslCommonH
#define dslCommonH
#include "dslVersion.h"

namespace dsl
{
extern DSL_COMMON dsl::Version gAPIVersion;

DSL_COMMON Version 				getVersion();
DSL_COMMON const char*          getCopyright();
DSL_COMMON string               getCompilerVersion();

}

#endif
