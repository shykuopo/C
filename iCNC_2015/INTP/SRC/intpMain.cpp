#include "StdAfx.h"
#include "../INC/intp.h"
#include "../../LINK/INC/link.h"
#include "../../CNC/INC/cnc.h"
extern  CNC_DATA* cncDataPtr;


void intpIdle(INTP_DATA *intpDataPtr)
{
	FIFO_STATUS fifoStatus;
	fifoStatus = rdDecToIntpFifo(intpDataPtr->decToIntpFifoPtr,intpDataPtr->decToIntpBlockPtr);
	//½T©wFIFOÅª¨ì
	if(fifoStatus == RD_DONE)
	{
		if((intpDataPtr->decToIntpBlock.motType != ZERO_TYPE)&&(intpDataPtr->decToIntpBlock.stpEnd !=ZERO_STOP))
			intpDataPtr->intpState = INTP_ERR; 
		else if(intpDataPtr->decToIntpBlock.motType != ZERO_TYPE)
		{
			if(intpDataPtr->decToIntpBlock.motType == DWELL_TIME_CMD)
			{
				intpDataPtr->dwellTiLast = (((intpDataPtr->decToIntpBlock.cordValue[0])*1000)/(50));
				
				intpDataPtr->intpState = INTP_DWELL_TIME; 
				

			}
			else
				intpDataPtr->intpState = INTP_PRE;
		}
		else if(intpDataPtr->decToIntpBlock.stpEnd != ZERO_STOP)
		{
			intpDataPtr->intpState = INTP_PROGRAM_END;
		}

		cncDataPtr->linkData.intpToMmiBlock.blockNumber = intpDataPtr->decToIntpBlock.blockNumber;
	}
	else if(fifoStatus == FIFO_EMPTY)
	{
		intpDataPtr->intpState = INTP_IDLE;
	}

	return;
	
}

void intpDwellTi(INTP_DATA *intpDataPtr)
{
	intpDataPtr->dwellTiLast--; 

	if(intpDataPtr->dwellTiLast>0)
		intpDataPtr->intpState = INTP_DWELL_TIME;
	else if(intpDataPtr->dwellTiLast<=0)
		intpDataPtr->intpState = INTP_IDLE;
	return;
}

void intpPre(INTP_DATA *intpDataPtr)
{
	if(intpDataPtr->decToIntpBlock.inputMod == UVW_INPUT) // transform coordi from UVW to XYZ
	trafoUVWtoXYZ(intpDataPtr);
	

	switch(intpDataPtr->decToIntpBlock.motType) 
	{
	case RAPID_CMD:
	case LINEAR_CMD:
		intpLinearPre(intpDataPtr); 
		break;
	case CIR_CW_CMD:
	case CIR_CCW_CMD:
		break;
	default:
		break;
	}
	return;
}

void intpExe(INTP_DATA *intpDataPtr)
{
	switch(intpDataPtr->decToIntpBlock.motType)
	{
	case RAPID_CMD:
	case LINEAR_CMD:
		intpLinearExe(intpDataPtr);
		break;
	case CIR_CW_CMD:
		break;
	case CIR_CCW_CMD:
		break;
	default:
		break;
	}
	return;
}

void intpProEnd(INTP_DATA *intpDataPtr)
{
	switch(intpDataPtr->decToIntpBlock.stpEnd)
	{
	case M00_STOP:
		break;
	case M01_STOP:
		break;
	case M30_END:
		cncDataPtr->mmiDataPtr->startHold = false;
		cncDataPtr->mmiDataPtr->M30 = true;
		intpDataPtr->intpState = INTP_IDLE;
		break;
	default:
		break;
	}
	return;
}

void intpEnd(INTP_DATA* intpDataPtr)
{
	if(intpDataPtr->resiLength != 0)
	{
		intpDataPtr->slopeData.restCheck = false;
		for(int i=0;i<3;i++)
		{
			intpDataPtr->oldRKPos[i] = intpDataPtr->newRKPos[i];
			intpDataPtr->newRKPos[i] = intpDataPtr->endRKPos[i];
		}
		trafoXYZtoUVW(intpDataPtr);

		for(int i=0;i<3;i++)
		{
			cncDataPtr->linkData.intpToMmiBlock.newRKPos[i] = intpDataPtr->newRKPos[i];
			cncDataPtr->linkData.intpToMmiBlock.newMKPos[i] = intpDataPtr->newMKPos[i];
		}
	}



	for(int i=0; i<3;i++)
	{
		intpDataPtr->oldRKPos[i] = intpDataPtr->newRKPos[i];
		intpDataPtr->startRKPos[i] = intpDataPtr->newRKPos[i];
	}
	for(int i=0;i<3;i++)
	{
		cncDataPtr->linkData.intpToMmiBlock.newRKPos[i] = intpDataPtr->newRKPos[i];
		cncDataPtr->linkData.intpToMmiBlock.newMKPos[i] = intpDataPtr->newMKPos[i];
	}



	intpDataPtr->intpState = INTP_IDLE;
	return;
}
