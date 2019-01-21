#ifndef dslGetOptionsH
#define dslGetOptionsH
#include "dslCommonExporter.h"
//---------------------------------------------------------------------------

namespace dsl
{
DSL_COMMON extern int   optind;
DSL_COMMON extern int   opterr;
DSL_COMMON extern char  *optarg;
DSL_COMMON int          getOptions(int argc, char *argv[], char *optstring);
}
#endif
