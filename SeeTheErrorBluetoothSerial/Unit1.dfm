object Form1: TForm1
  Left = 260
  Top = 124
  Width = 1043
  Height = 550
  VertScrollBar.Position = 202
  Caption = 'SeeTheError by Ailton'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 408
    Top = 476
    Width = 25
    Height = 13
    Caption = 'Porta'
  end
  object Label2: TLabel
    Left = 880
    Top = 476
    Width = 3
    Height = 13
  end
  object Label3: TLabel
    Left = 640
    Top = 476
    Width = 32
    Height = 13
    Caption = 'Range'
  end
  object Button1: TButton
    Left = 560
    Top = 470
    Width = 75
    Height = 25
    Caption = 'Conectar'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 470
    Width = 81
    Height = 25
    Caption = 'Limpar Grafico'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 152
    Top = 470
    Width = 73
    Height = 25
    Caption = 'Print / Parar'
    TabOrder = 2
    OnClick = Button3Click
  end
  object Edit2: TEdit
    Left = 680
    Top = 472
    Width = 49
    Height = 21
    TabOrder = 3
    Text = '65'
  end
  object Edit3: TEdit
    Left = 736
    Top = 472
    Width = 49
    Height = 21
    TabOrder = 4
    Text = '135'
  end
  object Button4: TButton
    Left = 792
    Top = 470
    Width = 75
    Height = 25
    Caption = 'Apply'
    TabOrder = 5
    OnClick = Button4Click
  end
  object Combo1: TComboBox
    Left = 440
    Top = 472
    Width = 113
    Height = 21
    ItemHeight = 13
    TabOrder = 6
    Text = 'COM10'
    Items.Strings = (
      'COM1'
      'COM2'
      'COM3'
      'COM4'
      'COM5'
      'COM10'
      'COM246'
      'COM247'
      'COM248')
  end
  object PageControl1: TPageControl
    Left = 0
    Top = -195
    Width = 1361
    Height = 647
    ActivePage = TabSheet1
    BiDiMode = bdLeftToRight
    ParentBiDiMode = False
    TabOrder = 7
    TabPosition = tpBottom
    object TabSheet1: TTabSheet
      Caption = 'Gr'#225'fico'
      object Chart1: TChart
        Left = 0
        Top = 4
        Width = 1345
        Height = 629
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        PrintProportional = False
        Title.Text.Strings = (
          'TChart')
        Title.Visible = False
        BottomAxis.ExactDateTime = False
        LeftAxis.Automatic = False
        LeftAxis.AutomaticMaximum = False
        LeftAxis.AutomaticMinimum = False
        LeftAxis.Maximum = 135.000000000000000000
        LeftAxis.Minimum = 65.000000000000000000
        Legend.Visible = False
        View3D = False
        TabOrder = 0
        object Series1: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clRed
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1.000000000000000000
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1.000000000000000000
          YValues.Order = loNone
        end
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Terminal'
      ImageIndex = 1
      object Label4: TLabel
        Left = 544
        Top = 598
        Width = 53
        Height = 13
        Caption = 'Velocidade'
      end
      object Label5: TLabel
        Left = 688
        Top = 598
        Width = 13
        Height = 13
        Caption = 'Kp'
      end
      object Label6: TLabel
        Left = 776
        Top = 598
        Width = 13
        Height = 13
        Caption = 'Kd'
      end
      object Label7: TLabel
        Left = 856
        Top = 598
        Width = 9
        Height = 13
        Caption = 'Ki'
      end
      object Label8: TLabel
        Left = 1048
        Top = 598
        Width = 84
        Height = 13
        Caption = 'Salvar com Nome'
      end
      object Button5: TButton
        Left = 80
        Top = 592
        Width = 49
        Height = 25
        Caption = 'Send'
        TabOrder = 0
        OnClick = Button5Click
      end
      object Button6: TButton
        Left = 136
        Top = 592
        Width = 49
        Height = 25
        Caption = 'Clear'
        TabOrder = 1
        OnClick = Button6Click
      end
      object ComTerminal1: TComTerminal
        Left = 8
        Top = 0
        Width = 1353
        Height = 585
        Color = clWhite
        Columns = 110
        Emulation = teVT100orANSI
        Font.Charset = ANSI_CHARSET
        Font.Color = clBlack
        Font.Height = -16
        Font.Name = 'Courier New'
        Font.Style = []
        ScrollBars = ssBoth
        SmoothScroll = True
        TabOrder = 2
        WrapLines = True
      end
      object Button7: TButton
        Left = 8
        Top = 592
        Width = 65
        Height = 25
        Caption = 'START'
        TabOrder = 3
        OnClick = Button7Click
      end
      object ComboBox1: TComboBox
        Left = 192
        Top = 591
        Width = 345
        Height = 27
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Consolas'
        Font.Style = []
        ItemHeight = 19
        ItemIndex = 2
        ParentFont = False
        TabOrder = 4
        Text = 'Z01=500X'
        Items.Strings = (
          'Z01=999X'
          'Z01=700X'
          'Z01=500X'
          'Z01=200X'
          'Z01=1X'
          'Z09=700X'
          'Z09=800X'
          'Z09=900X'
          'Z09=1000X'
          'Z09=1250X'
          'Z09=1500X'
          'Z09=2000X'
          'Z09=3000X')
      end
      object ComboBox2: TComboBox
        Left = 608
        Top = 594
        Width = 65
        Height = 21
        ItemHeight = 13
        ItemIndex = 5
        TabOrder = 5
        Text = '450'
        Items.Strings = (
          '1'
          '100'
          '200'
          '300'
          '400'
          '450'
          '500'
          '550'
          '600'
          '650'
          '700'
          '750'
          '800'
          '850'
          '999')
      end
      object ComboBox3: TComboBox
        Left = 704
        Top = 594
        Width = 65
        Height = 21
        ItemHeight = 13
        TabOrder = 6
        Text = '1000'
        Items.Strings = (
          '125'
          '250'
          '500'
          '750'
          '900'
          '1000'
          '1100'
          '1200'
          '1300'
          '1400'
          '1500'
          '2000'
          '3000'
          '4000'
          '4500'
          '5000'
          '6000')
      end
      object ComboBox4: TComboBox
        Left = 792
        Top = 594
        Width = 57
        Height = 21
        ItemHeight = 13
        TabOrder = 7
        Text = '4500'
        Items.Strings = (
          '0'
          '125'
          '250'
          '500'
          '750'
          '900'
          '1000'
          '1100'
          '1200'
          '1300'
          '1400'
          '1500'
          '2000'
          '3000'
          '4000'
          '4500'
          '5000'
          '6000')
      end
      object ComboBox5: TComboBox
        Left = 872
        Top = 594
        Width = 65
        Height = 21
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 8
        Text = '0'
        Items.Strings = (
          '0'
          '125'
          '250'
          '500'
          '750'
          '900'
          '1000'
          '1100'
          '1200'
          '1300'
          '1400'
          '1500'
          '2000'
          '3000'
          '4000'
          '4500'
          '5000'
          '6000')
      end
      object Button8: TButton
        Left = 944
        Top = 592
        Width = 75
        Height = 25
        Caption = 'Send PID'
        TabOrder = 9
        OnClick = Button8Click
      end
      object Edit1: TEdit
        Left = 1144
        Top = 594
        Width = 89
        Height = 21
        TabOrder = 10
      end
    end
  end
  object RadioGroup1: TRadioGroup
    Left = 225
    Top = 466
    Width = 177
    Height = 33
    Align = alCustom
    BiDiMode = bdLeftToRight
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      'Gr'#225'fico'
      'Terminal')
    ParentBiDiMode = False
    TabOrder = 8
    OnClick = RadioGroup1Click
  end
  object Button9: TButton
    Left = 96
    Top = 470
    Width = 49
    Height = 25
    Caption = 'Parar'
    TabOrder = 9
    OnClick = Button9Click
  end
  object ComPort1: TComPort
    BaudRate = br9600
    Port = 'COM1'
    Parity.Bits = prNone
    StopBits = sbOneStopBit
    DataBits = dbEight
    Events = [evRxChar, evTxEmpty, evRxFlag, evRing, evBreak, evCTS, evDSR, evError, evRLSD, evRx80Full]
    FlowControl.OutCTSFlow = False
    FlowControl.OutDSRFlow = False
    FlowControl.ControlDTR = dtrDisable
    FlowControl.ControlRTS = rtsDisable
    FlowControl.XonXoffOut = False
    FlowControl.XonXoffIn = False
    OnRxChar = ComPort1RxChar
    Left = 888
    Top = 672
  end
  object ComPort2: TComPort
    BaudRate = br9600
    Port = 'COM1'
    Parity.Bits = prNone
    StopBits = sbOneStopBit
    DataBits = dbEight
    Events = [evRxChar, evTxEmpty, evRxFlag, evRing, evBreak, evCTS, evDSR, evError, evRLSD, evRx80Full]
    FlowControl.OutCTSFlow = False
    FlowControl.OutDSRFlow = False
    FlowControl.ControlDTR = dtrDisable
    FlowControl.ControlRTS = rtsDisable
    FlowControl.XonXoffOut = False
    FlowControl.XonXoffIn = False
    Left = 928
    Top = 672
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 500
    OnTimer = Timer1Timer
    Left = 1168
    Top = 671
  end
end
