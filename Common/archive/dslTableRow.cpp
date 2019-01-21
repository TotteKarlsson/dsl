#pragma hdrstop
#include "dslFileUtils.h"
#include "dslIniFile.h"
#include "dslIniSection.h"
#include "dslLogger.h"
#include "dslTableRow.h"
//---------------------------------------------------------------------------
namespace dsl
{

TableRow::TableRow()
{
    mTablePointer = 0;
    mEntryCount = 0;
    mDelims = " \n\t\r\f,"; //space, tab, cr, nl, formfeed
}

TableRow::TableRow(const string& fName, const string& section, const string& delim)
{
    //Read ini section and fill the table with the lines in the section
    Log(lDebug)<<"Opening file: " + fName;
    mDelims = delim;
    //Check input data file
    if(!dsl::fileExists(fName))
    {
        Log(lDebug)<<("The file " + fName + " does not exist!?");
        return;
    }
    //Get the iniSection
    IniFile iniFile(fName, true);
    IniSection* iniSection = iniFile.getSection(section);
    if(iniSection)
    {
        string sectionContent = iniSection->getNonKeysAsString();
        int lineSize = sectionContent.size();
        Log(lDebug)<<"Section size: "<< lineSize;
        //Parse the section
        mTablePointer = 0;
        mEntryCount = 0;
        SetTableText(sectionContent, delim);
    }
}

TableRow::TableRow(const string& sstring, const string& sDelim)
{
    mTablePointer = 0;
    mEntryCount = 0;
    SetTableText(sstring, sDelim);
}

TableRow::TableRow(const string& sstring)
{
    mTablePointer = 0;
    mEntryCount = 0;
    mDelims = " \n\t\r\f,"; //space, tab, cr, nl, formfeed
    SetTableText(sstring, mDelims);
}
TableRow::TableRow(const TableRow& other)
{
    if (this != &other)
    {
        mTablePointer = other.mTablePointer;
        mEntryCount = other.mEntryCount;
        mEntryText = other.mEntryText;
        mDelims = mDelims;
        mTableRow = other.mTableRow;
    }
}

TableRow& TableRow::operator = (const TableRow& other)
{
    if (this != &other)
    {
        mTablePointer = other.mTablePointer;
        mEntryCount = other.mEntryCount;
        mEntryText = other.mEntryText;
        mDelims = mDelims;
        mTableRow = other.mTableRow;
    }
    return *this;
}

string& TableRow::GetEntry(int i)
{
    int nPointer = 0;
    if(mEntryCount >0 )
        nPointer = i % mEntryCount;
    return mTableRow[nPointer];
}

string TableRow::GetEntry(int i) const
{
    int nPointer = 0;
    if(mEntryCount > 0)
        nPointer = i % mEntryCount;
    return mTableRow[nPointer];
}

void TableRow::SetTablePointer(int nIndex)
{
    if (mEntryCount != 0)
        mTablePointer = nIndex % mEntryCount;
}

void TableRow::operator ++(int nNonsense)
{
    nNonsense = nNonsense;
    IncrementTablePointer(1);
}

void TableRow::operator -- (int nNonsense)
{
    nNonsense = nNonsense;
    DecrementTablePointer(1);
}

void TableRow::IncrementTablePointer(int nStep /* = 1*/)
{
    mTablePointer += nStep;
    //mod to wrap
    if (mEntryCount != 0)
        mTablePointer %= mEntryCount;
    //wrap in the other direction
    if (mTablePointer < 0 ) mTablePointer += mEntryCount;
}

void TableRow::SetTableText(const string& sstring, const string& sDelim)
{
    //store the string
    mEntryText = sstring;
    //store the deliminator
    if(sDelim.length() > 0)
    {
        mDelims = sDelim;
    }
    else // use white space as the delimitor
    {
        mDelims = " \n\t\r\f,";
    }
    ParseText();
}

void TableRow::ParseText()
{
    mTablePointer = 0;
    mEntryCount = CountEntries();
    mTableRow.resize(mEntryCount);
    const int bIsDelim = 1;
    int bOld=bIsDelim;
    int bNew=0;
    int nCount = 0;
    int nLength = mEntryText.length();
    int i = 0;
    int nBegin=0;
    int nEnd =0;
    char c;
    while(i < nLength)
    {
        c = mEntryText[i];
        if (IsDelimiter(c))
        {
            bNew = bIsDelim;
        }
        else
        {
            bNew = 0;
        }
        if (bNew != bIsDelim && bOld == bIsDelim)
        {
            //we got the beginning
            nBegin = i;
            //step forward to get rid of white spaces at the front
            c = mEntryText[nBegin];
            while (nBegin < nLength && (isspace(c) || IsDelimiter(c)) )
            {
                nBegin++;
                i++;
                c = mEntryText[nBegin];
            }
            //now we find the end
            while ((i < nLength ) && !IsDelimiter(mEntryText[i]) )//while delimitor is not found
            {
                i++;
            }
            //backup to get rid of white spaces at the end
            i--;
            nEnd = i;
            while( (nEnd > 0) && isspace(mEntryText[nEnd]) )
            {
                nEnd--;
            }
            if(nEnd >= nBegin)
            {
                mTableRow[nCount] = string(mEntryText, nBegin, nEnd - nBegin+1);
                nCount++;
            }
            if(i < nLength)
            {
                c = mEntryText[i];
                if (IsDelimiter(c))
                {
                    bNew = bIsDelim;
                }
                else
                {
                    bNew = 0;
                }
            }
        }
        bOld = bNew;
        i++;
    }
    mEntryCount = nCount;
}

//Count the number of elements in the string, it may over count by 1;
int TableRow::CountEntries()
{
    int const bIsDelim = 1;
    int  bNew   = 0;
    int  bOld   = bIsDelim;
    int nCount  = 0;
    int nLength = mEntryText.length();
    char c;
    for (int i=0; i<nLength; i++)
    {
        c = mEntryText[i];
        if (IsDelimiter(c))
            bNew =bIsDelim;
        else bNew = 0;
        //the follwing two condition is just to make sure that two delimitor is couted as one
        if (bNew != bIsDelim && bOld == bIsDelim )
            nCount++;
        bOld = bNew;
    }
    return nCount;
}

bool TableRow::IsDelimiter(char c)
{

    for (int i=0; i< int(mDelims.length()); i++)
    {
        if (c == mDelims[i])
        {
            return true;
        }
    }
    return false;
}

int TableRow::GetEntryCount()            const    {return mEntryCount;}
string TableRow::GetCurrentEntry() const {return mTableRow[mTablePointer];}
string& TableRow::operator [] (int n)         {return GetEntry(n);}
string TableRow::operator [] (int n) const     {return GetEntry(n);}
void TableRow::ResetTablePointer() {mTablePointer = 0;}
void TableRow::DecrementTablePointer(int nStep){IncrementTablePointer( -nStep);}
void TableRow::operator++()     {IncrementTablePointer(1);}        //prefix
void TableRow::operator--()     {DecrementTablePointer(1);}        //prefix
void TableRow::SetTableText(const string& sString) {SetTableText(sString, mDelims);}
string TableRow::GetRow()                        {return mEntryText;}
int TableRow::GetCurrentRowPosition()    const    {return mTablePointer;}
}
