#ifndef __CLOSEDFORMGEOMETRICASIAN_H__
#define __CLOSEDFORMGEOMETRICASIAN_H__
#ifndef __MATH_H__
#include <math.h>
#endif
#ifndef __NORMALS_H__
#include "normals.h"
#endif
struct Input{
double NumOfTimes;
double Spot;
double Vol;
double Expiry;
double Intere;
double Strike;
};
double ClosedFormFormulaForGeometricAsian(Input );

#endif