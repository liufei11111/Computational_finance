#include "../include/ExplicitFD.h"
double thisA(Parameters p,int thisStep,double CurrSpot,double CurrTime){
	return 0.5*(p.Vol*p.Vol*thisStep*thisStep-(p.InterestRate-p.divident)*thisStep)*(p.Expiry*1.0/timeStepGlobal);
}
double thisB(Parameters p,int thisStep,double CurrSpot,double CurrTime){
	return -1.0*(p.Vol*p.Vol*thisStep*thisStep+p.InterestRate)*(p.Expiry*1.0/timeStepGlobal);
}
double thisC(Parameters p,int thisStep,double CurrSpot,double CurrTime){
	return 0.5*(p.Vol*p.Vol*thisStep*thisStep+(p.InterestRate-p.divident)*thisStep)*(p.Expiry*1.0/timeStepGlobal);
}
// The CurrSpot is not used in this case but it may be used latter. So, I keep them there.
double ExplicitFD(Parameters p,PayOffCall thisPayOff,double (*thisA)(Parameters,int,double,double),double (*thisB)(Parameters,int,double,double),double (*thisC)(Parameters,int,double,double)){
	double TheMatrix[SpaceStepGlobal+1][timeStepGlobal+1];// Matrix<space><time> 
	double timeStepLength=p.Expiry*1.0/timeStepGlobal;
	double spaceStepLength=p.MaxSpot*1.0/SpaceStepGlobal;
	double EndingSpot[SpaceStepGlobal+1];
	for (int i=0;i<SpaceStepGlobal+1;i++){
		EndingSpot[i]=i*spaceStepLength;
		TheMatrix[i][0]=thisPayOff(EndingSpot[i]);
	}
	for (int k=0;k<timeStepGlobal;k++){
		double RealTime=p.Expiry-k*timeStepLength;//not needed here but keep it for future uses.
		for (int i=1;i<SpaceStepGlobal;i++){
			TheMatrix[i][k+1]=thisA(p,i,i*spaceStepLength,RealTime)*TheMatrix[i-1][k]+(thisB(p,i,i*spaceStepLength,RealTime)+1)*TheMatrix[i][k]+thisC(p,i,i*spaceStepLength,RealTime)*TheMatrix[i+1][k];
		}
		TheMatrix[0][k+1]=0;
		TheMatrix[SpaceStepGlobal][k+1]=2*TheMatrix[SpaceStepGlobal-1][k+1]-TheMatrix[SpaceStepGlobal-2][k+1];
	}
	int NoOfGrid=(int)p.Spot/spaceStepLength;
		return TheMatrix[NoOfGrid][timeStepGlobal];
}
double ExplicitFDAmerican(Parameters p,PayOffCall thisPayOff,double (*thisA)(Parameters,int,double,double),double (*thisB)(Parameters,int,double,double),double (*thisC)(Parameters,int,double,double)){
	double TheMatrix[SpaceStepGlobal+1][timeStepGlobal+1];// Matrix<space><time> 
	double timeStepLength=p.Expiry*1.0/timeStepGlobal;
	double spaceStepLength=p.MaxSpot*1.0/SpaceStepGlobal;
	double EndingSpot[SpaceStepGlobal+1];
	for (int i=0;i<SpaceStepGlobal+1;i++){
		EndingSpot[i]=i*spaceStepLength;
		TheMatrix[i][0]=thisPayOff(EndingSpot[i]);
	}
	for (int k=0;k<timeStepGlobal;k++){
		double RealTime=p.Expiry-k*timeStepLength;//not needed here but keep it for future uses.
		for (int i=1;i<SpaceStepGlobal;i++){
			TheMatrix[i][k+1]=max(thisPayOff(i*spaceStepLength),thisA(p,i,i*spaceStepLength,RealTime)*TheMatrix[i-1][k]+(thisB(p,i,i*spaceStepLength,RealTime)+1)*TheMatrix[i][k]+thisC(p,i,i*spaceStepLength,RealTime)*TheMatrix[i+1][k]);
		}
		TheMatrix[0][k+1]=0;
		TheMatrix[SpaceStepGlobal][k+1]=2*TheMatrix[SpaceStepGlobal-1][k+1]-TheMatrix[SpaceStepGlobal-2][k+1];
	}
	int NoOfGrid=(int)p.Spot/spaceStepLength;
		return TheMatrix[NoOfGrid][timeStepGlobal];
}
double ExplicitFDBarrier(Parameters p,PayOffCall thisPayOff,double (*thisA)(Parameters,int,double,double),double (*thisB)(Parameters,int,double,double),double (*thisC)(Parameters,int,double,double)){
	double TheMatrix[SpaceStepGlobal+1][timeStepGlobal+1];// Matrix<space><time> 
	double timeStepLength=p.Expiry*1.0/timeStepGlobal;
	double spaceStepLength=p.MaxSpot*1.0/SpaceStepGlobal;
	double EndingSpot[SpaceStepGlobal+1];
	for (int i=0;i<SpaceStepGlobal+1;i++){
		EndingSpot[i]=i*spaceStepLength;
		TheMatrix[i][0]=thisPayOff(EndingSpot[i]);
	}
	for (int k=0;k<timeStepGlobal;k++){
		double RealTime=p.Expiry-k*timeStepLength;//not needed here but keep it for future uses.
		for (int i=1;i<SpaceStepGlobal;i++){
			
			if (i*spaceStepLength>=p.Barrier)
				TheMatrix[i][k+1]=0;
			else 
			TheMatrix[i][k+1]=thisA(p,i,i*spaceStepLength,RealTime)*TheMatrix[i-1][k]+(thisB(p,i,i*spaceStepLength,RealTime)+1)*TheMatrix[i][k]+thisC(p,i,i*spaceStepLength,RealTime)*TheMatrix[i+1][k];
		}
		TheMatrix[0][k+1]=0;
		TheMatrix[SpaceStepGlobal][k+1]=2*TheMatrix[SpaceStepGlobal-1][k+1]-TheMatrix[SpaceStepGlobal-2][k+1];
	}
	int NoOfGrid=(int)p.Spot/spaceStepLength;
		return TheMatrix[NoOfGrid][timeStepGlobal];
}