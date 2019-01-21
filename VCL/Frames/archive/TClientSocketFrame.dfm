object ClientSocketFrame: TClientSocketFrame
  Left = 0
  Top = 0
  Width = 654
  Height = 543
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  OnExit = FrameExit
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 654
    Height = 543
    Align = alClient
    Caption = 'Panel2'
    PopupMenu = SocketFramePopupMenu1
    TabOrder = 0
    object StatusBar1: TStatusBar
      Left = 1
      Top = 523
      Width = 652
      Height = 19
      Panels = <
        item
          Text = 'isConnected'
          Width = 50
        end>
    end
    object ToolBar1: TToolBar
      Left = 1
      Top = 1
      Width = 652
      Height = 35
      BorderWidth = 1
      ButtonHeight = 21
      Caption = 'ToolBar1'
      EdgeBorders = [ebTop, ebBottom]
      TabOrder = 1
      object ServerCB: TComboBox
        Left = 0
        Top = 0
        Width = 137
        Height = 21
        ItemIndex = 0
        TabOrder = 0
        Text = 'localhost'
        Items.Strings = (
          'localhost'
          '3.112.212.99')
      end
      object BitBtn1: TBitBtn
        Left = 137
        Top = 0
        Width = 79
        Height = 21
        Action = ToggleConnection
        Align = alLeft
        Caption = 'TogglCon'
        TabOrder = 2
      end
      object AutoReconnectCB: TCheckBox
        Left = 216
        Top = 0
        Width = 128
        Height = 21
        BiDiMode = bdLeftToRight
        Caption = 'Auto Reconnect'
        ParentBiDiMode = False
        TabOrder = 1
      end
      object PortNrE: mtkIntEdit
        Left = 344
        Top = 0
        Width = 121
        Height = 21
        TabOrder = 3
        Text = '0'
      end
    end
    object Panel1: TPanel
      Left = 1
      Top = 36
      Width = 652
      Height = 487
      Align = alClient
      Caption = 'Panel1'
      TabOrder = 2
      object Splitter1: TSplitter
        Left = 1
        Top = 372
        Width = 650
        Height = 7
        Cursor = crVSplit
        Align = alBottom
        ExplicitTop = 85
        ExplicitWidth = 383
      end
      object RecMsgMemo: TMemo
        Left = 1
        Top = 1
        Width = 650
        Height = 371
        Align = alClient
        Color = clBtnFace
        Lines.Strings = (
          '')
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
      end
      object ConsoleMemo: TMemo
        Left = 1
        Top = 379
        Width = 650
        Height = 107
        Align = alBottom
        PopupMenu = ConsolePopup
        ScrollBars = ssVertical
        TabOrder = 1
        WordWrap = False
        OnKeyDown = ConsoleMemoKeyDown
      end
    end
  end
  object SocketFramePopupMenu1: TPopupMenu
    Left = 80
    Top = 56
    object Connect1: TMenuItem
      Action = ClearReceivedMemoA
    end
  end
  object SocketFrameActionList1: TActionList
    Left = 160
    Top = 144
    object ToggleConnection: TAction
      Category = 'socketStuff'
      Caption = 'ToggleConnection'
      OnExecute = ToggleConnectionExecute
      OnUpdate = ToggleConnectionUpdate
    end
    object ClearReceivedMemoA: TAction
      Category = 'MemosA'
      Caption = 'Clear'
      OnExecute = ClearReceivedMemoAExecute
    end
    object Disconnect: TAction
      Category = 'socketStuff'
      Caption = 'Disconnect'
      OnExecute = DisconnectExecute
    end
    object Connect: TAction
      Category = 'socketStuff'
      Caption = 'Connect'
      OnExecute = ConnectExecute
    end
    object ClearConsoleMemoA: TAction
      Category = 'MemosA'
      Caption = 'Clear'
      OnExecute = ClearConsoleMemoAExecute
    end
  end
  object ReconnectTimer: TTimer
    Enabled = False
    OnTimer = ReconnectTimerTimer
    Left = 264
    Top = 72
  end
  object ConsolePopup: TPopupMenu
    Left = 208
    Top = 424
    object Clear1: TMenuItem
      Action = ClearConsoleMemoA
    end
  end
end
