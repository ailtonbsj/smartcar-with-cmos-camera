object Form1: TForm1
  Left = 49
  Top = 129
  Width = 1359
  Height = 600
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
    Left = 15
    Top = 7
    Width = 85
    Height = 60
    Stretch = True
  end
  object Image5: TImage
    Left = 192
    Top = 24
    Width = 105
    Height = 105
  end
  object Label1: TLabel
    Left = 8
    Top = 168
    Width = 25
    Height = 13
    Caption = 'Porta'
  end
  object Label2: TLabel
    Left = 8
    Top = 544
    Width = 40
    Height = 13
    Caption = 'Usando:'
  end
  object Button1: TButton
    Left = 8
    Top = 72
    Width = 97
    Height = 25
    Caption = 'Configurar'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 104
    Width = 97
    Height = 25
    Caption = 'Conectar'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 8
    Top = 136
    Width = 97
    Height = 25
    Caption = 'Capturar Quadro'
    TabOrder = 2
    OnClick = Button3Click
  end
  object PageControl1: TPageControl
    Left = 112
    Top = 8
    Width = 1225
    Height = 545
    ActivePage = TabSheet3
    TabOrder = 3
    object TabSheet1: TTabSheet
      Caption = 'Visualizar'
      object Image2: TImage
        Left = 113
        Top = 8
        Width = 920
        Height = 505
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Linhas'
      ImageIndex = 1
      object LinhaSelecionada: TLabel
        Left = 8
        Top = 485
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
      object Image4: TImage
        Left = 8
        Top = 8
        Width = 385
        Height = 289
      end
      object Image6: TImage
        Left = 168
        Top = 376
        Width = 72
        Height = 60
      end
      object Maximo: TLabel
        Left = 272
        Top = 485
        Width = 77
        Height = 24
        Caption = 'Maximo: '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Minimo: TLabel
        Left = 400
        Top = 485
        Width = 72
        Height = 24
        Caption = 'Minimo: '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 40
        Top = 440
        Width = 26
        Height = 13
        Caption = 'Titulo'
      end
      object Chart1: TChart
        Left = 400
        Top = 4
        Width = 817
        Height = 477
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Text.Strings = (
          'Linha Selecionada')
        BottomAxis.Automatic = False
        BottomAxis.AutomaticMaximum = False
        BottomAxis.AutomaticMinimum = False
        BottomAxis.Maximum = 72.000000000000000000
        LeftAxis.Automatic = False
        LeftAxis.AutomaticMinimum = False
        View3D = False
        TabOrder = 0
        object Series1: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clRed
          Title = 'SignalRaw'
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
        object Series2: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = 10485760
          Title = 'Threshold'
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
        object Series3: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = False
          SeriesColor = clGreen
          Title = 'Derivate'
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
      object TrackBar1: TTrackBar
        Left = 8
        Top = 312
        Width = 393
        Height = 33
        Max = 59
        TabOrder = 1
        TickMarks = tmTopLeft
        TickStyle = tsNone
        OnChange = TrackBar1Change
      end
      object Button6: TButton
        Left = 248
        Top = 392
        Width = 137
        Height = 25
        Caption = 'Gerar M'#233'dia na Linha 59'
        TabOrder = 2
        OnClick = Button6Click
      end
      object Button7: TButton
        Left = 32
        Top = 360
        Width = 113
        Height = 25
        Caption = 'Salvar Imagem'
        TabOrder = 3
        OnClick = Button7Click
      end
      object Edit2: TEdit
        Left = 32
        Top = 456
        Width = 113
        Height = 21
        TabOrder = 4
      end
      object Button8: TButton
        Left = 32
        Top = 392
        Width = 113
        Height = 25
        Caption = 'Carregar Imagem'
        TabOrder = 5
        OnClick = Button8Click
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Processamento'
      ImageIndex = 2
      object Label3: TLabel
        Left = 5
        Top = 4
        Width = 109
        Height = 24
        Caption = 'Limiar Unico:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Image3: TImage
        Left = 0
        Top = 72
        Width = 673
        Height = 441
      end
      object Label5: TLabel
        Left = 272
        Top = 40
        Width = 85
        Height = 16
        Caption = 'DeltaAmostra:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel
        Left = 680
        Top = 88
        Width = 32
        Height = 13
        Caption = 'Label6'
      end
      object TrackBar2: TTrackBar
        Left = 112
        Top = 8
        Width = 441
        Height = 25
        Max = 255
        TabOrder = 0
        TickStyle = tsNone
        OnChange = TrackBar2Change
      end
      object Button4: TButton
        Left = 552
        Top = 0
        Width = 121
        Height = 33
        Hint = 
          'Calcula um unico limiar baseado em todos os pixeis do Quadro e a' +
          'plica Limiariza'#231#227'o com esse valor de limiar.'
        Caption = 'Limiar Unico p/Frame'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = Button4Click
      end
      object Button5: TButton
        Left = 0
        Top = 32
        Width = 97
        Height = 33
        Hint = 'Para cada linha um limiar diferente'
        Caption = 'Limiar p/ Linha'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        OnClick = Button5Click
      end
      object TrackBar3: TTrackBar
        Left = 384
        Top = 40
        Width = 289
        Height = 25
        Max = 255
        Position = 40
        TabOrder = 3
        TickStyle = tsNone
        OnChange = TrackBar3Change
      end
      object CheckBox2: TCheckBox
        Left = 152
        Top = 40
        Width = 97
        Height = 17
        Caption = 'Usar UltimoDelta'
        Checked = True
        State = cbChecked
        TabOrder = 4
      end
      object Button9: TButton
        Left = 680
        Top = 0
        Width = 137
        Height = 33
        Caption = 'Encontra Centros'
        TabOrder = 5
        OnClick = Button9Click
      end
      object Button10: TButton
        Left = 680
        Top = 48
        Width = 137
        Height = 33
        Caption = 'Encontra Parada'
        TabOrder = 6
        OnClick = Button10Click
      end
      object Button11: TButton
        Left = 832
        Top = 56
        Width = 75
        Height = 25
        Caption = 'Limpar'
        TabOrder = 7
      end
    end
  end
  object Edit1: TEdit
    Left = 8
    Top = 184
    Width = 97
    Height = 21
    TabOrder = 4
    Text = 'COM10'
  end
  object CheckBox1: TCheckBox
    Left = 8
    Top = 216
    Width = 97
    Height = 17
    Caption = 'Usar essa porta'
    TabOrder = 5
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
    Left = 8
    Top = 368
  end
  object XPManifest1: TXPManifest
    Left = 40
    Top = 368
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = '.bmp'
    InitialDir = '/capturas'
    Left = 76
    Top = 368
  end
end
