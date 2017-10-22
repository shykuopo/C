#include "StdAfx.h"
#include "../INC/intp.h"
#include"../../LINK/INC/link.h"
#include "..\..\CNC\INC\CNC.h"
#include "../../FIFO/INC/fifo.h"
#include "../../UTIL/INC/util.h"
extern  CNC_DATA* cncDataPtr;

void intpInit(INTP_DATA *intpDataPtr)
{
	intpDataPtr->intpReset = false;
	intpDataPtr->intpRestart = true;

	intpDataPtr->startRKPos[0] = 75;
	intpDataPtr->startRKPos[1] = 75;
	intpDataPtr->startRKPos[2] = 0;

    intpDataPtr->newMKPos[0] = 0;
	intpDataPtr->newMKPos[1] = 90;
	intpDataPtr->newMKPos[2] = 0;
	for(int i=0;i<3;i++)
	{
		intpDataPtr->increRKPos[i] = 0;
		intpDataPtr->oldRKPos[i] = intpDataPtr->startRKPos[i];
		intpDataPtr->endRKPos[i] = intpDataPtr->startRKPos[i];
		intpDataPtr->newRKPos[i] = intpDataPtr->startRKPos[i];
		intpDataPtr->oldMKPos[i] = intpDataPtr->newMKPos[i];
		

	}

	intpDataPtr->slopeData.state = SLOPE_LONG;
	intpDataPtr->slopeData.restCheck = false;
	intpDataPtr->slopeData.acceleration = 0.01; //m/s
	intpDataPtr->slopeData.cyclingTime = realTimer; // 20 ms 
	intpDataPtr->slopeData.counter = 1;
	intpDataPtr->slopeData.steadyFeed = 0;
	intpDataPtr->slopeData.totalCount = 0;
	intpDataPtr->slopeData.vStep = 0;
	intpDataPtr->slopeData.accDist = 0;
	intpDataPtr->slopeData.diccDist = 0;
	intpDataPtr->slopeData.steadyDist = 0;
	intpDataPtr->slopeData.restLength = 0;
	intpDataPtr->slopeData.restVelocity = 0;
	intpDataPtr->slopeData.pathLength = 0;
	intpDataPtr->slopeData.vStep = 0;
	intpDataPtr->slopeData.accStep = 0;
	intpDataPtr->slopeData.diccStep = 0;
	intpDataPtr->slopeData.steadyStep = 0;
	intpDataPtr->slopeData.velocityNow = 0;



	intpDataPtr->decToIntpBlockPtr = &intpDataPtr->decToIntpBlock; // <-- seems to be unnecessary ....
	intpDataPtr->decToIntpFifoPtr = &cncDataPtr->linkDataPtr->decToIntpFifo;
	intpDataPtr->decToIntpFifoPtr->head.rdIndex=0;
	

	for(int i=0;i<3;i++)
	{
		cncDataPtr->linkData.intpToMmiBlock.newRKPos[i] = intpDataPtr->newRKPos[i];
		cncDataPtr->linkData.intpToMmiBlock.newMKPos[i] = intpDataPtr->newMKPos[i];
	}

	

	intpDataPtr->intpCtlState = INTP_RUN;
	return  ; 

}

void intpCtrl(INTP_DATA *intpDataPtr)
{
	
	switch(intpDataPtr->intpCtlState)
	{
	case INTP_INIT:
		intpInit(intpDataPtr);
		break;
	case INTP_RUN:
		intpRun(intpDataPtr);
		break;
	case INTP_WAIT_RESET_HOLD:
		intpWaitResetHold(intpDataPtr);
		break;
	case INTP_DO_RESET:
		intpDoReset(intpDataPtr);
		break;
	case INTP_RESET_READY:
		intpResetReady(intpDataPtr);
		break;
	}
	
	return ;
}

void intpMain(INTP_DATA *intpDataPtr)
{

	switch(intpDataPtr->intpState)
	{
	case INTP_IDLE:      
		intpIdle(intpDataPtr);
		break;
	case INTP_DWELL_TIME: 
		intpDwellTi(intpDataPtr);
		break;
	case INTP_PROGRAM_END:
		intpProEnd(intpDataPtr);
		break;
	case INTP_PRE:       
		intpPre(intpDataPtr);
		break;
	case INTP_EXE:       
		intpExe(intpDataPtr); 
		break;
	case INTP_END:      
		intpEnd(intpDataPtr);
		break;
	case INTP_ERR:      
		break;
	}
	return ;

}

void intpRun(INTP_DATA *intpDataPtr)
{
	intpMain(intpDataPtr);

	if(intpDataPtr->intpReset == true)
	{
		intpDataPtr->intpCtlState = INTP_WAIT_RESET_HOLD;
		intpDataPtr->intpRestart = false;

	}
	return ;
}

void intpWaitResetHold(INTP_DATA *intpDataPtr)
{
	//速度規0
	intpDataPtr->slopeData.velocityNow -= intpDataPtr->slopeData.vStep;

	if(intpDataPtr->slopeData.velocityNow > 0)
	{
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
			cncDataPtr->linkData.intpToMmiBlock.newRKPos[i] = intpDataPtr->newRKPos[i];
			cncDataPtr->linkData.intpToMmiBlock.newMKPos[i] = intpDataPtr->newMKPos[i];
		}

	}

	else if(intpDataPtr->slopeData.velocityNow <= 0)
	{
		intpDataPtr->intpCtlState = INTP_DO_RESET;
	}

	return;
}

void intpDoReset(INTP_DATA *intpDataPtr)
{
	for(int i=0;i<3;i++)
	{
		cncDataPtr->linkData.intpToSysBlock.nowRKPos[i] = cncDataPtr->linkData.intpToMmiBlock.newRKPos[i];
		cncDataPtr->linkData.intpToSysBlock.nowMKPos[i] = cncDataPtr->linkData.intpToMmiBlock.newMKPos[i];
	}
	//intpDataPtr decToIntpFifoPtr decTointBlockPtr 清空
	intpDataPtr->decToIntpFifoPtr = &cncDataPtr->linkData.decToIntpFifo;
	intpDataPtr->decToIntpBlockPtr = &intpDataPtr->decToIntpBlock;

	delByteSpace((char *)intpDataPtr->decToIntpBlockPtr,sizeof(DEC_TO_INTP_Block));
	delByteSpace((char *)intpDataPtr,sizeof(INTP_DATA));
	
	for(int i=0; i<DEC_TO_INTP_FIFO_LENGTH ; i++)
	{
		DEC_TO_INTP_Block *resetFifoBlockPtr;
		resetFifoBlockPtr = &cncDataPtr->linkData.decToIntpFifo.block[i];
        delByteSpace((char *)resetFifoBlockPtr,sizeof(DEC_TO_INTP_Block));
		
		cncDataPtr->linkData.decToIntpFifo.valid[i] = false;
	}

	intpDataPtr->decToIntpFifoPtr = &cncDataPtr->linkData.decToIntpFifo;
	intpDataPtr->decToIntpBlockPtr = &intpDataPtr->decToIntpBlock;

	cncDataPtr->linkData.decToIntpFifo.head.wrIndex = 0;
	cncDataPtr->linkData.decToIntpFifo.head.rdIndex = 0;

	cncDataPtr->mmiDataPtr->restart = true ;

	intpDataPtr->intpCtlState = INTP_RESET_READY;

	return;
}

void intpResetReady(INTP_DATA *intpDataPtr)
{
	intpDataPtr->intpReset = false;
	cncDataPtr->mmiData.startHold = false;
	
	if(intpDataPtr->intpRestart == true)
	{
		for(int i=0;i<3;i++)
		{
			intpDataPtr->startRKPos[i] = cncDataPtr->linkData.intpToSysBlock.nowRKPos[i];
			intpDataPtr->newMKPos[i] = cncDataPtr->linkData.intpToSysBlock.nowMKPos[i];
		}

		intpDataPtr->slopeData.state = SLOPE_LONG;
		intpDataPtr->slopeData.restCheck = false;
		intpDataPtr->slopeData.acceleration = 0.01;
		intpDataPtr->slopeData.cyclingTime = realTimer; 
		intpDataPtr->slopeData.counter = 1;

		intpDataPtr->intpCtlState = INTP_RUN;

	}
	return;
}




