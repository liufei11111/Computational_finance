#include "../include/ClosedFormGeometricAsian.h"
#include <iostream>
double ClosedFormFormulaForGeometricAsian(Input input){
	double dt=input.Expiry/input.NumOfTimes;
	double v=input.Intere-input.Vol*input.Vol*0.5;
	double v0=exp(-input.Intere*input.Expiry)*input.Spot*exp(0.5*(input.NumOfTimes+1)*v*dt+\
		(1/(12*input.NumOfTimes))*(input.NumOfTimes+1)*(2*input.NumOfTimes+1)*input.Vol*input.Vol*dt);
	double standardDeviationAverage =sqrt(input.Expiry)*input.Vol*sqrt((1.0/6.0)*input.NumOfTimes*(input.NumOfTimes+1)*(2*input.NumOfTimes+1))/pow(input.NumOfTimes,1.5);
    double moneyness = log(input.Spot/input.Strike);
	double d1 =( moneyness +  (input.Intere)*input.Expiry+0.5* standardDeviationAverage*standardDeviationAverage)/standardDeviationAverage;
    double d2 = d1 - standardDeviationAverage;
	return v0* CumulativeNormal(d1) - input.Strike*exp(-input.Intere*input.Expiry)*CumulativeNormal(d2);
}