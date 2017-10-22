#include "stdafx.h"
#include <string.h>
#include "../INC/dec.h"
#include "../../LINK/INC/link.h"
#include "../../CNC/INC/cnc.h"
#include "../../UTIL/INC/util.h"
#include <sys/stat.h>

extern  CNC_DATA* cncDataPtr;


off_t fsize(const char *filename) 
{
	struct stat st; 

	if (stat(filename, &st) == 0)
		return st.st_size;

	return -1; 
}

void decIdle(DEC_DATA* decDataPtr)
{		
	if (cncDataPtr->linkDataPtr->sysToDecBlock.ncFileValid == true && cncDataPtr->linkDataPtr->sysToDecBlock.startHold == true && cncDataPtr->mmiDataPtr->restart == false)
	{
		strcpy(decDataPtr->ncFilePath,cncDataPtr->linkDataPtr->sysToDecBlock.ncFilePath);
		cncDataPtr->linkDataPtr->sysToDecBlock.ncFileValid=false;
		decDataPtr->decState = DEC_OPEN_NC_FILE;
	}
	return;
}//decIdle()

void decOpenNcFile(DEC_DATA* decDataPtr)
{
	decDataPtr->asciiPtr=decDataPtr->fileBuffer;
	decDataPtr->ncFilePtr = fopen(decDataPtr->ncFilePath,"r");

	decDataPtr->fileSize=fsize(decDataPtr->ncFilePath);
	if(decDataPtr->ncFilePtr != NULL)
	{
		char c;
		while ((c = getc(decDataPtr->ncFilePtr)) != EOF)
		{
			*decDataPtr->asciiPtr=c;
			decDataPtr->asciiPtr++;
		}

		decDataPtr->asciiPtr=decDataPtr->fileBuffer;
		decDataPtr->decState = DEC_EXE;
		fclose(decDataPtr->ncFilePtr);

	}
	else if (cncDataPtr->mmiDataPtr->opMode == MDI_MODE)
	{
		strcpy(decDataPtr->fileBuffer, cncDataPtr->linkDataPtr->sysToDecBlock.ncFileCord);
		decDataPtr->asciiPtr=decDataPtr->fileBuffer;
		decDataPtr->decState =DEC_EXE;
	}
	else
	{
		decDataPtr->decState = DEC_ERROR;	
	}
	return; 
}

void decExe(DEC_DATA* decDataPtr)
{
	switch( *decDataPtr->asciiPtr )
	{
	case 'N':
		nFunction(decDataPtr);
		break;
	case 'G':
		gFunction(decDataPtr);
		break;
	case 'F':
		fFunction(decDataPtr);
		break;
	case 'X':
	case 'Y':
	case 'Z':
		xyzFunction(decDataPtr);
		break;
	case 'I':
	case 'J':
	case 'K':
		ijkFunction(decDataPtr);
		break;
	case 'U':
	case 'V':
	case 'W':
		uvwFunction(decDataPtr);
		break;
	case 'M':
		mFunction(decDataPtr);
		break;
	case '\0':
	case '\n':
	case ';':
		decDataPtr->decState = DEC_END_LINE;
		break;
	default:
		decDataPtr->decState= DEC_ERROR;
		break;	
	}
	return ;
	
}

void endOfLine(DEC_DATA* decDataPtr)
{
	FIFO_STATUS fifoStatus;
	fifoStatus = wrDecToIntpFifo(decDataPtr->decToIntpFifoPtr,decDataPtr->decToIntpBlockPtr);
	//確定寫入
	if(fifoStatus == WR_DONE)
	{
		if( *decDataPtr->asciiPtr=='\n' ||  *decDataPtr->asciiPtr==';' ||*decDataPtr->asciiPtr==' ')
		{
			decDataPtr->decState = DEC_EXE;
			decDataPtr->asciiPtr++;

			//避免MDI兩次換行兩次寫入FIFO
			if( *decDataPtr->asciiPtr=='\n' ||  *decDataPtr->asciiPtr==';' ||*decDataPtr->asciiPtr==' ')
			{
				decDataPtr->asciiPtr++;
			}
			
		}
	}
	else if(fifoStatus == FIFO_FULL)
	{
		decDataPtr->decState = DEC_END_LINE;
	}

	decDataPtr->decToIntpBlockPtr->stpEnd = ZERO_STOP;
	for(int i=0; i<3 ; i++)
	{
		decDataPtr->decToIntpBlockPtr->cordValue[i] = 0;
		decDataPtr->decToIntpBlockPtr->cordInput[i] = false;
		decDataPtr->decToIntpBlockPtr->ijkCordValue[i] = 0;
		decDataPtr->decToIntpBlockPtr->ijkInput[i] = false;
	}
	
	return ;
}

void endM30(DEC_DATA *decDataPtr)
{
	if(decDataPtr->ncFilePtr!= NULL)
	fclose(decDataPtr->ncFilePtr);

	decDataPtr->asciiPtr=decDataPtr->fileBuffer;
	decInit(decDataPtr);              

	return;
}

void err(DEC_DATA *decDataPtr)
{

	return ;
}




