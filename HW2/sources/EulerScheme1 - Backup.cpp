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
double EulerScheme1(EulerScheme SchemeE,double Barrier,double (*pt2func1)(double,double,double), double (*pt2func2)(double,double) ,double (*pt2func3)(double,double,double,double),bool flag=0){
	double dt=SchemeE.t/SchemeE.NofIntervals;
	double x=SchemeE.startOrlog;
	bool hit=false;
	for (int i=0;i<SchemeE.NofIntervals;i++){
		double a;
		if (flag==0)
			a=pt2func1(x,SchemeE.r,SchemeE.d);
		else 
			a=pt2func1(SchemeE.sigma,SchemeE.r,SchemeE.d);
		double b=pt2func2(x,SchemeE.sigma);
		double dw=GetOneGaussianByBoxMuller()*(sqrt(dt));
		x+=a*dt+b*dw;
		if (x>Barrier){
		hit=true;
		break;
		}
	}
	return hit? 0:pt2func3(x,SchemeE.strike,SchemeE.r,SchemeE.t);
}
Output_twoD EulerScheme2(EulerScheme SchemeE,double Barrier,double (*pt2func1)(double,double,double), double (*pt2func2)(double,double) ,double (*pt2func3)(double,double,double,double),bool flag=0){
	double dt=SchemeE.t/SchemeE.NofIntervals;
	double x1=SchemeE.startOrlog;
	double x2=SchemeE.startOrlog;
	bool hit1=false;
	bool hit2=false;
	Output_twoD output;
	for (int i=0;i<SchemeE.NofIntervals;i++){
		double a1;
		double a2;
		if (flag==0){
		a1=pt2func1(x1,SchemeE.r,SchemeE.d);
		a2=pt2func1(x2,SchemeE.r,SchemeE.d);
		}
		else{ 
			a1=pt2func1(SchemeE.sigma,SchemeE.r,SchemeE.d);
			a2=pt2func1(SchemeE.sigma,SchemeE.r,SchemeE.d);
		}
		double b1=pt2func2(x1,SchemeE.sigma);
		double b2=pt2func2(x2,SchemeE.sigma);
		double dw=GetOneGaussianByBoxMuller()*(sqrt(dt));
		x1+=a1*dt+b1*dw;
		x2+=a2*dt+b2*dw;

		if (x1>Barrier){
		hit1=true;
		}
		if (x2>Barrier){
		hit2=true;
		}
		if (hit1&&hit2){
			break;
		}
	}
	output.two_double[0]= hit1? 0:pt2func3(x1,SchemeE.strike,SchemeE.r,SchemeE.t);
	output.two_double[1]= hit2? 0:pt2func3(x2,SchemeE.strike,SchemeE.r,SchemeE.t);
	return output;
}
