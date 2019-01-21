object ThreadHealth: TThreadHealth
  Left = 0
  Top = 0
  Width = 216
  Height = 117
  TabOrder = 0
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 64
    Height = 13
    Caption = 'Thread Name'
  end
  object Label2: TLabel
    Left = 8
    Top = 27
    Width = 48
    Height = 13
    Caption = 'Thread ID'
  end
  object mThreadNameLbl: TLabel
    Left = 96
    Top = 8
    Width = 40
    Height = 13
    Caption = '<none>'
  end
  object mThreadIDLbl: TLabel
    Left = 96
    Top = 27
    Width = 10
    Height = 13
    Caption = '-1'
  end
  object Button1: TButton
    Left = 8
    Top = 52
    Width = 48
    Height = 21
    Action = ToggleStartStopA
    TabOrder = 0
  end
  object ActionList1: TActionList
    Left = 160
    Top = 32
    object ToggleStartStopA: TAction
      Caption = 'Start'
      OnExecute = ToggleStartStopAExecute
    end
    object AbortThreadA: TAction
      Caption = 'Abort'
    end
  end
  object Timer1: TTimer
    Enabled = False
    OnTimer = Timer1Timer
    Left = 160
    Top = 64
  end
end
