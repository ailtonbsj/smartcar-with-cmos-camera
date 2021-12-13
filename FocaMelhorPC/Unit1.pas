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
    Series2: TLineSeries;
    Series3: TLineSeries;
    Maximo: TLabel;
    Minimo: TLabel;
    Label1: TLabel;
    Edit1: TEdit;
    CheckBox1: TCheckBox;
    Label2: TLabel;
    Button6: TButton;
    Button7: TButton;
    Edit2: TEdit;
    Label4: TLabel;
    OpenDialog1: TOpenDialog;
    Button8: TButton;
    Button5: TButton;
    TrackBar3: TTrackBar;
    Label5: TLabel;
    CheckBox2: TCheckBox;
    Button9: TButton;
    Button10: TButton;
    Label6: TLabel;
    Button11: TButton;
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure ComPort1RxChar(Sender: TObject; Count: Integer);
    procedure TrackBar1Change(Sender: TObject);
    procedure TrackBar2Change(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
    procedure Button6Click(Sender: TObject);
    procedure Button7Click(Sender: TObject);
    procedure Button8Click(Sender: TObject);
    procedure TrackBar3Change(Sender: TObject);
    procedure Button9Click(Sender: TObject);
    procedure Button10Click(Sender: TObject);
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
  limiar: integer;
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
    if CheckBox1.Checked then
      ComPort1.Port := Edit1.Text;
    ComPort1.Open();
    Label2.Caption := 'Usando: ' + ComPort1.Port;
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
  for i := 1 to 71 do
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
  buffimg := TBitmap.Create;
  buffimg.Height := 60;
  buffimg.Width := 72;
  for i:=0 to 60 do
    for j:=0 to 72 do
      begin
        buffimg.Canvas.Pixels[j,i] := Image6.Picture.Bitmap.Canvas.Pixels[j,i];
      end;

  //buffimg := resizebitmap(Image6.Picture.Bitmap,90,70);
  lima := TrackBar2.Position;
  for i:=0 to 60 do
    for j:=0 to 72 do
      begin
        if GetRValue(buffimg.Canvas.Pixels[j,i]) > lima then
        buffimg.Canvas.Pixels[j,i] := RGB(254,254,254)
        else
        buffimg.Canvas.Pixels[j,i] := RGB(2,2,2);
      end;
  Image3.picture.bitmap := resizebitmap(buffimg,673,441);
  Label3.Caption := 'Limiar: ' + IntToStr(lima);
end;

procedure TForm1.Button3Click(Sender: TObject);
begin
  contaCaps :=3;
end;

procedure TForm1.Button4Click(Sender: TObject);
var
pdiBuf: TBitmap;
i,j, max, min, limiar: integer;
begin
  //Criacao de Buffer
  pdiBuf := TBitmap.Create;
  pdiBuf.Height := 60;
  pdiBuf.Width := 72;
  //Aquisicao de Imagem
  for j:=0 to 60 do
    for i:=0 to 72 do
      pdiBuf.Canvas.Pixels[i,j] := Image6.Picture.Bitmap.Canvas.Pixels[i,j];
  //Busca menor e maior de amostra
  max:= 0;
  min:= 255;
  for j:=29 to 59 do
    for i:=0 to 71 do
      begin
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) > max then max:= GetRValue(pdiBuf.Canvas.Pixels[i,j]);
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) < min then min:= GetRValue(pdiBuf.Canvas.Pixels[i,j]);
      end;
  //Calcula Limiar
  limiar := Ceil((max+min)/2);
  ShowMessage('Limiar encontrado: ' + IntToStr(limiar));
  //Aplica Limialização
  for j:=0 to 59 do
    for i:=0 to 71 do
      begin
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) > limiar then
        pdiBuf.Canvas.Pixels[i,j] := RGB(255,255,255)
      else
        pdiBuf.Canvas.Pixels[i,j] := RGB(0,0,0);
      end;
  //Mostra a Imagem na Tela
  Image3.picture.bitmap := resizebitmap(pdiBuf,673,441);
end;

procedure TForm1.Button5Click(Sender: TObject);
var
pdiBuf: TBitmap;
i,j, max, min, limiar: integer;
begin
  //Criacao de Buffer
  pdiBuf := TBitmap.Create;
  pdiBuf.Height := 60;
  pdiBuf.Width := 72;
  //Aquisicao de Imagem
  for j:=0 to 60 do
    for i:=0 to 72 do
      pdiBuf.Canvas.Pixels[i,j] := Image6.Picture.Bitmap.Canvas.Pixels[i,j];
  //Aplica Limialização
  for j:=0 to 59 do
    begin
    //Busca menor e maior de amostra
    max:= 0;
    min:= 255;
    for i:=0 to 71 do
      begin
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) > max then max:= GetRValue(pdiBuf.Canvas.Pixels[i,j]);
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) < min then min:= GetRValue(pdiBuf.Canvas.Pixels[i,j]);
      end;
    //Calcula Limiar
    limiar := Ceil((max+min)/2);
    //Aplica Limialização em Linha
    for i:=0 to 71 do
      begin
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) > limiar then
        pdiBuf.Canvas.Pixels[i,j] := RGB(255,255,255)
      else
        pdiBuf.Canvas.Pixels[i,j] := RGB(0,0,0);
      end;
    end;
  //Mostra a Imagem na Tela
  Image3.picture.bitmap := resizebitmap(pdiBuf,673,441);
end;

procedure TForm1.Button6Click(Sender: TObject);
var media: Array[0..72] of Double;
ix, iy, inter, aux: Integer;
begin
  for ix:=0 to 72 do media[ix] := 0;
  inter:=0;
  for iy:=2 to 58 do
  begin
    inter:=inter+1;
    for ix:=0 to 72 do
    begin
      media[ix] := media[ix] + GetRValue(Image6.Picture.Bitmap.Canvas.Pixels[ix,iy]);
    end;
  end;
  for ix:=0 to 72 do
  begin
    aux := trunc(media[ix]/inter);
    Image6.Picture.Bitmap.Canvas.Pixels[ix,0] := rgb(aux,aux,aux);
  end;
end;

procedure TForm1.Button7Click(Sender: TObject);
begin
Image6.Picture.SaveToFile('capturas/' + Edit2.Text + '.bmp');
end;

procedure TForm1.Button8Click(Sender: TObject);
begin
  if OpenDialog1.Execute then
    begin
    Image6.Picture.LoadFromFile(OpenDialog1.FileName);
    //Edit2.Text:= OpenDialog1.Files.Text;
    Image4.Picture.Bitmap := resizebitmap(Image6.Picture.Bitmap,385,289);
    end;
end;

procedure TForm1.TrackBar3Change(Sender: TObject);
var
pdiBuf: TBitmap;
i,j, max, min: integer;
begin
  Label5.Caption := 'DeltaAmostra: ' + intToStr(TrackBar3.Position);

  //Criacao de Buffer
  pdiBuf := TBitmap.Create;
  pdiBuf.Height := 60;
  pdiBuf.Width := 72;
  //Aquisicao de Imagem
  for j:=0 to 60 do
    for i:=0 to 72 do
      pdiBuf.Canvas.Pixels[i,j] := Image6.Picture.Bitmap.Canvas.Pixels[i,j];
  //Aplica Limialização
  limiar := 85;
  for j:=0 to 59 do
    begin
    //Busca menor e maior de amostra
    max:= 0;
    min:= 255;
    for i:=0 to 71 do
      begin
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) > max then max:= GetRValue(pdiBuf.Canvas.Pixels[i,j]);
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) < min then min:= GetRValue(pdiBuf.Canvas.Pixels[i,j]);
      end;
    //Calcula Limiar
    if (max-min) > TrackBar3.Position then limiar := Ceil((max+min)/2)
    else if not CheckBox2.Checked then limiar := 85;
    //Aplica Limialização em Linha
    for i:=0 to 71 do
      begin
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) > limiar then
        pdiBuf.Canvas.Pixels[i,j] := RGB(255,255,255)
      else
        pdiBuf.Canvas.Pixels[i,j] := RGB(0,0,0);
      end;
    end;
  //Mostra a Imagem na Tela
  Image3.picture.bitmap := resizebitmap(pdiBuf,673,441);

end;

procedure TForm1.Button9Click(Sender: TObject);
var
pdiBuf: TBitmap;
i,j, max, min,l,r, centroid, centTotal: integer;
begin

  //Criacao de Buffer
  pdiBuf := TBitmap.Create;
  pdiBuf.Height := 60;
  pdiBuf.Width := 72;
  //Aquisicao de Imagem
  for j:=0 to 60 do
    for i:=0 to 72 do
      pdiBuf.Canvas.Pixels[i,j] := Image6.Picture.Bitmap.Canvas.Pixels[i,j];
  //Aplica Limialização
  limiar := 85;
  for j:=0 to 59 do
    begin
    //Busca menor e maior de amostra
    max:= 0;
    min:= 255;
    for i:=0 to 71 do
      begin
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) > max then max:= GetRValue(pdiBuf.Canvas.Pixels[i,j]);
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) < min then min:= GetRValue(pdiBuf.Canvas.Pixels[i,j]);
      end;
    //Calcula Limiar
    if (max-min) > TrackBar3.Position then limiar := Ceil((max+min)/2)
    else if not CheckBox2.Checked then limiar := 85;
    //Aplica Limialização em Linha
    for i:=0 to 71 do
      begin
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) > limiar then
        pdiBuf.Canvas.Pixels[i,j] := RGB(255,255,255)
      else
        pdiBuf.Canvas.Pixels[i,j] := RGB(0,0,0);
      end;
    end;

    centroid := 0;
    centTotal := 0;
    for j:=59 downto 29 do
      begin
        l := 71;
        for i:=36 to 71 do
          begin
          if (GetRValue(pdiBuf.Canvas.Pixels[i,j]) <> GetRValue(pdiBuf.Canvas.Pixels[i-1,j])) then
             begin
             l := i;
             break;
             end;
          end;
        r := 0;
        for i:=35 downto 1 do
          begin
          if GetRValue(pdiBuf.Canvas.Pixels[i,j]) <> GetRValue(pdiBuf.Canvas.Pixels[i-1,j]) then
            begin
            r := i;
            break;
            end;
          end;
        if (l <> 71) and (r <> 0) then
        begin
        centroid := centroid + trunc((l + r)/2);
        centTotal := centTotal + 1;
        pdiBuf.Canvas.Pixels[trunc((l + r)/2),j] := RGB(255,0,0);
        end;
      end;
      pdiBuf.Canvas.Pixels[trunc(centroid/centTotal),29] := RGB(0,255,0);
  //Mostra a Imagem na Tela
  Image3.picture.bitmap := resizebitmap(pdiBuf,673,441);

end;

procedure TForm1.Button10Click(Sender: TObject);
var
pdiBuf: TBitmap;
i,j, max, min, stopL, stopR: integer;
waitBL, waitBR : Boolean;
begin

  //Criacao de Buffer
  pdiBuf := TBitmap.Create;
  pdiBuf.Height := 60;
  pdiBuf.Width := 72;
  //Aquisicao de Imagem
  for j:=0 to 60 do
    for i:=0 to 72 do
      pdiBuf.Canvas.Pixels[i,j] := Image6.Picture.Bitmap.Canvas.Pixels[i,j];
  //Aplica Limialização
  limiar := 85;
  for j:=0 to 59 do
    begin
    //Busca menor e maior de amostra
    max:= 0;
    min:= 255;
    for i:=0 to 71 do
      begin
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) > max then max:= GetRValue(pdiBuf.Canvas.Pixels[i,j]);
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) < min then min:= GetRValue(pdiBuf.Canvas.Pixels[i,j]);
      end;
    //Calcula Limiar
    if (max-min) > TrackBar3.Position then limiar := Ceil((max+min)/2)
    else if not CheckBox2.Checked then limiar := 85;
    //Aplica Limialização em Linha
    for i:=0 to 71 do
      begin
      if GetRValue(pdiBuf.Canvas.Pixels[i,j]) > limiar then
        pdiBuf.Canvas.Pixels[i,j] := RGB(255,255,255)
      else
        pdiBuf.Canvas.Pixels[i,j] := RGB(0,0,0);
      end;
    end;

  stopL := 0;
  stopR := 0;
  waitBL := False;
  waitBR := False;
  for j:=59 downto 35 do
  begin
    for i:=35 to 71 do
    begin
      if (GetRValue(pdiBuf.Canvas.Pixels[i,j]) = 0) and
         (GetRValue(pdiBuf.Canvas.Pixels[i,j-1]) = 255) and
         (GetRValue(pdiBuf.Canvas.Pixels[i,j+1]) = 255) then
      begin
        stopL := stopL + 1;
      end
      else stopL := 0;
      if stopL  = 3 then
      begin
        waitBL := True;
      end;
      if waitBL and (GetRValue(pdiBuf.Canvas.Pixels[i,j]) = 255) then
      begin
        break;
      end
    end;

    for i:=36 downto 1 do
    begin
      if (GetRValue(pdiBuf.Canvas.Pixels[i,j]) = 0) and
         (GetRValue(pdiBuf.Canvas.Pixels[i,j-1]) = 255) and
         (GetRValue(pdiBuf.Canvas.Pixels[i,j+1]) = 255) then
      begin
        stopR := stopR + 1;
      end
      else stopR := 0;
      if stopR = 3 then
      begin
        pdiBuf.Canvas.Pixels[i,j] := RGB(255,0,0);
        waitBR := True;
      end;
      if waitBR and (GetRValue(pdiBuf.Canvas.Pixels[i,j]) = 255) then
      begin
        break;
      end;
    end;

  end;

  //Mostra a Imagem na Tela
  Image3.picture.bitmap := resizebitmap(pdiBuf,673,441);

end;

end.
