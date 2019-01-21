#ifndef TStatusBarManagerH
#define TStatusBarManagerH
#include <ComCtrls.hpp>
#include <vector>
#include <map>
#include "dslObject.h"
#include "dslConstants.h"


//---------------------------------------------------------------------------

using std::vector;
using dsl::gEmptyString;
using std::map;

class PACKAGE TStatusBarManager : public dsl::DSLObject
{
    public:
                                        TStatusBarManager(TStatusBar& theBar);
        TStatusPanel*                   addPanel(int width = 150, int tag = 0, const string& initialText = gEmptyString);
        int                             count();
        TStatusPanel*					getPanel(int tag);


    protected:
        TStatusBar&                     mStatusBar;        //!<The statusbar to manage...
        vector<TStatusPanel*>        	mPanels;
        map<int, TStatusPanel*>			mPanelLookup;
};
#endif
