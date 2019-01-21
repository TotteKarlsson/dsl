#ifndef dslFileFinderH
#define dslFileFinderH
#include <string>
#include <vector>
#include <system.hpp>
#include "VCLCommonExporter.h"

using namespace std;
//---------------------------------------------------------------------------
class PACKAGE mtkFileFinder
{
    private:
        String                  rootFolder;
        bool                    searchSubFolders;
        String                  fileMask;
        void                    FindFilesInDirectory(const String &directory, const String& Extension);
        vector<string>          fileList;

    public:
                                mtkFileFinder();
                                ~mtkFileFinder(){}
        void                    SetRoot(const String& fileRoot);
        string                  GetRoot();
        void                    SetFileMask(const String& mask){fileMask = mask;}
        void                    DoSearch();
        bool                    SearchSubFolder(){return searchSubFolders;}
        void                    SearchSubFolders(bool search){searchSubFolders = search;}
        int                     NrOfFiles(){return fileList.size();}
        string                  FileNr(int i){return fileList[i];}
};
#endif
