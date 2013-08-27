#ifndef __EULERSCHEME_H__
#define __EULERSCHEME_H__
	#ifndef __RANDOM1_H__
	#include "Random1.h"
	#endif
	#ifndef __MATH_H__
	#include <math.h>
	#endif
struct EulerScheme{double startOrlog;double strike; double t;int NofIntervals;double r; double d;double sigma;};
struct Output_twoD{double two_double[2];};
//Euler takes Spot,Strike,Expiry,NumberOfPaths,r,d,Vol,functiona and functionb,plus payoff function for regular and log situation
double EulerScheme1(EulerScheme,double,double (*)(double,double,double), double (*)(double,double),double (*)(double,double,double,double),bool) ;
Output_twoD EulerScheme2(EulerScheme,double,double (*)(double,double,double), double (*)(double,double),double (*)(double,double,double,double),bool) ;
Output_twoD EulerScheme3(EulerScheme,double,double (*)(double,double,double), double (*)(double,double),double (*)(double,double,double,double),bool) ;
double Functiona(double, double, double);
double Functionb(double,double);
double Functiona_log(double,double,double);
double Functionb_log(double,double);
double payoff(double , double,double ,double);
double payoff_log(double , double,double ,double);
#endif