#pragma hdrstop
#include "dslStatusBarManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

dslStatusBarManager::dslStatusBarManager(TStatusBar& theBar)
:
mStatusBar(theBar)
{}

TStatusPanel* dslStatusBarManager::AddPanel(int width, int position)
{
    TStatusPanel* newPanel = new TStatusPanel(nullptr);
    if(newPanel)
    {
        newPanel->Width = width;
        if(position)
        {
            mStatusBar.Panels->AddItem(newPanel, position);
        }
        else
        {
            mStatusBar.Panels->AddItem(newPanel, mStatusBar.Panels->Count);
        }

    }

    return newPanel ? newPanel : nullptr;
}

int dslStatusBarManager::Count()
{
    return mPanels.size();
}
