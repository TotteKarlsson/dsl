object PluginInfoFrame: TPluginInfoFrame
  Left = 0
  Top = 0
  Width = 821
  Height = 382
  TabOrder = 0
  object GroupBox2: TGroupBox
    Left = 0
    Top = 0
    Width = 257
    Height = 382
    Align = alLeft
    Caption = 'Plugin Info (Base)'
    TabOrder = 0
    object PluginNameE: TSTDStringLabeledEdit
      Left = 16
      Top = 40
      Width = 233
      Height = 21
      EditLabel.Width = 27
      EditLabel.Height = 13
      EditLabel.Caption = 'Name'
      Enabled = False
      TabOrder = 0
    end
    object WorkerButton: TButton
      Left = 16
      Top = 80
      Width = 75
      Height = 25
      Caption = 'Run'
      TabOrder = 1
      OnClick = WorkerButtonClick
    end
  end
  object Panel1: TPanel
    Left = 257
    Top = 0
    Width = 564
    Height = 382
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 564
      Height = 382
      Align = alClient
      Caption = 'Plugin Properties'
      TabOrder = 0
      object PropertiesPanel: TFlowPanel
        Left = 2
        Top = 15
        Width = 560
        Height = 337
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
      end
      object ProgressBar1: TProgressBar
        Left = 2
        Top = 352
        Width = 560
        Height = 28
        Align = alBottom
        TabOrder = 1
      end
    end
  end
  object RunningTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = RunningTimerTimer
    Left = 64
    Top = 176
  end
end
