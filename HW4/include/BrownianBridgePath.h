#ifndef __BrownianBridgePath_H__
#define __BrownianBridgePath_H__
	#ifndef __SOBOL_H__
	#include "sobol.h"
	#endif
	#ifndef __MATH_H__
	#include "math.h"
	#endif
	#ifndef __NORMALS_H__
	#include "normals.h"
	#endif
	#ifndef __EXOTICENGINE_H__
	#include "ExoticEngine.h"
	#endif
	#ifndef __RANDOM2_H__
	#include "Random2.h"
	#endif
#include "ExoticEngine.h"
#include "Random2.h"
#include <stdlib.h>
extern const int MAXPATHS;
extern const double Expiry_global;
class BrownianBridgePath : public ExoticEngine
{
public:

     BrownianBridgePath(const Wrapper<PathDependent>& TheProduct_,
                     const Parameters& R_,
                     const Parameters& D_,
                     const Parameters& Vol_,
                     const Wrapper<RandomBase>& TheGenerator_,
                     double Spot_);

      virtual void GetOnePath(MJArray& SpotValues);
      virtual ~BrownianBridgePath(){}
 

private:

    Wrapper<RandomBase> TheGenerator;
    MJArray Drifts;
    MJArray StandardDeviations;
    double LogSpot;
    unsigned long NumberOfTimes;
    MJArray Variates;
};

#endif


