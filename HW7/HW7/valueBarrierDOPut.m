function valueB= valueBarrierDOPut(opt)
sigmaSq=opt.Vol*opt.Vol;	 
lambda=(opt.InterestRate+sigmaSq*0.5)/(sigmaSq);
y=log(opt.Barrier*opt.Barrier/(opt.Spot*opt.Strike))...
    /(opt.Vol*sqrt(opt.Expiry))+lambda*opt.Vol*sqrt(opt.Expiry);
x1=log(opt.Spot/opt.Barrier)/(opt.Vol*sqrt(opt.Expiry))...
    +lambda*opt.Vol*sqrt(opt.Expiry);
y1=log(opt.Barrier/opt.Spot)/(opt.Vol*sqrt(opt.Expiry))...
    +lambda*opt.Vol*sqrt(opt.Expiry);

s1=opt.Strike*exp(-1*opt.InterestRate*opt.Expiry)...
    *normcdf(-1*d(opt.Spot/opt.Strike,opt.Expiry,opt,false));
s2=-1*opt.Spot*normcdf(-1*d(opt.Spot/opt.Strike,opt.Expiry,opt,true));
s3=opt.Spot*normcdf(-1*x1);
s4=-1*opt.Strike*exp(-1*opt.InterestRate*opt.Expiry)...
    *normcdf(-1*x1+opt.Vol*sqrt(opt.Expiry));
s5=-1*opt.Spot*power(opt.Barrier/opt.Spot,2*lambda)...
    *(normcdf(y)-normcdf(y1));
s6=opt.Strike*exp(-1*opt.InterestRate*opt.Expiry)...
    *power(opt.Barrier/opt.Spot,2*lambda-2)...
    *(normcdf(y-opt.Vol*sqrt(opt.Expiry))-normcdf(y1-opt.Vol*sqrt(opt.Expiry)));
valueB=s1+s2+s3+s4+s5+s6;

%{
s1=opt.Spot*(normcdf(d(opt.Spot/opt.Strike,opt.Expiry,opt,true))-normcdf(d(opt.Spot/opt.Barrier,opt.Expiry,opt,true)));
	 s2=-exp(-opt.InterestRate*opt.Expiry)*  opt.Strike*(normcdf(d(  opt.Spot/  opt.Strike, opt.Expiry,opt,false)) - normcdf(d( opt.Spot/ opt.Barrier,opt.Expiry,opt,false)));
	 s3=-opt.Barrier*power( opt.Spot/ opt.Barrier,-2* opt.InterestRate/( opt.Vol* opt.Vol))*(normcdf(d( opt.Barrier* opt.Barrier/( opt.Strike* opt.Spot), opt.Expiry,opt,true))-normcdf(d( opt.Barrier/ opt.Spot, opt.Expiry,opt,true)));
     s4=exp(- opt.InterestRate* opt.Expiry)* opt.Strike*power( opt.Spot/ opt.Barrier,(-2* opt.InterestRate/( opt.Vol* opt.Vol)+1))*(normcdf(d( (opt.Barrier* opt.Barrier/( opt.Strike* opt.Spot)),opt.Expiry,opt,false))-normcdf(d( (opt.Barrier/ opt.Spot),opt.Expiry,opt,false)));
	valueB= s1+s2+s3+s4;
%}