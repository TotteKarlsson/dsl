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

DSL_COMMON std::string          getTime(const string& format = "%b-%m-%y-%H%M%S", int timeZoneDiff = 0);
DSL_COMMON std::string          getLocalTime(const string& format = "%b-%m-%y-%H%M%S");
DSL_COMMON string           	getTimeString();    //Return a string containing the date time in format "Wed Mar 31 15:02:11 2004\n"
DSL_COMMON string           	getDateTimeString();    //Return a string containing the date time in format "2004 Mar 31 15:02:11"


//See: http://www.cplusplus.com/reference/ctime/strftime/
DSL_COMMON string           	getFormattedDateTimeString(const string& format);    //Return a string containing the date time in format "2004 Mar 31 15:02:11"

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
