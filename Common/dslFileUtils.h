#ifndef dslFileUtilsH
#define dslFileUtilsH
#include "dslObject.h"
#include "dslConstants.h"
#include "dslStringList.h"
#include <fstream>
#include <iostream>
#include <string>
//---------------------------------------------------------------------------

namespace dsl
{

#undef CreateFile

DSL_COMMON fstream*             openFile(const string& FileName, const FILE_FORMAT& type = ffASCII, const FILEINOUT& outIn = mtkIn);
DSL_COMMON bool                 createFile(const string& fName, ios_base::openmode = ios::trunc);
DSL_COMMON bool                 copyFile(const string& fName, const string& destPath);
DSL_COMMON bool                 copyFileToFolder(const string& fName, const string& destPath);
DSL_COMMON bool                 removeFile(const string& fName);
DSL_COMMON bool                 clearFile(const string& fName);
DSL_COMMON bool                 closeFile(fstream *file);
DSL_COMMON bool                 fileExists(const string& fileN);
DSL_COMMON bool                 saveStringToFile(const string& str, const string& fName);
DSL_COMMON StringList        	getFilesInFolder(const string& folder, const string& fileExtension, bool withPath = true);
DSL_COMMON StringList        	getFilesInFolder(const string& folder, const string& startingWith, const string& fileExtension, bool withPath = true);
DSL_COMMON StringList        	getSubFoldersInFolder(const string& folder, bool withFullPath = false);
DSL_COMMON string				getLastFolderInPath(const string& p);
DSL_COMMON string				getSecondToLastFolderInPath(const string& p);

DSL_COMMON DATA_FORMAT          processDataHeader(const string& h);
DSL_COMMON bool                 folderExists(const string& folder);
DSL_COMMON bool                 createFolder(const string& folder);
DSL_COMMON int                  countFiles(const string& folder, const string& extension);
DSL_COMMON bool                 checkIfDBExistsInFolder(const string& dbName,const string& folder);
DSL_COMMON string               getFileContent(const string& fName);
DSL_COMMON string				getHumanReadableFileSize(double sizeInBytes);
DSL_COMMON double 				getFileSize(const string& file, FileSizeType type);



/*** Get The current directory including the driveletter ***/
DSL_COMMON string               intToDriveLetter(int Number);
DSL_COMMON string               getSystemTempFolder();
}
#endif
