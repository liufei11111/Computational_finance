function [L,U]=LUDecompositionFD(M)
I=size(M);
L=eye(I);
U=zeros(I);
U(1,1)=M(1,1);
for i=2:I
	L(i,i-1)=M(i,i-1)./U(i-1,i-1);
	U(i-1,i)=M(i-1,i);
	U(i,i)=M(i,i)-L(i,i-1)*U(i-1,i);
end
