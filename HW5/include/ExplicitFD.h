#ifndef __EXPLICITFD_H__
#define __EXPLICITFD_H__
#include <math.h>
#include <iostream>
#include "Payoff3.h"
#include <minmax.h>
#define timeStepGlobal (252)
#define SpaceStepGlobal (50)
struct Parameters{
	double Strike;
	double Spot;
	double Barrier;
	double MaxSpot;
	double MinSpot;
	double Expiry;
	double InterestRate;
	double Vol;
	double divident;
};
double thisA(Parameters,int,double,double);
double thisB(Parameters,int,double,double);
double thisC(Parameters,int,double,double);
double ExplicitFD(Parameters,PayOffCall,double (*)(Parameters,int,double,double),double (*)(Parameters,int,double,double),double (*)(Parameters,int,double,double));
double ExplicitFDBarrier(Parameters,PayOffCall,double (*)(Parameters,int,double,double),double (*)(Parameters,int,double,double),double (*)(Parameters,int,double,double));
double ExplicitFDAmerican(Parameters,PayOffCall,double (*)(Parameters,int,double,double),double (*)(Parameters,int,double,double),double (*)(Parameters,int,double,double));
#endif