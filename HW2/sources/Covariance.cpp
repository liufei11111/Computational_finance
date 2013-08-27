#include "../include/Covariance.h"

double cov(double *x, double *y,int size,double mean_x,double mean_y){
	double result=0;
	for (int i=0;i<size;i++){
		result+=(x[i]-mean_x)*(y[i]-mean_y);
	}
	return result/size;
}
