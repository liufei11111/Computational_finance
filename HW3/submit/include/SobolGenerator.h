//
//
//                      SobolGenerator.h
//
//
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
	int GetDimensionality(){
		return RandomBase::GetDimensionality();
	}
    virtual void ResetDimensionality(unsigned long NewDimensionality);

private:

    long int seed;
    unsigned long InitialSeed;



};
#endif

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
*/

