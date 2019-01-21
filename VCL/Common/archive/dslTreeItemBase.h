#ifndef dslTreeItemBaseH
#define dslTreeItemBaseH
#include <System.hpp>
#include <string>
#include "dslObject.h"
using std::string;
//---------------------------------------------------------------------------
class PACKAGE mtkTreeItemBase
{
    protected:
        unsigned int     mID;              // unique ID
        string             mLabel;          // reflects node label
        bool             mDeleted;        // used for soft deletes
        int                mIconIndex;
        int                mIconSelectedIndex;
        bool            mIsRoot;

    public:
                        mtkTreeItemBase(const string& label = "tree_item", const bool& isRoot = false);
        virtual        ~mtkTreeItemBase();
        unsigned int    GetID();
        string            GetLabel();
        void            SoftDelete(bool what);
        bool            SoftDelete();
        int                GetIconIndex();
        int                GetIconSelectedIndex();
};

typedef mtkTreeItemBase* PTreeItemBase;
#endif
