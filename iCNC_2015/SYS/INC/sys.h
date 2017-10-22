#ifndef SYS_H
#define SYS_H
#include <stdio.h>
#include<string.h>
#include"../../LINK/INC/link.h"



struct SYS_DATA
{
	SYS_CTRL_STATE sysStrlState;
	SYS_MAIN_STATE sysMainState;
	

	double xyzSetValue[3];
	double axisSetVaalue[3];
	bool xyzSetValueValid[3];
	bool axisSetVaalueValid[3];

	bool startHold;

	bool ncFileValid;
	char ncFilePath[200];

	LINK_DATA *linkDataPtr;
	MMI_TO_SYS_Block mmiToSysBlock;
};
void sysInit( SYS_DATA* sysDataPtr, LINK_DATA *linkDataPtr);
void sysCtrl(SYS_DATA* sysDataPtr);
void sysClose(SYS_DATA* sysDataPtr);
void sysReset(SYS_DATA* sysDataPtr);

void sysMain(SYS_DATA* sysDataPtr);
void sysInputUpdate(SYS_DATA* sysDataPtr);
void sysOutputUpdate(SYS_DATA* sysDataPtr);

#endif