#include "stdafx.h"
#include "../INC/sys.h"

void sysMain(SYS_DATA* sysDataPtr)
{
	sysInputUpdate(sysDataPtr);
	sysOutputUpdate(sysDataPtr);
return;
}

void sysOutputUpdate(SYS_DATA* sysDataPtr)
{
	if(sysDataPtr->ncFileValid==true)
	{
	    strcpy(sysDataPtr->linkDataPtr->sysToDecBlock.ncFilePath, sysDataPtr->ncFilePath);
	    sysDataPtr->linkDataPtr->sysToDecBlock.ncFileValid = true;
	    sysDataPtr->ncFileValid=false;

	}
	sysDataPtr->linkDataPtr->sysToDecBlock.startHold = sysDataPtr->startHold;
	
	
	return;
}

void sysInputUpdate(SYS_DATA* sysDataPtr)
{
	if(sysDataPtr->linkDataPtr->mmiToSysDataValid == true)
	{
		sysDataPtr -> mmiToSysBlock = sysDataPtr->linkDataPtr->mmiToSysBlock ;
		strcpy(sysDataPtr -> ncFilePath , sysDataPtr->mmiToSysBlock.ncFilePath) ;

		sysDataPtr -> linkDataPtr ->mmiToSysDataValid = false ;
	}
	
	if (sysDataPtr->mmiToSysBlock.ncFileValid == true)
	{
		
		sysDataPtr->ncFileValid=true;
    	sysDataPtr->mmiToSysBlock.ncFileValid = false;
	}

	sysDataPtr->startHold = sysDataPtr->mmiToSysBlock.startHold;
	

	return;
}

