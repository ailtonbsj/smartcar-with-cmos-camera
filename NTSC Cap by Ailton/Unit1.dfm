object Form1: TForm1
  Left = 99
  Top = 124
  Width = 1263
  Height = 622
  Caption = 'NTSC Capture by Ailton'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 495
    Top = 39
    Width = 55
    Height = 70
    Stretch = True
  end
  object Image2: TImage
    Left = 8
    Top = 8
    Width = 440
    Height = 560
  end
  object Label1: TLabel
    Left = 496
    Top = 544
    Width = 163
    Height = 24
    Caption = 'Linha selecionada: '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 712
    Top = 24
    Width = 496
    Height = 75
    Caption = 'NTSC-Cap  by Ailton'
    Font.Charset = ANSI_CHARSET
    Font.Color = clBlack
    Font.Height = -64
    Font.Name = 'Arial Narrow'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 864
    Top = 108
    Width = 60
    Height = 24
    Caption = 'Limiar: '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Button1: TButton
    Left = 496
    Top = 8
    Width = 97
    Height = 25
    Caption = 'Configurar'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 600
    Top = 8
    Width = 97
    Height = 25
    Caption = 'Conectar'
    TabOrder = 1
    OnClick = Button2Click
  end
  object TrackBar1: TTrackBar
    Left = 456
    Top = 8
    Width = 33
    Height = 569
    Max = 69
    Orientation = trVertical
    TabOrder = 2
    TickMarks = tmTopLeft
    TickStyle = tsNone
    OnChange = TrackBar1Change
  end
  object Chart1: TChart
    Left = 480
    Top = 152
    Width = 761
    Height = 385
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Title.Text.Strings = (
      'Linha Selecionada')
    BottomAxis.Automatic = False
    BottomAxis.AutomaticMaximum = False
    BottomAxis.AutomaticMinimum = False
    BottomAxis.Maximum = 54.000000000000000000
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Maximum = 130.000000000000000000
    View3D = False
    TabOrder = 3
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
  object Button3: TButton
    Left = 600
    Top = 40
    Width = 99
    Height = 25
    Caption = 'Capturar Quadro'
    TabOrder = 4
    OnClick = Button3Click
  end
  object TrackBar2: TTrackBar
    Left = 488
    Top = 112
    Width = 369
    Height = 25
    Max = 255
    TabOrder = 5
    TickStyle = tsNone
    OnChange = TrackBar2Change
  end
  object Button4: TButton
    Left = 600
    Top = 72
    Width = 97
    Height = 25
    Caption = 'Media Autom'#225'tica'
    TabOrder = 6
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 992
    Top = 112
    Width = 81
    Height = 25
    Caption = 'Cortar Imagem'
    TabOrder = 7
    OnClick = Button5Click
  end
  object Edit1: TEdit
    Left = 768
    Top = 552
    Width = 473
    Height = 21
    TabOrder = 8
    Text = 'Edit1'
  end
  object ComPort1: TComPort
    BaudRate = br9600
    Port = 'COM5'
    Parity.Bits = prNone
    StopBits = sbOneStopBit
    DataBits = dbEight
    Events = [evRxChar, evTxEmpty, evRxFlag, evRing, evBreak, evCTS, evDSR, evError, evRLSD, evRx80Full]
    Buffer.InputSize = 12600
    Buffer.OutputSize = 12600
    FlowControl.OutCTSFlow = False
    FlowControl.OutDSRFlow = False
    FlowControl.ControlDTR = dtrDisable
    FlowControl.ControlRTS = rtsDisable
    FlowControl.XonXoffOut = False
    FlowControl.XonXoffIn = False
    OnRxChar = ComPort1RxChar
    Left = 1208
    Top = 48
  end
  object XPManifest1: TXPManifest
    Left = 1216
    Top = 16
  end
end
