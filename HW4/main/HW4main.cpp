//
//
//		UNI:fl2312
//		Name: Fei Liu
//		HW4
//		Testing Environment is Visual Studio 2012
//      Largely, this is an excercise of understanding what Joshi did in his code. The framework (brillient!) was given by Joshi.
//		Below is a list of change I made:
//		1. For the GeometricAsianCF class. The main change happened for the way to average.
//		2. I wrote a new class called ExoticBSEngine and it is an extension of ExoticEngine. I used terminal stratfication
//			as well as Brownian bridge in the class.
//		3. I use global variables to store all simulated values and use them to calculate the variance for each method.
//		4. I also use global variable to pass Expiry to ExoticBSEngine and thisStrata and count_i to the main without fundamentally changing the parameter systems.
//			In this way, I can make sure everyvalue is reseted before next use.
	#include"../include/ParkMiller.h"
	#include<iostream>
	using namespace std;
	#include"../include/MCStatistics.h"
	#include"../include/ConvergenceTable.h"
	#include"../include/AntiThetic.h"
	#include"../include/PathDependentAsian.h"
	#include"../include/ExoticBSEngine.h"
	#include"../include/BlackScholesFormulas.h"
	#include"../include/SobolGenerator1.h"
	#include "../include/GeometricAsianCF.h"
	#include "../include/ClosedFormGeometricAsian.h"
	#include "../include/ExoticBSEngine.h"
	#include "../include/BrownianBridgePath.h"
	// I want to keep track of every result generated in this array and don't need to pass it everywhere and destroy the original function
	// So, I set the MAXPATHS here and you can modify the number here to change the entire program.
	// this global variable is used to measure variance of each 10000 simulations.
	const int MAXPATHS=10000;
	const double Expiry_global=1.0;
	const double interestRate_global=0.05;
	extern unsigned long count_i;
	extern int thisStrata;
	int COUNT_OF_RESULTS=0;
	double *RESULT_TOTAL=(double *)malloc(sizeof(double)*MAXPATHS);


int main()
{
	double Expiry=Expiry_global;
	double Strike=110; 
	double Spot=100; 
	double Vol=0.3; 
	double r=interestRate_global;
    double d=0; // this is not dimension and is just dividend
	unsigned long NumberOfPaths=MAXPATHS;
    
	unsigned long NumberOfLookBack=12;// This is for Asian Option.
	Input input;
	input.Expiry=Expiry;
	input.Strike=Strike;
	input.Spot=Spot;
	input.Vol=Vol;
	input.Intere=r-d;
	input.NumOfTimes=12;
    ////////////////////////////////////// Q1 //////////////////////////////////////
	cout<< "Closed-form vanilla call option price = "<<(double)BlackScholesCall(Spot, Strike,r,0,Vol,Expiry)<< "\n";
	// repeat the result of last homework
		PayOffCall thePayOff(Strike);
		MJArray times(1);
	times[0]=Expiry;
	ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);
    PathDependentAsian theOption(times, Expiry, thePayOff);
    StatisticsMean gatherer;
    ConvergenceTable gathererTwo(gatherer);
    RandomParkMiller generator(NumberOfLookBack);
	generator.SetSeed(1);
	AntiThetic gener(generator);
	
	ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, gener, Spot);
	    theEngine.DoSimulation(gathererTwo, NumberOfPaths);
    vector<vector<double> > results =gathererTwo.GetResultsSoFar();
	double var=0;
	for (int i=0;i<MAXPATHS;i++){
		var+=(RESULT_TOTAL[i]-results[0][0])*(RESULT_TOTAL[i]-results[0][0]);}
	double stddev=sqrt(var/MAXPATHS);
	cout <<"MC vanilla call price,Park-Miller uniforms = "<< results[0][0]<<"  stddev = "<<stddev<<"\n";
	COUNT_OF_RESULTS=0;
	count_i=0;
	thisStrata=1;
	///////////////////////////////
	PayOffCall thePayOff4(Strike);
	MJArray times4(1);
	times4[0]=Expiry;
    ParametersConstant VolParam4(Vol);
    ParametersConstant rParam4(r);
    ParametersConstant dParam4(d);
    PathDependentAsian theOption4(times4, Expiry, thePayOff);
    StatisticsMean gatherer4;
    ConvergenceTable gathererTwo4(gatherer4);
	SobolGenerator generator4(NumberOfLookBack);
	generator4.SetSeed(1);
	ExoticBSEngine theEngine4(theOption, rParam, dParam, VolParam, generator4, Spot);
    theEngine4.DoSimulation(gathererTwo4, NumberOfPaths);
    vector<vector<double> > results4 =gathererTwo4.GetResultsSoFar();
	double var4=0;
	for (int i=0;i<MAXPATHS;i++){
		var4+=(RESULT_TOTAL[i]-results4[0][0])*(RESULT_TOTAL[i]-results4[0][0]);}
	double stddev4=sqrt(var4/MAXPATHS);
	cout <<"QMC vanilla call price, Sobol sequence = "<< results4[0][0]<<"  stddev = "<<stddev4<<"\n\n";
	 count_i=0;
	COUNT_OF_RESULTS=0;
	thisStrata=1;
	////////////////////////////////////// Q2 //////////////////////////////////////
	double closedForm=ClosedFormFormulaForGeometricAsian(input);
	cout<<"Closed-form geometric Asian call price= "<<closedForm<<"\n";
	////////////////////////////////////
	
	PayOffCall thePayOff2(Strike);
	MJArray times2(NumberOfLookBack);
	for (unsigned long i=0; i < NumberOfLookBack; i++){
		 times2[i] = (i+1.0)*Expiry/NumberOfLookBack;
	 }
    GeometricAsianCF theOption2(times2, Expiry, thePayOff2);
    StatisticsMean gatherer2;
    ConvergenceTable gathererTwo2(gatherer2);
	RandomParkMiller generator2(NumberOfLookBack);
	AntiThetic gener2(generator2);
	gener2.SetSeed(1);
	ExoticBSEngine  theEngine2(theOption2, rParam, dParam, VolParam, gener2, Spot);
    theEngine2.DoSimulation(gathererTwo2, NumberOfPaths);
    vector<vector<double> > results2 =gathererTwo2.GetResultsSoFar();
	double var2=0;
	for (int i=0;i<MAXPATHS;i++){
		var2+=(RESULT_TOTAL[i]-results2[0][0])*(RESULT_TOTAL[i]-results2[0][0]);}
	double stddev2=sqrt(var2/MAXPATHS);
	cout <<"MC geometric Asian call, Park-Miller uniforms = "<< results2[0][0]<<"  stddev = "<<stddev2<<"\n";
	COUNT_OF_RESULTS=0;
	count_i=0;
	thisStrata=1;
	/////////////////////////////////////
	
	PayOffCall thePayOff3(Strike);
	MJArray times3(NumberOfLookBack);
	for (unsigned long i=0; i < NumberOfLookBack; i++){
		 times3[i] = (i+1.0)*Expiry/NumberOfLookBack;
	}
	
    GeometricAsianCF theOption3(times3, Expiry, thePayOff3);
    StatisticsMean gatherer3;
    ConvergenceTable gathererTwo3(gatherer3);
	SobolGenerator generator3(NumberOfLookBack);
	generator3.SetSeed(1);
	BrownianBridgePath theEngine3(theOption3, rParam, dParam, VolParam, generator3, Spot);
    theEngine3.DoSimulation(gathererTwo3, NumberOfPaths);
    vector<vector<double> > results3 =gathererTwo3.GetResultsSoFar();
	double var3=0;
	for (int i=0;i<MAXPATHS;i++){
		var3+=(RESULT_TOTAL[i]-results3[0][0])*(RESULT_TOTAL[i]-results3[0][0]);}
	double stddev3=sqrt(var3/MAXPATHS);
	cout <<"QMC geometric Asian call, Sobol sequence = "<< results3[0][0]<<"  stddev = "<<stddev3<<"\n\n";
	COUNT_OF_RESULTS=0;
	 count_i=0;
	 thisStrata=1;
	////////////////////////////////////// Q3 //////////////////////////////////////
	PayOffCall thePayOff5(Strike);
	MJArray times5(NumberOfLookBack);
	for (unsigned long i=0; i < NumberOfLookBack; i++){
		 times5[i] = (i+1.0)*Expiry/NumberOfLookBack;
	 }
	PathDependentAsian theOption5(times5, Expiry, thePayOff5);
    StatisticsMean gatherer5;
    ConvergenceTable gathererTwo5(gatherer5);
	RandomParkMiller generator5(NumberOfLookBack);
	AntiThetic gener5(generator5);
	gener5.SetSeed(1);
	ExoticBSEngine theEngine5(theOption5, rParam, dParam, VolParam, gener5, Spot);
    theEngine5.DoSimulation(gathererTwo5, NumberOfPaths);
    vector<vector<double> > results5 =gathererTwo5.GetResultsSoFar();
	double var5=0;
	for (int i=0;i<MAXPATHS;i++){
		var5+=(RESULT_TOTAL[i]-results5[0][0])*(RESULT_TOTAL[i]-results5[0][0]);}
	double stddev5=sqrt(var5/MAXPATHS);
	cout <<"MC Arithmetic Asian call, Park-Miller uniforms = "<< results5[0][0]<<"  stddev = "<<stddev5<<"\n";
	COUNT_OF_RESULTS=0;
	count_i=0;
	thisStrata=1;
	/////////////////////////////////////
	PayOffCall thePayOff6(Strike);
	MJArray times6(NumberOfLookBack);
	for (unsigned long i=0; i < NumberOfLookBack; i++){
		 times6[i] = (i+1.0)*Expiry/NumberOfLookBack;
	}
	
	PathDependentAsian theOption6(times6, Expiry, thePayOff2);
    StatisticsMean gatherer6;
    ConvergenceTable gathererTwo6(gatherer6);
    SobolGenerator generator6(NumberOfLookBack);
	generator6.SetSeed(1);
	BrownianBridgePath theEngine6(theOption6, rParam, dParam, VolParam, generator6, Spot);
	theEngine6.DoSimulation(gathererTwo6, NumberOfPaths);
    vector<vector<double> > results6 =gathererTwo6.GetResultsSoFar();
	double var6=0;
	for (int i=0;i<MAXPATHS;i++){
		var6+=(RESULT_TOTAL[i]-results6[0][0])*(RESULT_TOTAL[i]-results6[0][0]);}
	double stddev6=sqrt(var6/MAXPATHS);
	cout <<"QMC arithmetic Asian call, Sobol sequence = "<< results6[0][0]<<"  stddev = "<<stddev6<<"\n";
	COUNT_OF_RESULTS=0;
	 count_i=0;
	 thisStrata=1;
	 /////////////////////////////////////
free(RESULT_TOTAL);
  double temp;
  cin>>temp;
	return 0;

}

