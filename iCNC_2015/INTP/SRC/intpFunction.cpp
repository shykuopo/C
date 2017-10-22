#include "stdafx.h"
#include "../../INTP/INC/intp.h"
#include "..\..\CNC\INC\CNC.h"
#include <math.h>
extern  CNC_DATA* cncDataPtr;
                 
void intpLinearPre(INTP_DATA* intpDataPtr)
{
	double relRK[3];        
	
	for(int i=0;i<3;i++)
	intpDataPtr->startRKPos[i]=cncDataPtr->linkData.intpToMmiBlock.newRKPos[i];
	
	if(intpDataPtr->decToIntpBlock.relMotion == false)
	{
		for(int i=0;i<3;i++)
		{  
			intpDataPtr->endRKPos[i] = intpDataPtr->decToIntpBlock.cordValue[i];
			relRK[i] = intpDataPtr->endRKPos[i] - intpDataPtr->startRKPos[i];
		}
	}
	else if (intpDataPtr->decToIntpBlockPtr->relMotion == true)
	{
		for(int i=0;i<3;i++)
		{
			relRK[i] = intpDataPtr->decToIntpBlock.cordValue[i];
			intpDataPtr->endRKPos[i] = intpDataPtr->startRKPos[i] + relRK[i];
		}
	}

	if(intpDataPtr->decToIntpBlock.feed == 0)
	intpDataPtr->decToIntpBlock.feed = defaultFeed;

	intpDataPtr->increment = intpDataPtr->decToIntpBlock.feed *(realTimer*0.001);
	intpDataPtr->totalLength = sqrt(relRK[0]*relRK[0]+relRK[1]*relRK[1]+relRK[2]*relRK[2]);

	for(int i=0;i<3;i++)
	intpDataPtr->increRKPos[i] = relRK[i] / intpDataPtr->totalLength;

	intpDataPtr->slopeData.steadyFeed = intpDataPtr->decToIntpBlock.feed;
	intpDataPtr->slopeData.pathLength = intpDataPtr->totalLength;
	intpDataPtr->sumLength = 0;
	intpDataPtr->resiLength = intpDataPtr->totalLength;
	intpDataPtr->slopeData.state = SLOPE_LONG;
	intpDataPtr->slopeData.counter = 1;

	slopeMain(intpDataPtr);

	intpDataPtr->intpState = INTP_EXE;

	return ;
}

void intpLinearExe(INTP_DATA* intpDataPtr)
{
	//判定速度算經過和剩下距離
	if(intpDataPtr->slopeData.state == SLOPE_LONG)
	{
		if(intpDataPtr->slopeData.counter < intpDataPtr->slopeData.accStep)
		{
			intpDataPtr->slopeData.velocityNow = intpDataPtr->slopeData.vStep * intpDataPtr->slopeData.counter;
		}
		else if((intpDataPtr->slopeData.counter>=intpDataPtr->slopeData.accStep)&&(intpDataPtr->slopeData.counter<=(intpDataPtr->slopeData.accStep+intpDataPtr->slopeData.steadyStep+1)))
		{
			intpDataPtr->slopeData.velocityNow = intpDataPtr->slopeData.steadyFeed;
		}
		else if(intpDataPtr->slopeData.counter >(intpDataPtr->slopeData.accStep+intpDataPtr->slopeData.steadyStep+1))
		{
			intpDataPtr->slopeData.velocityNow = intpDataPtr->slopeData.vStep*(intpDataPtr->slopeData.totalCount-intpDataPtr->slopeData.counter+1);
			if((intpDataPtr->slopeData.velocityNow <= intpDataPtr->slopeData.restVelocity)&&(intpDataPtr->slopeData.restCheck == true))
			{
				intpDataPtr->slopeData.velocityNow = intpDataPtr->slopeData.restVelocity;
				intpDataPtr->slopeData.counter--;
				intpDataPtr->slopeData.restCheck = false; 
			}
		}
	}

	else if(intpDataPtr->slopeData.state == SLOPE_SHORT)
	{
		if(intpDataPtr->slopeData.counter <= intpDataPtr->slopeData.accStep)
			intpDataPtr->slopeData.velocityNow = intpDataPtr->slopeData.vStep * intpDataPtr->slopeData.counter;
		
		if(intpDataPtr->slopeData.counter > intpDataPtr->slopeData.accStep)
		{
			intpDataPtr->slopeData.velocityNow = intpDataPtr->slopeData.vStep *(intpDataPtr->slopeData.totalCount-intpDataPtr->slopeData.counter+1);
			
			if((intpDataPtr->slopeData.velocityNow <= intpDataPtr->slopeData.restVelocity)&&(intpDataPtr->slopeData.restCheck == true))
			{
				intpDataPtr->slopeData.velocityNow = intpDataPtr->slopeData.restVelocity;
				intpDataPtr->slopeData.counter--;
				intpDataPtr->slopeData.restCheck = false;
			}
		}
	}

	intpDataPtr->sumLength += (intpDataPtr->slopeData.velocityNow*intpDataPtr->slopeData.cyclingTime*(0.001));
	intpDataPtr->resiLength = intpDataPtr->slopeData.pathLength - intpDataPtr->sumLength;

	for(int i=0;i<3;i++)
	{
		intpDataPtr->oldMKPos[i] = intpDataPtr->newMKPos[i];
		intpDataPtr->oldRKPos[i] = intpDataPtr->newRKPos[i];
		intpDataPtr->newRKPos[i] = intpDataPtr->startRKPos[i] + intpDataPtr->increRKPos[i]*intpDataPtr->sumLength;
	}

	trafoXYZtoUVW(intpDataPtr);

	for(int i=0;i<3;i++)
	{
		cncDataPtr->linkData.intpToMmiBlock.oldRKPos[i] = intpDataPtr->oldRKPos[i];
		cncDataPtr->linkData.intpToMmiBlock.newRKPos[i] = intpDataPtr->newRKPos[i];
		cncDataPtr->linkData.intpToMmiBlock.oldMKPos[i] = intpDataPtr->oldMKPos[i];
		cncDataPtr->linkData.intpToMmiBlock.newMKPos[i] = intpDataPtr->newMKPos[i];

	}

	intpDataPtr->slopeData.counter++;

	if(intpDataPtr->slopeData.counter > intpDataPtr->slopeData.totalCount)
		intpDataPtr->intpState = INTP_END;
	return ;
}


