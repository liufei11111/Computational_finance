#include "../include/EulerScheme1.h"
#include <iostream>
using namespace std;
double Functiona(double x,double r,double d){
	return x*(r-d);
}
double Functionb(double x,double sigma){
	return sigma*x;
}
double Functiona_log(double/*simply fit the signiture of EulerScheme1*/ sigma,double r,double d){
	return r-d-0.5*sigma*sigma;
}
double Functionb_log(double null,double sigma){
	return sigma;
}
double payoff(double x, double strike,double r,double t){
	double thisPayoff = x - strike;
    	thisPayoff = thisPayoff >0 ? thisPayoff : 0;
		return thisPayoff*exp(-r*t);
}
double payoff_log(double logx, double strike,double r,double t){
	double k=exp(logx);
	double thisPayoff= k >strike ? k-strike : 0;
		return thisPayoff*exp(-r*t);
}
double EulerScheme1(double startOrlog,double strike, double t,int NofIntervals,double r, double d,double sigma,double (*pt2func1)(double,double,double), double (*pt2func2)(double,double) ,double (*pt2func3)(double,double,double,double),bool flag=0){
	double dt=t/NofIntervals;
	double x=startOrlog;
	for (int i=0;i<NofIntervals;i++){
		double a;
		if (flag==0)
			a=pt2func1(x,r,d);
		else 
			a=pt2func1(sigma,r,d);
		double b=pt2func2(x,sigma);
		double dw=GetOneGaussianByBoxMuller()*(sqrt(dt));
		x+=a*dt+b*dw;
//	cout<< "this is the step in simulation: "<<x<<"\n";

	}
	return pt2func3(x,strike,r,t);
}
