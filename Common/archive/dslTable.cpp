#pragma hdrstop
#include "dslIniFile.h"
#include "dslIniSection.h"
#include "dslLogger.h"
#include "dslTable.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------
namespace dsl
{
Table::Table()
{
    mTablePointer = 0;
    mDelims = " \n\t\r\f,"; //space, tab, cr, nl, formfeed
}

Table::Table(const string& fName, const string& section, const string& delim)
{
    //Read ini section and fill the table with the lines in the section
    Log(lDebug5)<<"Opening file "<<fName<<" in table object";
    mDelims = delim;
    //Check input data file
    if(!dsl::fileExists(fName))
    {
        Log(lDebug)<<"The file "<<fName<<" does not exist!";
        return;
    }
    //Get the iniSection
    IniFile iniFile(fName, true);
    IniSection* iniSection = iniFile.getSection(section);
    if(iniSection)
    {
        string sectionContent = iniSection->getNonKeysAsString();
        int chars = sectionContent.size();
        Log(lDebug5)<<"Section contain  "<< chars <<" characters";
        //Parse the section
        mTablePointer = 0;
        SetTableText(sectionContent, delim);
    }
}
Table::Table(const string& sstring, const string& sDelim)
{
    mTablePointer = 0;
    SetTableText(sstring, sDelim);
}
Table::Table(const string& sstring)
{
    mTablePointer = 0;
    mDelims = " \n\t\r\f,";
    SetTableText(sstring, mDelims);
}
Table::Table(const Table& other)
{
    if (this != &other)
    {
        mTablePointer = other.mTablePointer;
        mDelims = mDelims;
        mTheTable = other.mTheTable;
    }
}
Table& Table::operator = (const Table& other)
{
    if (this != &other)
    {
        mTablePointer = other.mTablePointer;
        mDelims = mDelims;
        mTheTable = other.mTheTable;
    }
    return *this;
}
TableRow& Table::GetEntry(int i)
{
    int nPointer = 0;
    if(mTheTable.size() > 0 )
        nPointer = i % mTheTable.size();
    return mTheTable[nPointer];
}
TableRow Table::GetEntry(int i) const
{
    int nPointer = 0;
    if(mTheTable.size() > 0)
        nPointer = i % mTheTable.size();
    return mTheTable[nPointer];
}
//double Table::GetCurrentEntryValue() const
//{
//    string s = mTheTable[mTablePointer];
//    return ConvertstringToDouble(s);
//}
void Table::SetTablePointer(int nIndex)
{
    if (mTheTable.size() != 0)
        mTablePointer = nIndex % mTheTable.size();
}
void Table::operator ++(int /*nNonsense*/)
{
    IncrementTablePointer(1);
}
void Table::operator -- (int /*nNonsense*/)
{
    DecrementTablePointer(1);
}
void Table::IncrementTablePointer(int nStep /* = 1*/)
{
    mTablePointer += nStep;
    //mod to wrap
    if(mTheTable.size() != 0)
    {
        mTablePointer %= mTheTable.size();
    }
    //wrap in the other direction
    if (mTablePointer < 0 )
    {
        mTablePointer += mTheTable.size();
    }
}
void Table::SetTableText(const string& tableText, const string& sDelim)
{
    //store the deliminator
    if(sDelim.length() > 0)
    {
        mDelims = sDelim;
    }
    else // use white space as the delimitor
    {
        mDelims = " \n\t\r\f,";
    }
    vector<string> rows = splitString(tableText,"\n");
    for(unsigned int i = 0; i < rows.size(); i++)
    {
        InsertRow(rows[i]);
    }
}
void Table::InsertRow(const string& _Row)
{
    mTheTable.push_back(TableRow(_Row, mDelims));
}
TableRow             Table::GetCurrentRow() const {return mTheTable[mTablePointer];}
TableRow&            Table::operator [] (int n)         {return GetEntry(n);}
TableRow             Table::operator [] (int n) const     {return GetEntry(n);}
void                    Table::ResetTablePointer() {mTablePointer = 0;}
void                    Table::DecrementTablePointer(int nStep){IncrementTablePointer( -nStep);}
void                    Table::operator++()     {IncrementTablePointer(1);}        //prefix
void                    Table::operator--()     {DecrementTablePointer(1);}        //prefix
void                    Table::SetTableText(const string& sString) {SetTableText(sString, mDelims);}
int                     Table::GetRowCount()        const    {return mTheTable.size();}
int                     Table::GetRowEntryCount()    const    {return GetCurrentRow().GetEntryCount();}
}
