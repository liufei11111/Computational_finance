clear;

%   FEI LIU
%   fl2312
%   HW6
%   TEST ENVIRONMENT: MATLAB2009
%   After adding the folder containing all files to the working directory
%   Press control+ENTER 
option=struct('Strike',110.0,'Spot',100.0,'Barrier',120.0,'MaxSpot',400.0,...
    'MinSpot',0.0,'Expiry',1.0,'InterestRate',0.05,'Vol',0.3,'timeStep',...
    252.0,'SpaceStep',50,'divident',0.02);
C=option_bs(option.Spot,option.Strike,option.InterestRate,option.divident,option.Vol,option.Expiry);
Closed_Form_European_Style_Vanilla_Call=C
Value=vanillaEuropeanCallPDE(option);

CrankNicolsonFD_European_style_vanilla_call=Value(round((option.Spot/option.MaxSpot)*option.SpaceStep))
%DOPut(option.Spot,option.Strike,option.InterestRate,option.,sigma,Sb)
Closed_Form_Barrier_option=valueBarrier(option)
Value=BarrierEuropeanCallPDE(option);
Crank_Nicolson_FD_Barrier_Call=Value(round((option.Spot/option.MaxSpot)*option.SpaceStep))
