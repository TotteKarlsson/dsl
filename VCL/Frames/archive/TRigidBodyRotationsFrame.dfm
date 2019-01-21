object RigidBodyRotationsFrame: TRigidBodyRotationsFrame
  Left = 0
  Top = 0
  Width = 320
  Height = 240
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object xTB: TTrackBar
    Left = 24
    Top = 80
    Width = 150
    Height = 45
    Max = 180
    Min = -180
    TabOrder = 0
    OnChange = zTBChange
    OnExit = xTBExit
  end
  object yTB: TTrackBar
    Left = 24
    Top = 123
    Width = 150
    Height = 45
    Max = 180
    Min = -180
    Frequency = 25
    TabOrder = 1
    OnChange = zTBChange
  end
  object zTB: TTrackBar
    Left = 24
    Top = 166
    Width = 150
    Height = 45
    Max = 180
    Min = -180
    Frequency = 25
    TabOrder = 2
    OnChange = zTBChange
  end
  object frameOfRotation: TRadioGroup
    Left = 16
    Top = 3
    Width = 105
    Height = 71
    Caption = 'Frame of Rotation'
    ItemIndex = 0
    Items.Strings = (
      'World'
      'Local')
    TabOrder = 3
  end
  object CheckBox1: TCheckBox
    Left = 152
    Top = 48
    Width = 97
    Height = 17
    Caption = 'CheckBox1'
    TabOrder = 4
    OnClick = CheckBox1Click
  end
end
