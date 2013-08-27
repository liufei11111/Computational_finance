/////////////////////////////////////////////////////
/////////////HW1 from Fei Liu-fl2312/////////////////
////test-environment: Visual Studio 2012/////////////
////If you feel any problem with code,please call////
////9176557918 or e-mail me.Thank you////////////////
/////////////////////////////////////////////////////
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "../include/Random1.h"
#include "../include/BlackScholesFormulas.h"
#include "../include/EulerScheme1.h"
#include "../include/MilsteinScheme1.h"
using namespace std;
/*SimpleMonteCarlo1 is given by Joshi*/
double SimpleMonteCarlo1(double Expiry, double Strike,double Spot,double Vol,double r, unsigned long NumberOfPaths)
{

	double variance = Vol*Vol*Expiry;
	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5*variance;

	double movedSpot = Spot*exp(r*Expiry +itoCorrection);
	double thisSpot;
	double runningSum=0;
///////////////////////////////////////////////////
	
	for (unsigned long i=0; i < NumberOfPaths; i++)
	{
		double thisGaussian = GetOneGaussianByBoxMuller();
		thisSpot = movedSpot*exp( rootVariance*thisGaussian);
		double thisPayoff = thisSpot - Strike;
    	thisPayoff = thisPayoff >0 ? thisPayoff : 0;
		runningSum += thisPayoff;
	}

	double mean = runningSum / NumberOfPaths;
	mean *= exp(-r*Expiry);
	return mean;
}

int main()
{
	
	double Expiry=1.0;
	double Strike=110.0; 
	double Spot=100.0; 
	double Vol=0.3; 
	double r=0.05; 
	double d=0.02;
	int NumberOfPaths=252;
	//question a)
	cout<< "Option price using closed-form formula = "<<BlackScholesCall(Spot, Strike,r,d,Vol,Expiry)<< "\n";
	////////////////////////////////////////////////
	//question b)
	double result =0;
	for (int i=0;i<10000;i++){
		result+=SimpleMonteCarlo1(Expiry, Strike,Spot,Vol,r-d,NumberOfPaths);
	}
	double mean=result/10000.0;
	cout <<"Option price using single-step exact SDE solution = " << mean << "\n";
	/////////////////////////////////////////////////
	//question c)
	double result1 =0;
	for (int i=0;i<10000;i++){
		result1+=EulerScheme1(Spot,Strike,Expiry,NumberOfPaths,r,d,Vol,&Functiona, &Functionb, &payoff,0 );
	}
	double mean1=result1/10000.0;
	cout <<"Option price using Euler numerical solution of SED for spot = " <<mean1<< "\n";
	
	////////////////////////////////////////////////
	//question d)
	double result2 =0;
	for (int i=0;i<10000;i++){
		result2+=EulerScheme1(log(Spot),Strike,Expiry,NumberOfPaths,r,d,Vol,&Functiona_log, &Functionb_log ,&payoff_log,true);
	}
	double mean2=result2/10000.0;
	cout <<"Option price using Euler numerical solution of SED for log spot = " <<mean2<< "\n";
	
	////////////////////////////////////////////////
	//question e)
	double result3 =0;
	
	for (int i=0;i<10000;i++){
		result3+=MilsteinScheme1(Spot,Strike,Expiry,NumberOfPaths,r,d,Vol,&Functiona_inMil, &Functionb_inMil,&FunctionbDeriv_inMil );
	}
	double mean3=result3/10000.0;
	cout <<"Option price using Milstein numerical solution of SED for spot = " <<mean3<< "\n";

	////////////////////////////////////////////////
    double tmp;
    cin >> tmp;
	return 0;
}

