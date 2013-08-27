#include"../include/StdError.h"
double GetStdError(double *array_Save,double mean,int NumOfValue){
	double result=0;
	for (int i=0;i<NumOfValue;i++){
		result+=(array_Save[i]-mean)*(array_Save[i]-mean);
	}
	return sqrt(result/(NumOfValue*1.0));
}


