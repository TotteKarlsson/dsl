
#pragma hdrstop
#include "dslShellItemIterator.h"
#include "dslShellHelpers.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void dslShellItemIterator::_Init()
{
    _pidlRel = nullptr;

    if (SUCCEEDED(_hr))
    {
        _hr = SHGetDesktopFolder(&_psfCur);
    }
}

dslShellItemIterator::dslShellItemIterator(IShellItem *psi)
:
_hr(SHGetIDListFromObject(psi, &_pidlFull)),
_psfCur(nullptr)
{
    _Init();
}

dslShellItemIterator::dslShellItemIterator(PCIDLIST_ABSOLUTE pidl)
:
_hr(SHILCloneFull(pidl, &_pidlFull)),
_psfCur(nullptr)
{
    _Init();
}

dslShellItemIterator::~dslShellItemIterator()
{
    CoTaskMemFree(_pidlFull);
    SafeRelease(&_psfCur);
}

bool dslShellItemIterator::MoveNext()
{
    bool fMoreItems = false;

    if (SUCCEEDED(_hr))
    {
        if (nullptr == _pidlRel)
        {
            fMoreItems = true;
            _pidlRel = _pidlFull;   // first item, might be empty if it is the desktop
        }
        else if (!ILIsEmpty(_pidlRel))
        {
            PCUITEMID_CHILD pidlChild = (PCUITEMID_CHILD)_pidlRel;  // save the current segment for binding
            _pidlRel = ILNext(_pidlRel);

            // if we are not at the end setup for the next itteration
            if (!ILIsEmpty(_pidlRel))
            {
                const WORD cbSave = _pidlRel->mkid.cb;  // avoid cloning for the child by truncating temporarily
                _pidlRel->mkid.cb = 0;                  // make this a child

                IShellFolder *psfNew;
                _hr = _psfCur->BindToObject(pidlChild, nullptr, IID_PPV_ARGS(&psfNew));
                if (SUCCEEDED(_hr))
                {
                    _psfCur->Release();
                    _psfCur = psfNew;   // transfer ownership
                    fMoreItems = true;
                }

                _pidlRel->mkid.cb = cbSave; // restore previous ID size
            }
        }
    }
    return fMoreItems;
}

HRESULT dslShellItemIterator::GetCurrent(REFIID riid, void **ppv)
{
    *ppv = nullptr;
    if (SUCCEEDED(_hr))
    {
        // create teh childID by truncating _pidlRel temporarily
        PUIDLIST_RELATIVE pidlNext = ILNext(_pidlRel);
        const WORD cbSave = pidlNext->mkid.cb;  // save old cb
        pidlNext->mkid.cb = 0;                  // make _pidlRel a child

        _hr = SHCreateItemWithParent(nullptr, _psfCur, (PCUITEMID_CHILD)_pidlRel, riid, ppv);

        pidlNext->mkid.cb = cbSave;             // restore old cb
    }
    return _hr;
}

HRESULT dslShellItemIterator::GetResult() const
{
    return _hr;
}

PCUIDLIST_RELATIVE dslShellItemIterator::GetRelativeIDList() const
{
    return _pidlRel;
}




