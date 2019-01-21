#ifndef dslStatusBarManagerH
#define dslStatusBarManagerH
#include <ComCtrls.hpp>
#include <list>
#include "dslObject.h"
//---------------------------------------------------------------------------

using std::list;

class PACKAGE mtkStatusBarManager : public dsl::DSLObject
{
    private:
        list<TStatusPanel*>             mPanels;

    protected:
        TStatusBar&                     mStatusBar;        //!<The statusbar to manage...

    public:
                                        mtkStatusBarManager(TStatusBar& theBar);
        TStatusPanel*                   AddPanel(int width = 150, int position = 0);
        int                             Count();
};
#endif
