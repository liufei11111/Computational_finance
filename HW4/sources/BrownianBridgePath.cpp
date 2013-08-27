#include "../include/BrownianBridgePath.h"
#include <iostream>
#include <cmath>
unsigned long count_i=0;
int thisStrata=1;
void BrownianBridgePath::GetOnePath(MJArray& SpotValues) 
{ 

	int sizeofVariates=Variates.size();
Variates.resize(1);
TheGenerator->GetUniforms(Variates);
int K=30;
double 
	V_inFormula=(thisStrata-1+Variates[0])/(K*1.0);
	if (thisStrata==K-1) //repeat the period again
		thisStrata=0;
	thisStrata++;

double * // just for the formula to be valid, we need sizeofVariates+1 instead of sizeofVariates
	Wt_inFormula=(double *)malloc((sizeofVariates+1)*sizeof(double));
	Wt_inFormula[sizeofVariates]=sqrt(Expiry_global)*InverseCumulativeNormal(V_inFormula);
	Wt_inFormula[0]=0;
double * 
		temp2_times=(double*)malloc(sizeof(double)*(sizeofVariates+1));
	for (int i=0; i < sizeofVariates+1; i++){
		 temp2_times[i] = (i)*Expiry_global/sizeofVariates;
	 }
	Variates.resize(sizeofVariates);
	TheGenerator->GetGaussians(Variates);// What ever generator is used doesn't matter since I didn't specify here.
	for (int j=1;j<sizeofVariates;j++){
		
		double a=(temp2_times[sizeofVariates]-temp2_times[j])/(temp2_times[sizeofVariates]-temp2_times[j-1]);
		double b=(Expiry_global/sizeofVariates)/(temp2_times[sizeofVariates]-temp2_times[j-1]);
		double c=sqrt(((temp2_times[sizeofVariates]-temp2_times[j])*(Expiry_global/sizeofVariates))/(temp2_times[sizeofVariates]-temp2_times[j-1]));
		Wt_inFormula[j]=a*Wt_inFormula[j-1]+b*Wt_inFormula[sizeofVariates]+c*Variates[j];
	}// just the formula 
	Variates.resize(sizeofVariates);
	for (int i=0;i<sizeofVariates;i++){
		Variates[i]=(Wt_inFormula[i+1]-Wt_inFormula[i])/sqrt(Expiry_global/sizeofVariates);
	}
	free(temp2_times);
	free(Wt_inFormula);
	
	double CurrentLogSpot = LogSpot;
	
    for (unsigned long j=0; j < NumberOfTimes; j++)
    {
        CurrentLogSpot += Drifts[j];
        CurrentLogSpot += StandardDeviations[j]*Variates[j];
		SpotValues[j] = exp(CurrentLogSpot);
    }
	return;
}

BrownianBridgePath::BrownianBridgePath(const Wrapper<PathDependent>& TheProduct_,
                                    const Parameters& R_,
                                    const Parameters& D_,
                                    const Parameters& Vol_,
                                    const Wrapper<RandomBase>& TheGenerator_,
                                    double Spot_)
                                    :
                                    ExoticEngine(TheProduct_,R_),
                                    TheGenerator(TheGenerator_)
{
    MJArray Times(TheProduct_->GetLookAtTimes());
    NumberOfTimes = Times.size();

    TheGenerator->ResetDimensionality(NumberOfTimes);
	// Here is the place for change of models for different products
    Drifts.resize(NumberOfTimes);
    StandardDeviations.resize(NumberOfTimes);

    double Variance = Vol_.IntegralSquare(0,Times[0]);

    Drifts[0] = R_.Integral(0.0,Times[0]) - D_.Integral(0.0,Times[0]) - 0.5 * Variance;
    StandardDeviations[0] = sqrt(Variance);
	// here calculates the r*dt sigma*dw
    for (unsigned long j=1; j < NumberOfTimes; ++j)
    {   
        double thisVariance = Vol_.IntegralSquare(Times[j-1],Times[j]);
        Drifts[j] = R_.Integral(Times[j-1],Times[j]) - D_.Integral(Times[j-1],Times[j]) 
                    - 0.5 * thisVariance;
        StandardDeviations[j] = sqrt(thisVariance);
    }

    LogSpot = log(Spot_);                                   
    Variates.resize(NumberOfTimes);
}
