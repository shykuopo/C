#include "StdAfx.h"
#include"../../CNC/INC/cnc.h"
#include"../../LINK/INC/link.h"





void cncInit(CNC_DATA *cncDataPtr)
{
	
	//delByteSpace((char *)cncDataPtr,sizeof(CNC_DATA));

	
	cncDataPtr->decDataPtr = &cncDataPtr->decData;
	cncDataPtr->intpDataPtr = &cncDataPtr->intpData;
	cncDataPtr->mmiDataPtr = &cncDataPtr->mmiData;
	cncDataPtr->linkDataPtr = &cncDataPtr->linkData;
	cncDataPtr->sysDataPtr = &cncDataPtr->sysData;

	
	mmiInit(cncDataPtr->mmiDataPtr, cncDataPtr->linkDataPtr);
	sysInit(cncDataPtr->sysDataPtr, cncDataPtr->linkDataPtr);
	decInit(cncDataPtr->decDataPtr);
	linkInit(cncDataPtr->linkDataPtr);
	intpInit(cncDataPtr->intpDataPtr);
	initFifo(cncDataPtr->decData.decToIntpFifoPtr);
	

	return ;

}//cncInit()

void cncNrtCtrl(CNC_DATA *cncDataPtr)
{
	mmiCtrl(cncDataPtr->mmiDataPtr);
	sysCtrl(cncDataPtr->sysDataPtr);	
	decCtrl(cncDataPtr->decDataPtr);
	return ;

}//cncNrtCtl()

void cncRtCtrl(CNC_DATA *cncDataPtr)
{
	intpCtrl(cncDataPtr->intpDataPtr);
	return ;

}//cncRtCtl()

void cncReset(CNC_DATA *cncDataPtr)
{
return ;
}

void cncClose(CNC_DATA *cncDataPtr)
{
	return;
}
