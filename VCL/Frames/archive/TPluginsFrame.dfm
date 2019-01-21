object PluginsFrame: TPluginsFrame
  Left = 0
  Top = 0
  Width = 234
  Height = 178
  TabOrder = 0
  object GroupBox4: TGroupBox
    Left = 0
    Top = 0
    Width = 234
    Height = 50
    Align = alTop
    Caption = 'Folder'
    TabOrder = 0
    object PluginFolderLbl: TLabel
      Left = 8
      Top = 24
      Width = 71
      Height = 13
      Caption = 'PluginFolderLbl'
      ParentShowHint = False
      ShowHint = True
    end
  end
  object GroupBox2: TGroupBox
    Left = 0
    Top = 50
    Width = 234
    Height = 128
    Align = alClient
    Caption = 'Files'
    TabOrder = 1
    object CheckListBox1: TCheckListBox
      Left = 2
      Top = 15
      Width = 230
      Height = 111
      OnClickCheck = CheckListBox1Click
      Align = alClient
      Columns = 1
      ItemHeight = 13
      TabOrder = 0
    end
  end
  object ActionList1: TActionList
    Left = 144
    Top = 32
  end
  object Toolbars: TAction
    Category = 'ToolBars'
    Caption = 'Toolbars'
    Enabled = False
  end
end
