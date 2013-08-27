function valueB= valueBarrier(opt)
	 s1=opt.Spot*(normcdf(d(opt.Spot/opt.Strike,opt.Expiry,opt,true))-normcdf(d(opt.Spot/opt.Barrier,opt.Expiry,opt,true)));
	 s2=-exp(-opt.InterestRate*opt.Expiry)*  opt.Strike*(normcdf(d(  opt.Spot/  opt.Strike, opt.Expiry,opt,false)) - normcdf(d( opt.Spot/ opt.Barrier,opt.Expiry,opt,false)));
	 s3=-opt.Barrier*power( opt.Spot/ opt.Barrier,-2* opt.InterestRate/( opt.Vol* opt.Vol))*(normcdf(d( opt.Barrier* opt.Barrier/( opt.Strike* opt.Spot), opt.Expiry,opt,true))-normcdf(d( opt.Barrier/ opt.Spot, opt.Expiry,opt,true)));
     s4=exp(- opt.InterestRate* opt.Expiry)* opt.Strike*power( opt.Spot/ opt.Barrier,(-2* opt.InterestRate/( opt.Vol* opt.Vol)+1))*(normcdf(d( (opt.Barrier* opt.Barrier/( opt.Strike* opt.Spot)),opt.Expiry,opt,false))-normcdf(d( (opt.Barrier/ opt.Spot),opt.Expiry,opt,false)));
	valueB= s1+s2+s3+s4;