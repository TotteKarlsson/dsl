object managePluginsForm: TmanagePluginsForm
  Left = 610
  Top = 409
  BorderStyle = bsToolWindow
  Caption = 'Manage Plugins'
  ClientHeight = 380
  ClientWidth = 495
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  KeyPreview = True
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 495
    Height = 33
    Align = alTop
    TabOrder = 0
    object pluginsCB: TComboBox
      Left = 8
      Top = 6
      Width = 145
      Height = 21
      Style = csDropDownList
      TabOrder = 0
      OnChange = pluginsCBChange
    end
  end
  object ActionList1: TActionList
    Left = 260
    Top = 8
    object FillPluginsCB: TAction
      Caption = 'FillPluginsCB'
      OnExecute = FillPluginsCBExecute
    end
  end
end
