function x = CrankNicolsonSORFD(A,b,x0,omega,eps,MaxIter)
oldx = x0;
x = x0;
N = length(x0);
omega1 = 1-omega;
for k=1:MaxIter
    for i=1:N
        z = (b(i) - sum(A(i,(1:i-1))*x(1:(i-1))) ...
          - sum(A(i,(i+1):N)*x((i+1):N))) / A(i,i);
        x(i) = omega*z + omega1*oldx(i);
    end
    if norm(x-oldx) < eps*norm(oldx) break; end
    oldx = x;       
end
