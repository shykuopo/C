#ifndef DEC_H
#define DEC_H
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <conio.h>
#include"../../LINK/INC/link.h"


struct DEC_DATA
{
	LINK_DATA *linkDataPtr;
	DEC_STATE	decState;
	DECODER_CTL_STATE   decCtlState;


	bool decReset;
	bool decRestart;
	char ncFilePath[200];	//nc file path
	char lineBuffer[100];
	char fileBuffer[20000];        //  to restore the MEM code
	char *asciiPtr;
	FILE *ncFilePtr;
	int fileSize;// in Bytes
	int blockNumber;  // N data, N1233 atoi( )
	bool nInput;

	SYS_TO_DEC_Block sysToDecBlock;
	SYS_TO_DEC_Block *sysToDecBlockPtr;
	DEC_TO_INTP_Block decToIntpBlock;
	DEC_TO_INTP_Block *decToIntpBlockPtr;
	DEC_TO_INTP_FIFO  *decToIntpFifoPtr;

	LINE_CMD lineCmd;
	bool lineCmdValid;

	bool relAbs;	//G91/G90
	double xyzCoordinate[3];
	bool xyzInput[3];
	double uvwCoordinate[3];
	bool uvwInput[3];
	int plane[3];	//G17,G18,G19
	bool planeValid[3];
	bool m00;
	bool m01;

};///DEC_DATA;

void decInit( DEC_DATA* decDataPtr);
void decCtrl(DEC_DATA* decDataPtr);
void decClose(DEC_DATA* decDataPtr);
void decMain(DEC_DATA* decDataPtr);
void decReset(DEC_DATA *decDataPtr);

void decIdle(DEC_DATA* decDataPtr);
void decOpenNcFile(DEC_DATA* decDataPtr);
void decExe(DEC_DATA* decDataPtr);
void decInit(DEC_DATA *decDataPtr);

void nFunction(DEC_DATA*decDataPtr);
void gFunction(DEC_DATA *decDataPtr);
void mFunction(DEC_DATA *decDataPtr);
void fFunction(DEC_DATA *decDataPtr);
void xyzFunction(DEC_DATA *decDataPtr);
void uvwFunction(DEC_DATA *decDataPtr);
void ijkFunction(DEC_DATA *decDataPtr);
void endOfLine(DEC_DATA *decDataPtr);
void endM30(DEC_DATA *decDataPtr);
void err(DEC_DATA *decDataPtr);
void afterEndOfLine(DEC_DATA *decDataPtr);
#endif