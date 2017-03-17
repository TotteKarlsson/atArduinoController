object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Arduino Controller'
  ClientHeight = 707
  ClientWidth = 990
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -19
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 23
  object TopPanel: TPanel
    Left = 0
    Top = 0
    Width = 990
    Height = 89
    Align = alTop
    TabOrder = 0
    object Button1: TArrayBotButton
      Left = 822
      Top = 1
      Width = 88
      Height = 87
      Align = alRight
      Caption = 'About'
      ParentDoubleBuffered = True
      TabOrder = 0
      OnClick = mAboutBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
    object Button5: TArrayBotButton
      Left = 910
      Top = 1
      Width = 79
      Height = 87
      Action = FileExit1
      Align = alRight
      Caption = 'E&xit'
      ParentDoubleBuffered = True
      TabOrder = 1
      SoundID = 'BUTTON_CLICK_4'
    end
    object GroupBox1: TGroupBox
      Left = 1
      Top = 1
      Width = 299
      Height = 87
      Align = alLeft
      Caption = 'Socket Server'
      TabOrder = 2
      object mArduinoServerPortE: TIntegerLabeledEdit
        Left = 184
        Top = 28
        Width = 96
        Height = 31
        EditLabel.Width = 33
        EditLabel.Height = 23
        EditLabel.Caption = 'Port'
        LabelPosition = lpLeft
        TabOrder = 0
        Text = '50000'
        Value = 50000
      end
      object mArduinoServerStartBtn: TButton
        Left = 11
        Top = 27
        Width = 126
        Height = 55
        Caption = 'Start/Stop'
        TabOrder = 1
        OnClick = mArduinoServerStartBtnClick
      end
    end
  end
  object CenterPanel: TPanel
    Left = 0
    Top = 89
    Width = 990
    Height = 599
    Align = alClient
    Caption = 'CenterPanel'
    TabOrder = 1
    object Splitter1: TSplitter
      Left = 1
      Top = 419
      Width = 988
      Height = 3
      Cursor = crVSplit
      Align = alTop
      ExplicitLeft = 57
      ExplicitTop = 457
      ExplicitWidth = 821
    end
    object BottomPanel: TPanel
      Left = 1
      Top = 422
      Width = 988
      Height = 176
      Align = alClient
      TabOrder = 0
      object Panel2: TPanel
        Left = 1
        Top = 1
        Width = 986
        Height = 174
        Align = alClient
        Caption = 'Panel2'
        TabOrder = 0
        object infoMemo: TMemo
          Left = 1
          Top = 34
          Width = 984
          Height = 139
          Align = alClient
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -19
          Font.Name = 'Tahoma'
          Font.Style = []
          ParentFont = False
          ReadOnly = True
          ScrollBars = ssBoth
          TabOrder = 0
          WordWrap = False
        end
        object Panel1: TPanel
          Left = 1
          Top = 1
          Width = 984
          Height = 33
          Align = alTop
          TabOrder = 1
          object ToolBar1: TToolBar
            Left = 1
            Top = 1
            Width = 947
            Height = 31
            Align = alClient
            ButtonHeight = 30
            Caption = 'ToolBar1'
            TabOrder = 0
            object mClearLogMemoBtn: TBitBtn
              Left = 0
              Top = 0
              Width = 75
              Height = 30
              Caption = 'Clear'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              OnClick = MiscBtnClick
            end
            object LogLevelCB: TComboBox
              Left = 75
              Top = 0
              Width = 145
              Height = 31
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -19
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 1
              Text = 'INFO'
              OnChange = LogLevelCBChange
              Items.Strings = (
                'INFO'
                'DEBUG'
                'DEBUG1'
                'DEBUG2'
                'DEBUG3'
                'DEBUG4'
                'DEBUG5')
            end
          end
          object ToolBar2: TToolBar
            Left = 948
            Top = 1
            Width = 35
            Height = 31
            Align = alRight
            AutoSize = True
            ButtonHeight = 30
            Caption = 'ToolBar1'
            List = True
            AllowTextButtons = True
            TabOrder = 1
            Wrapable = False
            object mHideBottomPanelBtn: TBitBtn
              Left = 0
              Top = 0
              Width = 35
              Height = 30
              Align = alRight
              Caption = 'x'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -16
              Font.Name = 'Tahoma'
              Font.Style = []
              ParentFont = False
              TabOrder = 0
              OnClick = MiscBtnClick
            end
          end
        end
      end
    end
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 988
      Height = 418
      ActivePage = TabSheet1
      Align = alTop
      TabOrder = 1
      object TabSheet1: TTabSheet
        Caption = 'Controls'
        object GroupBox4: TGroupBox
          Left = 0
          Top = 0
          Width = 463
          Height = 380
          Align = alLeft
          Caption = 'Lights'
          TabOrder = 0
          object mFrontBackLEDBtn: TArrayBotButton
            Left = 18
            Top = 37
            Width = 200
            Height = 80
            Caption = 'Flip LEDs ON'
            ParentDoubleBuffered = True
            TabOrder = 0
            OnClick = LigthsBtnsClick
            SoundID = 'BUTTON_CLICK_4'
          end
        end
      end
      object TabSheet2: TTabSheet
        Caption = 'Board Settings'
        ImageIndex = 1
        ExplicitLeft = 0
        ExplicitTop = 0
        ExplicitWidth = 0
        ExplicitHeight = 0
        object mArduinoSB: TScrollBox
          Left = 0
          Top = 0
          Width = 980
          Height = 380
          Align = alClient
          TabOrder = 0
        end
      end
    end
  end
  object mShowBottomPanelBtn: TButton
    Left = 0
    Top = 688
    Width = 990
    Height = 19
    Align = alBottom
    Caption = '^'
    TabOrder = 2
    Visible = False
    OnClick = mShowBottomPanelBtnClick
  end
  object ActionList1: TActionList
    Left = 164
    Top = 464
    object checkForDevices: TAction
      Caption = 'Devices Check'
    end
    object addDevicesToListBox: TAction
      Caption = 'Connect All'
    end
    object identifyCurrent: TAction
      Caption = 'Identify'
    end
    object homeDevice: TAction
      Caption = 'Home'
    end
    object jogForward: TAction
      Caption = 'Fwd'
    end
    object jogBackwards: TAction
      Caption = 'Rev'
    end
    object moveForward: TAction
      Caption = 'Forward'
    end
    object moveBackward: TAction
      Caption = 'Backward'
    end
    object stopAllA: TAction
      Caption = 'Stop All'
    end
    object reInitBotA: TAction
      Caption = 'Reinitialize Devices'
    end
    object ShutDownA: TAction
      Caption = 'Disconnect Devices'
    end
    object FileExit1: TFileExit
      Caption = 'E&xit'
      Hint = 'Exit|Quits the application'
      ImageIndex = 0
    end
    object abortLiftA: TAction
      Caption = 'Abort Lift'
    end
    object liftA: TAction
      Caption = 'Lift'
    end
  end
  object ShutDownTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = ShutDownTimerTimer
    Left = 260
    Top = 400
  end
  object ApplicationEvents1: TApplicationEvents
    OnException = ApplicationEvents1Exception
    Left = 32
    Top = 464
  end
  object UIUpdateTimer: TTimer
    Enabled = False
    Interval = 300
    OnTimer = UIUpdateTimerTimer
    Left = 260
    Top = 464
  end
end
