
#include "../include/SobolGenerator1.h"
#include <stdio.h>
#include <assert.h>

SobolGenerator::SobolGenerator(unsigned long Dimensionality, unsigned long Seed)
	:    RandomBase(Dimensionality),InitialSeed(Seed)
{
SobolGenerator::seed=Seed;

}


void SobolGenerator::GetUniforms(MJArray& variates)
{// here is the Sobol sequence generated. Note that I have a static value to remember the seed.
	float *quasi= (float*)malloc( sizeof(float)*GetDimensionality());
	//cout<<"size of Dimensionality"<<GetDimensionality()<<"\n";
  static int seed_1=(int)SobolGenerator::seed;
	
	i4_sobol ( GetDimensionality(),&seed_1, quasi );
	for (int j=0; j < GetDimensionality(); j++){
		variates[j] =(double) quasi[j];
	}
	free(quasi);
}
//below are just some functions override the RandomBase class methods.
void SobolGenerator::Skip(unsigned long numberOfPaths){
MJArray tmp(GetDimensionality());
    for (unsigned long j=0; j < numberOfPaths; j++)
        SobolGenerator::GetUniforms(tmp);
}
  
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
	SetSeed(InitialSeed);
  
}


