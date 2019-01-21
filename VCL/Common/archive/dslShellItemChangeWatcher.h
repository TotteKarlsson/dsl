#ifndef dslShellItemChangeWatcherH
#define dslShellItemChangeWatcherH
#include <string>
using std::string;
//---------------------------------------------------------------------------

/* This class encapsulates the registration and dispatching of shell change notification events
         To use this class:
         1) Derive a class from this class. The derived class will implement the virtual
            method OnChangeNotify() that is called when the events occur.

         2) Create an HWND and designate a message (in the WM_USER range) that will be used to
            dispatch the events. This HWND and MSG is passed to StartWatching() along with the
            item you want to watch.

         3) In your window procedure, on receipt of the notification message, call OnChangeMessage().

         4) Declare and implement OnChangeNotify() and write the code there that handles the events.
-------------------------------------------------------------------------------------------------------*/

class PACKAGE mtkShellItemChangeWatcher
{
    protected:
        ULONG               mRegistrationID;
        bool                IsItemNotificationEvent(long lEvent);

    public:
                            mtkShellItemChangeWatcher();
                           ~mtkShellItemChangeWatcher();
        bool                IsWatching();

                            // lEvents is SHCNE_XXX values like SHCNE_ALLEVENTS
                            // fRecursive means to listen for all events under this folder
        virtual HRESULT     StartWatching(PIDLIST_ABSOLUTE pidl, HWND hwnd, UINT uMsg, long lEvents, BOOL fRecursive);
        virtual void        StopWatching();

                            // In your window procedure call this message to dispatch the events
        void                OnChangeMessage(WPARAM wParam, LPARAM lParam);

                            // Derived class implements this event
        virtual void        OnChangeNotify(long lEvent, const string& path1, const string& path2) = 0;
};

#endif
