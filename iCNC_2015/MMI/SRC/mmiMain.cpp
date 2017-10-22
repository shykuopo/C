#include "StdAfx.h"
#include "../INC/mmi.h"
#include "../../CNC/INC/cnc.h"

extern  CNC_DATA* cncDataPtr;





void mmiOutputUpdata(MMI_DATA *mmiDataPtr)
{
	

	mmiDataPtr->mmiToSysBlock.opMode=mmiDataPtr->opMode;
	mmiDataPtr->mmiToSysBlock.feedHold=mmiDataPtr->feedHold;
	mmiDataPtr->mmiToSysBlock.M01Hold=mmiDataPtr->M01Hold;
	mmiDataPtr->mmiToSysBlock.SBHold=mmiDataPtr->SBHold;
	mmiDataPtr->mmiToSysBlock.FeedOverride=mmiDataPtr->FeedOverride;
	mmiDataPtr->mmiToSysBlock.startHold=mmiDataPtr->startHold;
	strcpy(mmiDataPtr->mmiToSysBlock.ncFilePath,mmiDataPtr->ncFilePath);
	
	//mmiDataPtr->mmiToSysBlock.ncFilePath=mmiDataPtr->ncFilePath;

	/*
	if(mmiDataPtr->startValid == true)
	{
		mmiDataPtr->mmiToSysBlock.startHold = mmiDataPtr->startHold;
		mmiDataPtr->mmiToSysBlock.startValid = true;
		mmiDataPtr->startValid = false;
	}
	*/
	if(mmiDataPtr->ncFileValid== true)
	{
		
		mmiDataPtr->mmiToSysBlock.ncFileValid = mmiDataPtr->ncFileValid;
		mmiDataPtr->mmiToSysBlock.ncFileValid = true;
		//mmiDataPtr->ncFileValid = false;
	}


	if(mmiDataPtr->resetValid == true)
	{
		mmiDataPtr->mmiToSysBlock.resetHold = mmiDataPtr->resetHold;
		mmiDataPtr->mmiToSysBlock.resetValid = true;
		mmiDataPtr->resetValid = false;
	}
	if(mmiDataPtr->teachStartValid == true)
	{
		mmiDataPtr->mmiToSysBlock.teachStart = mmiDataPtr->teachStart;
		mmiDataPtr->mmiToSysBlock.teachStartValid = true;
		mmiDataPtr->teachStartValid = false;
	}
	if(mmiDataPtr->recordValid == true)
	{
		mmiDataPtr->mmiToSysBlock.record = mmiDataPtr->record;
		mmiDataPtr->mmiToSysBlock.recordValid = true;
		mmiDataPtr->recordValid = false;
	}
	if(mmiDataPtr->teachEndValid == true)
	{
		mmiDataPtr->mmiToSysBlock.teachEnd = mmiDataPtr->teachEnd;
		mmiDataPtr->mmiToSysBlock.teachEndValid = true;
		mmiDataPtr->teachEndValid = false;
	}
	if(mmiDataPtr->EmStopHoldValid == true)
	{
		mmiDataPtr->mmiToSysBlock.EmStopHold = mmiDataPtr->EmStopHold;
		mmiDataPtr->mmiToSysBlock.EmStopHoldValid = true;
		mmiDataPtr->EmStopHoldValid = false;
	}

	for(int i=0;i<3;i++)
	{
		if (mmiDataPtr->axisButtonValid[i]==true)
		{
			mmiDataPtr->mmiToSysBlock.axisButton[i]=mmiDataPtr->axisButton[i];
			mmiDataPtr->mmiToSysBlock.axisButtonValid[i]=true;
			mmiDataPtr->axisButtonValid[i]=false;
		}
	}
	
	if(mmiDataPtr->linkDataPtr->mmiToSysDataValid == false)
	{
		mmiDataPtr->linkDataPtr->mmiToSysBlock = mmiDataPtr->mmiToSysBlock;
		mmiDataPtr->linkDataPtr->mmiToSysDataValid = true;
	}
	return;
}

void mmiInputUpdata(MMI_DATA *mmiDataPtr)
{
	int i = 0;
	if (mmiDataPtr->linkDataPtr->mmiToSysDataValid == false)
		return;
	else
	{
		mmiDataPtr->sysToMmiBlock = mmiDataPtr->linkDataPtr->sysToMmiBlock;
		mmiDataPtr->linkDataPtr->sysToMmiDataValid = false;

		for(i=0;i<3;i++)
		{
			if (mmiDataPtr->sysToMmiBlock.xyzSetValueValid[i] == true)
			{
				mmiDataPtr->xyzSetValue[i] = mmiDataPtr->sysToMmiBlock.xyzSetValue[i];
				mmiDataPtr->sysToMmiBlock.xyzSetValueValid[i] = false;
			}
			if (mmiDataPtr->sysToMmiBlock.axisSetValueValid[i] == true)
			{
				mmiDataPtr->axisSetValue[i] = mmiDataPtr->sysToMmiBlock.axisSetValue[i];
				mmiDataPtr->sysToMmiBlock.axisSetValueValid[i] = false;
			}
		}
	}
	return;
} // mmiInputUpdata ()
void mmiMain(MMI_DATA *mmiDataPtr)
{
	mmiOutputUpdata(mmiDataPtr);
	mmiInputUpdata(mmiDataPtr);



	return ;

}//mmiMain()