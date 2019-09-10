#pragma hdrstop
#include "dslFileUtils.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/Glob.h"
#include <Poco/DirectoryIterator.h>
#include <fstream>
#include <string>
#include <cerrno>
#include <set>
#include "Poco/Exception.h"

#if !defined(_Linux)
//#include <io.h>
#endif

#if defined(_MSC_VER)
    #include "dirent/dirent.h"
    #include <direct.h>
	#include  <io.h>
#elif defined(__BORLANDC__)
	#include <dir.h>
    #include <io.h>
    #include <dirent.h>
#elif defined(__GNUC__)
    #include <unistd.h>
    #include <sys/dir.h>
    #include <string.h>
#else
    #include <dirent.h>
#endif

#include <stdlib.h>
#include <sys/stat.h>
//#include "dslFile.h"
#include "dslUtils.h"
#include "dslStringUtils.h"
#include "dslLogger.h"
//#include "../dslCompilerSpecifics.h"
//---------------------------------------------------------------------------

namespace dsl
{
typedef unsigned int uint;
using namespace std;
using namespace Poco;

#undef CreateFile
string getFileContent(const string& fName)
{
    std::ifstream in(fName.c_str(), std::ios::in | std::ios::binary);
    if (in)
	{
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize( (unsigned int) in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return contents;
    }

    throw(errno);
}

//string getFileContent(const string& fName)
//{
//    std::ifstream t(fName.c_str());
//    std::stringstream buffer;
//    buffer << t.rdbuf();
//    return buffer.str();
//}

bool createFile(const string& fName, ios_base::openmode mode)
{
    ofstream test;
    test.open(fName.c_str(), mode);
    test.close();
    return fileExists(fName);
}

//Copy file to folder
bool copyFileToFolder(const string& srcFilePath, const string& destPath)
{
    Poco::File theFile(srcFilePath);
    Poco::File destFile(destPath);
    if(!destFile.isDirectory())
    {
        return false;
    }

    theFile.copyTo(destPath);
    return fileExists(joinPath(destPath, getFileNameNoPath(srcFilePath)));
}

//Copy file to folder
bool copyFile(const string& srcFilePath, const string& destPath)
{
    Poco::File theFile(srcFilePath);
    Poco::File destFile(destPath);

    theFile.copyTo(destPath);
    return fileExists(destPath);
}

bool clearFile(const string& file)
{
    fstream f(file.c_str(), ios::in );
    if(f)
    {
        // Yes, truncate it
        f.close();
		f.open( file.c_str(), ios::out | ios::trunc );
	}

	bool result = (f) ? true: false;
	f.close();
	return result;
}

bool saveStringToFile(const string& src, const string& fName)
{
    ofstream f(fName.c_str());
    if(f)
    {
        StringList lines(src,'\r');
        for(uint i = 0; i < lines.count(); i++)
        {
            f <<lines[i];
        }
    }
    else
    {
        Log(lError) << "Failed writing file...";
        return false;
    }
    f.close();
    return true;
}

bool checkIfDBExistsInFolder(const string& dbName,const string& folder)
{

	if(hasFileExtension(dbName)) //i.e. fName.bla or fName.db
	{
		//Check for 'unconventional' db
		return fileExists(joinPath(folder, dbName));
	}
	else
	{
		string fullName(dbName);
		fullName = fullName + ".db";
		return fileExists(joinPath(folder, fullName));
	}
}

bool removeFile(const string& fName)
{
	return (remove(fName.c_str()) == 0) ? true : false;
}

bool fileExists(const string& fName)
{
    try
    {
        if (!fName.size())
        {
            return false;
        }
        Poco::File file(fName);
        bool res = file.exists();
        return res;
    }
    catch(const Poco::PathSyntaxException& e)
    {
        Log(lError) << "The path \"" << fName << "\" is not valid: " << e.what();
        return false;
    }
}

bool folderExists(const string& folder)
{
    string f(trimBack(folder, gPathSeparator));
    struct stat St;
    return stat(f.c_str(), &St) == 0;
}

bool createFolder(const string& folder)
{
    Poco::File path(folder);
    path.createDirectories();
    return path.exists();
}

//Change this function to use POCO routines
int countFiles(const string& folder, const string& searchPattern)
{
    string search(joinPath(folder, searchPattern));

    std::set<std::string> files;
    Glob::glob(search, files); // Glob::glob("/usr/include/*/*.h", files);
    return (int) files.size();
}

StringList getFilesInFolder(const string& folder, const string& ext, bool withPath)
{
    string globPath =  joinPath(folder, "*." + ext);
    set<string> files;

    //Get all files in folder with extension ext
    Glob::glob(globPath, files, Glob::GLOB_CASELESS);

 	StringList list;
    for (set<string>::iterator it = files.begin(); it != files.end(); ++it)
    {
		string fName;
        if(withPath)
        {
    		fName = *(it);
        }
        else
        {
            fName = getFileNameNoPath(*(it));
        }
    	list.append(fName);
    }
    return list;
}

StringList getFilesInFolder(const string& folder, const string& starting_with, const string& ext, bool withPath)
{
    if(starting_with.size() == 0)
    {
        return getFilesInFolder(folder, ext, withPath);
    }

    string globPath =  joinPath(folder, starting_with + "*." + ext);
    set<string> files;

    //Get all files in folder with extension ext
    Glob::glob(globPath, files, Glob::GLOB_CASELESS);

 	StringList list;
    for (set<string>::iterator it = files.begin(); it != files.end(); ++it)
    {
		string fName;
        if(withPath)
        {
    		fName = *(it);
        }
        else
        {
            fName = getFileNameNoPath(*(it));
        }
    	list.append(fName);
    }
    return list;
}

string getLastFolderInPath(const string& p)
{
    StringList folders(p, gPathSeparator);
    if(folders.size() > 0)
    {
        return folders[folders.size() -1 ];
    }
    return gEmptyString;
}

StringList getSubFoldersInFolder(const string& folder, bool withFullPath)
{

    if(!folderExists(folder))
    {
        Log(lWarning) << "The folder: " << folder<<" do not exist.";
        return StringList("");
    }
    StringList folders;
 	DirectoryIterator end;
    for (DirectoryIterator it(folder); it != end; ++it)
    {
        if(it->isDirectory())
        {
            if(withFullPath)
            {
                folders.append(it->path());
            }
            else
            {
				folders.append(getLastFolderInPath(it->path()));
            }
        }
    }
    return folders;
}

string getHumanReadableFileSize(double sizeInBytes)
{
	char buf[32];
    int i = 0;
    const char* units[] = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
    while (sizeInBytes > 1024)
    {
        sizeInBytes /= 1024;
        i++;
    }

    sprintf(buf, "%.*f %s", i, sizeInBytes, units[i]);
    return string(buf);
}


DATA_FORMAT processDataHeader(const string& h)
{
    string header = h;
    //Check string for known tokens

//    if(header.find("[HEADER]") != std::string::npos)
//        return dslFREE_FORMAT;
    if(header.find("COMPND") != std::string::npos)
        return dfPDB;
    if(header.find("HETATM") != std::string::npos) //First line of pdb file
        return dfPDB;
    if(header.find("ATOM") != std::string::npos) //First line of pdb file
        return dfPDB;
    if(header.find("ORIG") != std::string::npos) //First line of pdb file
        return dfPDB;
    if(header.find("dfMolecule") != std::string::npos) //First line of dfMolecule file
        return dfMolecule;
    if(header.find("dfMoleculix") != std::string::npos) //First line of dslDATA file
        return dfMoleculix;
    if(header.find("dfComplex") != std::string::npos) //In first line of dslDATA (Complex) file
        return dfComplex;
//  if(header.find("dfDouble") != std::string::npos) //First line of dslDATA (Real) file
//      return dfDouble;
//  if(header.find("dslIMAGINARY") != std::string::npos) //First line of dslDATA (Real) file
//      return dslIMAGINARY;
    if(header.find("params") != std::string::npos) //First line of dfVAX_ASCII
        return dfVAX_ASCII;
    if(header.find("SIMP") != std::string::npos) //First line of simpson file
        return dfSimpson;
    if(header.find("SpinVision") != std::string::npos) //First line of simpson file
        return dfSpinVision;

    return dfText;        //The fileformat is unknown, to clients who need a format, open it as a text file
}


string getSystemTempFolder()
{
    return Path::temp();
}

}
