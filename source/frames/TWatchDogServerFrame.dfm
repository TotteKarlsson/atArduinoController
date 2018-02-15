object WatchDogServerFrame: TWatchDogServerFrame
  Left = 0
  Top = 0
  Width = 397
  Height = 315
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 397
    Height = 315
    Align = alClient
    Caption = 'WatchDog Server Settings'
    TabOrder = 0
    ExplicitWidth = 257
    ExplicitHeight = 169
    object STDStringLabeledEdit1: TSTDStringLabeledEdit
      Left = 16
      Top = 64
      Width = 193
      Height = 42
      EditLabel.Width = 45
      EditLabel.Height = 13
      EditLabel.Caption = 'Server IP'
      TabOrder = 0
      Text = '192.168.123.123'
      Value = '192.168.123.123'
    end
    object GroupBox2: TGroupBox
      Left = 16
      Top = 112
      Width = 241
      Height = 193
      Caption = 'MIB'#39's'
      TabOrder = 1
      object mMIBRoot: TSTDStringLabeledEdit
        Left = 25
        Top = 48
        Width = 177
        Height = 21
        EditLabel.Width = 44
        EditLabel.Height = 13
        EditLabel.Caption = 'MIB Root'
        TabOrder = 0
        Text = '1.3.1.6.4.21239.5.1'
        Value = '1.3.1.6.4.21239.5.1'
      end
      object STDStringLabeledEdit3: TSTDStringLabeledEdit
        Left = 25
        Top = 120
        Width = 177
        Height = 21
        EditLabel.Width = 65
        EditLabel.Height = 13
        EditLabel.Caption = 'Get Server IP'
        TabOrder = 1
        Text = '1.5.0'
        Value = '1.5.0'
      end
    end
    object ArrayBotButton1: TArrayBotButton
      Left = 215
      Top = 62
      Width = 75
      Height = 44
      Caption = 'Walk'
      TabOrder = 2
      SoundID = 'BUTTON_CLICK_4'
    end
  end
end
