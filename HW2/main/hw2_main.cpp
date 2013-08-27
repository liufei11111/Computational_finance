//						UNI: fl2312	
//					    Name: Fei Liu
//	                	HW2
//						Borrowed Code for Normals, BlackSholes Formula, Payoff1 and, Random from Joshi
//						Everything else if self-made
//						I modified some code I wrote last time. They have the same name but different content
#include<iostream>
#include"../include/Barrier_Close.h"
#include"../include/EulerScheme1.h"
#include "../include/PayOff1.h"
#include "../include/StdError.h"
#include <time.h>
#include <stdlib.h>
#include "../include/Covariance.h"
#include "../include/BlackScholesFormulas.h"
using namespace std;

int main()
{

	double Expiry=1;
	double Strike=200; 
	double Spot=100; 
	double Vol=0.3; 
	double r=0.05;
	double d=0.02;
	unsigned long NumberOfIterval=252;
	double Barrier=120;
	const int NumberOfSimulations=10000;
	
	///////////////////////Question 1///////////////////////
	Option opt;
	opt.Barrier=Barrier;
	opt.Expiry=Expiry;
	opt.Rate=r-d;
	opt.Strike=Strike;
	opt.Vol=Vol;
	opt.spot=Spot;
	long int start1,end1;
	start1=clock();
	double x=value(opt);
	end1=clock();
	long int dif1=end1-start1;
	cout<<"Closed-form barrier option price = " <<x<<","<<"run time= "<<((long double)dif1)/(1.0*CLOCKS_PER_SEC)<<"\n";
	///////////////////////Question 2///////////////////////
	double result2 =0;
	EulerScheme SchemeE; // the inputs Euler scheme takes
	SchemeE.d=d;
	SchemeE.NofIntervals=NumberOfIterval;
	SchemeE.r=r;
	SchemeE.sigma=Vol;
	SchemeE.startOrlog=Spot;
	SchemeE.strike=Strike;
	SchemeE.t=Expiry;
	double Array_Save[NumberOfSimulations];// Keep track of the simulations
	long int start2,end2;
	start2=clock();
	for (int i=0;i<NumberOfSimulations;i++){
		Array_Save[i]=EulerScheme1(SchemeE,Barrier,&Functiona, &Functionb, &payoff,0 );
		result2+=Array_Save[i];
	}
	double mean2=result2/(NumberOfSimulations*1.0);
	double stderr2=GetStdError(Array_Save,mean2,NumberOfSimulations);// A function I wrote to compute stderr
	end2=clock();
	long int dif2=end2-start2;
	cout <<"Monte Carlo barrier option price =" <<mean2<<","<< " std error = "<<\
		stderr2<<","<<" run time = "<<((double)dif2)/(1.0*CLOCKS_PER_SEC)<<"\n";
	///////////////////////Question 3///////////////////////
	int NumberOfIterval_half;
	if (NumberOfIterval%2==1){
	//make sure that all generation are in pairs
	//every value in previous application is splitted into pairs passed on from EulerScheme2 which generate a struct that contains
	// two path values on its way.
	NumberOfIterval_half=(NumberOfSimulations+1)/2;
	}else NumberOfIterval_half=NumberOfSimulations/2;
	double result3_1=0;
	double result3_2=0;
	double * Array_Save3_1=(double *)malloc(NumberOfIterval_half*sizeof(double));// a pair of everything for paired up simulations
	double * Array_Save3_2=(double *)malloc(NumberOfIterval_half*sizeof(double));
	long int start3,end3;
	start3=clock();
	for (int i=0;i<NumberOfIterval_half;i++){
		Output_twoD temp=EulerScheme2(SchemeE,Barrier,&Functiona, &Functionb, &payoff,0 );//Output is a struct of two doubles , which I created for convenience. 
		Array_Save3_1[i]=temp.two_double[0];
		Array_Save3_2[i]=temp.two_double[1];
		result3_1+=Array_Save3_1[i];
		result3_2+=Array_Save3_2[i];
	}
	double mean3_1=result3_1/(NumberOfIterval_half*1.0);
	double mean3_2=result3_2/(NumberOfIterval_half*1.0);
	double stderr3_1=GetStdError(Array_Save3_1,mean3_1,NumberOfIterval_half);
	double stderr3_2=GetStdError(Array_Save3_2,mean3_2,NumberOfIterval_half);
	double stderr3_total=sqrt((stderr3_1*stderr3_1+stderr3_2*stderr3_2)/2);// Since the number is evenly divided, the total can be sum of sqrt.
	double mean3_total=(mean3_1+mean3_2)/2.0;
	end3=clock();
	long int dif3=end3-start3;// returns the number of clicks in between and will be converted into seconds below.
	cout <<"Antithetic variates barrier option price = " <<mean3_total<<","<< " std error = "<<stderr3_total<<\
		","<<" time run = "<<((long double)dif3)/(1.0*CLOCKS_PER_SEC)<<"\n";
	free(Array_Save3_1);
	free(Array_Save3_2);
	///////////////////////Question 4///////////////////////
	
	int NumberOfIterval_half1=(int)ceil(NumberOfSimulations*0.3);
	int NumberOfIterval_half2=NumberOfSimulations-NumberOfIterval_half1;// just deivid the Number of simulation so that 30% of simulation is used to get b
	double result4_1=0;
	double result4_2=0;
	double * Array_Save4_1=(double *)malloc(NumberOfIterval_half1*sizeof(double));
	double * Array_Save4_2=(double *)malloc(NumberOfIterval_half1*sizeof(double));
	long int start4,end4;
	start4=clock();
	for (int i=0;i<NumberOfIterval_half1;i++){
		Array_Save4_1[i]=EulerScheme1(SchemeE,Barrier,&Functiona, &Functionb, &payoff,0 );
		Array_Save4_2[i]=EulerScheme2(SchemeE,Barrier,&Functiona, &Functionb, &payoff,0 ).two_double[1];// again the struct saves a double array of size 2.
		result4_1+=Array_Save4_1[i];
		result4_2+=Array_Save4_2[i];
	}
	double mean4_1=result4_1/(NumberOfIterval_half1*1.0);
	double mean4_2=result4_2/(NumberOfIterval_half1*1.0);
	double stderr4_1=GetStdError(Array_Save4_1,mean4_1,NumberOfIterval_half1);
	double stderr4_2=GetStdError(Array_Save4_2,mean4_2,NumberOfIterval_half1);
	double b_estimated=cov(Array_Save4_1,Array_Save4_2,NumberOfIterval_half1,mean4_1,mean4_2)/(stderr4_1*stderr4_1);
	double pou=cov(Array_Save4_1,Array_Save4_2,NumberOfIterval_half1,mean4_1,mean4_2)/(stderr4_1*stderr4_2);
	free(Array_Save4_1);
	free(Array_Save4_2);
	cout<<"B_estimated is : "<<b_estimated<<" pou is : "<<pou<<"\n";
	double result4_22=0;
	double * Array_Save4_12=(double *)malloc(NumberOfIterval_half2*sizeof(double));
	double * Array_Save4_22=(double *)malloc(NumberOfIterval_half2*sizeof(double));
	for (int i=0;i<NumberOfIterval_half2;i++){
		Output_twoD temp=EulerScheme2(SchemeE,Barrier,&Functiona, &Functionb, &payoff,0 );
		Array_Save4_12[i]=EulerScheme1(SchemeE,Barrier,&Functiona, &Functionb, &payoff,0 );
		Array_Save4_22[i]=temp.two_double[1]-b_estimated*(Array_Save4_12[i]-\
		BlackScholesCall(opt.spot,opt.Strike,opt.Rate,0,opt.Vol,opt.Expiry));// appllied control variable method by using plain European option as paired variabel
		result4_22+=Array_Save4_22[i];
	}
	double mean4_22=result4_22/(NumberOfIterval_half2*1.0);
	double stderr4_22=GetStdError(Array_Save4_22,mean4_22,NumberOfIterval_half2);
	free(Array_Save4_22);
	end4=clock();
	long int dif4=end4-start4;
	cout <<"Control variates barrier option price =" << mean4_22 <<","<< " std error = "<<stderr4_22<<","<<\
		" time run = "<<((long double)dif4)/(1.0*CLOCKS_PER_SEC)<<"\n";
	    double tmp;
    cin >> tmp;
	return 0;
}

