#include "stdafx.h"
#include "..\INC\INTP.h"
#include "..\..\CNC\INC\CNC.h"

void slopeMain(INTP_DATA *intpDataPtr)
{
	//先進LONG看steadyStep是否小於0(是否SHORT)
	if(intpDataPtr->slopeData.state == SLOPE_LONG)
	{

	//計算出方格走多少距離
	intpDataPtr->slopeData.vStep = intpDataPtr->slopeData.acceleration *intpDataPtr->slopeData.cyclingTime;
	intpDataPtr->slopeData.stepDist = intpDataPtr->slopeData.vStep*intpDataPtr->slopeData.cyclingTime*(0.001);
	
    //加速的格數和距離
	intpDataPtr->slopeData.accStep = (int)(intpDataPtr->slopeData.steadyFeed / intpDataPtr->slopeData.vStep);
	intpDataPtr->slopeData.accDist = (0.5)*(1 + intpDataPtr->slopeData.accStep)*(intpDataPtr->slopeData.accStep)*(intpDataPtr->slopeData.stepDist);
	
	//減速=加速
	intpDataPtr->slopeData.diccStep = intpDataPtr->slopeData.accStep;
    intpDataPtr->slopeData.diccDist = intpDataPtr->slopeData.accDist;
	
	//最高速
	intpDataPtr->slopeData.steadyFeed = (intpDataPtr->slopeData.accStep)*(intpDataPtr->slopeData.vStep);
	
	//等速格數和距離
	intpDataPtr->slopeData.steadyStep =(int)((intpDataPtr->slopeData.pathLength-intpDataPtr->slopeData.accDist-intpDataPtr->slopeData.diccDist)/(intpDataPtr->slopeData.steadyFeed*intpDataPtr->slopeData.cyclingTime*0.001));
	intpDataPtr->slopeData.steadyDist = (intpDataPtr->slopeData.steadyStep)*(intpDataPtr->slopeData.accStep)*(intpDataPtr->slopeData.stepDist);
	
	//剩下距離和速度
	intpDataPtr->slopeData.restLength = intpDataPtr->slopeData.pathLength-intpDataPtr->slopeData.accDist-intpDataPtr->slopeData.diccDist- intpDataPtr->slopeData.steadyDist;
	intpDataPtr->slopeData.restVelocity = intpDataPtr->slopeData.restLength/(intpDataPtr->slopeData.cyclingTime*(0.001));
	
	//總費時
	intpDataPtr->slopeData.totalCount = intpDataPtr->slopeData.accStep + intpDataPtr->slopeData.diccStep + intpDataPtr->slopeData.steadyStep;
	

	if(intpDataPtr->slopeData.restLength >0)
	{
		intpDataPtr->slopeData.restCheck = true;
	}

	if(intpDataPtr->slopeData.steadyStep <= 0)
	{
		double check;
		check = intpDataPtr->slopeData.pathLength-intpDataPtr->slopeData.accDist-intpDataPtr->slopeData.diccDist;
		if(check <0)
		{
		intpDataPtr->slopeData.state = SLOPE_SHORT;
		slopeShort(intpDataPtr);
		}
	}
	}

	else if (intpDataPtr->slopeData.state == SLOPE_SHORT)
	{
		slopeShort(intpDataPtr);
	}
	return ;
}

void slopeShort(INTP_DATA *intpDataPtr)
{
	
	int accStep = 0;
	double shortDist;

	bool pass=false;

	while(shortDist < intpDataPtr->slopeData.pathLength && pass==false)
	{
		//利用短距離決定加速格數
		accStep++;
		shortDist = ((accStep)*(accStep-1)+accStep)*(intpDataPtr->slopeData.stepDist);
		
		//取到大於所需
		if(shortDist > (intpDataPtr->slopeData.pathLength))
		{
			//正確的加速格數
			accStep--;
			intpDataPtr->slopeData.accStep = accStep;

			//restLength restVelocity totalCount定義
			shortDist = ((accStep)*(accStep-1)+accStep)*(intpDataPtr->slopeData.stepDist);
			intpDataPtr->slopeData.restLength = intpDataPtr->slopeData.pathLength - shortDist;
			intpDataPtr->slopeData.restVelocity = (intpDataPtr->slopeData.restLength)/(intpDataPtr->slopeData.cyclingTime*0.001);
			intpDataPtr->slopeData.totalCount = (accStep-1)*2-1;
			
			intpDataPtr->slopeData.restCheck = true;
			pass = true;
		}
		else if(shortDist == intpDataPtr->slopeData.pathLength)
		{
			//restLength restVelocity totalCount定義
			intpDataPtr->slopeData.accStep = accStep;
			intpDataPtr->slopeData.restVelocity = 0;
			intpDataPtr->slopeData.totalCount = accStep*2-1;
			
			intpDataPtr->slopeData.restCheck = false;
			pass = true;
		}

	}

	return ;
}