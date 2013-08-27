// I wrote this SobolGenerator class
#ifndef __SOBOLGENERATOR_H__
#define __SOBOLGENERATOR_H__
#include "Random2.h"
#include "sobol.h"
#include <stdlib.h>
class SobolGenerator : public RandomBase
{
public:


    SobolGenerator(unsigned long Dimensionality, unsigned long Seed=1);

    void GetUniforms(MJArray& variates);
    void Skip(unsigned long numberOfPaths);
   
  virtual RandomBase* clone() const;  
    virtual void SetSeed(unsigned long Seed);
    virtual void Reset();
    virtual void ResetDimensionality(unsigned long NewDimensionality);

private:

     long seed;
    unsigned long InitialSeed;



};
#endif

