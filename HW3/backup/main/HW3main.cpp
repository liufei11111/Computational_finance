//
//
//		UNI:fl2312
//		Name: Fei Liu
//		HW3
//      Largely, this is an excercise of understanding what Joshi did in his code. The framework (brillient!) was given by Joshi.
//		I took off the temp in the end that is supposed to stop the windows from quiting if you are testing on Windows. 
//		Below is a list of change I made:
//		1. For Coverge table, I actually changed the frequency of showing so that I don't need to show the progress of the tree
//		in the only entry of the array.
//		2. I build a new class called SobolGenerator where methods of RandomBase are extended and Sobol sequence fills the GenUniform function.
//		3. In main function, I take off Antithetic for plain MC case and QMC case. 
//		4. I use global variables to store all simulated values and use them to calculate the variance for each method.
	#include"../include/ParkMiller.h"
	#include<iostream>
	using namespace std;
	#include"../include/MCStatistics.h"
	#include"../include/ConvergenceTable.h"
	#include"../include/AntiThetic.h"
	#include"../include/PathDependentAsian.h"
	#include"../include/ExoticBSEngine.h"
	#include"../include/BlackScholesFormulas.h"
	#include"../include/SobolGenerator.h"
	// I want to keep track of every result generated in this array and don't need to pass it everywhere and destroy the original function
	// So, I set the MAXPATHS here and you can modify the number here to change the entire program.
	// this global variable is used to measure variance of each 10000 simulations.
	const int MAXPATHS=10000;
	int COUNT_OF_RESULTS=0;
	double *RESULT_TOTAL=(double *)malloc(sizeof(double)*MAXPATHS);
int main()
{
	
	double Expiry=1.0;
	double Strike=50; 
	double Spot=100; 
	double Vol=0.3; 
	double r=0.05;
    double d=0;// this is not dimension and is just dividend
	unsigned long NumberOfPaths=MAXPATHS;
    unsigned NumberOfDates=21*12;
	//Important!!! The NumberOfDates has to be a multiple of 12 because the dimension of Sobol sequence is set to be 12.
	

    ////////////////////////////////////// Q1 //////////////////////////////////////
	cout<< "Closed-form vanilla call option price = "<<BlackScholesCall(Spot, Strike,r,0,Vol,Expiry)<< "\n";
	////////////////////////////////////// Q2 //////////////////////////////////////
		PayOffCall thePayOff(Strike);
		MJArray times(1);
	times[0]=Expiry;
	ParametersConstant VolParam(Vol);
    ParametersConstant rParam(r);
    ParametersConstant dParam(d);
    PathDependentAsian theOption(times, Expiry, thePayOff);
    StatisticsMean gatherer;
    ConvergenceTable gathererTwo(gatherer);
    RandomParkMiller generator(NumberOfDates);
	generator.SetSeed(1);
	ExoticBSEngine theEngine(theOption, rParam, dParam, VolParam, generator, Spot);
    theEngine.DoSimulation(gathererTwo, NumberOfPaths);
    vector<vector<double> > results =gathererTwo.GetResultsSoFar();
	double var=0;
	for (int i=0;i<MAXPATHS;i++){
		var+=(RESULT_TOTAL[i]-results[0][0])*(RESULT_TOTAL[i]-results[0][0]);}
	double stddev=sqrt(var/MAXPATHS);
	cout <<"MC vanilla call price with Park-Miller uniforms = "<< results[0][0]<<"  stddev = "<<stddev<<"\n";
	COUNT_OF_RESULTS=0;
	////////////////////////////////////// Q3 //////////////////////////////////////
	PayOffCall thePayOff3(Strike);
	MJArray times3(1);
	times3[0]=Expiry;
    ParametersConstant VolParam3(Vol);
    ParametersConstant rParam3(r);
    ParametersConstant dParam3(d);
    PathDependentAsian theOption3(times3, Expiry, thePayOff);
    StatisticsMean gatherer3;
    ConvergenceTable gathererTwo3(gatherer3);
    RandomParkMiller generator3(NumberOfDates);
	generator3.SetSeed(1);
    AntiThetic GenTwo3(generator3);
    ExoticBSEngine theEngine3(theOption, rParam, dParam, VolParam, GenTwo3, Spot);
    theEngine3.DoSimulation(gathererTwo3, NumberOfPaths);
    vector<vector<double> > results3 =gathererTwo3.GetResultsSoFar();
	double var3=0;
	for (int i=0;i<MAXPATHS;i++){
		var3+=(RESULT_TOTAL[i]-results[0][0])*(RESULT_TOTAL[i]-results[0][0]);}
	double stddev3=sqrt(var3/MAXPATHS);
	cout <<"MC vanilla call price with Park-Miller uniforms and antithetics = "<< results3[0][0]<<"  stddev = "<<stddev3<<"\n";
	COUNT_OF_RESULTS=0;
	////////////////////////////////////// Q4 //////////////////////////////////////
	PayOffCall thePayOff4(Strike);
		MJArray times4(1);
	times4[0]=Expiry;
    ParametersConstant VolParam4(Vol);
    ParametersConstant rParam4(r);
    ParametersConstant dParam4(d);
    PathDependentAsian theOption4(times4, Expiry, thePayOff);
    StatisticsMean gatherer4;
    ConvergenceTable gathererTwo4(gatherer4);
    SobolGenerator generator4(NumberOfDates);
	generator4.SetSeed(1);
    ExoticBSEngine theEngine4(theOption, rParam, dParam, VolParam, generator4, Spot);
    theEngine4.DoSimulation(gathererTwo4, NumberOfPaths);
    vector<vector<double> > results4 =gathererTwo4.GetResultsSoFar();
	double var4=0;
	for (int i=0;i<MAXPATHS;i++){
		var4+=(RESULT_TOTAL[i]-results[0][0])*(RESULT_TOTAL[i]-results[0][0]);}
	double stddev4=sqrt(var4/MAXPATHS);
	cout <<"QMC vanilla call price with Sobol sequence = "<< results4[0][0]<<"  stddev = "<<stddev4<<"\n";
	COUNT_OF_RESULTS=0;
	
	//////////////////// Please be noted that below code are for the ploting part in the report. If you want to see it, please comment out the code above this line

	////////////////////and uncommend below code to see the generated txt file in the homedirectory. 

	////////////////////////////////////// Graph data generation //////////////////////////////////////
	// below code generate the paired sequences that will be exported to MATLAB and plot graphs in the report.
	/*float* quasi=i4_sobol_generate ( 2, 1024,0 );
			FILE* fp =fopen("savedSobol.txt","w+");
		for (int d=0;d<2;d++){
			for(int i=0;i<1023;i++){
			fprintf(fp,"%f ",quasi[i+d*1024]);
			}
			fprintf(fp,"%f\n",quasi[d*1024+1023]);
		}
		fclose(fp);
		RandomParkMiller generator0(2048);
		MJArray ArrayParkMiller(2048);
		generator0.GetUniforms(ArrayParkMiller);
		FILE* fp1 =fopen("parkMiller.txt","w+");
		for (int d=0;d<2;d++){
			for(int i=0;i<1023;i++){
				fprintf(fp1,"%f ",ArrayParkMiller[i+d*1024]);
			}
			fprintf(fp1,"%f\n",ArrayParkMiller[d*1024+1023]);
		}
		fclose(fp1);
		*/
free(RESULT_TOTAL);
  double temp;
  cin>>temp;
	return 0;

}

