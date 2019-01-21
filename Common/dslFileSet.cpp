#pragma hdrstop
#include "dslFileSet.h"
#include "dslLogger.h"
#include "dslUtils.h"
//---------------------------------------------------------------------------

namespace dsl
{
using namespace std;
ostream& operator << (ostream& st, const FileList& fl);

FileSet::FileSet()
{}

FileSet::~FileSet()
{}

void FileSet::clearAll()
{
    for (map<FileExtension, FileList>::iterator it=mFiles.begin(); it!=mFiles.end(); ++it)
    {
        it->second.clear();
    }

    mFiles.clear();
}

FileSet::FileSet(const FileSet& fs)
:
mFiles(fs.mFiles)
{}

FileSet& FileSet::operator=(const FileSet& fs)
{
    mFiles = fs.mFiles;
    return *this;
}

bool FileSet::insert(const PocoFile& file)
{
    mFileSetMutex.lock();
    FileExtension ext = getFileExtension(file.path());
    FileList& fList = mFiles[ext];
    fList.push_back(file);
    mFileSetMutex.unlock();
    return true;
}

const FileList* FileSet::getFirstSet()
{
    mFileSetIterator = mFiles.begin();
    return getCurrentSet();
}

const FileList* FileSet::getNextSet()
{
    if(mFileSetIterator != mFiles.end())
    {
        mFileSetIterator++;
    }
    return getCurrentSet();
}

const FileList* FileSet::getCurrentSet()
{
    if(mFileSetIterator != mFiles.end())
    {
        return &(mFileSetIterator)->second;
    }
    return nullptr;
}

long FileSet::getNumberOfFiles()
{
    mFileSetMutex.lock();
    long nr = 0;

    for (map<FileExtension, FileList>::iterator it=mFiles.begin(); it!=mFiles.end(); ++it)
    {
        //Log(lInfo) << it->first << " => " << it->second << '\n';
        nr += it->second.size();
    }

    mFileSetMutex.unlock();
    return nr;
}

const PocoFile* FileSet::getFirstFile()
{
    const FileList* fl = getFirstSet();
    if(fl)
    {
        mFileIterator = fl->begin();
        return & (*mFileIterator);
    }
    else
    {
        return nullptr;
    }
}

const PocoFile* FileSet::getNextFile()
{
    mFileIterator++;
    const FileList* fl = getCurrentSet();
    if(mFileIterator == fl->end())
    {
        //Try to get next fileSet
        fl = getNextSet();
        if(fl)
        {
            mFileIterator = fl->begin();
            return & (*mFileIterator);
        }
        else
        {
            return nullptr;
        }
    }
    return & (*mFileIterator);
}

string FileSet::asString(const char& delimiter) const
{
    mFileSetMutex.lock();
    stringstream st;
    for (map<FileExtension, FileList>::const_iterator it = mFiles.begin(); it != mFiles.end(); ++it)
    {
        st << "=== Files with extension:\n"<<it->first;
        st << it->second << '\n';
    }

    mFileSetMutex.unlock();
    return st.str();
}

ostream& operator << (ostream& st, const FileSet& fs)
{
    st << fs.asString('\n');
    return st;
}

ostream& operator << (ostream& st, const FileList& fl)
{
    for (FileList::const_iterator it = fl.begin(); it != fl.end(); ++it)
    {
        st << it->path() << "\n";
    }
    return st;
}

}
