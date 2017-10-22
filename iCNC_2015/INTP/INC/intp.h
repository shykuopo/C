#ifndef INTP_H
#define INTP_H
#include <stdio.h>
#include<string.h>
#include "../../LINK/INC/link.h"

#define pi 3.14159265359
#define L 75 //晶圓取放機臂長(mm)
#define defaultFeed 20
#define realTimer 20

struct SLOPE_DATA
{
	SLOPE_STATE  state;

	double acceleration;
	int cyclingTime;
	double steadyFeed;
	double vStep;

	double pathLength;
	double accDist;
	double diccDist;
	double steadyDist;
	double stepDist;
	double restLength;

	double restVelocity;
	bool restCheck;
	int accStep;
	int diccStep;
	int steadyStep;

	double velocityNow;
	double totalCount;
	double counter;
};

struct INTP_DATA
{

	bool intpReset;
	bool intpRestart;

	INTP_STATE intpState;
	INTP_CTL_STATE intpCtlState;

	SLOPE_DATA slopeData;
	//  以下主要為XYZ座標的型式
	double startRKPos[3];//起點  
	double endRKPos[3];  //終點
	double newRKPos[3];  //輸出點
	double oldRKPos[3];  //上ㄧ個輸出點
	double increRKPos[3];      //單位向量


	// 儲存對應在UVW上的座標
	double oldMKPos[3];    //上ㄧ個輸出點  (between 0 & 360)
	double newMKPos[3];    //輸出點       (between 0 & 360)
	double OldOp[3];//between -360 & 360
	double NewOP[3];//between -360 & 360

	double increment;    //每次進給的單位量
	double totalLength;  //起點到終點的路徑總長
	double resiLength;
	double sumLength;

	float dwellTiLast;  // real timer is 13ms，

	double cirCenter[3];

	DEC_TO_INTP_Block decToIntpBlock;
	DEC_TO_INTP_Block *decToIntpBlockPtr;

	DEC_TO_INTP_FIFO  decToIntpFifo;
	DEC_TO_INTP_FIFO  *decToIntpFifoPtr;

	LINK_DATA  linkData;
	LINK_DATA*  linkDataPtr;

};

void intpInit(INTP_DATA* intpDataPtr);
void intpCtrl(INTP_DATA* intpDataPtr);
void intpEnd(INTP_DATA* intpDataPtr);

void intpRun(INTP_DATA* intpDataPtr);

void intpMain(INTP_DATA* intpDataPtr);

void intpIdle(INTP_DATA* intpDataPtr);
void intpPre(INTP_DATA* intpDataPtr);
void intpExe(INTP_DATA* intpDataPtr);

/********* INTP_RESET*************/
void intpWaitResetHold(INTP_DATA *intpDataPtr);
void intpDoReset(INTP_DATA *intpDataPtr);
void intpResetReady(INTP_DATA *intpDataPtr);

/********INTP_LINEAR******************/
void intpLinearPre(INTP_DATA* intpDataPtr);   
void intpLinearExe(INTP_DATA* intpDataPtr);

//***********************************//
void intpDwellTi(INTP_DATA* intpDataPtr);
void intpProEnd(INTP_DATA* intpDataPtr);

//**********  XYZ_UVW_TRANSFORM_***********//
void trafoXYZtoUVW(INTP_DATA* intpDataPtr);
void trafoUVWtoXYZ(INTP_DATA* intpDataPtr);
double thetaDegree(double sintheta, double costheta);

//********** SLOPE ***********//
void slopeMain(INTP_DATA *intpDataPtr);
void slopeShort(INTP_DATA *intpDataPtr);

#endif