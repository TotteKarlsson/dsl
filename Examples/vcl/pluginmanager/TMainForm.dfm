object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'MainForm'
  ClientHeight = 784
  ClientWidth = 1104
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnCloseQuery = FormCloseQuery
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 489
    Width = 1104
    Height = 295
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    inline TLogMemoFrame1: TLogMemoFrame
      Left = 1
      Top = 1
      Width = 1102
      Height = 293
      Align = alClient
      TabOrder = 0
      ExplicitLeft = 1
      ExplicitTop = 1
      ExplicitWidth = 1102
      ExplicitHeight = 293
      inherited Panel1: TPanel
        Width = 1102
        Height = 293
        ExplicitWidth = 1102
        ExplicitHeight = 293
        inherited GroupBox1: TGroupBox
          Width = 1100
          ExplicitWidth = 1100
        end
        inherited infoMemo: TMemo
          Width = 1100
          Height = 241
          ExplicitWidth = 1100
          ExplicitHeight = 241
        end
      end
    end
  end
  object ControlBar1: TControlBar
    Left = 0
    Top = 0
    Width = 1104
    Height = 56
    Align = alTop
    AutoSize = True
    TabOrder = 1
    object Panel2: TPanel
      Left = 26
      Top = 2
      Width = 255
      Height = 48
      Align = alClient
      TabOrder = 0
      object LoadPluginsBtn: TButton
        Left = 1
        Top = 1
        Width = 113
        Height = 46
        Align = alLeft
        Caption = 'Load Plugins'
        TabOrder = 0
        OnClick = LoadPluginsBtnClick
      end
      object GetPluginsInfoBtn: TButton
        Left = 114
        Top = 1
        Width = 113
        Height = 46
        Align = alLeft
        Caption = 'Get Plugin Info'
        TabOrder = 1
        OnClick = LoadPluginsBtnClick
      end
    end
  end
  object PythonGB: TGroupBox
    Left = 0
    Top = 56
    Width = 1104
    Height = 433
    Align = alTop
    Caption = 'Plugin Info'
    TabOrder = 2
    object PluginsLB: TListBox
      Left = 2
      Top = 15
      Width = 121
      Height = 416
      Align = alLeft
      ItemHeight = 13
      TabOrder = 0
      OnClick = PythonPluginsLBClick
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 10
    OnTimer = ShutDownTimerTimer
    Left = 584
    Top = 104
  end
  object PluginManager1: TPluginManager
    Left = 248
    Top = 184
  end
end
