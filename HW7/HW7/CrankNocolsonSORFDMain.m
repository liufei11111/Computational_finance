clear

%   FEI LIU
%   fl2312
%   HW7
%   TEST ENVIRONMENT: MATLAB2009
%   After changing the working directory to the folder containing all files
%   Press control+ENTER 
%   Note that the accuracy of PSOR method is set to be 0.001
%
option=struct('Strike',90.0,'Spot',100.0,'Barrier',80.0,'MaxSpot',200.0,...
    'MinSpot',50.0,'Expiry',1.0,'InterestRate',0.05,'Vol',0.3,'timeStep',...
    252.0,'SpaceStep',50,'divident',0.02);
result=zeros(12,1);
%
C=option_BS(option.Spot,option.Strike,option.InterestRate,...
    option.divident,option.Vol,option.Expiry);
Closed_Form_European_Style_Vanilla_Call=C
result(1)=Closed_Form_European_Style_Vanilla_Call;
%
SOR=VanillaCallAmericanSOR(1.5,option);
Crank_Nicolson_PSOR_American_Style_Call=SOR(...
    round(option.SpaceStep*(option.Spot/option.MaxSpot)))
result(2)=Crank_Nicolson_PSOR_American_Style_Call;
%
SOR=VanillaPutAmericanSOR(1.5,option);
Crank_Nicolson_PSOR_American_Style_Put=SOR(...
    round(option.SpaceStep*(option.Spot/option.MaxSpot)))
result(3)=Crank_Nicolson_PSOR_American_Style_Put;
%
Value=vanillaAmericanPutPDE(option);
Crank_Nicolson_LUD_American_style_Put=Value...
    (round((option.Spot/option.MaxSpot)*option.SpaceStep))
result(4)=Crank_Nicolson_LUD_American_style_Put;
%%%%%%%%%%%%%%%%%%%%%%%%

%
Closed_Form_European_Style_DO_Barrier_Call_option=valueBarrierDOCall(option)
result(5)=Closed_Form_European_Style_DO_Barrier_Call_option;
%
Value=BarrierCallAmericanSOR_DO(1.5,option);
SORValue=Value(...
    round((option.Spot/option.MaxSpot)*option.SpaceStep));
Crank_Nicolson_PSOR_American_DO_Barrier_Call=SORValue
result(6)=Crank_Nicolson_PSOR_American_DO_Barrier_Call;
%
%{
option=struct('Strike',90.0,'Spot',100.0,'Barrier',120.0,'MaxSpot',200.0,...
    'MinSpot',0.0,'Expiry',1.0,'InterestRate',0.05,'Vol',0.3,'timeStep',...
    252.0,'SpaceStep',50,'divident',0.02);
%}

Value=BarrierPutAmericanSOR_DO(1.5,option);
SORValue=Value(...
    round((option.Spot/option.MaxSpot)*option.SpaceStep));
Crank_Nicolson_PSOR_American_DO_Barrier_Put=SORValue
result(7)=Crank_Nicolson_PSOR_American_DO_Barrier_Put;
%
BarrierLUD=BarrierAmericanPutPDE_DO(option);
Crank_Nicolson_LUD_American_Style_DO_barrier_Put=BarrierLUD(round...
    ((option.Spot/option.MaxSpot)*option.SpaceStep))
result(8)=Crank_Nicolson_LUD_American_Style_DO_barrier_Put;
%%%%%%%%%%%%%%%%%%%%%%%%

option.Barrier=120;

Closed_Form_European_Style_UO_Barrier_option=valueBarrier(option)
result(9)=Closed_Form_European_Style_UO_Barrier_option;
%
Value=BarrierCallAmericanSOR(1.5,option);
SORValue=Value(...
    round((option.Spot/option.MaxSpot)*option.SpaceStep));
Crank_Nicolson_PSOR_American_UO_Barrier_Call=SORValue
result(10)=Crank_Nicolson_PSOR_American_UO_Barrier_Call;
%

%
Value=BarrierPutAmericanSOR(1.5,option);
SORValue=Value(...
    round((option.Spot/option.MaxSpot)*option.SpaceStep));
Crank_Nicolson_PSOR_American_UO_Barrier_Put=SORValue
result(11)=Crank_Nicolson_PSOR_American_UO_Barrier_Put;
%
BarrierLUD=BarrierAmericanPutPDE(option);
Crank_Nicolson_LUD_American_Style_UO_barrier_Put=BarrierLUD(round...
    ((option.Spot/option.MaxSpot)*option.SpaceStep))
result(12)=Crank_Nicolson_LUD_American_Style_UO_barrier_Put;
% this result put everything together compactly. If you just want to match 
%the numbers, just uncommant below code
%result





