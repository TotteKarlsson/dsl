#pragma hdrstop
#include <cstring>
#include "dslFileUtils.h"
#include "dslStringUtils.h"
#include "dslFile.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
namespace dsl
{

int File::mNrOfFiles = 0;

File::File(const string& _fName, const DATA_FORMAT& dF, const FILE_FORMAT& fF)
:
mFileName(_fName),
mFileInfo(dF,fF)
{
    Log(lDebug)<<"The File "<<_fName<<" is being constructed."<<endl;
    mNrOfFiles++;
}

File::File(const File& fN)
{
    Log(lDebug)<<"The File "<<fN.GetNameAndPath()<<" is being constructed";
    mFileName.SetFileNameAndPath(fN.GetNameAndPath());
    mFileInfo = fN.GetFileInfo();
    mNrOfFiles++;
}

File::~File()
{
    if(mFileStream.is_open())
    {
        mFileStream.close();
        if(mFileStream.fail())
        {
            Log(lDebug)<<"The File "<<GetNameAndPath()<<" is BAD."<<endl;
        }
        else
        {
            Log(lDebug)<<"The File "<<GetNameAndPath()<<" was closed."<<endl;
        }
    }

    bool isOpen = mFileStream.is_open();

    if(isOpen)
    {
        Log(lDebug)<<"The File "<<GetNameAndPath()<<" could not be closed.";
    }
    else
    {
        Log(lDebug)<<"The File "<<GetNameAndPath()<<" is being destructed.";
    }

    mNrOfFiles--;
}

File& File::operator = (const File* fN)
{
    mFileName.SetFileNameAndPath(fN->GetNameAndPath());
      mFileInfo = fN->GetFileInfo();
      return *this;
}

File& File::operator = (const File& fN)
{
    mFileName.SetFileNameAndPath(fN.GetNameAndPath());
      mFileInfo = fN.GetFileInfo();
      return *this;
}

File& File::operator=(const string& fN)
{
    mFileName.SetFileName(fN);
      return *this;
}

bool File::operator!=(const char* fN)
{
    return (mFileName.GetFileName() != string(fN));
}

File::operator char() const
{
      char str;
    strcpy(&str, mFileName.GetFileName().c_str());
    return str;
}

bool File::Open(const FILE_FORMAT& fF, const FILEINOUT& InOut)
{
    mFileInfo.SetFileFormat(fF);
    string fName = GetNameAndPath();
    switch(InOut)
    {
        case dslOut:
            switch(mFileInfo.GetFileFormat())
            {
                case ffASCII:
                    mFileStream.open(GetNameAndPath().c_str(), ios_base::trunc|ios_base::out);
                break;
                case ffBINARY:
                    mFileStream.open(fName.c_str(), ios_base::trunc|ios_base::out|ios::binary);
                break;
            }
        break;
        case dslIn:
            switch(mFileInfo.GetFileFormat())
            {
                case ffASCII:
                    mFileStream.open(GetNameAndPath().c_str());
                break;
                case ffBINARY:
                       mFileStream.open(GetNameAndPath().c_str(), ios_base::in|ios::binary);
                break;
            }
    break;
    }
    bool isOpen = mFileStream.is_open();
    if(!isOpen)
    {
        Log(lDebug)<<"The File "<<GetNameAndPath()<<" was NOT opened."<<endl;
    }
    else
    {
        Log(lDebug)<<"The File "<<GetNameAndPath()<<" was opened."<<endl;
    }
      return isOpen;
}

bool File::IsOpen() const
{
    return mFileStream.is_open();
}

bool File::Close()
{
    mFileStream.close();
    bool isOpen = mFileStream.is_open();
    if(isOpen)
    {
        Log(lDebug)<<"The File "<<GetNameAndPath()<<" was NOT closed.";
    }
    else
    {
        Log(lDebug)<<"The File "<<GetNameAndPath()<<" was closed.";
    }
    return !isOpen;
}

string File::GetNameAndPath() const
{
    return mFileName.GetPathAndFileName();
}

FileInfo File::GetFileInfo() const
{
      return FileInfo(mFileInfo);
}

void File::Set(const File& fN)
{
    mFileName.SetFileNameAndPath(fN.GetNameAndPath());
    mFileInfo.SetDataFormat(fN.GetFileInfo().GetDataFormat());
    mFileInfo.SetFileFormat(fN.GetFileInfo().GetFileFormat());
}

void File::SetFileName(const string& name)
{
    //Check if there is a path
    mFileName = name;
    SetFileNameAndPath(name);
}

void File::SetFileNameAndPath(const string& fNS)
{
    mFileName.SetFileNameAndPath(fNS);
}

string File::GetFileName() const
{
      return mFileName.GetFileName();
}

void File::SetPath(const string& path)
{
    mFileName.SetPath(path);
}

string File::GetPath() const
{
    return mFileName.GetPath();
}

void File::SetDataFormat(const DATA_FORMAT& dFormat)
{
    mFileInfo.SetDataFormat(dFormat);
}

DATA_FORMAT   File::GetDataFormat() const
{
    return mFileInfo.GetDataFormat();
}

void File::SetFileFormat(const FILE_FORMAT& dFormat)
{
    mFileInfo.SetFileFormat(dFormat);
}

FILE_FORMAT File::GetFileFormat() const
{
    return mFileInfo.GetFileFormat();
}

bool File::CheckFile()
{
  if(mFileName.GetFileName().empty())
  {
      if(fileExists(mFileName.GetPathAndFileName()))
        return true;
  }
    return false;
}

string File::RegistryString() const
{
    string rStr = mFileName.GetFileName()
                    + ","
                    + dataFormatToStr(mFileInfo.GetDataFormat())
                    + ","
                    + fileFormatToStr(mFileInfo.GetFileFormat())
                    + "\0";
    return rStr;
}

bool File::ReadLines(vector<string>& lines)
{
    //Read line be line into a vector of strings
    vector<string> theFile;
    if(!IsOpen())
    {
        return false;
    }
    char line_buffer[1024];

    //Make sure the file is at the beginning
    mFileStream.seekg(0, ios::beg);
      while (! mFileStream.eof() )
      {
        mFileStream.getline (line_buffer,1024);
        lines.push_back(line_buffer);
    }
    return true;
}

fstream* File::PStream()
{
    return &mFileStream;
}

fstream& File::Stream()
{
    return mFileStream;
}

}
