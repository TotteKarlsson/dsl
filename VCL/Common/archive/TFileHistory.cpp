#pragma hdrstop
#include "dslVCLUtils.h"
#include "TFileHistory.h"
#include "dslStringUtils.h"

#include "dslIniSection.h"
#include "dslIniFile.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TFileHistory *FileHistory;
//---------------------------------------------------------------------------

using namespace dsl;
TFileHistory::TFileHistory(int maxItems, TMenuItem *fileMenu, TMenuItem *topSeperator)
:
mMaxHistoryItems(maxItems),
mRootMenuItem(fileMenu),
mTopSeparator(topSeperator),
mBottomSeparator(nullptr)
{}

TFileHistory::~TFileHistory()
{}


bool TFileHistory::load(IniFile* aIniFile, const string& section, OnClickHandler clickHandler)
{
    if(!aIniFile)
    {
        maintain();
        return false;
    }

    IniSection*  sec = aIniFile->getSection("PROJECT HISTORY", true);
    if(sec != nullptr && sec->keyCount() > 0)
    {
        for(unsigned int i = 0; i < sec->keyCount(); i++)
        {
            IniKey* aKey = sec->mKeys[i];
            TMenuItem* mItem = this->append(aKey->mValue);
            mItem->OnClick = clickHandler;
        }
    }

    //If no items in history, make greyed out..:w
    maintain();
    return true;
}

bool TFileHistory::save(IniFile* aIniFile, const string& section)
{
    IniSection* sec = aIniFile->getSection("PROJECT HISTORY", true);
    if(sec)
    {
        sec->clear();
         //Insert history
        for(int i = 0; i < count(); i++)
        {
            IniKey* aKey = sec->createKey("Project " + dsl::toString(i + 1));
            aKey->mValue = stdstr(getFileName(i));
        }
    }
    return true;
}

void TFileHistory::setMaxNumberOfHistoryItems(int count)
{
    mMaxHistoryItems = count;
}

int TFileHistory::getMaxNumberOfHistoryItems()
{
    return mMaxHistoryItems;
}

void TFileHistory::maintain()
{
    if(mRootMenuItem)
    {

        if(mRootMenuItem->Count > mMaxHistoryItems)
        {
            //Remove items
            rebuildHistory();

        }
        mRootMenuItem->Enabled = (mRootMenuItem->Count < 1) ? false : true;
    }
}

TMenuItem* TFileHistory::getMenuItem(int i)
{
    return (*this)[i];
}

TMenuItem* TFileHistory::getLastMenuItem()
{
    if(mRootMenuItem == nullptr)
    {
        return nullptr;
    }

    return nullptr;
}

TMenuItem* TFileHistory::operator[](int i)
{
    TMenuItem* item = nullptr;
    if(count() < 1)
    {
        return nullptr;
    }
    if(i < mRootMenuItem->Count)
    {
        return mRootMenuItem->Items[i];
    }
    return nullptr;
}

int TFileHistory::count()
{
    if(mTopSeparator != nullptr && mBottomSeparator == nullptr)
    {

    }
    else if(mTopSeparator == nullptr && mBottomSeparator != nullptr)
    {

    }
    else if(mTopSeparator != nullptr && mBottomSeparator != nullptr)
    {

    }
    else    //Both separators are nullptr
    {
        return mRootMenuItem->Count;
    }
    return 0;
}

void TFileHistory::rebuildHistory()
{
    //We need to rebuild history when new item is added or item removed
    //Mainly to update the numbers
    for(int i = 0; i < count(); i++)
    {
        TMenuItem* item = getMenuItem(i);
        if(item)
        {
            string fName = getFileName(i);
            string itemText = dsl::toString(i + 1) + " " + fName;
            item->Caption = vclstr(itemText);
        }
        if(i >= mMaxHistoryItems)
        {
            remove(item);
        }
    }
}

TMenuItem* TFileHistory::insertAtTop(const string& fName)
{
    TMenuItem *item = new TMenuItem(nullptr);
    item->Caption = vclstr(fName);
    mRootMenuItem->Insert(0, item);
    rebuildHistory();
    return item;
}

TMenuItem* TFileHistory::append(const string& caption)
{
    TMenuItem* item = nullptr;
    if(mTopSeparator != nullptr && mBottomSeparator == nullptr)
    {

    }
    else if(mTopSeparator == nullptr && mBottomSeparator != nullptr)
    {

    }
    else if(mTopSeparator != nullptr && mBottomSeparator != nullptr)
    {

    }
    else    //Both separators are nullptr
    {
        string count = dsl::toString(mRootMenuItem->Count + 1);
        string itemText = count + " " + caption;
        item = new TMenuItem(nullptr);
        item->Caption = vclstr(itemText);
        mRootMenuItem->Add(item);
    }
    return item;
}

string TFileHistory::getFileName(int i)
{
    TMenuItem* item = (*this)[i];
    if(item == nullptr)
    {
        return "";
    }


    string itemText(stdstr(item->Caption));

    //Clear leading number and space
    itemText = stripToAlpha(itemText);
    return itemText;
}

string TFileHistory::getFileName(TMenuItem* item)
{
    if(item == nullptr)
    {
        return "";
    }

    string itemText(stdstr(item->Caption));

    //Clear leading number and space
    itemText = stripToAlpha(itemText);
    return itemText;
}

bool TFileHistory::remove(TMenuItem* item)
{
    mRootMenuItem->Remove(item);
    rebuildHistory();
    return true;
}

bool TFileHistory::remove(const string& name)
{
    TMenuItem* anItem = getMenuItem(name);
    if(anItem)
    {
        mRootMenuItem->Remove(anItem);
        rebuildHistory();
        return true;
    }
    return false;
}

TMenuItem* TFileHistory::getMenuItem(const string& fName)
{
    //Find menu item with name
    for(int i = 0; i < count(); i++)
    {
        string itemName = getFileName(i);
        if(compareStrings(itemName, fName))
        {
            return getMenuItem(i);
        }
    }
    return nullptr;
}

void TFileHistory::clear()
{
    mRootMenuItem->Clear();
}
