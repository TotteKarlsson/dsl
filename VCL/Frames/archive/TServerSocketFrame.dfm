object ServerSocketFrame: TServerSocketFrame
  Left = 0
  Top = 0
  Width = 792
  Height = 651
  TabOrder = 0
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 792
    Height = 651
    Align = alClient
    Caption = 'Panel2'
    PopupMenu = SocketFramePopupMenu1
    TabOrder = 0
    object StatusBar1: TStatusBar
      Left = 1
      Top = 631
      Width = 790
      Height = 19
      Panels = <
        item
          Text = 'isConnected'
          Width = 150
        end
        item
          Text = 'Nr of clients:'
          Width = 50
        end>
    end
    object ToolBar1: TToolBar
      Left = 1
      Top = 1
      Width = 790
      Height = 29
      AutoSize = True
      BorderWidth = 1
      ButtonHeight = 21
      Caption = 'ToolBar1'
      EdgeBorders = [ebTop, ebBottom]
      TabOrder = 1
      object BitBtn1: TBitBtn
        Left = 0
        Top = 0
        Width = 83
        Height = 21
        Action = ToggleListening
        Caption = 'TogglCon'
        TabOrder = 0
      end
      object ToolButton1: TToolButton
        Left = 83
        Top = 0
        Width = 14
        Caption = 'ToolButton1'
        Style = tbsSeparator
      end
      object PortNrE: mtkIntEdit
        Left = 97
        Top = 0
        Width = 80
        Height = 21
        AutoSize = False
        TabOrder = 1
        Text = '50000'
      end
    end
    object Panel1: TPanel
      Left = 1
      Top = 30
      Width = 790
      Height = 601
      Align = alClient
      Caption = 'Panel1'
      TabOrder = 2
      object Splitter1: TSplitter
        Left = 1
        Top = 486
        Width = 788
        Height = 7
        Cursor = crVSplit
        Align = alBottom
        ExplicitTop = 251
        ExplicitWidth = 441
      end
      object logMemo: TMemo
        Left = 1
        Top = 1
        Width = 788
        Height = 485
        Align = alClient
        Color = clBtnFace
        Lines.Strings = (
          '')
        ReadOnly = True
        ScrollBars = ssBoth
        TabOrder = 0
        WordWrap = False
      end
      object writeMemo: TMemo
        Left = 1
        Top = 493
        Width = 788
        Height = 107
        Align = alBottom
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Courier New'
        Font.Style = [fsBold, fsItalic]
        Lines.Strings = (
          '')
        ParentFont = False
        ScrollBars = ssVertical
        TabOrder = 1
        WordWrap = False
        OnKeyDown = writeMemoKeyDown
      end
    end
  end
  object SocketFramePopupMenu1: TPopupMenu
    Left = 72
    Top = 552
    object Clear1: TMenuItem
      Action = ClearLogMemoA
    end
  end
  object SocketFrameActionList1: TActionList
    OnUpdate = SocketFrameActionList1Update
    Left = 72
    Top = 240
    object ToggleListening: TAction
      Category = 'socketStuff'
      Caption = 'ToggleConnection'
      OnExecute = ToggleListeningExecute
    end
    object StartListening: TAction
      Category = 'socketStuff'
      Caption = 'StartListening'
      OnExecute = StartListeningExecute
    end
    object StopListening: TAction
      Category = 'socketStuff'
      Caption = 'StopListening'
      OnExecute = StopListeningExecute
    end
    object ClearLogMemoA: TAction
      Category = 'memos'
      Caption = 'Clear'
      OnExecute = ClearLogMemoAExecute
    end
  end
end
