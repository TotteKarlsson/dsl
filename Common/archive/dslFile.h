#ifndef dslFileH
#define dslFileH
#include "dslFileInfo.h"
#include "dslFileName.h"
#include "dslFileUtils.h"
#include "dslObject.h"
#include "dslCommonExporter.h"
#include <string>
#include <vector>
#include <fstream>
//---------------------------------------------------------------------------

namespace dsl
{

using std::fstream;
using std::vector;
class File;

//This should be deprecated..
DSL_COMMON bool                 openFile(File* file, const FILEINOUT& outIn = mtkIn);
DSL_COMMON bool                 fileExists(const File* file);
DSL_COMMON bool                 fileExists(const File& file);
DSL_COMMON DATA_FORMAT          getDataFormat(File* file);

class DSL_COMMON File : public DSLObject
{
    public:
										File(const string& astr = gEmptyString, const DATA_FORMAT& dF = dfMoleculix, const FILE_FORMAT& fF = ffASCII);
										File(const File& fN);
									    ~File();
        File&                           operator=(const File* fN);
        File&                           operator=(const File& fN);
        File&                           operator=(const string& fN);
        File&                           operator=(const char* fN);
        void							Set(const File& fN);

        bool				            operator!=(const char* fN);
        operator						char() const;
        FileInfo                     	GetFileInfo() const;
        string                          GetFileName() const;
        string                          GetPath() const;
        string                          GetNameAndPath() const;

        void                            SetFileName(const string& name);
        void                            SetFileNameAndPath(const string& fN);
        void                            SetPath(const string& p);

		DATA_FORMAT  					GetDataFormat() const;
        void      						SetDataFormat(const DATA_FORMAT& dFormat);
   		FILE_FORMAT					    GetFileFormat() const;
        void                            SetFileFormat(const FILE_FORMAT& dFormat);
        bool                            Open(const FILE_FORMAT& fF = ffASCII, const FILEINOUT& InOut = mtkIn);
        bool                            Close();
        fstream*                        PStream();
        fstream&                        Stream();
        bool                            IsOpen() const;
        string                          RegistryString() const;
        bool                            ReadLines(vector<string>& lines);

    private:
        static int						mNrOfFiles;
        FileName  						mFileName;
        FileInfo  						mFileInfo;
        fstream   						mFileStream;
        bool      						CheckFile();
};

}
#endif
