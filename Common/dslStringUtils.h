#ifndef dslStringUtilsH
#define dslStringUtilsH
#include "dslCommonExporter.h"
#include "dslConstants.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include <list>
#include <vector>
#include <string>
//---------------------------------------------------------------------------
namespace dsl
{

using Poco::DateTime;
using std::string;
using std::list;
using std::vector;
using std::wstring;
using std::ostream;

class StringList;

template<typename T>
class Range;

enum STR2INT_ERROR { stiSUCCESS, stiOVERFLOW, stiUNDERFLOW, stiINCONVERTIBLE };
DSL_COMMON STR2INT_ERROR 	str2int (int &i, char const *s, int base = 0);

DSL_COMMON string			toHex(int byte);
DSL_COMMON int 				hexToDec(const string& hex);
DSL_COMMON string 			hexCharToBinString(char c);
DSL_COMMON string 			hexStringToBinString(const std::string& hex);

DSL_COMMON DateTime			strToDateTime(const string& dateTime);
DSL_COMMON string 			zeroPadString(unsigned int z, const string& str);
DSL_COMMON string 			createZeroPaddedString(unsigned int z, unsigned int digits);

DSL_COMMON string           stdstr(const char* str );
DSL_COMMON string           stdstr(vector<char>& str );
DSL_COMMON string           stdstr(const string& str );
DSL_COMMON string 			stdstr( const std::wstring& str );
DSL_COMMON wstring 			wstdstr(const string& str);

DSL_COMMON StringList       getLinesInFile(const string& fName);
DSL_COMMON string           getFileContent(const string& fName);

DSL_COMMON string           getParentFolder(const string& folder);
DSL_COMMON string           getStringFromSeconds(long seconds);
DSL_COMMON int              indexOf(const std::vector<std::string>& vec, const std::string& elem);

DSL_COMMON bool             startsWith( const string& prefix, const string& src);
DSL_COMMON bool             endsWith(const string& postFix, const string& src);
DSL_COMMON DATA_FORMAT      intToDataFormat(int type);

DSL_COMMON void             stripToNonWhiteSpace(string& sline, string& result);
DSL_COMMON string           stripToAlpha(const string& sline);
DSL_COMMON string           stripToAlphaR(const string& sline);
DSL_COMMON string           stripToDigit(const string& sline);
DSL_COMMON string           stripToDigitR(const string& sline);
DSL_COMMON string           stripToAlphaNumR(const string& sline);

DSL_COMMON string           stripNewLine(const string& str);
DSL_COMMON string           stripCharacter(const char& ch, const string& source);
DSL_COMMON string           stripCharacters(const string& chars, const string& source);

DSL_COMMON string           trimChars(const string& str, const string& chars = gEmptyString);
DSL_COMMON string           trim(const string& str, const char& aChar = ' ');
DSL_COMMON string           trimBack(const string& str, const char& aChar = ' ', int max_trim = 1);
DSL_COMMON string           trimFront(const string& str, const char& aChar = ' ', int max_trim = 1);

DSL_COMMON string           trimWS(const string& str);
DSL_COMMON string           trimWSBack(const string& str);
DSL_COMMON string           trimWSFront(const string& str);

//"eat" functions return a string where component is gone....
DSL_COMMON string           eatWhiteSpace(const string& sline);
DSL_COMMON string           eatWhiteSpaceR(const string& sline);

DSL_COMMON double           eatNumber(string& sline);
DSL_COMMON void             eatNumber(string& sline, double& result);
DSL_COMMON string           readFirstWord(const string& sline);
DSL_COMMON string           eatWord(string& sline);
DSL_COMMON string           eatRecord(string& sline);
DSL_COMMON string           eatRecord(string &text, const string& sep);

DSL_COMMON void             extractRecord(int recordNr, const string& sline, string &record);

DSL_COMMON string           sqlEscape(const string& in_this);
DSL_COMMON string           replaceCharacter(const char& replace_this, const char& with_this, const string& in_this);
DSL_COMMON string           replaceSubstring(const string& replace_this, const string& with_this, const string& in_this);

DSL_COMMON void             cleanLines(vector<string>& lines, const string& chars);

//conversions
DSL_COMMON DATA_FORMAT      strToDataFormat(const string& str);
DSL_COMMON DATA_FORMAT      fileExtensionToDataFormat(const string& str);
DSL_COMMON string           dataFormatToStr(const DATA_FORMAT& format);
DSL_COMMON string           fileFormatToStr(const FILE_FORMAT& format);
DSL_COMMON FILE_FORMAT      strToFileFormat(const string& str);

DSL_COMMON string           getTimeString();    //Return a string containing the date time in format "Wed Mar 31 15:02:11 2004\n"
DSL_COMMON string           getDateTimeString();    //Return a string containing the date time in format "2004 Mar 31 15:02:11"


//See: http://www.cplusplus.com/reference/ctime/strftime/
DSL_COMMON string           getFormattedDateTimeString(const string& format);    //Return a string containing the date time in format "2004 Mar 31 15:02:11"

DSL_COMMON vector<string>   split(const string &s, char delim);
DSL_COMMON vector<string>&  split(const string &s, char delim, vector<string> &elems);

DSL_COMMON size_t           splitString(vector<string>& strs, const string &text, const string &separators);
DSL_COMMON vector<string>   splitString(const string& input, const char& delimiter);
DSL_COMMON vector<string>   splitString(const string& input, const string& delimiters, bool cutDel = true);
DSL_COMMON vector<string>   splitStringAtWord(const string& input, const string& word);

//DSL_COMMON string           AsString(const vector<string>& list);
DSL_COMMON int              toInt(const string& str, bool fromBeginning = true);
DSL_COMMON long             toLong(const string& str);
DSL_COMMON bool             toBool(const string& str);
DSL_COMMON double           toDouble(const string& str);

#if defined(__CODEGEARC__)
DSL_COMMON string           toUpperOrLowerCase(const string& inStr, int (*func)(int) = std::toupper);
#else
//DSL_COMMON string        ToUpperOrLowerCase(const string& inStr, int (*func)(_Elem, const std::locale) = std::toupper);
#endif

DSL_COMMON string           toUpperCase(const string& inStr);
DSL_COMMON string           toLowerCase(const string& inStr);

//Make toString a template
DSL_COMMON string           toString(const bool b);
DSL_COMMON string           toString(const char n);
DSL_COMMON string           toString(const unsigned char n);
DSL_COMMON string           toString(const char* str);
DSL_COMMON string           toString(const unsigned char n);
DSL_COMMON string           toString(const int n,            const string& format = gIntFormat, const int nBase=10);
DSL_COMMON string           toString(const unsigned int n,   const string& format = gIntFormat, const int nBase=10);
DSL_COMMON string           toString(const long n,           const int nBase=10);
DSL_COMMON string           toString(const unsigned long n,  const int nBase=10);
DSL_COMMON string           toString(double d, const string& format = gDoubleFormat);
DSL_COMMON string           toString(const string& s);
DSL_COMMON string           toString(const vector<int>& 	vec, const string& sep = gCommaSpace);
DSL_COMMON string           toString(const vector<double>& 	vec, const string& sep = gCommaSpace);
DSL_COMMON string           toString(const vector<string>& 	vec, const string& sep = gCommaSpace);
DSL_COMMON string           toString(const DateTime& dt, const string& sep = Poco::DateTimeFormat::ISO8601_FORMAT);

DSL_COMMON const char*      toCString(const bool b);
DSL_COMMON const char*      toCString(const char n);
DSL_COMMON const char*      toCString(const unsigned char n);
DSL_COMMON const char*      toCString(const char* str);
DSL_COMMON const char*      toCString(const unsigned char n);
DSL_COMMON const char*      toCString(const int n,            const string& format = gIntFormat, const int nBase=10);
DSL_COMMON const char*      toCString(const unsigned int n,   const string& format = gIntFormat, const int nBase=10);
DSL_COMMON const char*      toCString(const long n,           const int nBase=10);
DSL_COMMON const char*      toCString(const unsigned long n,  const int nBase=10);
DSL_COMMON const char*      toCString(double d, const string& format = gDoubleFormat);
DSL_COMMON const char*      toCString(const string& s);
DSL_COMMON const char*      toCString(const vector<int>& vec, const string& sep = gCommaSpace);
DSL_COMMON const char*      toCString(const vector<double>& vec, const string& sep = gCommaSpace);
DSL_COMMON const char*      toCString(const vector<string>& vec, const string& sep = gCommaSpace);
DSL_COMMON const char*      toCString(const DateTime& dt, const string& sep = Poco::DateTimeFormat::ISO8601_FORMAT);

DSL_COMMON bool             compareStrings(const string& str1, const string& str2, 	CASE_SENSITIVITY casing = csCaseSensitive);
DSL_COMMON bool             compareNoCase(const string& str1, const string& str2);
DSL_COMMON bool             contains(const StringList& words, const string& aString,CASE_SENSITIVITY casing = csCaseSensitive);
DSL_COMMON bool             contains(const string& aWord, const string& aString, 	CASE_SENSITIVITY casing = csCaseSensitive);

DSL_COMMON bool             hasFilePath(const string& fileN);
DSL_COMMON string           getFilePath(const string& fileN);
DSL_COMMON string           getFileNameNoPath(const string& fileN);
DSL_COMMON string           getFileNameNoExtension(const string& fileN);
DSL_COMMON string           getFileNameNoPathNoExtension(const string& fileN);
DSL_COMMON string           getFileExtension(const string& fileN);
DSL_COMMON bool             hasFileExtension(const string& fileN);

//Can't use va_arg for non pod data.. :(
DSL_COMMON string           joinPath(const string& p1, const string& p2, const char pathSeparator = gPathSeparator);
DSL_COMMON string           joinPath(const string& p1, const string& p2, const string& p3, const char pathSeparator = gPathSeparator);
DSL_COMMON string           joinPath(const string& p1, const string& p2, const string& p3, const string& p4, const char pathSeparator = gPathSeparator);
DSL_COMMON string           joinPath(const string& p1, const string& p2, const string& p3, const string& p4, const string& p5, const char pathSeparator = gPathSeparator);

DSL_COMMON string           extractPathTo(const string& filePathOrJustPath, const char& pathSeparator = gPathSeparator);
DSL_COMMON string           changeFileExtensionTo(const string& theFileName, const string& newExtension);

DSL_COMMON bool             inStringList(const string& fldr, list<string>& theList);
DSL_COMMON ostream&         operator<<(ostream& os, const vector<string>& list);

////String format
DSL_COMMON string           format(const string& src, int arg);
//DSL_COMMON string           format(const string& str, int arg1);
//DSL_COMMON string           format(const string& str1, int arg1, double arg2);
//DSL_COMMON string           format(const string& src, const string& arg);
DSL_COMMON string           format(const string& src, const string& arg1, const string& arg2, const string& arg3);
//DSL_COMMON string           format(const string& src, const string& arg1, const string& arg2);
//DSL_COMMON string           format(const string& src, const string& arg1, int arg2);
DSL_COMMON string           format(const string& src, const string& arg1, int arg2, const string& arg3);
//DSL_COMMON string           format(const string& str1, const string& str2);
//DSL_COMMON string           format(const string& str1, const string& arg1, const string& arg2);
//DSL_COMMON string           format(const string& str1, const string& arg1, int arg2);
//DSL_COMMON string           format(const string& str1, const string& arg1, int arg2, const string& arg3);
//DSL_COMMON string           format(const string& str1, const string& arg1, const string& arg2, const string& arg3);
//DSL_COMMON string           format(const string& str1, const string& arg1, const string& arg2, const string& arg3, const string& arg4);
//DSL_COMMON string           format(const string& str1, const string& arg1, const string& arg2, const string& arg3, const string& arg4, const string& arg5);
//DSL_COMMON string           format(const string& str1, const unsigned int& arg1, const string& arg2);
//DSL_COMMON string           format(const string& str1, const unsigned int& arg1, const string& arg2, const string& arg3);
//DSL_COMMON string           format(const string& str1, const unsigned int& arg1, const unsigned int& arg2, const string& arg3, const string& arg4);


DSL_COMMON string           substitute(const string& src, const string& thisOne, int withThisOne, int howMany = -1);
DSL_COMMON string           substitute(const string& src, const string& thisOne, double withThisOne, int howMany = -1);
DSL_COMMON string           substitute(const string& src, const string& thisOne, const string& withThisOne, int howMany = -1);

class DSL_COMMON IsThisChar
{
    char mTheChar;

    public:
                IsThisChar(const char& isThis);
        bool    operator() (const char& aChar);
};


//TO RETIRE-------------------------------
#define TEXT_WIDTH  15
DSL_COMMON string           getFormattedParStr(const string& varS, const double var, const int width = TEXT_WIDTH);
DSL_COMMON string           getFormattedParStr(const string& varS, const unsigned int var, const int width = TEXT_WIDTH);
DSL_COMMON string           getFormattedParStr(const string& varS, const int var, const int width = TEXT_WIDTH);
DSL_COMMON string           getFormattedParStr(const string& varS, const bool val, const int width = TEXT_WIDTH);
DSL_COMMON string           getFormattedParStr(const string& varS, const vector<int>& vec, const int width = TEXT_WIDTH);
DSL_COMMON string           getFormattedParStr(const string& varS, const string& var, const int width = TEXT_WIDTH);
DSL_COMMON vector<int>      stringRecordsToIntVector(const string& theString);

}
#endif
