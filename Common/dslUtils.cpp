#pragma hdrstop
#include "dslUtils.h"
#include "dslStringUtils.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
#include <iomanip>

#include "Poco/Thread.h"
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include <cmath>
#if defined(__BORLANDC__)
    #include <dir.h>
#elif defined (_MSC_VER)
	#include <direct.h>
	#define _getcwd getcwd
#else
	#include <unistd.h>
#endif
//---------------------------------------------------------------------------

namespace dsl
{

using namespace std;
using Poco::UUID;
using Poco::UUIDGenerator;

string getUUID()
{
	UUIDGenerator& generator = UUIDGenerator::defaultGenerator();
	UUID uuid1(generator.create()); // time based
    return uuid1.toString();
}

string getCWD()
{
    //Get the working directory
    char buffer[sizeof(char) * 512];
  	char* answer = getcwd(buffer, sizeof(buffer));

    // Get the current working directory:
    if(!answer)
    {
        Log(lError)<<"getCWD() failed";
        return "";
    }

    string cwd = buffer;
    //free(buffer);

    return cwd;
}

string rgbToString(double rgb[3])
{
    string rgbs;
    rgbs = toString(rgb[0]);
    rgbs +=", " + toString(rgb[1]);
    rgbs +=", " + toString(rgb[2]);
    return rgbs;
}

bool setupLogging(const string& logFileLocation, const string& logFileName)
{
	if(!folderExists(logFileLocation))
	{
		createFolder(logFileLocation);
	}

	string fullLogFileName(joinPath(logFileLocation, logFileName));
	clearFile(fullLogFileName);
	dsl::gLogger.logToFile(fullLogFileName);
    dsl::gLogger.setLogLevel(lDebug5);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = true;
	LogOutput::mUseLogTabs 	= true;
	Log(lInfo) << "Logger was setup";
    return true;
}

bool sameSign(double x, double y)
{
	return x*y >= 0.0f;
}

bool isEqual(double x, double y, double resolution)
{
	 return std::fabs(x - y) < resolution ? true : false;
}

void sleep(long ms)
{
    Poco::Thread::sleep(ms);
}

void pause(bool doIt, const string& msg)
{
    if(!doIt)
    {
        return;
    }
    cout<<"\n"<<msg;
    cin.ignore(0,'\n');
//    getch();
}

string getLocalTime(const string& format)
{
    Poco::LocalDateTime ts;
    Poco::DateTimeFormatter f;
    return  f.format(ts, format);
}

string getTime(const string& format, int timeZoneDiff)
{
    Poco::Timestamp ts;
    Poco::DateTimeFormatter f;
    return  f.format(ts, format, timeZoneDiff);
}

string getTimeString()
{
    time_t timer;
    struct tm *tblock;
    /* gets time of day */
    timer = time(NULL);
    /* converts date/time to a structure */
    tblock = localtime(&timer);
    string theTime = asctime(tblock);
    return theTime;
}

string getFormattedDateTimeString(const string& format)
{
    struct tm *time_now;
    time_t secs_now;
    char str[200];
    time(&secs_now);
    time_now = localtime(&secs_now);
    strftime(str, 80, format.c_str(), time_now);
    return string(str);
}

string getDateTimeString()
{
    string theTime = getTimeString();
    //TableRow tTimeTbl(theTime);
    StringList tTimeTbl(theTime);
    string timeStr = tTimeTbl[4] + " " + tTimeTbl[1] + " " + tTimeTbl[2] + " " + tTimeTbl[3];
    return timeStr;
}


//---------------------------------------------------------------------------
string zeroPadIntLeft(int nr, int width)
{
	stringstream s;
    s << std::setw(width) << std::setfill( '0' ) << std::right << nr;
    return s.str();
}

//---------------------------------------------------------------------------
string zeroPadIntRight(int nr, int width)
{
	stringstream s;
    s << std::setw(width) << std::setfill( '0' ) << std::left << nr;
    return s.str();
}


}
