#pragma hdrstop
#include <vector>
#include "dslLoggerUtils.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
//---------------------------------------------------------------------------

using Poco::DateTime;
using Poco::DateTimeFormatter;

namespace dsl
{

string getLogTime(bool show_milli_sec)
{
	Poco::LocalDateTime dt;
	std::string s(DateTimeFormatter::format(dt, "%H:%M:%S %i"));
    return s;
}

}
