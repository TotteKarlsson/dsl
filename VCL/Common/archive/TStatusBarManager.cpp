#pragma hdrstop
#include "TStatusBarManager.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;


TStatusBarManager::TStatusBarManager(TStatusBar& theBar)
:
mStatusBar(theBar)
{}

TStatusPanel* TStatusBarManager::getPanel(int tag)
{
	return (mPanelLookup[tag]);
}

TStatusPanel* TStatusBarManager::addPanel(int width, int tag, const string& initialText)
{
    TStatusPanel* newPanel = new TStatusPanel(NULL);

    if(newPanel)
    {
	    mPanels.push_back(newPanel);
        newPanel->Width = width;
        mStatusBar.Panels->AddItem(newPanel, mStatusBar.Panels->Count);
    	newPanel->Text = vclstr(initialText);
    }
    mPanelLookup[tag] = newPanel;
    return newPanel ? newPanel : NULL;
}

int TStatusBarManager::count()
{
    return mPanels.size();
}
