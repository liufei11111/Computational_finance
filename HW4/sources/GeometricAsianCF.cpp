// This is the code for Geometirc Asian option payoff
#include "../include/GeometricAsianCF.h"
#include <iostream>
extern const double Expiry_global;
 const double interestRate_global=0.05;
GeometricAsianCF::GeometricAsianCF(const MJArray& LookAtTimes_, 
                                       double DeliveryTime_,
                                       const PayOffBridge& ThePayOff_)
                                       :
                                        PathDependent(LookAtTimes_),
                                        DeliveryTime(DeliveryTime_),
                                        ThePayOff(ThePayOff_),
                                        NumberOfTimes(LookAtTimes_.size())
{
}

unsigned long GeometricAsianCF::MaxNumberOfCashFlows() const
{
     return 1UL;
}

MJArray GeometricAsianCF::PossibleCashFlowTimes() const
{
    MJArray tmp(1UL);
    tmp[0] = DeliveryTime;
    return tmp;
}

unsigned long GeometricAsianCF::CashFlows(const MJArray& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const
{//Here is the place of primary change
    double product = 1;

	double * temp2_times=(double*)malloc(sizeof(double)*(SpotValues.size()+1));
	temp2_times[0]=0;
	for (int i=1; i < (int)SpotValues.size()+1; i++){
		 temp2_times[i] = (i)*Expiry_global/SpotValues.size();
	 }
	for (int i=0;i<(int)SpotValues.size();i++){
		product*=SpotValues[i];
	}
	
	double mean = pow(product,(1.0/SpotValues.size()));
	//std::cout<<"mean of Geo"<< mean<<"\n";
    GeneratedFlows[0].TimeIndex = 0UL;
    GeneratedFlows[0].Amount = ThePayOff(mean);

    return 1UL;
}

PathDependent* GeometricAsianCF::clone() const
{
    return new GeometricAsianCF(*this);
}



