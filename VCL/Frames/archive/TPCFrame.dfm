object PCFrame: TPCFrame
  Left = 0
  Top = 0
  Width = 576
  Height = 397
  Color = clBtnFace
  ParentColor = False
  TabOrder = 0
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 576
    Height = 397
    Align = alClient
    DockSite = True
    PopupMenu = PageControlPopup
    TabOrder = 0
    OnChanging = PageControlChanging
  end
  object PageActions: TActionList
    Left = 48
    Top = 32
    object CreatePageA: TAction
      Category = 'Manage Tabs'
      Caption = 'Create Page'
      OnExecute = CreatePageAExecute
    end
    object ClosePageA: TAction
      Category = 'Manage Tabs'
      Caption = 'Close'
      ShortCut = 16449
      OnExecute = ClosePageAExecute
    end
    object CloseAllPagesA: TAction
      Category = 'Manage Tabs'
      Caption = 'Close All'
      OnExecute = CloseAllPagesAExecute
    end
    object CloseAllTabsExceptThisA: TAction
      Category = 'Manage Tabs'
      Caption = 'Close All Others'
      OnExecute = CloseAllTabsExceptThisAExecute
    end
    object ActivateTabA: TAction
      Category = 'Manage Tabs'
      Caption = 'Activate'
      OnExecute = ActivateTabAExecute
    end
    object HidePageA: TAction
      Category = 'Manage Tabs'
      Caption = 'Hide'
      OnExecute = HidePageAExecute
    end
  end
  object PageControlPopup: TPopupMenu
    Left = 240
    Top = 56
    object ClosePage1: TMenuItem
      Action = ClosePageA
    end
    object CloseAll1: TMenuItem
      Action = CloseAllPagesA
    end
    object CloseAllOtherTabs1: TMenuItem
      Action = CloseAllTabsExceptThisA
    end
    object Activate1: TMenuItem
      Action = ActivateTabA
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object Hide1: TMenuItem
      Action = HidePageA
    end
  end
  object PCManager: mtkPCManager
    PageControl = PageControl
    Left = 48
    Top = 128
  end
end
