#pragma hdrstop
#include <vcl.h>
#include "dslTrayIcon.h"
#include "dslTrayIcon.rh"
#include "dslPackageDefs.h"
#pragma package(smart_init)
//#pragma resource "*.res"

//---------------------------------------------------------------------------
__fastcall dslTrayIcon::dslTrayIcon(TComponent* Owner)
   : TComponent(Owner)
{
   FIcon    = new TIcon();
   FTimer   = new TTimer(nullptr);

   FIconIndex = 0;
   FIcon->Assign(Application->Icon);
   FAppRestore      = imDoubleClick;
   FOnAnimate       = DoOnAnimate;
   FPopupMenuShow   = imNone;
   FVisible         = false;
   FHide            = true;
   FTimer->Enabled  = false;
   FTimer->OnTimer  = OnAnimate;
   FTimer->Interval = 1000;

   if (!ComponentState.Contains(csDesigning))
   {
      memset(&FData, 0, sizeof(NOTIFYICONDATA));
      FData.cbSize = sizeof(NOTIFYICONDATA);
      FData.hWnd = AllocateHWnd(DoMessage);
      FData.uID = (UINT)this;
      FData.hIcon = FIcon->Handle;
      FData.uFlags = NIF_ICON | NIF_MESSAGE;
      FData.uCallbackMessage = WM_SYSTEM_TRAY_NOTIFY;

      FApplicationHook = ApplicationHookProc;
      Update();
   }
}

//---------------------------------------------------------------------------
__fastcall dslTrayIcon::~dslTrayIcon()
{
    if (!ComponentState.Contains(csDesigning))
    {
        Shell_NotifyIcon(NIM_DELETE, &FData);
        DeallocateHWnd(FData.hWnd);
    }

    if (FIcon)
        delete FIcon;

    if (FTimer)
        delete FTimer;
    Update();
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::Notification(TComponent *AComponent, TOperation Operation)
{
    TComponent::Notification(AComponent, Operation);

    if (Operation == opRemove)
    {
        if (AComponent == FIconList)
        {
            FIconList = nullptr;
        }
        else if (AComponent == FPopupMenu)
        {
            FPopupMenu = nullptr;
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::Loaded()
{
    TComponent::Loaded();
    if (!FIconList)
    {
        FAnimate = false;
        FIcon->Assign(Application->Icon);
    }
    else
    {
        FTimer->Enabled = FAnimate;
        FIconList->GetIcon(FIconIndex, FIcon);
    }

    Update();
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::SetVisible(bool Value)
{
    FVisible = Value;
    if (!ComponentState.Contains(csDesigning))
    {
        if (FVisible)
        {
            if (!Shell_NotifyIcon(NIM_ADD, &FData))
                throw EOutOfResources(LoadStr(sCannotCreate));

            Hide = true;
            Application->HookMainWindow(FApplicationHook);
        }
        else
        {
            if (!Shell_NotifyIcon(NIM_DELETE, &FData))
                throw EOutOfResources(LoadStr(sCannotRemove));

            Hide = false;
            Application->UnhookMainWindow(FApplicationHook);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::SetHint(String Hint)
{
   	// The new hint must be different than the previous hint and less than
   	// 64 characters to be modified. 64 is an operating system limit.
	if ((FHint != Hint) && (Hint.Length() < 64))
   	{
    	FHint = Hint;
      	StrPLCopy(FData.szTip, Hint, sizeof(FData.szTip) - 1);

      	// If there is no hint then there is no tool tip.
      	if (Hint.Length())
        {
         	FData.uFlags = FData.uFlags | NIF_TIP;
        }
      	else
      	{
         	FData.uFlags = FData.uFlags & !NIF_TIP;
        }

      	Update();
   	}
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::SetHide(bool Value)
{
    FHide = Value;
}

//---------------------------------------------------------------------------
int __fastcall dslTrayIcon::GetAnimateInterval()
{
    return FTimer->Interval;
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::SetAnimateInterval(int Value)
{
    FTimer->Interval = Value;
}

//---------------------------------------------------------------------------
bool __fastcall dslTrayIcon::GetAnimate()
{
    return FAnimate;
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::SetAnimate(bool Value)
{
    if (FIconList || ComponentState.Contains(csLoading))
        FAnimate = Value;

    if (FIconList && !ComponentState.Contains(csDesigning))
        FTimer->Enabled = Value;
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::EndSession()
{
    Shell_NotifyIcon(NIM_DELETE, &FData);
}

//---------------------------------------------------------------------------
TShiftState dslTrayIcon::ShiftState()
{
    TShiftState result;

    if (GetKeyState(VK_SHIFT) < 0)
        result << ssShift;

    if (GetKeyState(VK_CONTROL) < 0)
        result << ssCtrl;

    if (GetKeyState(VK_MENU) < 0)
        result << ssAlt;

    return result;
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::DoMessage(TMessage &Message)
{
    TPoint point;
    TShiftState shift;

    switch(Message.Msg)
    {
        case WM_QUERYENDSESSION:
            Message.Result = 1;
        break;

        case WM_ENDSESSION:
            EndSession();
        break;

        case WM_SYSTEM_TRAY_NOTIFY:
            switch(Message.LParam)
            {
                case WM_MOUSEMOVE:
                if (FOnClick)
                {
                    shift = ShiftState();
                    GetCursorPos(&point);
                    DoMouseMove(shift, point.x, point.y);
                }
                break;

                case WM_LBUTTONDOWN:
                    shift = ShiftState();
                    shift << ssLeft;
                    GetCursorPos(&point);
                    DoMouseDown(mbLeft, shift, point.x, point.y);
                    FIsClicked = true;
                break;

                case WM_LBUTTONUP:
                    shift = ShiftState();
                    shift << ssLeft;
                    GetCursorPos(&point);

                    if (FOnClick)
                        DoClick();

                    DoMouseUp(mbLeft, shift, point.x, point.y);

                    if (FToggleVisibility == imLeftClickUp)
                        ToggleVisibility();

                    if (FAppRestore == imLeftClickUp)
                        Restore();

                    if (FPopupMenuShow == imLeftClickUp)
                        ShowMenu();
                break;

                case WM_LBUTTONDBLCLK:
                    DoDblClick();

                    if (FAppRestore == imLeftDoubleClick)
                        Restore();

                    if (FPopupMenuShow == imLeftDoubleClick)
                        ShowMenu();
                break;

                case WM_RBUTTONDOWN:
                    shift = ShiftState();
                    shift << ssRight;
                    GetCursorPos(&point);
                    DoMouseDown(mbRight, shift, point.x, point.y);
                break;

                case WM_RBUTTONUP:
                    shift = ShiftState();
                    shift << ssRight;
                    GetCursorPos(&point);

                    DoMouseUp(mbRight, shift, point.x, point.y);

                    if (FAppRestore == imRightClickUp)
                        Restore();

                    if (FPopupMenuShow == imRightClickUp)
                        ShowMenu();
                break;

                case WM_RBUTTONDBLCLK:
                    DoDblClick();

                    if (FAppRestore == imRightDoubleClick)
                        Restore();

                    if (FPopupMenuShow == imRightDoubleClick)
                        ShowMenu();
                break;

                case WM_MBUTTONDOWN:
                    shift = ShiftState();
                    shift << ssMiddle;
                    GetCursorPos(&point);

                    DoMouseDown(mbMiddle, shift, point.x, point.y);
                break;

                case WM_MBUTTONUP:
                    shift = ShiftState();
                    shift << ssMiddle;
                    GetCursorPos(&point);
                    DoMouseUp(mbMiddle, shift, point.x, point.y);
                break;

                case WM_MBUTTONDBLCLK:
                    DoDblClick();
                break;
            }
    }

    TComponent::Dispatch(&Message);
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::ShowMenu()
{
    TPoint point;
    GetCursorPos(&point);

    if (Screen->ActiveForm && (Screen->ActiveForm->Handle != nullptr))
        SetForegroundWindow(Screen->ActiveForm->Handle);

    FPopupMenu->Popup(point.x, point.y);
}
//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::DoClick()
{
    if(FAppRestore == imClick)
        Restore();

    if(FPopupMenuShow == imClick)
        ShowMenu();

    if(FOnClick)
        FOnClick(this);
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::DoDblClick()
{
    if (FAppRestore == imDoubleClick)
        Restore();

    if (FPopupMenuShow == imDoubleClick)
        ShowMenu();

    if (FOnDblClick)
        FOnDblClick(this);
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::DoMouseMove(TShiftState Shift, int X, int Y)
{
    if (FOnMouseMove)
        FOnMouseMove(this, Shift, X, Y);
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::DoMouseDown(TMouseButton Button, TShiftState Shift,
                                       int X, int Y)
{
    if (FAppRestore == imMouseDown)
        Restore();

    if (FPopupMenuShow == imMouseDown)
        ShowMenu();

    if (FOnMouseDown)
        FOnMouseDown(this, Button, Shift, X, Y);
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::DoMouseUp(TMouseButton Button, TShiftState Shift,
                                     int X, int Y)
{
    if (FAppRestore == imMouseDown)
        Restore();

    if (FPopupMenuShow == imMouseDown)
        ShowMenu();

    if (FOnMouseUp)
        FOnMouseUp(this, Button, Shift, X, Y);
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::DoOnAnimate(TObject *Sender)
{
    if (IconIndex < FIconList->Count)
        FIconIndex++;
    else
        FIconIndex = 0;

    SetIconIndex(FIconIndex);
    Update();
}

//---------------------------------------------------------------------------
// When the application minimizes, hide it, so only the icon in the system
// tray is visible.
//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::Minimize()
{
    Application->Minimize();
    ShowWindow(Application->Handle, SW_HIDE);

    if (FOnMinimize)
        FOnMinimize(this);
}

//---------------------------------------------------------------------------
// Restore the application by making its window visible again, which is a
// little weird since its window is invisible, having no height or width, but
// that's what determines whether the button appears on the taskbar.
//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::Restore()
{
    Application->Restore();
    ShowWindow(Application->Handle, SW_RESTORE);
    SetForegroundWindow(Application->Handle);

    if (FOnRestore)
        FOnRestore(this);
}

void __fastcall dslTrayIcon::ToggleVisibility()
{
    if(IsIconic(Application->Handle))
    {
        Restore();
    }
    else
    {
        Minimize();
    }
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::Update()
{
    if (!ComponentState.Contains(csDesigning))
    {
        FData.hIcon = FIcon->Handle;

        if (Visible == true)
            Shell_NotifyIcon(NIM_MODIFY, &FData);
    }
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::SetIconIndex(int Value)
{
    FIconIndex = Value;

    if (FIconList)
        FIconList->GetIcon(FIconIndex, FIcon);

    Update();
}

//---------------------------------------------------------------------------
bool __fastcall dslTrayIcon::ApplicationHookProc(TMessage &Message)
{
    if (Message.Msg == WM_SYSCOMMAND)
    {
        if (Message.WParam == SC_MINIMIZE)
            Minimize();

        if (Message.WParam == SC_RESTORE)
            Restore();
    }

    return false;
}

//---------------------------------------------------------------------------
void __fastcall dslTrayIcon::SetDefaultIcon()
{
    FIcon->Assign(Application->Icon);
    Update();
}

//---------------------------------------------------------------------------
HWND __fastcall dslTrayIcon::GetHandle()
{
    return FData.hWnd;
}

// Register and ValidCtrCheck need to be removed and placed in another package.
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(dslTrayIcon *)
{
   new dslTrayIcon(nullptr);
}

namespace Mtktrayicon
{
    void __fastcall PACKAGE Register()
    {
//        ShowMessage("TrayIcon installed");
        TComponentClass classes[1] = {__classid(dslTrayIcon)};
        RegisterComponents(dslComponents::gDuneComponents, classes, 0);
    }
}
