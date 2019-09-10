#pragma hdrstop
#include "dslStringUtils.h"
#include "dslStringList.h"
#include "dslCompareStrings.h"
#include "dslRange.h"
#include "dslException.h"
#include "Poco/Path.h"
#include "Poco/DateTimeParser.h"
#include <algorithm>
#include <fstream>
#include <functional>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <clocale>

#ifdef _MSC_VER
#include <ctype.h>
#endif
//---------------------------------------------------------------------------

namespace dsl
{
    typedef unsigned int uint;
using namespace std;
using Poco::DateTimeParser;


string toHex(int byte)
{
	stringstream h;
    h << std::uppercase << hex << byte;
    return h.str();
}

DateTime strToDateTime(const string& dateTime)
{
	int diff(0);
	return DateTimeParser::parse(dateTime, diff);
}

string zeroPadString(unsigned int z, const string& str)
{
	if (str.size() < z )
    {
    	return string( z-str.size(), '0').append(str);
    }
    return str;
}

string createZeroPaddedString(unsigned int zeroes, unsigned int number)
{
	string val(dsl::toString(number));
    if(val.size() >= zeroes)
    {
    	return val;
    }
    else
    {
		string prefix(zeroes - val.size(), '0');
        return prefix + val;
    }
}

//Passing a NULL string, returns a empty std string..
string stdstr(const char* str)
{
    return (str != NULL) ? string(str) : string("");
}

string stdstr(vector<char>& str )
{
	return (str.size()) ? stdstr( &str[0] ) : string("");
}

string stdstr(const string& str)
{
	return str;
}

string stdstr( const std::wstring& str )
{
    std::locale const loc("");
    wchar_t const* from = str.c_str();
    std::size_t const len = str.size();
    std::vector<char> buffer(len + 1);

    std::use_facet<std::ctype<wchar_t> >(loc).narrow(from, from + len, '_', &buffer[0]);
    return std::string(&buffer[0], &buffer[len]);
}

wstring wstdstr(const string& str)
{
	std::wstring widestr = std::wstring(str.begin(), str.end());
	return widestr;
}

string getParentFolder(const string& folder)
{
    StringList path = splitString(folder, "\\/");
	if(path.count())
    {
        string prnt = path[0];
        for(unsigned int i = 1; i < path.count() - 1; i++)
        {
            prnt +="\\" + path[i];
        }
        return prnt;
    }
    return folder;
}

StringList getLinesInFile(const string& fName)
{
    StringList lines;
    ifstream ifs(fName.c_str());
    if(!ifs)
    {
        //Log(lError)<<"Failed opening file: "<<fName;
        return lines;
    }
    string line;
    while (std::getline(ifs, line))
    {
           lines.append(line);
    }
   return lines;
}

string readFirstWord(const string& sline)
{
    vector<string> words = splitString(sline," \t\r\n");
    return words.size() ? words[0] : string("");
}

bool startsWith(const string& prefix, const string& theStr, bool caseLess)
{
    string s(theStr), p(prefix);
    if(caseLess == true)
    {
    	s = toLowerCase(theStr);
    	p = toLowerCase(prefix);
    }

	return (s.find(p) == 0) ? true : false;
}

bool contains(const string& aWord, const string& aString, CASE_SENSITIVITY casing)
{
    if(casing == csCaseInsensitive)
    {
        string theString(toLowerCase(aString));
        string theWord(toLowerCase(aWord));
        return theString.find(theWord) != string::npos ? true : false;
    }
    return aString.find(aWord) != string::npos ? true : false;
}

bool contains(const StringList& words, const string& aString, CASE_SENSITIVITY casing)
{
    bool doesIt(false);
    for(uint i = 0; i < words.count(); i++)
    {
        if(contains(words[i], aString, casing))
        {
            return true;
        }
    }
    return false;
}

bool endsWith(const string& ending, const string& fullString)
{
    if(fullString.size() >=   ending.size())
    {
    	return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    }
    else
    {
    	return false;
    }
}

string getStringFromSeconds(long elapsed)
{
    if(elapsed < 0)
	{
        return "00:00:00";
    }
    int hours = elapsed / 3600;
    int minutes = (elapsed / 60) % 60 ;
    int seconds = elapsed % 60;
    string h,m,s;
    h     = toString(hours);
    m     = toString(minutes);
    s    = toString(seconds);
    if(hours < 10)
    {
        h = "0" + h;
    }
    if(minutes < 10)
    {
        m = "0" + m;
    }
    if(seconds < 10)
    {
        s = "0" + s;
    }
    string timeStr = h + ":" + m + ":" + s;
    return timeStr;
}

int indexOf(const vector<string>& vec, const string& elem)
{
    if(!vec.size())
    {
        return -1;
    }
    else
	{
        vector<string>::const_iterator it  = find(vec.begin(), vec.end(), elem);
        if(it == vec.end())
        {
            return -1;
        }
        else
        {
            return it - vec.begin();
        }
    }
}

bool inStringList(const string& fldr, list<string>& theList)
{
    list<string>::iterator index = std::find_if(theList.begin(), theList.end(), CompareStrings(fldr));
    return (index != theList.end()) ? true : false;
}

string stripNewLine(const string& msg)
{
    string aMsg = msg;
    //Strip new lines
    if(aMsg[aMsg.size()-1] == '\n')
    {
        aMsg.erase(aMsg.size()-1);
    }
    return aMsg;
}

string trimChars(const string& str, const string& chars, int max_trim)
{
    string res(str);
    for(uint i = 0; i < chars.size(); i++)
    {
        res = trim(res, chars[i], max_trim);
    }
    return res;
}

// trim from both ends
string trim(const string& _s, const char& ch, int max_trim)
{
    return trimFront(trimBack(_s, ch, max_trim), ch, max_trim);
}

// trim from start
string trimFront(const string& _s, const char& ch, int max_trim)
{
    string s(_s);
    int count(0);
    while(s.size() > 0 && s[0] == ch)
    {
        s.erase(0, 1);
        count++;
        if(count >= max_trim)
        {
            break;
        }
    }
    return s;
}

// trim from end
string trimBack(const string& _s, const char& ch, int max_trim)
{
    string s(_s);
    int count(0);
    while(s[s.size() - 1] == ch)
    {
        s.erase(s.size() - 1);
        count++;
        if(count >= max_trim)
        {
            break;
        }
    }
    return s;
}

// trim from start
string trimWSFront(const string& _s)
{
    string s(_s);
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1( std::ptr_fun<int, int>(isspace))));
    return s;
}

// trim from end
string trimWSBack(const string& _s)
{
    string s(_s);
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

// trim from both ends
string trimWS(const string& _s)
{
//    string s(_s);
    return trimWSFront(trimWSBack(_s));
}

//string Trim(const string& str, const string& chars)
//{
//    string rStr = str;
//
//    //Remove WhiteSpaces in front and back of str
//    rStr = TrimForward(rStr, chars);
//    return TrimReverse(rStr, chars);
//}
//
//string TrimForward(const string& sline, const string& chars)
//{
//    int charNr = 0;
//    string line = sline;
//    bool canContinue = false;
//    do
//    {
//        char aChar = line[charNr];
//        if(chars.find(aChar) != string::npos)
//        {
//            canContinue = true;
//            charNr++;
//        }
//        else
//        {
//            canContinue = false;
//        }
//    }
//    while(canContinue == true);
//
//    if(charNr != 0)
//    {
//        line.erase(0,charNr);
//    }
//    return line;
//}
//
//string TrimReverse(const string& sline, const string& chars)
//{
//    int charNr = 0;
//    string line = sline;
//    bool canContinue = false;
//    do
//    {
//        char aChar = line[line.size() - 1 - charNr];
//        if(chars.rfind(aChar) != string::npos)
//        {
//            canContinue = true;
//            charNr++;
//        }
//        else
//        {
//            canContinue = false;
//        }
//    }
//    while(canContinue == true);
//
//    if(charNr != 0)
//    {
//        line.erase(line.size() - charNr, line.size());
//        line += "\n";
//    }
//    return line;
//}

//void CleanLines(vector<string>& lines, const string& chars)
//{
//    for(unsigned int i = 0; i < lines.size(); i++)
//    {
//        lines[i] = Trim(lines[i], chars);
//    }
//}
//
string asString(const vector<string>& list)
{
    string res;
    for(uint i = 0; i < list.size(); i++)
    {
        res += list[i] ;
    }
    return res;
}

void stripToNonWhiteSpace(string &line, string &result)
{
    int charNr = 0;
    while(line[charNr] != ' ' && line[charNr] != '\t')
    {
            result += line[charNr++];
    }

    while(line[charNr] == ' ' || line[charNr] == '\t')
    {
        charNr++;
    }

    line.erase(0,charNr);
}

string stripToAlpha(const string& sline)
{
    //  ctype.h
    string str = sline;
    int charNr = 0;
    char ch;
    while(str[charNr])
    {
        ch = str[charNr];
        if(isalpha(ch))
            return str;
        else
            str.erase(0,1);
    }
    return str;
}

string stripToDigit(const string& sline)
{
    //  ctype.h
	string str = sline;
    while(str[0])
    {
        char ch = str[0];
        if(isdigit(ch))
            return str;
        else
        {
            str.erase(0,1);
        }
    }
    return str;
}

string stripToDigitR(const string& sline)
{
    //  ctype.h
    string str = sline;
    while(str[str.size() -1])
    {
        char ch = str[str.size() -1];
        if(isdigit(ch))
            return str;
        else
        {
            str.erase(str.size() -1,1);
        }
    }
    return str;
}

string stripToAlphaNumR(const string& sline)
{
    //  ctype.h
    string str = sline;
    char ch;
    while(str[str.size()-1])
    {
        ch = str[str.size()-1];
        if(isalnum(ch))
        {
            return str;
        }
        else
        {
            str.erase(str.size() -1,1);
        }
    }
    return str;
}

string stripToAlphaR(const string& sline)
{
    string str = sline;
    while(str[str.size()-1])
    {
        char ch = str[str.size()-1];
        if(isalpha(ch))
        {
            return str;
        }
        else
        {
            str.erase(str.size() -1, 1);
        }
    }
    return str;
}

string eatWhiteSpace(const string& str)
{
    int charNr = 0;
    string line = str;
    while(line[charNr] == ' ' || line[charNr] == '\t' || line[charNr] == ',' || line[charNr] == '\"' || line[charNr] == '>')
    {
        charNr++;
    }

    if(charNr != 0)
    {
        line.erase(0,charNr);
    }

    return line;
}

string eatWhiteSpaceR(const string& str)
{
    unsigned int charNr = str.size();
    string line = str;
    while(line[charNr-1] == ' ' || line[charNr-1] == '\t' || line[charNr-1] == ',' || line[charNr] == '"' || line[charNr] == '>')
    {
        charNr--;
    }

    if(charNr != str.size())
    {
        line.erase(charNr, str.size());
    }
    return line;
}

double eatNumber(string &str)
{
    char *endptr;
    double nr = strtod(str.c_str(), &endptr);
    str.erase(0, str.find(endptr));
    return nr;
}

void eatNumber(string &sline, double &result)
{
    string number;
    char *endptr;
    unsigned int charNr = 0;
    string temp;
    stripToNonWhiteSpace(sline, temp);
    while(charNr <= sline.size() &&  sline[charNr] != ' ' && sline[charNr] != '\t')
    {
            number += sline[charNr++];
    }
    sline.erase(0,charNr);
    result = strtod(number.c_str(), &endptr);
}

string eatWord(string& sline)
{
    return eatRecord(sline);
}

string eatRecord(string &text, const string& sep)
{
    if(!text.size())
    {
        return "";
    }

    //Remove any initial whitespace
    text = text.substr(text.find_first_not_of(sep), text.size());

    //find next seperator
    int start, stop;
    start = 0;
    stop = text.find_first_of(sep, start);
    if(stop == -1) //If there are no seperators, the string is one record
    {
        stop = text.size();
    }

    //This is the record
	 string temp = text.substr(start, stop);

    //This is the rest
    text = text.substr(stop,text.size());
    if(text.size())
    {
        size_t ws = text.find_first_not_of(sep);
        if(ws == -1) //Means there is only whitespace!
        {
            text = "";
        }
        else
        {
            text = text.substr(ws, text.size()); //Remove any more ws
        }
    }
    return temp;
}

string eatRecord(string &sline)
{
    unsigned int charNr = 0;
    string result;
    string temp;
    sline = eatWhiteSpace(sline);
    while(charNr <= sline.size())
    {
        if(!isspace(sline[charNr]))
        {
            if(sline[charNr] ==',')
            {
                charNr++;
                break;
            }
            result += sline[charNr];
            charNr++;
        }
        else
            break;
    }
    if(charNr != 0)
    {
        sline.erase(0, charNr);
    }
    result[result.size()] = '\0';
    return result;
}

void extractRecord(int recordNr, const string& sline, string& record)
{
	string temp = sline;
	for(int i = 0; i < recordNr; i++)
	{
        record = eatRecord(temp);
    }
}

string getFileNameNoPath(const string& fileN)
{
    string fName;
    if(fileN.find_last_of( '\\' ) != std::string::npos)
    {
        fName = fileN.substr(fileN.find_last_of( '\\' )+ 1, fileN.size());
        return fName;
    }
    else if(fileN.find_last_of( '/' ) != std::string::npos)
    {
        fName = fileN.substr(fileN.find_last_of( '/' ) + 1, fileN.size());
        return fName;
    }

    return fileN; //There was no path in present..
}

bool hasFileExtension(const string& fileN)
{
	Poco::Path aFile(fileN);
    return aFile.getExtension().size() ? true : false;
}

string getFileNameNoExtension(const string& fileN)
{
    string fName;
    if(fileN.find_last_of( '\\' ) != std::string::npos)
    {
        fName = fileN.substr(fileN.find_last_of( '\\' )+ 1, fileN.size());
    }
    else if(fileN.find_last_of( '/' ) != std::string::npos)
    {
        fName = fileN.substr(fileN.find_last_of( '/' ) + 1, fileN.size());
    }
    else
    {
    	fName = fileN;
    }

	return changeFileExtensionTo(fName, "");
}

string getFileNameNoPathNoExtension(const string& fileN)
{
    return getFileNameNoExtension(getFileNameNoPath(fileN));
}

string getFileExtension(const string& fileName)
{
    if(fileName.find_last_of(".") != std::string::npos)
    {
        return fileName.substr(fileName.find_last_of(".")+1);
    }
    return "";
}

string getFilePath(const string& fileN)
{
    string path;
    if(fileN.find_last_of( '\\' ) != std::string::npos)
    {
        path = fileN.substr( 0, fileN.find_last_of( '\\' ));
        return path;
    }
    else if(fileN.find_last_of( '/' ) != std::string::npos)
    {
        path = fileN.substr( 0, fileN.find_last_of( '/' ));
        return path;
    }

    return "";
}

bool hasFilePath(const string& fileN)
{
    if(fileN.find_last_of( gPathSeparator ) != std::string::npos)
    {
        return true;
    }
    return false;
}

string changeFileExtensionTo(const string& _fName, const string& newExtension)
{
    //Be aware of the case
    //".\\fName"
    //where  the . is not part of the filename
    string path = getFilePath(_fName);
    string fName = getFileNameNoPath(_fName);
    //First create the file name, remove current extension if it exists

    if(fName.find_last_of('.') != string::npos)
    {
        //Extension does exist. Cut it, and append new one
        fName =  fName.substr(0, fName.find_last_of('.'));
    }

    if(newExtension[0] == '.')
    {
        fName = fName + newExtension;
    }
    else if(newExtension.size() == 0)	//No extension
    {
    	return fName;
    }
    else
    {
        fName = fName + "." + newExtension;
    }

    return joinPath(path, fName);
}


string dataFormatToStr(const DATA_FORMAT& format)
{
    switch(format)
    {
        case dfMoleculix:       return string("dfMoleculix");
        case dfDouble:          return string("dfDouble");
        case dfComplex:         return string("dfComplex");
//        case dfUW:   return string("dfUW");
//        case dfCMX:  return string("dfCMX");
//        case dfVAX_ASCII:   return string("dfVAX_ASCII");
//        case dfSimpson:    return string("dfSimpson");
//        case dfSpinVision: return string("dfSpinVision");
        case dfMolecule:        return string("dfMolecule");
//        case dslMXQETFORMAT:return string("dslMXQET");
//        case dslWINSPIN:    return string("dslWINSPIN");
//        case dslFELIX:      return string("dslFELIX");
        default:
                                return string("Unknown Data Format");
    }
}

DATA_FORMAT strToDataFormat(const string& str)
{
    if(str.find("dfMoleculix") != std::string::npos )
    {
        return dfMoleculix;
    }

    if(str.find("dfDouble") != std::string::npos)
    {
        return dfDouble;
    }

    if(str.find("dfComplex") != std::string::npos)
    {
        return dfComplex;
    }
//    if(str.find("dfDouble")       != std::string::npos) return dfDouble;
//    if(str.find("dslIMAGINARY")  != std::string::npos) return dslIMAGINARY;
//    if(str.find("dfUnknown")    != std::string::npos) return dfUnknown;
//    if(str.find("dfUW")   != std::string::npos) return dfUW;
//    if(str.find("dfCMX")  != std::string::npos) return dfCMX;
//    if(str.find("dfVAX_ASCII")   != std::string::npos) return dfVAX_ASCII;
//    if(str.find("dfSimpson")    != std::string::npos) return dfSimpson;
//    if(str.find("dfSpinVision") != std::string::npos) return dfSpinVision;
//    if(str.find("dfMolecule")   != std::string::npos) return dfMolecule;
//    if(str.find("dslMXQET" )     != std::string::npos) return dslMXQETFORMAT;
//    if(str.find("dslWINSPIN")    != std::string::npos) return dslWINSPIN;
//    if(str.find("dslFELIX")      != std::string::npos) return dslFELIX;
    return dfUnknown;
}

DATA_FORMAT fileExtensionToDataFormat(const string& eStr)
{
    string str;
    for(unsigned int i = 0; i < eStr.size(); i++)
    {
        str += (char) tolower(eStr[i]);
    }

    if(str == "dsl")
    {
        return dfMoleculix;
    }

    if(str == "dat")
    {
        return dfUW;
    }

    if(str == "")
    {
        return dfCMX; // no extension
    }

    if(str == "asc")
    {
        return dfVAX_ASCII;
    }

    if(str == "fid")
    {
        return dfSimpson;
    }

    if(str == "svd")
    {
        return dfSpinVision;
    }

  return dfUnknown;
}

string fileFormatToStr(const FILE_FORMAT& format)
{
    switch(format)
    {
        case ffASCII: 	return string("ffASCII");
        case ffBINARY:	return string("ffBINARY");
        case ffUnkown:	return string("ffUnkown");
        default:        return string("Unknown Data Format");
    }
}

FILE_FORMAT strToFileFormat(const string& str)
{
    if(str.find("ffASCII") == 0)
    {
        return ffASCII;
    }

    if(str.find("ffBINARY") == 0)
    {
        return ffBINARY;
    }

    if(str.find("ffUnkown") == 0)
    {
        return ffUnkown;
    }
    return ffUnkown;
}

string replaceCharacter(const char& replace_this, const char& with_this, const string& source)
{
    string s = source;
    replace(s.begin(), s.end(), replace_this, with_this) ;
    return s;
}

string sqlEscape(const string& in_this)
{
    string escaped(in_this);
    //escaped = replaceCharacter(' ', '\ ', escaped);
    escaped = replaceSubstring("'", "''", escaped);
    return escaped;
}

//void replaceAll(std::string& str, const std::string& from, const std::string& to) {
//    if(from.empty())
//        return;
//    size_t start_pos = 0;
//    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
//        str.replace(start_pos, from.length(), to);
//        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
//    }
//}

string replaceSubstring(const string& replace_this, const string& with_this, const string& source)
{
    string str(source);
    if(replace_this.empty())
    {
        return str;
    }

    size_t start_pos = 0;
    while((start_pos = str.find(replace_this, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, replace_this.length(), with_this);
        start_pos += with_this.length(); // In case 'with_this' contains 'replace_this', like replacing 'x' with 'yx'
    }

    return str;
}

string stripCharacter(const char& ch, const string& source)
{
    string s = source;
    s.erase(std::remove_if(s.begin(), s.end(), IsThisChar(ch)), s.end() ) ;
    return s;
}

string stripCharacters(const string& chars, const string& source)
{
    string s = source;
    for(uint i = 0; i < chars.size(); i++)
    {
        s = stripCharacter(chars[i], s);
    }
    return s;
}

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    split(s, delim, elems); //Calls function below
    return elems;
}

vector<string>& split(const string &s, char delim, vector<string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

vector<string> splitString(const string &text, const char& oneSep)
{
    string separator;
    separator = oneSep;
    return splitString(text, separator);
}

vector<string> splitString(const string &text, const string &separators)
{
    vector<string> words;
    size_t n = text.length();
    size_t start = text.find_first_not_of(separators);
    while( (start >= 0) && (start < n) )
    {
        size_t stop = text.find_first_of(separators, start);
        if( (stop < 0) || (stop > n) )
        {
            stop = n;
        }
        words.push_back(text.substr(start, stop - start));
        start = text.find_first_not_of(separators, stop+1);
    }
    return words;
}

vector<string> splitString(const string& text, const string &separators, bool cutDelimiter)
{
    vector<string> words;
    size_t n = text.length();
    size_t start = text.find_first_not_of(separators);
    while( (start >= 0) && (start < n) )
    {
        size_t stop = text.find_first_of(separators, start);
        if( (stop < 0) || (stop > n) )
        {
            stop = n;
        }

        if(cutDelimiter)
        {
            words.push_back(text.substr(start, stop - start));
        }

        else
        {
            if(start > 0)
            {
                start -= 1;
            }

            if(stop != n)
            {
                stop += 1;
            }

            string temp(text.substr(start, stop - start));
            words.push_back(temp);
        }
        start = text.find_first_not_of(separators, stop+1);
    }
    return words;
}

size_t splitString(vector<string>& words, const string &text, const string &separators)
{
    size_t n = text.length();
    size_t start = text.find_first_not_of(separators);
    while( (start >= 0) && (start < n) )
    {
        size_t stop = text.find_first_of(separators, start);
        if( (stop < 0) || (stop > n) )
        {
            stop = n;
        }
        words.push_back(text.substr(start, stop - start));
        start = text.find_first_not_of(separators, stop+1);
    }
    return words.size();
}

string joinPath(const string& aPath, const string& aFile, const char pathSeparator)
{
    //Just check the paths last position. it has to be a "/"
    //Otherwise, add it before joining
    if(aPath.size() > 0)
    {
        if(aPath[aPath.size() - 1] == pathSeparator)
        {
	        return aPath + aFile;
        }
        else
        {
            return aPath + pathSeparator + aFile;
        }
    }

    return aFile;
}

string joinPath(const string& p1, const string& p2, const string& p3, const char pathSeparator)
{
	string tmp(joinPath(p1, p2, pathSeparator));
    return joinPath(tmp, p3, pathSeparator);
}

string joinPath(const string& p1, const string& p2, const string& p3, const string& p4, const char pathSeparator)
{
	string tmp(joinPath(p1, p2, p3, pathSeparator));
    return joinPath(tmp, p4, pathSeparator);
}

string joinPath(const string& p1, const string& p2, const string& p3, const string& p4, const string& p5, const char pathSeparator)
{
	string tmp(joinPath(p1, p2, p3, p4, pathSeparator));
    return joinPath(tmp, p5, pathSeparator);
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



int toInt(const string& str, bool fromBeginning)
{
	if(fromBeginning)
    {
    	if(str.size())
        {
    		return atoi(str.c_str());
        }
    }
    else
    {
		StringList tokens(splitString(str, ", ", true));
		//Read tokens from end
        for(int i = tokens.size() -1; i > -1; i--)
        {
        	string token = tokens[i];
            if(token.size())
            {
            	return atoi(token.c_str());
            }
        }
    }

    stringstream msg;
    msg <<"Failed to convert string to integer.";
    msg <<"The string was: \""<<str<<"\"";
	throw(DSLException(msg.str()));
}

long toLong(const string& str)
{
    return atol(str.c_str());
}

//STR2INT_ERROR str2int (int &i, char const *s, int base)
//{
//    char *end;
//    long  l;
//    errno = 0;
//    l = strtol(s, &end, base);
//    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX)
//    {
//        return OVERFLOW;
//    }
//
//    if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN)
//    {
//        return UNDERFLOW;
//    }
//
//    if (*s == '\0' || *end != '\0')
//    {
//        return INCONVERTIBLE;
//    }
//    i = l;
//    return SUCCESS;
//}

bool toBool(const string& str)
{
	string copy(trimChars(str," \r"));
    if(copy.size() < 2)
    {
        return (copy == "1") ? true : false;
    }
    else
    {
        return compareNoCase(copy, "true");
    }
}

double toDouble(const string& str)
{
    if(!str.size())
    {
        return 0;
    }

    string astr =  trimFront(str,'$');

    char *endptr = NULL;
    return strtod(astr.c_str(), &endptr);
}

string extractPathTo(const string& filePathOrJustPath, const char& pathSeparator)
{
    string file = filePathOrJustPath;
    //Check if the file comes with a path..
    size_t start = file.find_first_of(pathSeparator);
    size_t end   = file.find_last_of(pathSeparator);
    if(start < 0)
    {
        return string("");
    }
    else
    {
        return string(file.erase(end , file.size()));
    }
}

string toUpperOrLowerCase(const string& inStr, int (*func)(int))
{
    string rString(inStr);
    std::transform(rString.begin(), rString.end(), rString.begin(), func);
    return rString;
}

string toUpperCase(const string& inStr)
{
    string rString(inStr);
    std::transform(rString.begin(), rString.end(), rString.begin(), (int(*)(int)) toupper);
    return rString;
}

string toLowerCase(const string& inStr)
{
    string rString(inStr);
    std::transform(rString.begin(), rString.end(), rString.begin(), (int(*)(int)) tolower);
    return rString;
}


//============ To String functions ================================
string toString(const  bool b)
{
    return (b ? "true" : "false");
}

string toString(const  float d)
{
    char sBuffer[256];
    sprintf(sBuffer,"%g", d);
    return string(sBuffer);
}

string toString(const string& s)
{
    return s;
}

string toString(const char* str)
{
    return string(str);
}

string toString(const unsigned int n, const int nBase)
{
    char sBuffer[256];
    if (nBase == 16)
    {
        sprintf(sBuffer, "%X", n);
        return string("0x") + string(sBuffer);
    }
    else if(nBase == 2)
    {
        string tmp = "";
        int k = n;
        for (int i=0; i<8; i++)
        {
            if ((k & 0x80) != 0)
                tmp += "1";
            else
                tmp += "0";
            k = k<<1;
        }
        return "0b" + tmp;
    }
    else
    {
        sprintf(sBuffer, "%d", n);
        return string(sBuffer);
    }
}

string toString(const int n, const int nBase)
{
    char sBuffer[256];
    if (nBase == 16)
    {
        sprintf(sBuffer, "%X", n);
        return string("0x") + string(sBuffer);
    }
    else if(nBase == 2)
    {
        string tmp = "";
        int k = n;
        for (int i=0; i<8; i++)
        {
            if ((k & 0x80) != 0)
                tmp += "1";
            else
                tmp += "0";
            k = k<<1;
        }
        return "0b" + tmp;
    }
    else
    {
        sprintf(sBuffer, "%d", n);
        return string(sBuffer);
    }
}

string toString(const int n, const string& format, const int nBase)
{
    char sBuffer[256];
    if (nBase == 16)
    {
        sprintf(sBuffer, "%X", n);
        return format + string(sBuffer);
    }
    else if(nBase == 2)
    {
        string tmp = "";
        int k = n;
        for (int i=0; i<8; i++)
        {
            if ((k & 0x80) != 0)
                tmp += "1";
            else
                tmp += "0";
            k = k<<1;
        }
        return "0b" + tmp;
    }
    else
    {
        sprintf(sBuffer, "%d", n);
        return string(sBuffer);
    }
}

string toString(const unsigned int n, const string& format, const int nBase)
{
    char sBuffer[256];
    if (nBase == 16)
    {
        sprintf(sBuffer, "%X", n);
        return string("0x") + string(sBuffer);
    }
    else if(nBase == 2)
    {
        string tmp = "";
        int k = n;
        for (int i=0; i<8; i++)
        {
            if ((k & 0x80) != 0)
                tmp += "1";
            else
                tmp += "0";
            k = k<<1;
        }
        return "0b" + tmp;
    }
    else
    {
        sprintf(sBuffer, "%d", n);
        return string(sBuffer);
    }
}

string toString(const long n, const int nBase)
{
    char sBuffer[256];
    if (nBase == 10)
    {
        sprintf(sBuffer, "%lu", n);
        return string(sBuffer);
    }
    return toString( int(n), nBase);
}

string toString(const unsigned long n, const int nBase)
{
    char sBuffer[256];
    if (nBase == 10)
    {
        sprintf(sBuffer, "%lu", n);
        return string(sBuffer);
    }
    return toString( int(n), nBase);
}

string toString(const unsigned short n, const int nBase)
{
    char sBuffer[256];
    if (nBase == 10)
    {
        sprintf(sBuffer, "%u", n);
        return string(sBuffer);
    }
    return toString( int(n), nBase);
}

string toString(const short n, const int nBase)
{
    return toString(int(n), nBase);
}

string toString(const char n)
{
    char sBuffer[256];
	sprintf(sBuffer, "%c", n);
	return string(sBuffer);
}

string toString(const unsigned char n)
{
	char sBuffer[256];
	sprintf(sBuffer, "%c", n);
	return string(sBuffer);
}

string toString(double val, int precision)
{
    stringstream s;
    s << std::setprecision(precision) << val;
	return s.str();
}

string toString(const DateTime& dt, const string& format)
{
	return Poco::DateTimeFormatter::format(dt, format);
}

string toString(const vector<string>& vec, const string& sep)
{
	StringList sl(vec);
	return sl.asString();
}

const char* toCString(const  bool b)
{
    return (b ? "true" : "false");
}

const char* toCString(const  float d)
{
    char sBuffer[256];
    sprintf(sBuffer,"%g", d);
    return string(sBuffer).c_str();
}

const char* toCString(const string& s)
{
    return s.c_str();
}

const char* toCString(const char* str)
{
    return string(str).c_str();
}

//const char* toCString(const unsigned int n, const int nBase)
//{
//    char sBuffer[256];
//    if (nBase == 16)
//    {
//        sprintf(sBuffer, "%X", n);
//        return (string("0x") + string(sBuffer)).c_str();
//    }
//    else if(nBase == 2)
//    {
//        string tmp = "";
//        int k = n;
//        for (int i=0; i<8; i++)
//        {
//            if ((k & 0x80) != 0)
//                tmp += "1";
//            else
//                tmp += "0";
//            k = k<<1;
//        }
//        return ("0b" + tmp).c_str();
//    }
//    else
//    {
//        sprintf(sBuffer, "%d", n);
//        return string(sBuffer).c_str();
//    }
//}

//const char* toCString(const int n, const int nBase)
//{
//    char sBuffer[256];
//    if (nBase == 16)
//    {
//        sprintf(sBuffer, "%X", n);
//        return (string("0x") + string(sBuffer)).c_str();
//    }
//    else if(nBase == 2)
//    {
//        string tmp = "";
//        int k = n;
//        for (int i=0; i<8; i++)
//        {
//            if ((k & 0x80) != 0)
//                tmp += "1";
//            else
//                tmp += "0";
//            k = k<<1;
//        }
//        return ("0b" + tmp).c_str();
//    }
//    else
//    {
//        sprintf(sBuffer, "%d", n);
//        return string(sBuffer).c_str();
//    }
//}

const char* toCString(const int n, const string& format, const int nBase)
{
    static char sBuffer[256];
//    if (nBase == 16)
//    {
//        sprintf(sBuffer, "%X", n);
//        return "0x" + sBuffer;
//    }
////    else if(nBase == 2)
////    {
////        string tmp = "";
////        int k = n;
////        for (int i=0; i<8; i++)
////        {
////            if ((k & 0x80) != 0)
////                tmp += "1";
////            else
////                tmp += "0";
////            k = k<<1;
////        }
////        return "0b" + tmp).c_str();
////    }
//    else
    {
        sprintf(sBuffer, "%d", n);
        return sBuffer;
    }
}

//const char* toCString(const unsigned int n, const string& format, const int nBase)
//{
//    static char sBuffer[256];
//    if (nBase == 16)
//    {
//        sprintf(sBuffer, "%X", n);
//        return "0x" + sBuffer;
//    }
//    else if(nBase == 2)
//    {
//        string tmp = "";
//        int k = n;
//        for (int i=0; i<8; i++)
//        {
//            if ((k & 0x80) != 0)
//                tmp += "1";
//            else
//                tmp += "0";
//            k = k<<1;
//        }
//        return "0b" + tmp.c_str(););
//    }
//    else
//    {
//        sprintf(sBuffer, "%d", n);
//        return sBuffer;
//    }
//}

//const char* toCString(const long n, const int nBase)
//{
//    static char sBuffer[256];
//    if (nBase == 10)
//    {
//        sprintf(sBuffer, "%lu", n);
//        return sBuffer;
//    }
//
//    //Todo: this isnt right..
//    return toCString( int(n), nBase);
//}

//const char* toCString(const unsigned long n, const int nBase)
//{
//    static char sBuffer[256];
//    if (nBase == 10)
//    {
//        sprintf(sBuffer, "%lu", n);
//        return sBuffer;
//    }
//    //Todo: this isnt right..
//    return toCString( int(n), nBase);
//}
//
//const char* toCString(const unsigned short n, const int nBase)
//{
//    static char sBuffer[256];
//    if (nBase == 10)
//    {
//        sprintf(sBuffer, "%u", n);
//        return sBuffer;
//    }
//    return toCString( int(n), nBase);
//}
//
//const char* toCString(const short n, const int nBase)
//{
//    return toCString(int(n), nBase);
//}

const char* toCString(const char n)
{
    static char sBuffer[256];
	sprintf(sBuffer, "%c", n);
	return sBuffer;
}

const char* toCString(const unsigned char n)
{
	static char sBuffer[256];
	sprintf(sBuffer, "%c", n);
	return sBuffer;
}

const char* toCString(double val, const string& format)
{
	static char sBuffer[256];
	sprintf(sBuffer, format.c_str(), val);
	return sBuffer;
}

const char* toCString(const DateTime& dt, const string& format)
{
	return Poco::DateTimeFormatter::format(dt, format).c_str();
}

//===== End of toString functions ===========

bool compareStrings(const string& str1, const string& str2, CASE_SENSITIVITY sens)
{
    if(sens == csCaseInsensitive)
    {
        return compareNoCase(str1, str2);
    }
    else
    {
        return str1 == str2;
    }
}

bool compareNoCase(const string& a, const string& b)
{
    size_t sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}

string getFormattedParStr(const string& varS, const double var, const int width)
{
    char sBuf[512];
    string fStr = "%" + toString(width) + "s = %-"  + "f";
    sprintf(sBuf, fStr.c_str(), varS.c_str(), var);
    return string(sBuf);
}

string getFormattedParStr(const string& varS, const unsigned int var, const int width)
{
    char sBuf[512];
    //sprintf(sBuf, "%30s = %-30d\n", varS.c_str(), var);
    string fStr = "%" + toString(width) + "s = %-" + "d";
    sprintf(sBuf, fStr.c_str(), varS.c_str(), var);
    return string(sBuf);
}

string getFormattedParStr(const string& varS, const int var, const int width)
{
    char sBuf[512];
    //sprintf(sBuf, "%30s = %-30d\n", varS.c_str(), var);
    string fStr = "%" + toString(width) + "s = %-"  + "d";
    sprintf(sBuf, fStr.c_str(), varS.c_str(), var);
    return string(sBuf);
}

string getFormattedParStr(const string& varS, const bool val, const int width)
{
    char sBuf[512];
    string valStr = val ? "true" : "false";
    //sprintf(sBuf, "%30s = %-30s\n", varS.c_str(), valStr.c_str());
    string fStr = "%" + toString(width) + "s = %-"  + "s";
    sprintf(sBuf, fStr.c_str(), varS.c_str(), valStr.c_str());
    return string(sBuf);
}

//string GetFormattedParStr(const string& varS, const complex<double> val, const int width)
//{
//    string cpxStr = toString(val);
//    return GetFormattedParStr(varS, cpxStr, width);
//}

string getFormattedParStr(const string& varS, const vector<int>& vec, const int width)
{
    char sBuf[64];
    string rStr = "";
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        sprintf(sBuf, "%d ", vec[i]);
        rStr += string(sBuf);
    }
    //sprintf(sBuf, "%30s = %-30s\n", varS.c_str(), rStr.c_str());
    string fStr = "%" + toString(width) + "s = %-"  + "s";
    sprintf(sBuf, fStr.c_str(), varS.c_str(), rStr.c_str());
    return string(sBuf);
}

string getFormattedParStr(const string& varS, const string& var, const int width)
{
    char sBuf[1024];
    //sprintf(sBuf, "%30s = %-30s\n", varS.c_str(), var.c_str());
    string fStr = "%" + toString(width) + "s = %-"  + "s";
    sprintf(sBuf, fStr.c_str(), varS.c_str(), var.c_str());
    return string(sBuf);
}

string format(const string& src, int arg)
{
    return substitute(src, "{0}", toString(arg));
}

string format(const string& src, const string& arg)
{
    return substitute(src, "{0}", arg);
}

string format(const string& str1, int arg1, double arg2)
{
    string token1("{0}");
    string token2("{1}");
    string newString(str1);
    newString = substitute(newString, token1, arg1);
    newString = substitute(newString, token2, arg2);
    return newString;
}

string format(const string& src, const string& arg1, const string& arg2)
{
    string tmp = substitute(src, "{0}", arg1);
    return substitute(tmp, "{1}", arg2);
}

string format(const string& src, const string& arg1, int arg2)
{
    string tmp = substitute(src, "{0}", arg1);
    return substitute(tmp, "{1}", toString(arg2));
}

string format(const string& src, const string& arg1, const string& arg2, const string& arg3)
{
    string tmp(src);
    tmp = substitute(tmp, "{0}", arg1);
    tmp = substitute(tmp, "{1}", arg2);
    tmp = substitute(tmp, "{2}", arg3);
    return tmp;
}

string format(const string& src, const string& arg1, int arg2, const string& arg3)
{
    string tmp = substitute(src, "{0}", arg1);
    tmp = substitute(tmp, "{1}", toString(arg2));
     return substitute(tmp, "{2}", arg3);
}

string format(const string& str1, const string& arg1, const string& arg2, const string& arg3, const string& arg4)
{
    string token1("{0}");
    string token2("{1}");
    string token3("{2}");
    string token4("{3}");
    string newString(str1);
    newString = substitute(newString, token1, arg1);
    newString = substitute(newString, token2, arg2);
    newString = substitute(newString, token3, arg3);
    newString = substitute(newString, token4, arg4);
    return newString;
}

string format(const string& str1, const string& arg1, const string& arg2, const string& arg3, const string& arg4, const string& arg5)
{
    string token1("{0}");
    string token2("{1}");
    string token3("{2}");
    string token4("{3}");
    string token5("{4}");
    string newString(str1);
    newString = substitute(newString, token1, arg1);
    newString = substitute(newString, token2, arg2);
    newString = substitute(newString, token3, arg3);
    newString = substitute(newString, token4, arg4);
    newString = substitute(newString, token5, arg5);
    return newString;
}

string format(const string& str1, const unsigned int& arg1, const string& arg2)
{
    string token1("{0}");
    string token2("{1}");
    string newString(str1);
    newString = substitute(newString, token1, (int) arg1);
    newString = substitute(newString, token2, arg2);
    return newString;
}

string format(const string& str1, const unsigned int& arg1, const string& arg2, const string& arg3)
{
    string token1("{0}");
    string token2("{1}");
    string token3("{2}");
    string newString(str1);
    newString = substitute(newString, token1, dsl::toString(arg1));
    newString = substitute(newString, token2, arg2);
      newString = substitute(newString, token3, arg3);
    return newString;
}

string format(const string& str1, const unsigned int& arg1, const unsigned int& arg2, const string& arg3, const string& arg4)
{
    string tok1("{0}");
    string tok2("{1}");
    string tok3("{2}");
    string tok4("{2}");
    string newString(str1);
    newString = substitute(newString, tok1, (int) arg1);
    newString = substitute(newString, tok2, (int) arg2);
    newString = substitute(newString, tok3, arg3);
    newString = substitute(newString, tok4, arg4);
    return newString;
}

string substitute(const string& src, const string& thisOne, int withThisOne, int howMany)
{
    return substitute(src, thisOne, toString(withThisOne), howMany);
}

string substitute(const string& src, const string& thisOne, double withThisOne, int howMany)
{
    return substitute(src, thisOne, toString(withThisOne), howMany);
}

string substitute(const string& src, const string& thisOne, const string& withThisOne, int howMany)
{
    string newString(src);
    int count = 0;
    while(newString.find(thisOne) != string::npos)
    {
        if(count == howMany)
        {
            break;
        }
        else
        {
            newString.replace(newString.find(thisOne), thisOne.size(), withThisOne);
            count++;
        }
    }
    return newString;
}

//double ConvertstringToDouble(const string& dbl);
//double ConvertstringToDouble(const string& s)
//{
//    //get unit;
//    int nPos = strcspn(s.c_str(), "nums");
//    char unit = s[nPos];
//
//    //get the scaling factor;
//    double dScale = 1.0;
//    switch (unit)
//    {
//        case 'n':   dScale = 1.0; break;
//        case 'u':   dScale = 1.0e3; break;
//        case 'm':   dScale = 1.0e6; break;
//        case 's':   dScale = 1.0e9; break;
//        default:
//                dScale = 1.0;
//    }
//
//    return atof(s.c_str()) * dScale;
//}

IsThisChar::IsThisChar(const char& isThis)
:
mTheChar(isThis)
{}

bool IsThisChar::operator() (const char& aChar)
{
    return (aChar == mTheChar) ? true : false;
}

ostream& operator<<(ostream& os, const vector<string>& list)
{
    for(uint i = 0; i < list.size(); i++)
    {
        os << list[i];
    }
    return os;
}

vector<string> splitStringAtWord(const string& input, const string& delimiter)
{
	std::string::size_type pos, lastPos = 0, length = input.length();
	pos = input.find(delimiter, lastPos);
    vector<string> result;
    if(pos)
    {
		result.push_back(input.substr(0, input.at(pos) ));
		result.push_back(input.substr(pos));
    }
    return result;
}

string hexCharToBinString(char c)
{
    switch(toupper(c))
    {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'A': return "1010";
        case 'B': return "1011";
        case 'C': return "1100";
        case 'D': return "1101";
        case 'E': return "1110";
        case 'F': return "1111";
        default : return "";
    }
}

int hexToDec(const string& aHex)
{
	stringstream convert(aHex);
    int val;
    convert >> std::hex >> val;
    return val;
}

std::string hexStringToBinString(const std::string& hex)
{
    std::string bin;
    for(unsigned i = 0; i != hex.length(); ++i)
    {
    	bin += hexCharToBinString(hex[i]);
    }
    return bin;
}


}

