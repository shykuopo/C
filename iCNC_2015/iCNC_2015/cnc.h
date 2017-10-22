
#ifndef  CNC_H
#define  CNC_H
#include <stdio.h>

#include"../../SYS/INC/sys.h"
#include"../../INTP/INC/intp.h"
#include"../../LINK/INC/link.h"
#include"../../MMI/INC/mmi.h"
#include"../../DEC/INC/dec.h"
typedef struct
{
	DEC_DATA* decDataPtr;
	INTP_DATA* intpDataPtr;
	MMI_DATA* mmiDataPtr;
	SYS_DATA* sysDataPtr;
	LINK_DATA* linkDataPtr;

	DEC_DATA    decData;
	INTP_DATA   intpData;
	MMI_DATA    mmiData;
	SYS_DATA    sysData;
	LINK_DATA   linkData;

}CNC_DATA;