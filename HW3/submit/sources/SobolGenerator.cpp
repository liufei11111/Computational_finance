
#include "../include/SobolGenerator.h"





SobolGenerator::SobolGenerator(unsigned long Dimensionality, unsigned long Seed)
:    RandomBase(Dimensionality)
{
SobolGenerator::seed=Seed;

}


void SobolGenerator::GetUniforms(MJArray& variates)
{//this is the function to use to Sobel vectors	void i4_sobol ( int dim_num, int *seed, float quasi[ ] )
	float* quasi=(float *)malloc(sizeof(float)*GetDimensionality());
	i4_sobol ( GetDimensionality(), (int*)SobolGenerator::seed,quasi );
	for (unsigned long j=0; j < (unsigned long)GetDimensionality(); j++)
        variates[j] = quasi[j];
		free(quasi);

}
void SobolGenerator::Skip(unsigned long numberOfPaths){}
  //  virtual void GetSobol(MJArray& variates);    
 RandomBase* SobolGenerator::clone()const {
 return new SobolGenerator(*this);   }    


void SobolGenerator::SetSeed(unsigned long Seed)
{
    SobolGenerator::seed = Seed;
    
}

void SobolGenerator::Reset()
{
    SetSeed(InitialSeed);
}


void SobolGenerator::ResetDimensionality(unsigned long NewDimensionality)
{
    RandomBase::ResetDimensionality(NewDimensionality);
  
}

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

