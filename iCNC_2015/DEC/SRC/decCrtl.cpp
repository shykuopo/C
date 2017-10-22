#include "StdAfx.h"
#include <string.h>
#include "../INC/dec.h"
#include"../../LINK/INC/link.h"
#include "..\..\CNC\INC\cnc.h"
#include "../../UTIL/INC/util.h"
#include <sys/stat.h>
extern  CNC_DATA* cncDataPtr;

#include <sys/stat.h>

void decInit(DEC_DATA *decDataPtr)
{
	delByteSpace((char *)decDataPtr,sizeof(DEC_DATA));

	cncDataPtr->linkDataPtr->sysToDecBlock.ncFileValid=false;

	decDataPtr->decToIntpBlockPtr = &decDataPtr->decToIntpBlock;
	decDataPtr->decToIntpFifoPtr = &cncDataPtr->linkDataPtr->decToIntpFifo;

	decDataPtr->decState = DEC_IDLE;
	decDataPtr->decToIntpFifoPtr->head.wrIndex=0;

	decDataPtr->decCtlState = DEC_MAIN;
	return  ; 

}

void decCtrl(DEC_DATA *decDataPtr)
{
	switch(decDataPtr->decCtlState)
	{
	case DEC_INIT:
		decInit(decDataPtr);
		break;
	case DEC_MAIN:
		decMain(decDataPtr);
		break;
	case DEC_DO_RESET:
		decReset(decDataPtr);
		break;
	}
	
	return  ; 
}

void decMain(DEC_DATA *decDataPtr)
{
	switch (decDataPtr->decState)
		 {
		 case DEC_IDLE:         //    wait ncFileValid  == true    initiate DEC
			 decIdle(decDataPtr);
			 break;
		 case DEC_OPEN_NC_FILE:   //     read the file   and preprcessing (clean all space)
			 decOpenNcFile(decDataPtr);
			 break;
		 case DEC_EXE:
			 decExe(decDataPtr);
		   break;
		 case DEC_END_LINE:                     //  finish one line back to state = NC_LINE_LOOP or END_M30
 		   endOfLine(decDataPtr);
		   break;
		 case DEC_END_M30:
		   endM30(decDataPtr); // ¶¶«K²MªÅ DEC_DATA
		   break;
		 case DEC_ERROR:
		   err(decDataPtr);
		   break;

		 }  //switch()

	if(decDataPtr->decReset == true)
		decDataPtr->decCtlState = DEC_DO_RESET;


	
	return  ; 
}

void decReset(DEC_DATA* decDataPtr)
{
	delByteSpace((char *)decDataPtr,sizeof(DEC_DATA));

	decDataPtr->decToIntpBlockPtr = &decDataPtr->decToIntpBlock;
	delByteSpace((char *)decDataPtr->decToIntpBlockPtr,sizeof(DEC_TO_INTP_Block));
	cncDataPtr->linkDataPtr->sysToDecBlockPtr = &cncDataPtr->linkDataPtr->sysToDecBlock;
	delByteSpace((char *)cncDataPtr->linkDataPtr->sysToDecBlockPtr,sizeof(SYS_TO_DEC_Block));


	decDataPtr->decState = DEC_IDLE;

	decDataPtr->decReset = false;

	return;
}

void decClose(DEC_DATA *decDataPtr)
{
	return  ; 
}

