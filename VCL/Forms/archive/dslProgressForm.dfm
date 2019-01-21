object ProgressF: TProgressF
  Left = 585
  Top = 218
  BorderStyle = bsToolWindow
  Caption = 'Progress'
  ClientHeight = 58
  ClientWidth = 398
  Color = clSilver
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 57
    Height = 13
    Caption = 'Loading file:'
  end
  object FileNameLabel: TLabel
    Left = 72
    Top = 8
    Width = 41
    Height = 13
    Caption = 'fileName'
  end
  object Panel1: TPanel
    Left = 8
    Top = 24
    Width = 385
    Height = 21
    Color = clGray
    TabOrder = 0
    object ProgressBar1: TProgressBar
      Left = 1
      Top = 1
      Width = 383
      Height = 19
      Align = alClient
      Smooth = True
      Step = 100
      TabOrder = 0
    end
  end
end
