#ifndef MMI_H
#define MMI_H
#include <stdio.h>
#include<string.h>
#include"../../LINK/INC/link.h"





struct MMI_DATA
{

	OP_MODE opMode;             
	WHEEL_FEED wheelFeed;
	TEACH_BUTTON teachButton;
	RESET_MODE resetMode;
	MMI_TO_DEC_Block mmiToDecBlock;
	MMI_TO_SYS_Block mmiToSysBlock;
	SYS_TO_MMI_Block sysToMmiBlock;
	LINK_DATA *linkDataPtr;


	


	bool ncFileValid;
	char ncFilePath[200];
	char ncFileCord[200];
	bool startHold;
	bool startValid;
	bool resetHold;
	bool resetValid;
	bool restart;
	bool teachStart;
	bool teachStartValid;
	bool record;
	bool recordValid;
	bool teachEnd;
	bool teachEndValid;
	bool EmStopHold;
	bool EmStopHoldValid;
	bool M01Hold;
	bool M30;
	bool feedHold;
	bool SBHold;
	bool UVWtoXYZ;
	bool X1Valid;
	bool X10Valid;
	bool X100Valid;

	int axisButton[3];		
	bool axisButtonValid[3];
	int xyzSetValue[3];
	bool xyzSetValueValid[3];
	int axisSetValue[3];
	bool axisSetValueValid[3];
	int buttons[8];
	int FeedOverride;		
	int counter;			
	int wheelRatio;
	


	


};//MMI_DATA

void mmiInit(MMI_DATA* mmiDataPtr ,LINK_DATA* linkDataPtr);
void mmiCtrl(MMI_DATA* mmiDataPtr);
void mmiClose(MMI_DATA* mmiDataPtr);
void mmiReset(MMI_DATA* mmiDataPtr);

void mmiMain(MMI_DATA* mmiDataPtr);
void mmiInputUpdate(MMI_DATA* mmiDataPtr);
void mmiOutputUpdate(MMI_DATA* mmiDataPtr);
#endif