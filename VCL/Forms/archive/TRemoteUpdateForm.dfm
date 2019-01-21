object RemoteUpdateForm: TRemoteUpdateForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  Caption = 'Remote Version'
  ClientHeight = 537
  ClientWidth = 639
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poMainFormCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 639
    Height = 57
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object Label1: TLabel
      Left = 12
      Top = 16
      Width = 82
      Height = 13
      Caption = 'Current Version: '
    end
    object Label2: TLabel
      Left = 12
      Top = 35
      Width = 79
      Height = 13
      Caption = 'Remote Version:'
    end
    object Label3: TLabel
      Left = 229
      Top = 13
      Width = 198
      Height = 16
      Caption = 'Download the latest version from: '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = 16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object currentVersionLbl: TLabel
      Left = 116
      Top = 16
      Width = 83
      Height = 13
      Caption = 'currentVersionLbl'
    end
    object remoteVersionLbl: TLabel
      Left = 116
      Top = 35
      Width = 31
      Height = 13
      Caption = 'Label4'
    end
    object remoteDownloadURL: TURLLabel
      Left = 229
      Top = 35
      Width = 119
      Height = 16
      Cursor = crHandPoint
      Caption = 'remoteDownloadURL'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = 16
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 57
    Width = 639
    Height = 443
    Align = alClient
    Caption = 'Remote ChangeLog'
    TabOrder = 1
    object Memo1: TMemo
      Left = 2
      Top = 15
      Width = 635
      Height = 426
      Align = alClient
      Ctl3D = True
      ParentCtl3D = False
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 500
    Width = 639
    Height = 37
    Align = alBottom
    TabOrder = 2
    DesignSize = (
      639
      37)
    object mNetStatus: TLabel
      Left = 12
      Top = 12
      Width = 56
      Height = 13
      Caption = 'mNetStatus'
      Color = clRed
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
    object Button1: TButton
      Left = 549
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Close'
      ModalResult = 8
      TabOrder = 0
    end
  end
  object mStatusTimer: TTimer
    Enabled = False
    Interval = 150
    OnTimer = mStatusTimerTimer
    Left = 32
    Top = 360
  end
end
