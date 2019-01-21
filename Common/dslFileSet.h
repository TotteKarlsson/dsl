#ifndef dslFileSetH
#define dslFileSetH
#include "Poco/Mutex.h"
#include "dslObject.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include <list>
#include <map>

//---------------------------------------------------------------------------

namespace dsl
{

using std::list;
using std::map;
using Poco::Path;
//using Poco::File;
using Poco::Mutex;

typedef Poco::File PocoFile;
typedef list<PocoFile> FileList;
typedef string FileExtension;


DSL_COMMON ostream& operator << (ostream& st, const FileList* fl);

class DSL_COMMON FileSet : public DSLObject
{
    public:
                                                    FileSet();
                                                   ~FileSet();
                                                    FileSet(const FileSet& fs);
        FileSet&                                    operator=(const FileSet& fs);
        void                                        clearAll();
        bool                                        insert(const PocoFile& file);
        long                                        getNumberOfFiles();
        const FileList*                             getFirstSet();  //Rename to FirstFileList etc..
        const FileList*                             getNextSet();
        const FileList*                             getCurrentSet();

        const PocoFile*                             getFirstFile();
        const PocoFile*                             getNextFile();

        friend
        DSL_COMMON ostream&                         operator << (ostream& stream, const FileSet& fs);

	protected:
        map<FileExtension, FileList>                mFiles;
        mutable Poco::Mutex                         mFileSetMutex;

        map<FileExtension, FileList>::iterator      mFileSetIterator;
        FileList::const_iterator                    mFileIterator;
        string                                      asString(const char& delimiter) const;
};

}
#endif
