// This class describes the Geometric Asian option payoff

#ifndef __GEOMETRICASIANCF_H__
#define __GEOMETRICASIANCF_H__

#include "PathDependent.h"
#include "PayOffBridge.h"
#include "math.h"

class GeometricAsianCF : public PathDependent
{
public:

    GeometricAsianCF(const MJArray& LookAtTimes_, 
                       double DeliveryTime_,
                       const PayOffBridge& ThePayOff_);

    virtual unsigned long MaxNumberOfCashFlows() const;
    virtual MJArray PossibleCashFlowTimes() const;
    virtual unsigned long CashFlows(const MJArray& SpotValues, 
                                    std::vector<CashFlow>& GeneratedFlows) const;
    virtual ~GeometricAsianCF(){}
    virtual PathDependent* clone() const;

private:

    double DeliveryTime;
    PayOffBridge ThePayOff;
    unsigned long NumberOfTimes;
};


#endif


