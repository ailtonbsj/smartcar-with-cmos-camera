
dados = zeros(70,55);
Px = 1;
Py = 1;

s = serial('COM4');
set(s,'Terminator',0);
%set(s,'BytesAvailableFcnCount',48);
fopen(s);

while true
    buf = uint8(fgets(s));
    for ds = drange(buf)
        if ds == 255
            disp('Hi')
        end
    end
end
    
    %while true
    %end;

    %fclose(s);
    %delete(s);
    %clear s;
    

%function UARTCallback(obj,event)
%    global dados;
%    global Px
%    global Py;
%end