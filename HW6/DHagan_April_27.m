function varargout = DHagan_April_27(varargin)
% DHAGAN_APRIL_27 M-file for DHagan_April_27.fig
%      DHAGAN_APRIL_27, by itself, creates a new DHAGAN_APRIL_27 or raises the existing
%      singleton*.
%
%      H = DHAGAN_APRIL_27 returns the handle to a new DHAGAN_APRIL_27 or the handle to
%      the existing singleton*.
%
%      DHAGAN_APRIL_27('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DHAGAN_APRIL_27.M with the given input arguments.
%
%      DHAGAN_APRIL_27('Property','Value',...) creates a new DHAGAN_APRIL_27 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before DHagan_April_27_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to DHagan_April_27_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help DHagan_April_27

% Last Modified by GUIDE v2.5 28-Apr-2012 13:34:45

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @DHagan_April_27_OpeningFcn, ...
                   'gui_OutputFcn',  @DHagan_April_27_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT

end
% --- Executes just before DHagan_April_27 is made visible.
function DHagan_April_27_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to DHagan_April_27 (see VARARGIN)

handles.output = hObject;
% Update handles structure
guidata(hObject, handles);

% UIWAIT makes DHagan_April_27 wait for user response (see UIRESUME)
% uiwait(handles.figure1);

end
% --- Outputs from this function are returned to the command line.
function varargout = DHagan_April_27_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

end
function alpha_Callback(hObject, eventdata, handles)
    
end
function alpha_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end
function t0_Callback(hObject, eventdata, handles)

end
function t0_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end
function tf_Callback(hObject, eventdata, handles)

end
function tf_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end
function x0_Callback(hObject, eventdata, handles)

end
function x0_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end
function xf_Callback(hObject, eventdata, handles)

end
function xf_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end
function dt_Callback(hObject, eventdata, handles)

end
function dt_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end
function N_Callback(hObject, eventdata, handles)

end
function N_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end
function gridon_Callback(hObject, eventdata, handles)
    grid on;
end

function gridoff_Callback(hObject, eventdata, handles)
    grid off;  
end

function Tx0_Callback(hObject, eventdata, handles)
end

function Tx0_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end
function T0t_Callback(hObject, eventdata, handles)

end
function T0t_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end

end
function Txft_Callback(hObject, eventdata, handles)

end
function Txft_CreateFcn(hObject, eventdata, handles)

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end


function figure1_ResizeFcn(hObject, eventdata, handles)
end


% --- Executes on button press in updatedata.
function updatedata_Callback(hObject, eventdata, handles)
% hObject    handle to updatedata (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
format long
alpha = str2num(get(handles.alpha,'string'));
dt = str2num(get(handles.dt,'string'));
xi = str2num(get(handles.x0,'string'));
xf = str2num(get(handles.xf,'string'));
N = str2num(get(handles.N,'string'));
ti = str2num(get(handles.t0,'string'));
tf = str2num(get(handles.tf,'string'));
BC_Tx0 = inline(get(handles.Tx0,'string')); %make this an if/else to check whether it is a function of x or not
BC_T0t = str2num(get(handles.T0t,'string'));
BC_Txft = str2num(get(handles.Txft,'string'));

time = abs(tf-ti)/dt;
dx = abs(xf-xi)/(N+1);
dt_plot = ti:dt:(tf-dt);

d = (alpha*dt)/(dx.^2);
dd = num2str(d);
set(handles.diffusion,'string',dd);
%%%%%%%%%%%

        %Main Program:
        x = xi:dx:xf;                     %This is our position vector in step dx
        T = zeros(abs((tf-ti))/dt,N);    %This populates our entire matrix of temperature values

        for i = 1:length(x)
            T(1,i) = BC_Tx0(x(i));             %This is our initial condition T(x,0) = sin(pi*x)
            
            %T(1,end) = 0;                       %This specifies the BC T(x,tf) = 0;
        end

        for n = 1:time
            T(n,1) = BC_T0t;                     %This is our initial condition T(0,t) = 0
            %T(n,end) = 0;                   %This sepcifies our BC T(xf,t) = 0
        end

        for n = 1:(time-1)                  %n is time
            sol = zeros(1,N+2);
            sol(1) = T(n,1);
            sol(N+2) = T(n,end);                                      %This is a BC
            for i = 2:N+1                   %i is position
                sol(i) = d*T(n,i-1) + (1-2*d)*T(n,i) + d*T(n,i+1);           %left side of the equation
            end

            eqn = zeros(N+2,N+2);                                             %This populates our matrix we are using to solve for the values
            j = 1;
            eqn(1,1) = 1;                                                       %This sets T(n+1,i) = T(n,i) BC
            eqn(end,end) = 1;
            for k = 2:N+1
               eqn(k,j) = -d;
               eqn(k,j+1) = 1+2*d;
               eqn(k,j+2) = -d;
               j = j+1;
            end 

            T_vals = eqn\sol';
            T_vals = T_vals';
            for i = 1:N+2
                T(n+1,i) = T_vals(i);
            end
        end

        [X Y] = meshgrid(x,dt_plot);

%%%%%%%%%%%
handles.X = X;
handles.Y = Y;
handles.Z = T;
mesh(handles.X,handles.Y,handles.Z);
title('Crank-Nicholson Method for Solving Partial Differential Equations');
xlabel('Position');
ylabel('time ');
zlabel('Temperature ');

handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

end


% --- Executes on button press in surf.
function surf_Callback(hObject, eventdata, handles)
% hObject    handle to surf (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

    surf(handles.X,handles.Y,handles.Z);
    title('Crank-Nicholson Method for Solving Partial Differential Equations');
    xlabel('Position');
    ylabel('time ');
    zlabel('Temperature ');

end


% --- Executes on button press in contour.
function contour_Callback(hObject, eventdata, handles)
% hObject    handle to contour (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
contour(handles.X,handles.Y,handles.Z);
title('Crank-Nicholson Method for Solving Partial Differential Equations');
xlabel('Position/Time');
ylabel('Temperature');
end


% --- Executes on button press in mesh.
function mesh_Callback(hObject, eventdata, handles)
% hObject    handle to mesh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of mesh
mesh(handles.X,handles.Y,handles.Z);
title('Crank-Nicholson Method for Solving Partial Differential Equations');
xlabel('Position');
ylabel('time ');
zlabel('Temperature ');
end


% --- Executes on selection change in Tx0popup.
function Tx0popup_Callback(hObject, eventdata, handles)
% hObject    handle to Tx0popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns Tx0popup contents as cell array
%        contents{get(hObject,'Value')} returns selected item from Tx0popup

end
% --- Executes during object creation, after setting all properties.
function Tx0popup_CreateFcn(hObject, eventdata, handles)
% hObject    handle to Tx0popup (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
end
