function Boundary1= Boundary1(option,currTime,size)

Boundary1=zeros(size,1);
down=PayOff(option,option.MinSpot)*exp(-option.InterestRate*(currTime));
up=PayOff(option,option.MaxSpot)*exp(-option.InterestRate*(currTime));
Boundary1(1)=down;
Boundary1(size)=up;
