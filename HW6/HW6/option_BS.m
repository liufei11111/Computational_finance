function C= option_BS(S,X,r,d,sigma,T)
   
% for call
    d1 = (log(S/X) + (r-d + 0.5*sigma^2)*T)/(sigma*sqrt(T));
    d2 = d1 - sigma*sqrt(T);
    N1 = normcdf(d1);
    N2 =  normcdf(d2);

    C = S*exp(-d*T)*N1-X*exp(-r*T)*N2;

end