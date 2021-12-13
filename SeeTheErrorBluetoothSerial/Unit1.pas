unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, CPort, CPortCtl, TeEngine, Series, ExtCtrls, TeeProcs,
  Chart, ComCtrls;

type
  TForm1 = class(TForm)
    ComPort1: TComPort;
    Label1: TLabel;
    Button1: TButton;
    Label2: TLabel;
    Button2: TButton;
    Button3: TButton;
    Label3: TLabel;
    Edit2: TEdit;
    Edit3: TEdit;
    Button4: TButton;
    Combo1: TComboBox;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    Chart1: TChart;
    Series1: TLineSeries;
    RadioGroup1: TRadioGroup;
    Button5: TButton;
    Button6: TButton;
    ComTerminal1: TComTerminal;
    ComPort2: TComPort;
    Button7: TButton;
    ComboBox1: TComboBox;
    Label4: TLabel;
    ComboBox2: TComboBox;
    Label5: TLabel;
    ComboBox3: TComboBox;
    Label6: TLabel;
    ComboBox4: TComboBox;
    Label7: TLabel;
    ComboBox5: TComboBox;
    Button8: TButton;
    Timer1: TTimer;
    Edit1: TEdit;
    Label8: TLabel;
    Button9: TButton;
    procedure Button1Click(Sender: TObject);
    procedure ComPort1RxChar(Sender: TObject; Count: Integer);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure RadioGroup1Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure Timer1Timer(Sender: TObject);
    procedure Button9Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  ContPids: integer;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
  ContPids := 0;
  if RadioGroup1.ItemIndex = 0 then
    begin
    ComTerminal1.ComPort := ComPort2;
    end
  else
    begin
    ComTerminal1.ComPort := ComPort1;
    end;
  Series1.Clear();
  ComPort1.Port := Combo1.Text;
  ComPort1.Open();
  if ComPort1.Connected then
  begin
    Label2.Caption := 'Porta Aberta!';
  end;
end;

procedure TForm1.ComPort1RxChar(Sender: TObject; Count: Integer);
var buffer: AnsiString;
meubuf: integer;
begin
  ComPort1.ReadStr(buffer,Count);
  meubuf := Ord(buffer[1]);
  if RadioGroup1.ItemIndex = 0 then
    begin
    Series1.Add(meubuf);
    end;
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  Series1.Clear;
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  ComPort1.Close();
  Label2.Caption := 'Porta Fechada';
  if Edit1.Text = '' then
  Chart1.SaveToBitmapFile('saves/TRAC_'+ ComboBox2.Text +'-KP_'+ ComboBox3.Text +'-KD_'+ ComboBox4.Text +'-KI_'+ ComboBox5.Text +'.bmp')
  else
  Chart1.SaveToBitmapFile('saves/'+ Edit1.Text +'.bmp');
end;

procedure TForm1.Button4Click(Sender: TObject);
begin
  Chart1.LeftAxis.Maximum:= StrToFloat(Edit3.Text);
  Chart1.LeftAxis.Minimum:= StrToFloat(Edit2.Text);
end;

procedure TForm1.Button5Click(Sender: TObject);
begin
  ComPort1.WriteStr(ComboBox1.Text + #10 + #13);
end;

procedure TForm1.Button6Click(Sender: TObject);
begin
  ComTerminal1.ClearScreen;
end;

procedure TForm1.RadioGroup1Click(Sender: TObject);
begin
    if RadioGroup1.ItemIndex = 0 then
    begin
    ComTerminal1.ComPort := ComPort2;
    TabSheet1.Show;
    end
  else
    begin
    ComTerminal1.ComPort := ComPort1;
    TabSheet2.Show;
    end;
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
  RadioGroup1.ItemIndex := 0;
  ComTerminal1.ComPort := ComPort2;
  TabSheet1.Show;
  ComPort1.WriteStr('Z99X');
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
  Button8.Enabled := False;
  Timer1.Enabled := True;
end;

procedure TForm1.Timer1Timer(Sender: TObject);
begin
  if ContPids = 0 then
    begin
    ComPort1.WriteStr('Z01=' + ComboBox2.Text + 'X' + #10 + #13);
    end
  else if ContPids = 1 then
    begin
    ComPort1.WriteStr('Z09=' + ComboBox3.Text + 'X' + #10 + #13);
    end
  else if ContPids = 2 then
    begin
      ComPort1.WriteStr('Z10=' + ComboBox5.Text + 'X' + #10 + #13);
    end
  else if ContPids = 3 then
    begin
    ComPort1.WriteStr('Z11=' + ComboBox4.Text + 'X' + #10 + #13);
    end;
  ContPids := ContPids + 1;
  if ContPids > 3 then
    begin
    ContPids := 0;
    Timer1.Enabled := false;
    Button8.Enabled := true;
    end;
end;

procedure TForm1.Button9Click(Sender: TObject);
begin
    ComPort1.Close();
    Label2.Caption := 'Porta Fechada';
end;

end.
