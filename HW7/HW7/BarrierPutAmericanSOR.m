function SORValue=BarrierPutAmericanSOR(w,option)

[M1,M2]=CrankNicolsonMatrix(option,option.SpaceStep-1,1.0);
D=zeros(option.SpaceStep-1);
for i=1:option.SpaceStep-1
    D(i,i)=M1(i,i);
end
U=zeros(option.SpaceStep-1);
for i=2:option.SpaceStep-1
    U(i,i-1)=M1(i,i-1);
end
L=zeros(option.SpaceStep-1);
for i=1:option.SpaceStep-2
    L(i,i+1)=M1(i,i+1);
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
V0=zeros(option.SpaceStep+1,1);
for i=1:option.SpaceStep+1
    V0(i)=(i-1)*(option.MaxSpot/option.SpaceStep);
end

Vsmalli=zeros(option.SpaceStep-1,1);
for i=2:option.SpaceStep
   Vsmalli(i-1)=PayOffPut(option,V0(i));
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

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for j=1:option.timeStep
    b=M2*Vsmalli;
VsmalliPlus=max(CrankNicolsonSORFD(M1,b,Vsmalli,w,0.001,10),VsmalliCopy);
Vsmalli=VsmalliPlus;
for m=count:option.SpaceStep-1
        Vsmalli(m)=0;
end
end
SORValue= VsmalliPlus;

