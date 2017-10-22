#ifndef LINK_CTRL_H
#define LINK_CTRL_H
#include <stdio.h>
#include<string.h>
//#include "../../FIFO/INC/fifo.h"


#define DEC_TO_INTP_FIFO_LENGTH 10
#define OTHER_FIFO_LNG  100

//fifo type
#define DEC_TO_INTP  10
#define OTHER        100

enum MMI_STATE {MMI_RESET,MMI_RUN};

enum SYS_CTRL_STATE {SYS_CTRL_NULL = 0 ,SYS_CTRL_INIT , SYS_CTRL_RUN , SYS_CTRL_RESET};
enum SYS_MAIN_STATE{SYS_MAIN_NULL = 0 , SYS_MAIN_INIT , SYS_MAIN_RUN};

enum DEC_STATE {DEC_IDLE,DEC_OPEN_NC_FILE,DEC_EXE,DEC_WRITE_FIFO,DEC_FIFO_FULL, DEC_END_LINE,DEC_END_M30,DEC_ERROR,DEC_RESET};
enum DECODER_CTL_STATE{	DEC_INIT,DEC_MAIN,DEC_DO_RESET,DEC_RESET_READY};

enum INTP_STATE{INTP_IDLE, INTP_PRE, INTP_EXE, INTP_END, INTP_DWELL_TIME, INTP_PROGRAM_END,INTP_ERR};
enum INTP_CTL_STATE{INTP_INIT,INTP_RUN,INTP_WAIT_RESET_HOLD,INTP_DO_RESET,INTP_RESET_READY};

enum SLOPE_STATE{SLOPE_LONG,SLOPE_SHORT};

enum RESET_MODE{RESET_IDLE,RESET_START};

enum OP_MODE{NULL_MODE=0,MDI_MODE,MEM_MODE,JOG_MODE,WHEEL_MODE,TEACH_MODE,HOME_MODE};

enum LINE_CMD{NULL_CMD=0,G00_CMD,G01_CMD,G02_CMD,G03_CMD,G04_CMD,M30_CMD};
//enum MOT_TYPE{MOT_NULL = 0,RAPID_CMD, LINEAR_CMD, CIR_CW_CMD, CIR_CCW_CMD, DWELL_TIME_CMD};

enum MOTION_TYPE{ZERO_TYPE=0, RAPID_CMD , LINEAR_CMD, CIR_CW_CMD, CIR_CCW_CMD, DWELL_TIME_CMD};
enum CIR_PLANE {ZERO_PLANE=0, XY_PLANE, XZ_PLANE, YZ_PLANE };
enum STOP_END{ZERO_STOP=0, M00_STOP, M01_STOP, M30_END };
enum XYZ_UVW_INPUT{ZERO_INPUT=0, XYZ_INPUT, UVW_INPUT};

enum PLANE {PLANE_NULL, G17_XY, G18_YZ, G19_XZ};

enum FIFO_STATUS{FIFO_OK=0, FIFO_FULL, FIFO_EMPTY, WR_DONE, RD_DONE};

enum WHEEL_FEED{NULL_WHEEL=0,X1,X10,X100};
enum TEACH_BUTTON{NULL_TEACH=0,TEACH_IDLE,TEACH_START,TEACH_END};

typedef struct
{
	OP_MODE opMode;             //Operation Mode
	WHEEL_FEED wheelFeed;
	TEACH_BUTTON teachButton;
	RESET_MODE resetMode;


	bool ncFileValid;
	char ncFilePath[200];
	bool startHold;
	bool startValid;
	bool resetHold;
	bool resetValid;
	bool teachStart;
	bool teachStartValid;
	bool record;
	bool recordValid;
	bool teachEnd;
	bool teachEndValid;
	bool EmStopHold;
	bool EmStopHoldValid;
	bool M01Hold;
	bool feedHold;
	bool SBHold;
	int axisButton[3];		//[0]=X [1]=Y [2]=Z
	bool axisButtonValid[3];
	int xyzSetValue[3];
	bool xyzSetValueValid[3];
	int axisSetValue[3];
	bool axisSetValueValid[3];
	int buttons[8];
	int FeedOverride;		//0~200%
	int counter;			//Timer Counter

}MMI_TO_SYS_Block;
typedef struct 
{
	/*char        ncFilePath[20000];
	bool         ncFileValid;*/
	char          mdiInput[ 200 ];
	bool         mdiInputValid;
}MMI_TO_DEC_Block;

typedef struct
{
	int axisButton[3];		//[0]=X [1]=Y [2]=Z
	bool axisButtonValid[3];
	int xyzSetValue[3];
	bool xyzSetValueValid[3];
	int axisSetValue[3];
	bool axisSetValueValid[3];

}SYS_TO_MMI_Block;
typedef struct
{
	char         ncFilePath[200];
	char         ncFileCord[200];
	bool         ncFileValid;
	bool startHold;
}SYS_TO_DEC_Block;

typedef struct
{
	double newRKPos[3];
	double newMKPos[3];
	double oldMKPos[3];
	double oldRKPos[3];
	int increment[3];
	int outputdevi[3];

	int blockNumber;
}INTP_TO_MMI_Block;
typedef struct
{
	bool intpReset; // true: not yet down , false: finish or no need to reset

	double nowRKPos[3];
	double nowMKPos[3];
}INTP_TO_SYS_Block;

typedef struct
{
	bool mainLoop;
	bool lineLoop;

	DEC_STATE  decState;
	char ncFileName[100];

	FILE  *ncFilePtr;
	char  lineBuffer[100];
	char  *asciiPtr;
	char  *dynBufferPtr;

	int lineNumber;
	bool markLineNumber;

	//	LINE_CMD  lineCmd;
	bool lineCmdValid;
	bool relAbs;

	double xyzCoordinate[3];
	bool xyzInput[3];
	double uvwCoordinate[3];
	bool uvwInput[3];
	double ijkCoordinate[3];
	bool ijkInput[3];

	int plane[3]; //G17 G18 G19
	bool planeValid[3];

	bool m00;
	bool m01;
}DEC_TO_SYS_Block;
typedef struct
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
}DEC_TO_INTP_Block;

typedef struct
{
	char	     fileName[100];
	int		 programNumber;
} PROGRAM_END;
typedef struct
{
	double		 value;		//s
} DWELL_TIME;

typedef union
{
	PROGRAM_END            programEnd;
	DWELL_TIME			  dwellTime;
	// other real-time functions, M-code function
} FUNCTION;

typedef struct
{
	PLANE 	  plane; 	
	double    ijkCoordinate[3];
	bool      ijkInput[3];
} CIRCLE_CE;

typedef union
{
	CIRCLE_CE  	      circleCe;
	// for extension such as spline, NURBS, three-point-circle, ...
} EXTRA;

typedef struct
{

	float			 feedrate;
	bool              relative;
	bool              M00;				 
	bool              M01;				
	bool              G60;				

	double			 xyzCoordinate[3];	 
	bool 	         xyzInput[3];     

	double			 uvwCoordinate[3];	 
	bool 	         uvwInput[3];  

	double			 ijkCoordinate[3];	 
	bool 	         ijkInput[3];

	EXTRA			 extra;				 // extra input for different kind of path  

} MOTION;

typedef union
{
	MOTION	     motion;	//NC motion 
	FUNCTION  function;	//real-time functions
} MOTION_FUNCTION;

typedef struct
{
	int          wrIndex;
	int          rdIndex;
	int          type;
	int          sizeInByte;
	int          sizeInBlock;
}FIFO_HEAD;

typedef struct
{
	int   		        n;

}OTHER_BLOCK;

typedef struct
{
	FIFO_HEAD             head;
	OTHER_BLOCK	          block[OTHER_FIFO_LNG];
	bool                  blockValid[OTHER_FIFO_LNG];
} OTHER_FIFO;

typedef struct
{
	FIFO_HEAD             head;
	FIFO_HEAD*            headPtr;
	DEC_TO_INTP_Block	 block[DEC_TO_INTP_FIFO_LENGTH];
	bool                  valid[DEC_TO_INTP_FIFO_LENGTH];
} DEC_TO_INTP_FIFO;

typedef struct
{
	MMI_TO_SYS_Block          mmiToSysBlock;
	MMI_TO_DEC_Block          mmiToDecBlock;
	SYS_TO_DEC_Block          sysToDecBlock;
	SYS_TO_DEC_Block          *sysToDecBlockPtr;
	INTP_TO_MMI_Block         intpToMmiBlock;
	INTP_TO_SYS_Block         intpToSysBlock;
	SYS_TO_MMI_Block		  sysToMmiBlock;
	DEC_TO_INTP_FIFO		  decToIntpFifo;
	DEC_TO_INTP_FIFO          *decToIntpFifoPtr;
	bool sysToMmiDataValid;
	bool mmiToSysDataValid;
	bool sysToDecDataValid;
}LINK_DATA;

void linkInit(LINK_DATA* linkDataPtr);

#endif