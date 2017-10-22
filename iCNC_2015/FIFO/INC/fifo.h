#ifndef UTI_H_
#define UTI_H_
#include "../../LINK/INC/link.h"
#define DEC_TO_INTP_FIFO_LENGTH 10

//******************************************************************
/*struct FIFO_HEAD
{
	int wrIndex;
	int rdIndex;
	int type;
	int sizeInByte;
	int sizeInBlock;
};*/
//******************************************************************

/*struct  DEC_TO_INTP_BLOCK
{
	enum MOTION_TYPE	motType;  // G00(rapid), G01(linear), G02(CW), G03(CCW), G04(dwell)
	enum STOP_END       stpEnd;   //  M00 , M01 , M30
	enum CIR_PLANE      cirPlan;  // G17_XY, G18_XZ, G19_YZ
	enum XYZ_UVW_INPUT  inputMod; // input XYZ or UVW
	bool relMotion;               // G90, G91
	double cordValue[3];          // input coordinate value
	bool   cordInput[3];          // input check bool
	double ijkCordValue[3];       // ijk value for G02 & G03 Mode
	bool   ijkInput[3];           // input check bool
	double feed;                  // feed (mm/s)    
	bool feedVaild;
	int blockNumber;
};*/
//******************************************************************
/*struct DEC_TO_INTP_FIFO
{
	FIFO_HEAD head;
	FIFO_HEAD*            headPtr;
	DEC_TO_INTP_Block block[DEC_TO_INTP_FIFO_LENGTH];
	bool valid[DEC_TO_INTP_FIFO_LENGTH];
};*/

void initFifo(DEC_TO_INTP_FIFO* decToIntpFifo);
FIFO_STATUS wrDecToIntpFifo(DEC_TO_INTP_FIFO* decToIntpFifoPtr , DEC_TO_INTP_Block* decToIntpBlockPtr);
FIFO_STATUS rdDecToIntpFifo(DEC_TO_INTP_FIFO* decToIntpFifoPtr,DEC_TO_INTP_Block* decToIntpBlockPtr);
FIFO_STATUS testDecToIntpFifo(DEC_TO_INTP_FIFO* decToIntpFifoPtr);

#endif