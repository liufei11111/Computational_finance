#include "../include/MilsteinScheme1.h"

double Functiona_inMil(double x,double r,double d){
	return x*(r-d);
}
double Functionb_inMil(double x, double sigma){
	return x*sigma;
}
double FunctionbDeriv_inMil(double sigma){
	return sigma;
}
double MilsteinScheme1(double start,double strike, double t,int NofIntervals,double r, double d,double sigma,double (*pt2func1)(double,double,double), double (*pt2func2)(double,double),double (*pt2func3)(double) ){
	double dt=t/NofIntervals;
	double x=start;
	for (int i=0;i<NofIntervals;i++){
		double a=pt2func1(x,r,d);
		double b=pt2func2(x,sigma);
		double c=pt2func3(sigma);
		double dw=GetOneGaussianByBoxMuller()*sqrt(dt);
		x+=a*dt+b*dw+0.5*b*c*(dw*dw-dt);
	}
	double thisPayoff = x - strike;
    	thisPayoff = thisPayoff >0 ? thisPayoff : 0;

		return thisPayoff*exp(-r*t);
}
