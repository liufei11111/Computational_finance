function VsmalliPlus= BarrierAmericanPutPDE(option)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%% The first is the type I boundary and the
%%%%%%%%%%%%%%%%%%%%%%%%%%%%% difference between two boundary is very
%%%%%%%%%%%%%%%%%%%%%%%%%%%%% small.
if ((option.Barrier/(option.MaxSpot/option.SpaceStep))...
        ==(floor(option.Barrier/(option.MaxSpot/option.SpaceStep))))
[TheMatrix1,TheMatrix2]=CrankNicolsonMatrix(option,option.SpaceStep-1,1.00);
V0=zeros(option.SpaceStep,1);
for i=1:option.SpaceStep+1
    V0(i)=(i-1)*(option.MaxSpot/option.SpaceStep);
end
Vsmalli=zeros(option.SpaceStep-1,1);
for i=2:option.SpaceStep
   Vsmalli(i-1)=  PayOffPut(option,V0(i));
end
VsmalliCopy=zeros(option.SpaceStep-1,1);
for i=1:option.SpaceStep-1
    VsmalliCopy(i)=Vsmalli(i);
end
VsmalliPlus=zeros(option.SpaceStep-1,1);
count=round((option.Barrier/option.MaxSpot)*option.SpaceStep);
for j=count:option.SpaceStep-1
        Vsmalli(j)=0;
end

for i=1:option.timeStep
  
  VsmalliPlus=max(LUSolver(TheMatrix1,TheMatrix2*Vsmalli),VsmalliCopy);
   Vsmalli=VsmalliPlus;

for j=count:option.SpaceStep-1
        Vsmalli(j)=0;
end

end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% type II boundary is implemented
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% below
else 
    [TheMatrix1,TheMatrix2]=CrankNicolsonMatrix(option,option.SpaceStep-1,0);
V0=zeros(option.SpaceStep,1);
for i=1:option.SpaceStep+1
    V0(i)=(i-1)*(option.MaxSpot/option.SpaceStep);
end
Vsmalli=zeros(option.SpaceStep-1,1);
for i=2:option.SpaceStep
   Vsmalli(i-1)=  PayOffPut(option,V0(i));
end
VsmalliCopy=zeros(option.SpaceStep-1,1);
for i=1:option.SpaceStep-1
    VsmalliCopy(i)=Vsmalli(i);
end
VsmalliPlus=zeros(option.SpaceStep-1,1);
timeStepLength=(option.Expiry/option.timeStep);


count=round((option.Barrier/option.MaxSpot)*option.SpaceStep);
for j=count:option.SpaceStep-1
        Vsmalli(j)=0;
end

for i=1:option.timeStep
    VsmalliPlus=max(LUSolver(TheMatrix1,TheMatrix2*Vsmalli)...
        +2*Boundary1(option,i*timeStepLength,option.SpaceStep-1),VsmalliCopy);
    
   Vsmalli=VsmalliPlus;

for m=count:option.SpaceStep-1
        Vsmalli(m)=0;
end

end
    
end


