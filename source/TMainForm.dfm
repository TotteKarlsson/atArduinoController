object MainForm: TMainForm
  Left = 0
  Top = 0
  Caption = 'Arduino Controller'
  ClientHeight = 697
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
  object Splitter1: TSplitter
    Left = 0
    Top = 485
    Width = 990
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    ExplicitLeft = 32
    ExplicitTop = 657
  end
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
  object mShowBottomPanelBtn: TButton
    Left = 0
    Top = 678
    Width = 990
    Height = 19
    Align = alBottom
    Caption = '^'
    TabOrder = 1
    Visible = False
    OnClick = mShowBottomPanelBtnClick
  end
  object BottomPanel: TPanel
    Left = 0
    Top = 488
    Width = 990
    Height = 190
    Align = alBottom
    TabOrder = 2
    object Panel2: TPanel
      Left = 1
      Top = 1
      Width = 988
      Height = 188
      Align = alClient
      Caption = 'Panel2'
      TabOrder = 0
      object infoMemo: TMemo
        Left = 1
        Top = 34
        Width = 986
        Height = 153
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
        Width = 986
        Height = 33
        Align = alTop
        TabOrder = 1
        object ToolBar1: TToolBar
          Left = 1
          Top = 1
          Width = 949
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
          Left = 950
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
    Left = 0
    Top = 89
    Width = 990
    Height = 396
    ActivePage = TabSheet1
    Align = alClient
    TabOrder = 3
    object TabSheet1: TTabSheet
      Caption = 'Controls'
      object GroupBox4: TGroupBox
        Left = 0
        Top = 0
        Width = 463
        Height = 358
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
        Width = 982
        Height = 358
        Align = alClient
        TabOrder = 0
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'ATDB'
      ImageIndex = 2
      inline TATDBConnectionFrame1: TATDBConnectionFrame
        Left = 0
        Top = 0
        Width = 313
        Height = 358
        Align = alLeft
        TabOrder = 0
        ExplicitWidth = 313
        ExplicitHeight = 358
        inherited GroupBox1: TGroupBox
          Width = 313
          Height = 358
          Align = alClient
          ExplicitWidth = 313
          ExplicitHeight = 358
          inherited mServerIPE: TSTDStringLabeledEdit
            Top = 57
            Height = 31
            EditLabel.Width = 77
            EditLabel.Height = 23
            EditLabel.ExplicitLeft = 16
            EditLabel.ExplicitTop = 31
            EditLabel.ExplicitWidth = 77
            EditLabel.ExplicitHeight = 23
            ExplicitTop = 57
            ExplicitHeight = 31
          end
          inherited mDBUserE: TSTDStringLabeledEdit
            Top = 120
            Height = 31
            EditLabel.Width = 37
            EditLabel.Height = 23
            EditLabel.ExplicitLeft = 16
            EditLabel.ExplicitTop = 94
            EditLabel.ExplicitWidth = 37
            EditLabel.ExplicitHeight = 23
            ExplicitTop = 120
            ExplicitHeight = 31
          end
          inherited mPasswordE: TSTDStringLabeledEdit
            Left = 175
            Top = 120
            Height = 31
            EditLabel.Width = 78
            EditLabel.Height = 23
            EditLabel.ExplicitLeft = 175
            EditLabel.ExplicitTop = 94
            EditLabel.ExplicitWidth = 78
            EditLabel.ExplicitHeight = 23
            ExplicitLeft = 175
            ExplicitTop = 120
            ExplicitHeight = 31
          end
          inherited mATDBServerBtnConnect: TArrayBotButton
            Left = 16
            Top = 241
            Width = 234
            OnClick = TATDBConnectionFrame1mATDBServerBtnConnectClick
            ExplicitLeft = 16
            ExplicitTop = 241
            ExplicitWidth = 234
          end
          inherited mDatabaseE: TSTDStringLabeledEdit
            Left = 175
            Top = 52
            Height = 31
            EditLabel.Width = 78
            EditLabel.Height = 23
            EditLabel.ExplicitLeft = 175
            EditLabel.ExplicitTop = 26
            EditLabel.ExplicitWidth = 78
            EditLabel.ExplicitHeight = 23
            ExplicitLeft = 175
            ExplicitTop = 52
            ExplicitHeight = 31
          end
        end
      end
    end
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
