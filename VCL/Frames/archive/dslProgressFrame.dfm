object ProgressFrame: TProgressFrame
  Left = 0
  Top = 0
  Width = 620
  Height = 54
  TabOrder = 0
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 514
    Height = 54
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    object ProgressBar1: TProgressBar
      Left = 1
      Top = 1
      Width = 512
      Height = 52
      Align = alClient
      Position = 45
      Smooth = True
      Step = 100
      TabOrder = 0
    end
  end
  object Panel2: TPanel
    Left = 514
    Top = 0
    Width = 106
    Height = 54
    Align = alRight
    TabOrder = 1
    object progressLbl: TLabel
      Left = 1
      Top = 1
      Width = 72
      Height = 45
      Align = alClient
      Alignment = taCenter
      Caption = '46 %'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -37
      Font.Name = 'Calibri'
      Font.Style = []
      ParentFont = False
    end
  end
end
