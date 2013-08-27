#include "../include/Barrier_Close.h"
#include "../include/Normals.h"

double d(double s,double T,Option opt, bool choose){
	double log_s=log(s);
	if (choose==true)
		return (1/(opt.Vol*sqrt(T)))*(log_s+(opt.Rate+0.5*opt.Vol*opt.Vol)*T);
	else return (1/(opt.Vol*sqrt(T)))*(log_s+(opt.Rate-0.5*opt.Vol*opt.Vol)*T);
}
double value(Option opt){
	double s1=opt.spot*(CumulativeNormal(d(opt.spot/opt.Strike,opt.Expiry,opt,true))-CumulativeNormal(d(opt.spot/opt.Barrier,opt.Expiry,opt,true)));
	double s2=-exp(-opt.Rate*opt.Expiry)*  opt.Strike*(CumulativeNormal(d(  opt.spot/  opt.Strike, opt.Expiry,opt,false)) - CumulativeNormal(d( opt.spot/ opt.Barrier,opt.Expiry,opt,false)));
	double s3=-opt.Barrier*pow( opt.spot/ opt.Barrier,-2* opt.Rate/( opt.Vol* opt.Vol))*(CumulativeNormal(d( opt.Barrier* opt.Barrier/( opt.Strike* opt.spot), opt.Expiry,opt,true))-CumulativeNormal(d( opt.Barrier/ opt.spot, opt.Expiry,opt,true)));
	double s4=exp(- opt.Rate* opt.Expiry)* opt.Strike*pow( opt.spot/ opt.Barrier,(-2* opt.Rate/( opt.Vol* opt.Vol)+1))*(CumulativeNormal(d( (opt.Barrier* opt.Barrier/( opt.Strike* opt.spot)),opt.Expiry,opt,false))-CumulativeNormal(d( (opt.Barrier/ opt.spot),opt.Expiry,opt,false)));
	return s1+s2+s3+s4;
}
