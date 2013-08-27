//
//
//		UNI:fl2312
//		Name: Fei Liu
//		HW5
//		Testing Environment is Visual Studio 2012
//      What I did:
//		1. ExplicitFD in general is written in ExplicitFD header and cpp files. 
//		2. The thisA, thisB, thisC function takes more than necessary parameters as I want to leave a place for future updates. 
//		3. The space and time steps can be adjusted in the file- ExplicitFD.h. They are used as macros because the arraies I used don't take non-constant.
//		4. The othe files are either borrowed from Joshi or are written in previous homeworks.
#include "../include/BlackScholesFormulas.h"
#include "../include/normals.h"
#include "../include/ExplicitFD.h"
#include <iostream>
#include "../include/Barrier_Close.h"
using  namespace std;

// Note that the time/space number of intervals are specified in the file of ExplicitFD.h
void main(){
	double Strike=110;
	double Spot=100;
	double Barrier=120;
	double MaxSpot=200;
	double MinSpot=0;
	double Expiry=1;
	double InterestRate=0.05;
	double Vol=0.3;
	double divident=0.02;
	Parameters p;
	p.Strike=Strike;
	p.Barrier=Barrier;
	p.divident=divident;
	p.Expiry=Expiry;
	p.InterestRate=InterestRate;
	p.MaxSpot=MaxSpot;
	p.MinSpot=MinSpot;
	p.Spot=Spot;
	p.Vol=Vol;

	////////////////////////////////////////////////////////////
	cout<<"The Closed-form European-style vanilla call price = "<<BlackScholesCall(Spot,Strike,InterestRate,divident,Vol,Expiry)<<"\n";
	////////////////////////////////////////////////////////////
	PayOffCall thisPayOff(p.Strike);
	cout<<"Explicit FD European-style vanilla call price = "<<ExplicitFD(p,thisPayOff,thisA,thisB,thisC)<<"\n";
	////////////////////////////////////////////////////////////
	Option op;
	op.Barrier=Barrier;
	op.Expiry=Expiry;
	op.Rate=InterestRate-divident;
	op.spot=Spot;
	op.Strike=Strike;
	op.Vol=Vol;
	cout<<"The Closed-form European-style vanilla call price = "<<valueBarrier(op)<<"\n";
	////////////////////////////////////////////////////////////
	cout<<"Explicit FD European-style Barrier call price = "<<ExplicitFDBarrier(p,thisPayOff,thisA,thisB,thisC)<<"\n";
	////////////////////////////////////////////////////////////
	

	double temp;
	cin>>temp;
	return;


}