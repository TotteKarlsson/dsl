#pragma hdrstop
#include "dslIniSectionFrame.h"
#include "dslVCLUtils.h"
#include "dslTSTDStringLabeledEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTFloatLabeledEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma resource "*.dfm"
TIniSectionFrame *IniSectionFrame;

using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TIniSectionFrame::TIniSectionFrame(IniSection* section, TComponent* Owner)
	: TFrame(Owner),
    mSection(section)
{
    SectionGB->Caption = mSection->mName.c_str();

    for(int i = 0; i < mSection->keyCount(); i++)
    {
        IniKey* aKey = mSection->getKey(i);
        addKey(aKey);
    }
}

__fastcall TIniSectionFrame::~TIniSectionFrame()
{}

void  TIniSectionFrame::write()
{
    list<TLabeledPropertyEdit*>::iterator it;
    it = mEdits.begin();
    while(it != mEdits.end())
    {
    	TLabeledPropertyEdit* edit = *it;
        if(edit)
        {
            edit->getProperty()->write(const_cast<IniFile*>(mSection->getIniFile()), mSection->mName);
        }
        ++it;
    }
}

void TIniSectionFrame::addKey(IniKey* key)
{
    TPanel* aPanel = new TPanel(this);
    aPanel->Caption = "";

	TLabeledPropertyEdit* edit;

    if(key && key->mComment == "integer")
    {
	    edit = new TIntegerLabeledEdit(aPanel);
    }
    else if(key && key->mComment == "double")
    {
        edit = new TFloatLabeledEdit(aPanel);
        TFloatLabeledEdit* fe(dynamic_cast<TFloatLabeledEdit*>(edit));
        fe->NrOfDecimals = 10;
    }
    else if(key && key->mComment == "string")
    {
        edit = new TSTDStringLabeledEdit(aPanel);
    }

    edit->setValueFromString(key->mValue);
    edit->getProperty()->setLabel(key->mKey);
    edit->getProperty()->setComment(key->mComment);
    edit->EditLabel->Caption = vclstr(key->mKey);
    edit->Parent = aPanel;
    edit->Align = alBottom;
    aPanel->Parent = FlowPanel;
    mEdits.push_back(edit);
}

