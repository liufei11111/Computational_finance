function Value=LUSolver(M,q)
[L,U]=LUDecompositionFD(M);
[dims,n]=size(q);
W=zeros(dims,1);
W(1)=q(1);
for i=2:dims
W(i)=q(i)-L(i,i-1)*W(i-1);
end
Value=zeros(dims,1);
Value(dims)=W(dims)/U(dims,dims);
for i=(dims-1):-1:1
    Value(i)=(W(i)-U(i,i+1)*Value(i+1))/U(i,i);
end
return;



