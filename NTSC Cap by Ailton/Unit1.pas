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
    XPManifest1: TXPManifest;
    Button3: TButton;
    PageControl1: TPageControl;
    TabSheet1: TTabSheet;
    TabSheet2: TTabSheet;
    TabSheet3: TTabSheet;
    Image2: TImage;
    TrackBar2: TTrackBar;
    Label3: TLabel;
    Chart1: TChart;
    Series1: TLineSeries;
    LinhaSelecionada: TLabel;
    Image3: TImage;
    Image5: TImage;
    Image4: TImage;
    TrackBar1: TTrackBar;
    Image6: TImage;
    Button4: TButton;
    Button5: TButton;
    Series2: TLineSeries;
    Series3: TLineSeries;
    Maximo: TLabel;
    Minimo: TLabel;
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

function CropBitmap(Original: Tbitmap; x0, y0, x1, y1: Integer) : TBitmap;
var i,j: integer;
begin
  Result := TBitmap.Create;
  Result.Width := x1-x0;
  Result.Height := y1-y0;
  for i:=x0 to x1 do
  begin
    for j:=y0 to y1 do
    begin
      Result.Canvas.Pixels[i-x0,j-y0] := Original.Canvas.Pixels[i,j];
    end;
  end;
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
    MiImg: TBitmap;
begin
  ComPort1.ReadStr(buffer,Count);
  meubuf := Ord(buffer[1]);

  if praCapturar then
  begin

  if meubuf = 255 then
    begin
      posx := 0;
      posy := 0;
      Image2.picture.bitmap := resizebitmap(Image1.Picture.bitmap,920,505);
      if contaCaps > 1 then contaCaps:=contaCaps-1;
      if contaCaps = 1 then
        begin
        praCapturar := false;
        contaCaps := 0;
        ////////////
        MiImg := CropBitmap(Image1.Picture.bitmap,2,0,75,60);
        Image4.Picture.Bitmap := resizebitmap(MiImg,385,289);
        Image6.Picture.Bitmap := resizebitmap(MiImg,72,60);
        end;
      ComPort1.ClearBuffer(True,True);
    end
  else
    if meubuf = 250 then
      begin
      posx := 0;
      posy := posy+1;
      for i:=0 to 90 do
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
var i,aux,aux2, aux3,aux4, menorA, maiorA: integer;
begin
  Series1.Clear;
  Series2.Clear;
  Series3.Clear;
  menorA := 255;
  maiorA := 0;
  LinhaSelecionada.Caption := 'Linha selecionada: ' + IntToStr(59 - TrackBar1.Position);
  for i := 0 to 71 do
  begin
    aux := GetRValue(Image6.Canvas.Pixels[i, TrackBar1.Position]);
    Series1.Add(aux);
    if aux > maiorA then maiorA := aux;
    if aux < menorA then menorA := aux;
  end;
  Maximo.Caption := 'Maximo: ' + IntToStr(maiorA);
  Minimo.Caption := 'Minimo: ' + IntToStr(menorA);

  for i := 0 to 71 do
  begin
    aux := GetRValue(Image6.Canvas.Pixels[i, TrackBar1.Position]);
    aux2 := GetRValue(Image6.Canvas.Pixels[i+1, TrackBar1.Position]);
    aux3 := GetRValue(Image6.Canvas.Pixels[i+2, TrackBar1.Position]);
    aux4 := aux*(0)+aux2*(-1)+aux3*(1);
    if i < 69 then Series3.Add(aux4);
  end;

  aux := trunc(((maiorA - menorA)/2)+ menorA);
  for i := 0 to 71 do Series2.Add(aux);
  for i:=0 to 289 do
  begin
    Image4.Canvas.Pixels[384, i] := RGB(0,0,0);
    Image4.Canvas.Pixels[383, i] := RGB(0,0,0);
    Image4.Canvas.Pixels[382, i] := RGB(0,0,0);
  end;
  for i:=0 to 3 do
  begin
    Image4.Canvas.Pixels[384, Trunc(TrackBar1.Position*((Image4.Height)/60))+i] := RGB(0,255,0);
    Image4.Canvas.Pixels[383, Trunc(TrackBar1.Position*((Image4.Height)/60))+i] := RGB(0,255,0);
    Image4.Canvas.Pixels[382, Trunc(TrackBar1.Position*((Image4.Height)/60))+i] := RGB(0,255,0);
  end;

end;

procedure TForm1.TrackBar2Change(Sender: TObject);
var lima,i,j: integer;
buffimg: TBitmap;
begin
  buffimg := resizebitmap(Image1.Picture.Bitmap,90,70);
  lima := TrackBar2.Position;
  for i:=0 to 70 do
    for j:=0 to 90 do
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
  Image1.Picture.Bitmap := resizebitmap(buffimg,90,70);
end;

end.
