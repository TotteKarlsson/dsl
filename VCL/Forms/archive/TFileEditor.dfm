object FileEditor: TFileEditor
  Left = 672
  Top = 79
  AutoSize = True
  Caption = 'FileEditor'
  ClientHeight = 362
  ClientWidth = 498
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 57
    Width = 498
    Height = 305
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    object Memo1: TMemo
      Left = 1
      Top = 1
      Width = 496
      Height = 303
      Align = alClient
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      ScrollBars = ssBoth
      TabOrder = 0
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 498
    Height = 57
    Align = alTop
    Caption = 'File'
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 12
      Width = 32
      Height = 13
      Caption = 'Label1'
    end
    object SaveBtn: TButton
      Left = 88
      Top = 32
      Width = 57
      Height = 17
      Action = SaveFileAction1
      Caption = 'Save'
      TabOrder = 0
    end
    object ReloadButton: TButton
      Left = 8
      Top = 32
      Width = 75
      Height = 17
      Action = ReloadFileAction
      Caption = 'Reload'
      TabOrder = 1
    end
    object SaveAsBtn: TButton
      Left = 152
      Top = 32
      Width = 73
      Height = 17
      Action = SaveAsAction
      TabOrder = 2
    end
  end
  object ActionList1: TActionList
    Left = 368
    Top = 136
    object SaveFileAction1: TAction
      Caption = 'Save File'
      OnExecute = SaveFileAction1Execute
    end
    object ReloadFileAction: TAction
      Caption = 'Reload File'
      OnExecute = ReloadFileActionExecute
    end
    object SaveAsAction: TAction
      Caption = 'Save As'
      OnExecute = SaveAsActionExecute
    end
    object EditCopy1: TEditCopy
      Category = 'Edit'
      Caption = '&Copy'
      Hint = 'Copy|Copies the selection and puts it on the Clipboard'
      ImageIndex = 1
      ShortCut = 16451
    end
  end
  object SaveDialog1: TSaveDialog
    Left = 376
    Top = 24
  end
end
