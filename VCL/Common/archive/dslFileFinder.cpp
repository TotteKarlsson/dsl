
#pragma hdrstop
#include <StrUtils.hpp>
#include "dslVCLUtils.h"
#include "dslFileFinder.h"
#include "dslStringUtils.h"
#pragma package(smart_init)

using namespace dsl;

bool isDirectory(const string& path);

dslFileFinder::dslFileFinder()
{
    rootFolder = "c:\\";
    fileMask = "*.JPG";
    searchSubFolders = false;
}

void dslFileFinder::SetRoot(const String& fileRoot)
{
    rootFolder = fileRoot;
}

void dslFileFinder::DoSearch()
{
    fileList.clear();
    
    FindFilesInDirectory(rootFolder, fileMask);

    //Remove any items "." and ".." (gets there when searching for "*"
    for(int i = 0; i < fileList.size(); i++)
    {
        String aStr = fileList[i].c_str();
        if(AnsiEndsStr(".", aStr) == true || AnsiEndsStr("..", aStr) == true)
        {
            fileList.erase(fileList.begin() + i);
            i = 0;
        }

        if(isDirectory(stdstr((char*) aStr.c_str())))
        {
            fileList.erase(fileList.begin() + i);
            i = 0;
        }
    }
}

void dslFileFinder::FindFilesInDirectory(const String &directory, const String& Extension)
{
    // This method searches the directory specified by the parameter and all
    // of its subdirectories for the file matching the value in SearchCustomEdit.
    // The directory name is assumed to end with a backslash.

    WIN32_FIND_DATA filedata ;  // Structure for file data
    HANDLE filehandle ;         // Handle for searching

    // Pass 1 - Search for the files within the directory.
    filehandle = FindFirstFile ((directory + Extension).c_str (), &filedata);
    if (filehandle != INVALID_HANDLE_VALUE)
    {
        do
        {
            String fName = String (directory) + (String (filedata.cFileName)) ;
            fileList.push_back(fName.c_str());
//            Application->ProcessMessages();

        } while (FindNextFile (filehandle, &filedata));
        FindClose (filehandle) ;
    }

    // Pass 2 - Search for all the subdirectories within this directory
    if(searchSubFolders)
    {
        String dir = directory + "*.*" ;
        filehandle = FindFirstFile ((directory + "*.*").c_str (), &filedata) ;
        if (filehandle != INVALID_HANDLE_VALUE)
        {
          do
          {
            if ((filedata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0
                 && String (filedata.cFileName) != "."
                 && String (filedata.cFileName) != "..")
            {
              // Recursive call here
              FindFilesInDirectory(directory + filedata.cFileName + "\\", Extension);
            }

//            Application->ProcessMessages () ;
          } while (FindNextFile (filehandle, &filedata)) ;
          FindClose (filehandle) ;
        }
    }

//    Application->ProcessMessages();
    return;
}

bool isDirectory(string &path)
{
    DWORD dw =  GetFileAttributes(path.c_str());
    return ( dw != 0xffffffff  &&  dw & FILE_ATTRIBUTE_DIRECTORY);
}


