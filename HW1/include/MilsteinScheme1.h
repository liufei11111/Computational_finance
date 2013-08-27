#ifndef __MILSTEINSCHEME1_H__
#define __MILSTEINSCHEME1_H__
	#ifndef __RANDOM1_H__
	#include "Random1.h"
	#endif
	#ifndef __MATH_H__
	#include <math.h>
	#endif
double MilsteinScheme1(double,double,double ,int ,double , double ,double ,double (*)(double,double,double),double (*)(double,double), double (*)(double)) ;
double Functiona_inMil(double,double,double);
double Functionb_inMil(double,double);
double FunctionbDeriv_inMil(double );
#endif