#pragma hdrstop
#include "dslFileInfo.h"
//---------------------------------------------------------------------------
namespace dsl
{

FileInfo::FileInfo(const DATA_FORMAT& dF, const FILE_FORMAT& fF)
{
  mDataFormat = dF;
  mFileFormat = fF;
}

FileInfo& FileInfo::operator = (const FileInfo& fN)
{
  mDataFormat = fN.GetDataFormat();
  mFileFormat = fN.GetFileFormat();
  return *this;
}

void FileInfo::SetDataFormat(const DATA_FORMAT& dF)
{
    mDataFormat = dF;
}

DATA_FORMAT FileInfo::GetDataFormat() const
{
    return mDataFormat;
}

void FileInfo::SetFileFormat(const FILE_FORMAT& fF)
{
    mFileFormat = fF;
}

FILE_FORMAT FileInfo::GetFileFormat() const
{
    return mFileFormat;
}

}
