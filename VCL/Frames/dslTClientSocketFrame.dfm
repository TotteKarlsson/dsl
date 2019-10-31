object ClientSocketFrame: TClientSocketFrame
  Left = 0
  Top = 0
  Width = 1050
  Height = 679
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
    Width = 1050
    Height = 679
    Align = alClient
    Caption = 'Panel2'
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 1
      Top = 480
      Width = 1048
      Height = 7
      Cursor = crVSplit
      Align = alBottom
      ExplicitLeft = 73
      ExplicitTop = 363
    end
    object StatusBar1: TStatusBar
      Left = 1
      Top = 659
      Width = 1048
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
      Width = 1048
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
      object PortNrE: TIntegerEdit
        Left = 344
        Top = 0
        Width = 65
        Height = 21
        NumbersOnly = True
        TabOrder = 3
        Text = '50000'
        Value = 50000
      end
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 36
      Width = 1048
      Height = 444
      Align = alClient
      Caption = 'Received data'
      TabOrder = 2
      object ReceivedDataMemo: TMemo
        Left = 2
        Top = 15
        Width = 1044
        Height = 427
        Align = alClient
        Color = clBtnFace
        Lines.Strings = (
          '')
        PopupMenu = MemosPopup
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
      end
    end
    object GroupBox2: TGroupBox
      Left = 1
      Top = 487
      Width = 1048
      Height = 123
      Align = alBottom
      Caption = 'Sent data'
      TabOrder = 3
      object SentDataMemo: TMemo
        Left = 2
        Top = 15
        Width = 1044
        Height = 106
        Align = alClient
        PopupMenu = MemosPopup
        ScrollBars = ssVertical
        TabOrder = 0
        WordWrap = False
      end
    end
    object GroupBox3: TGroupBox
      Left = 1
      Top = 610
      Width = 1048
      Height = 49
      Align = alBottom
      Caption = 'Send'
      TabOrder = 4
      DesignSize = (
        1048
        49)
      object SendDataE: TSTDStringEdit
        Left = 10
        Top = 22
        Width = 987
        Height = 21
        Anchors = [akLeft, akTop, akRight]
        TabOrder = 0
        Text = 'Test'
        OnKeyDown = SendData
        Value = 'Test'
      end
      object SendDataBtn: TButton
        Left = 1003
        Top = 17
        Width = 42
        Height = 25
        Anchors = [akTop, akRight]
        Caption = 'Send'
        TabOrder = 1
        OnClick = SendDataBtnClick
      end
    end
  end
  object SocketFrameActionList1: TActionList
    Left = 96
    Top = 72
    object ToggleConnection: TAction
      Category = 'socketStuff'
      Caption = 'ToggleConnection'
      OnExecute = ToggleConnectionExecute
      OnUpdate = ToggleConnectionUpdate
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
    object ClearSentDataMemoA: TAction
      Category = 'MemosA'
      Caption = 'Clear'
      OnExecute = ClearMemo
    end
  end
  object ReconnectTimer: TTimer
    Enabled = False
    OnTimer = ReconnectTimerTimer
    Left = 264
    Top = 72
  end
  object MemosPopup: TPopupMenu
    Left = 152
    Top = 200
    object Clear1: TMenuItem
      Action = ClearSentDataMemoA
    end
  end
end
