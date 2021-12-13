unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, CPort, ExtCtrls, TeEngine, TeeFunci, Series,
  TeeProcs, Chart, ComCtrls, XPMan;

type
  TForm1 = class(TForm)
    ComPort1: TComPort;
    Button1: TButton;
    Button2: TButton;
    Image1: TImage;
    Image2: TImage;
    TrackBar1: TTrackBar;
    XPManifest1: TXPManifest;
    Chart1: TChart;
    Series1: TLineSeries;
    Label1: TLabel;
    Label2: TLabel;
    Button3: TButton;
    Label3: TLabel;
    TrackBar2: TTrackBar;
    Button4: TButton;
    Button5: TButton;
    Edit1: TEdit;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure ComPort1RxChar(Sender: TObject; Count: Integer);
    procedure TrackBar1Change(Sender: TObject);
    procedure TrackBar2Change(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  posx: integer;
  posy: integer;
  contaCaps: integer;
  praCapturar: boolean;
implementation

uses Math;

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
  ComPort1.ShowSetupDialog();
end;

function ResizeBitmap(Original: Tbitmap; ToWidth, ToHeight: Integer): TBitmap;
begin
  Result := TBitmap.Create;
  Result.Width := ToWidth;
  Result.Height := ToHeight;
  Result.Canvas.StretchDraw(Rect(0, 0, ToWidth, ToHeight), Original);
end;

procedure TForm1.Button2Click(Sender: TObject);
begin
  praCapturar := True;
  contaCaps := 0;

  if not ComPort1.Connected then
    begin
    ComPort1.Open();
    ComPort1.ClearBuffer(True,True)
    end
  else
    ComPort1.Close();
  if ComPort1.Connected then
    Button2.Caption := 'Desconectar'
  else
    Button2.Caption := 'conectar';
end;

procedure TForm1.ComPort1RxChar(Sender: TObject; Count: Integer);
var buffer: AnsiString;
    meubuf, i: integer;
begin
  ComPort1.ReadStr(buffer,Count);
  meubuf := Ord(buffer[1]);

  if praCapturar then
  begin

  if meubuf = 255 then
    begin
      posx := 0;
      posy := 0;
      Image2.picture.bitmap := resizebitmap(Image1.Picture.bitmap,440,560);
      if contaCaps > 1 then contaCaps:=contaCaps-1;
      if contaCaps = 1 then
        begin
        praCapturar := false;
        contaCaps := 0;
        end;
      ComPort1.ClearBuffer(True,True);
    end
  else
    if meubuf = 250 then
      begin
      posx := 0;
      posy := posy+1;
      for i:=0 to 55 do
        Image1.Picture.Bitmap.Canvas.Pixels[i,posy+1] := RGB(255,0,0);
      end
    else
    begin
          Image1.Canvas.Pixels[posx,posy] := RGB(meubuf,meubuf,meubuf);
          posx := posx + 1;
    end;
  end;
end;

procedure TForm1.TrackBar1Change(Sender: TObject);
var i: integer;
begin
  Series1.Clear;
  Label1.Caption := 'Linha selecionada: ' + IntToStr(TrackBar1.Position);
  for i := 0 to 75 do
  begin
    Series1.Add(GetRValue(Image1.Canvas.Pixels[i, TrackBar1.Position]));
  end;
  for i:=0 to 560 do
  begin
    Image2.Canvas.Pixels[437, i] := RGB(0,0,0);
    Image2.Canvas.Pixels[438, i] := RGB(0,0,0);
    Image2.Canvas.Pixels[439, i] := RGB(0,0,0);
  end;
  for i:=0 to 3 do
  begin
    Image2.Canvas.Pixels[437, (TrackBar1.Position*8)+2+i] := RGB(0,255,0);
    Image2.Canvas.Pixels[438, (TrackBar1.Position*8)+2+i] := RGB(0,255,0);
    Image2.Canvas.Pixels[439, (TrackBar1.Position*8)+2+i] := RGB(0,255,0);
  end;

end;

procedure TForm1.TrackBar2Change(Sender: TObject);
var lima,i,j: integer;
buffimg: TBitmap;
begin
  buffimg := resizebitmap(Image1.Picture.Bitmap,55,70);
  lima := TrackBar2.Position;
  for i:=0 to 70 do
    for j:=0 to 55 do
      begin
        if GetRValue(buffimg.Canvas.Pixels[j,i]) > lima then
        buffimg.Canvas.Pixels[j,i] := RGB(254,254,254)
        else
        buffimg.Canvas.Pixels[j,i] := RGB(2,2,2);
      end;
  Image2.picture.bitmap := resizebitmap(buffimg,440,560);
  Label3.Caption := 'Limiar: ' + IntToStr(lima);
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  contaCaps :=3;
end;

procedure TForm1.Button4Click(Sender: TObject);
var buffimg: TBitmap;
lima,i,j, max, min: integer;
begin
  buffimg := TBitmap.Create;
  buffimg.Height := 60;
  buffimg.Width := 43;
  for i:=2 to 61 do
    for j:=7 to 49 do
      begin
        buffimg.Canvas.Pixels[j-7,i-2] := Image1.Picture.Bitmap.Canvas.Pixels[j,i];
      end;
  for i:=0 to 59 do
  begin
    max := 0;
    min := 255;
    for j:=0 to 42 do
    begin
      if (GetRValue(buffimg.Canvas.Pixels[j,i]) > max) then max := GetRValue(buffimg.Canvas.Pixels[j,i]);
      if (GetRValue(buffimg.Canvas.Pixels[j,i]) < min) then min := GetRValue(buffimg.Canvas.Pixels[j,i]);
    end;
    lima := Ceil((max+min)/2);
    Edit1.Text := Edit1.Text + IntToStr(lima) + ', ';

    for j:=0 to 59 do
    begin
      if GetRValue(buffimg.Canvas.Pixels[j,i]) > lima then
        buffimg.Canvas.Pixels[j,i] := RGB(255,255,255)
      else
        buffimg.Canvas.Pixels[j,i] := RGB(0,0,0);
    end;
  end;
  Image2.picture.bitmap := resizebitmap(buffimg,440,560);
end;

procedure TForm1.Button5Click(Sender: TObject);
var buffimg: TBitmap;
i,j: integer;
begin
  buffimg := TBitmap.Create;
  buffimg.Height := 60;
  buffimg.Width := 43;
  for i:=2 to 61 do
    for j:=7 to 49 do
      begin
        buffimg.Canvas.Pixels[j-7,i-2] := Image1.Picture.Bitmap.Canvas.Pixels[j,i];
      end;
  Image2.picture.bitmap := resizebitmap(buffimg,440,560);
  Image1.Picture.Bitmap := resizebitmap(buffimg,55,70);
end;

end.
