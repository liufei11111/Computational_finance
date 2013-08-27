%%%%%%% NOTE THAT:
%%%%%%% the last two values of functionA/B/C are not used at all.They are reserved
%%%%%%% for potential future expansion.

function  [TheMatrix1,TheMatrix2] =CrankNicolsonMatrix(option,size,CoefOfBound2)
TheMatrix1=zeros(size,size);
TheMatrix1(1,1)=1-functionB(option,1,(200/50),0)-CoefOfBound2*functionA(option,1,(200/50),0);
for i=2:size
TheMatrix1(i,i)=1-functionB(option,i,i*(200/50),i);
%the last two values are not used at all. It is reserved for future
%expansion
TheMatrix1(i,i-1)=-functionA(option,i,i*(200/50),i);
TheMatrix1(i-1,i)=-functionC(option,i-1,i*(200/50),i);
end
TheMatrix1(size,size)=TheMatrix1(size,size)-CoefOfBound2*functionC(option,size,(200/50),0);


TheMatrix2=zeros(size,size);
TheMatrix2(1,1)=1+functionB(option,1,(200/50),0)+CoefOfBound2*functionA(option,1,(200/50),0);
for i=2:size
TheMatrix2(i,i)=1+functionB(option,i,i*(200/50),i);
%the last two values are not used at all. It is reserved for future
%expansion
TheMatrix2(i,i-1)=functionA(option,i,i*(200/50),i);
TheMatrix2(i-1,i)=functionC(option,i-1,i*(200/50),i);
end
TheMatrix2(size,size)=TheMatrix2(size,size)+CoefOfBound2*functionC(option,size,(200/50),0);


