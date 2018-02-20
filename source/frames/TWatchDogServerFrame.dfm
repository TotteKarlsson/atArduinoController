object WatchDogServerFrame: TWatchDogServerFrame
  Left = 0
  Top = 0
  Width = 883
  Height = 306
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 297
    Height = 306
    Align = alLeft
    Caption = 'WatchDog Server Settings'
    TabOrder = 0
    object ServerIPE: TSTDStringLabeledEdit
      Left = 17
      Top = 48
      Width = 193
      Height = 21
      EditLabel.Width = 45
      EditLabel.Height = 13
      EditLabel.Caption = 'Server IP'
      TabOrder = 0
      Text = '192.168.123.123'
      Value = '192.168.123.123'
    end
    object WalkBtn: TArrayBotButton
      Left = 216
      Top = 46
      Width = 75
      Height = 44
      Caption = 'Walk'
      TabOrder = 1
      OnClick = WalkBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
    object ReadSensorsBtn: TArrayBotButton
      Left = 17
      Top = 152
      Width = 256
      Height = 49
      Caption = 'Read Sensors'
      TabOrder = 2
      OnClick = ReadSensorsBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
    object StartReadsBtn: TArrayBotButton
      Left = 17
      Top = 224
      Width = 256
      Height = 49
      Caption = 'Start Periodic Reads'
      TabOrder = 3
      OnClick = StartReadsBtnClick
      SoundID = 'BUTTON_CLICK_4'
    end
  end
  object SensorPanel: TFlowPanel
    Left = 297
    Top = 0
    Width = 586
    Height = 306
    Align = alClient
    TabOrder = 1
  end
  object EnvSensorsReadsTimer: TTimer
    Enabled = False
    Interval = 60000
    OnTimer = EnvSensorsReadsTimerTimer
    Left = 64
    Top = 88
  end
end
