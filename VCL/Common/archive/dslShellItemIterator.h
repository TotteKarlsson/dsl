#ifndef dslShellItemIteratorH
#define dslShellItemIteratorH
#include <System.hpp>
#include <shlobj.h>             // shell stuff
class PACKAGE mtkShellItemIterator
{
    private:
        void                 _Init();
        HRESULT             _hr;
        PIDLIST_ABSOLUTE     _pidlFull;
        PUIDLIST_RELATIVE     _pidlRel;
        IShellFolder        *_psfCur;

    public:
                            mtkShellItemIterator(IShellItem *psi);
                            mtkShellItemIterator(PCIDLIST_ABSOLUTE pidl);
                           ~mtkShellItemIterator();
    bool                     MoveNext();
    HRESULT                 GetCurrent(REFIID riid, void **ppv);
    HRESULT                 GetResult() const ;
    PCUIDLIST_RELATIVE         GetRelativeIDList() const ;
};


#endif
