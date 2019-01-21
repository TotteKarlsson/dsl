object CreditsForm: TCreditsForm
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'CreditsForm'
  ClientHeight = 509
  ClientWidth = 534
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 113
    Width = 534
    Height = 396
    Align = alClient
    TabOrder = 0
    object creditsMemo: TMemo
      Left = 1
      Top = 1
      Width = 532
      Height = 394
      Align = alClient
      Color = clCream
      OEMConvert = True
      ReadOnly = True
      ScrollBars = ssVertical
      TabOrder = 0
      WordWrap = False
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 534
    Height = 113
    Align = alTop
    Color = clCream
    ParentBackground = False
    TabOrder = 1
    OnClick = Panel2Click
    DesignSize = (
      534
      113)
    object creditsImage: TImage
      Left = 399
      Top = 8
      Width = 122
      Height = 99
      Anchors = [akTop, akRight]
      Proportional = True
      Stretch = True
      ExplicitLeft = 576
    end
    object ProgramLabel: TLabel
      Left = 27
      Top = 24
      Width = 149
      Height = 55
      Caption = 'Credits'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -48
      Font.Name = 'Berlin Sans FB Demi'
      Font.Style = []
      ParentFont = False
    end
  end
end
