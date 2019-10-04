#ifndef dslUtilsH
#define dslUtilsH
#include "dslCommonExporter.h"
#include "dslConstants.h"
#include "dslVersion.h"
#include "dslFileUtils.h"
#include <string>
//---------------------------------------------------------------------------

namespace dsl
{

DSL_COMMON std::string          getTime(bool show_milli_sec = false);
DSL_COMMON std::string          rgbToString(double rgb[3]);
DSL_COMMON bool 				setupLogging(const string& logFileLocation, const string& logFileName);
DSL_COMMON void                 sleep(long ms);
DSL_COMMON void                 pause(bool doIt = true, const string& msg = gEmptyString);
DSL_COMMON bool 				sameSign(double x, double y);
DSL_COMMON bool 				isEqual(double x, double y, double resolution);

DSL_COMMON string				getUUID();
DSL_COMMON string              	zeroPadIntLeft(int nr, int width);
DSL_COMMON string              	zeroPadIntRight(int nr, int width);
DSL_COMMON string 				getCWD();

}
#endif
