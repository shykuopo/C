

#include "StdAfx.h"
#include <string.h>
#include "../INC/mmi.h"
#include "../../CNC/INC/cnc.h"
#include "../../UTIL/INC/util.h"



//extern void delByteSpace (char* bytePtr,int size);

void mmiInit( MMI_DATA *mmiDataPtr,LINK_DATA* linkDataPtr )
{
	
	mmiDataPtr-> FeedOverride = 0;
	mmiDataPtr->counter = 0;

	

	mmiDataPtr->ncFileValid = false;
	mmiDataPtr->startHold = false;
	mmiDataPtr->EmStopHold = false;
	mmiDataPtr->resetHold = false;

	mmiDataPtr->M01Hold = false;
	mmiDataPtr->feedHold = false;
	mmiDataPtr->SBHold = false;

	delByteSpace((char *)mmiDataPtr,sizeof(MMI_DATA));
	mmiDataPtr->linkDataPtr = linkDataPtr ;


	return  ;
}

void mmiCtrl(MMI_DATA* mmiDataPtr)
{
	mmiMain(mmiDataPtr);
	return ;

}//mmiCtrl()

void mmiClose(MMI_DATA* mmiDataPtr)
{
	
	return ;

}//mmiClose()

void mmiReset(MMI_DATA* mmiDataPtr)
{
	
	return ;

}//mmiReset()


