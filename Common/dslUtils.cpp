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
#include <unistd.h>
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
    char buffer[sizeof(char) * max_path_len];
    char* answer = getcwd(buffer, sizeof(buffer));
    // Get the current working directory:
    if(!answer)
    {
        Log(Logger::LOG_ERROR)<<"getCWD() failed";
        return "";
    }

    string cwd = buffer;
    free(buffer);

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

//char* createText(const string& str)
//{
//    if(str.size() == 0)
//    {
//        return nullptr;
//    }
//    char* text = new char[str.size() + 1];
//    std::copy(str.begin(), str.end(), text);
//    text[str.size()] = '\0'; //terminating 0!
//    return text;
//}
//
//char* createText(const char* str)
//{
//    string aString(str);
//    return createText(aString);
//}
//
//char* createText(const StringList& strList)
//{
//    if(strList.count() == 0)
//    {
//        return nullptr;
//    }
//    string list = strList.asString();
//    char* text = new char[list.size() + 1];
//    std::copy(list.begin(), list.end(), text);
//    text[list.size()] = '\0'; //terminating 0!
//    return text;
//}

#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    string getTime(bool show_milli_sec)
    {
        const int MAX_LEN = 200;
        char buffer[MAX_LEN];
        if (GetTimeFormatA(LOCALE_USER_DEFAULT, 0, 0, "HH':'mm':'ss", buffer, MAX_LEN) == 0)
        {
            return "Error in dsl::GetTime()";
        }
        char result[100] = {0};
        if(show_milli_sec)
        {
            static DWORD first = GetTickCount();
            std::sprintf(result, "%s.%03ld", buffer, (long)(GetTickCount() - first) % 1000);
            return string(result);
            }
        else
        {
            return string(buffer);
        }
    }
#else
#include <sys/time.h>
    string getTime(bool show_milli_sec)
    {
        char buffer[11];
        time_t t;
        time(&t);
        tm r = {0};
        strftime(buffer, sizeof(buffer), "%X", localtime_r(&t, &r));
        struct timeval tv;
        gettimeofday(&tv, 0);
        char result[100] = {0};
        std::sprintf(result, "%s.%03ld", buffer, (long)tv.tv_usec / 1000);
        return result;
    }
#endif

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
