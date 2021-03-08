object LogMemoFrame: TLogMemoFrame
  Left = 0
  Top = 0
  Width = 866
  Height = 404
  TabOrder = 0
  object LogPanel: TPanel
    Left = 0
    Top = 0
    Width = 866
    Height = 404
    Align = alClient
    Caption = 'LogPanel'
    TabOrder = 0
    object LogGroupBox: TGroupBox
      Left = 1
      Top = 1
      Width = 864
      Height = 50
      Align = alTop
      Caption = 'Logs'
      TabOrder = 0
      object ToolBar1: TToolBar
        Left = 2
        Top = 15
        Width = 258
        Height = 33
        Align = alLeft
        AutoSize = True
        ButtonHeight = 21
        Caption = 'LogToolbar'
        TabOrder = 0
        object mClearLogMemoBtn: TBitBtn
          Left = 0
          Top = 0
          Width = 113
          Height = 21
          Align = alLeft
          Caption = 'Clear'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 0
          OnClick = mClearLogMemoBtnClick
        end
        object LogLevelCB: TComboBox
          Left = 113
          Top = 0
          Width = 145
          Height = 21
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          Text = 'INFO'
          OnCloseUp = LogLevelCBCloseUp
          Items.Strings = (
            'ERROR'
            'WARNING'
            'INFO'
            'DEBUG'
            'DEBUG1'
            'DEBUG2'
            'DEBUG3'
            'DEBUG4'
            'DEBUG5')
        end
      end
    end
    object infoMemo: TMemo
      Left = 1
      Top = 51
      Width = 864
      Height = 352
      Align = alClient
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      ScrollBars = ssBoth
      TabOrder = 1
      WordWrap = False
    end
  end
  object LogFileReader1: TLogFileReader
    LogFileMemo = infoMemo
    Left = 64
    Top = 120
  end
end
