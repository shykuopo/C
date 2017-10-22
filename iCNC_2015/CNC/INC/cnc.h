#ifndef  CNC_H
#define  CNC_H
#include <stdio.h>
#include <string.h>
#include <vcclr.h>

#include"../../SYS/INC/sys.h"
#include"../../INTP/INC/intp.h"
#include"../../LINK/INC/link.h"
#include"../../MMI/INC/mmi.h"
#include"../../DEC/INC/dec.h"
#include"../../FIFO/INC/fifo.h"




typedef struct
{

	DEC_DATA    decData;
	INTP_DATA   intpData;
	MMI_DATA    mmiData;
	SYS_DATA    sysData;
	LINK_DATA   linkData;


	DEC_DATA  *decDataPtr;
	INTP_DATA *intpDataPtr;
	MMI_DATA  *mmiDataPtr;
	SYS_DATA  *sysDataPtr;
	LINK_DATA *linkDataPtr;



	

}CNC_DATA;


void cncNrtCtrl(CNC_DATA* cncDataPtr);
void cncRtCtrl(CNC_DATA* cncDataPtr);
void cncInit(CNC_DATA* cncDataPtr);
void cncReset(CNC_DATA *cncDataPtr);
void cncClose(CNC_DATA *cncDataPtr);

#endif