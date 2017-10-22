#include "StdAfx.h"
#include <string.h>
#include "../INC/dec.h"
#include "..\..\CNC\INC\cnc.h"
#include "../../UTIL/INC/util.h"
#include "../../FIFO/INC/fifo.h"
extern  CNC_DATA* cncDataPtr;

void nFunction(DEC_DATA* decDataPtr)
{
	decDataPtr->asciiPtr++;  // N123
	decDataPtr->nInput=true;
	decDataPtr->blockNumber = atoi(decDataPtr->asciiPtr);  //DECODING
	// STRING"123"converts to float 123
	// pass digit
	decDataPtr->decToIntpBlockPtr->blockNumber = decDataPtr->blockNumber;
	passDigit(decDataPtr);
	passSpace(decDataPtr);
	return;
}
void gFunction(DEC_DATA* decDataPtr)
{
	int i;
	decDataPtr->asciiPtr++;  
	i = atoi(decDataPtr->asciiPtr); 
	switch(i)
	{
	case 0:  // rapid motion
		decDataPtr->decToIntpBlockPtr->motType = RAPID_CMD;
		break;
	case 01:  //linear motion
		decDataPtr->decToIntpBlockPtr->motType = LINEAR_CMD; 
		break;
	case 02:  //CW circular motion
		decDataPtr->decToIntpBlockPtr->motType = CIR_CW_CMD; 
		break;
	case 03:  //CCW circular motion
		decDataPtr->decToIntpBlockPtr->motType = CIR_CCW_CMD;
		break;
	case 04:  //dwell time
		decDataPtr->decToIntpBlockPtr->motType = DWELL_TIME_CMD;
		break;
	case 91: //relative motion
		decDataPtr->decToIntpBlockPtr->relMotion = true;
		break;
	case 90: //absolute coordinate
		decDataPtr->decToIntpBlockPtr->relMotion = false;
		break;
	}
	passDigit(decDataPtr);
	passSpace(decDataPtr);
	decDataPtr->decToIntpBlockPtr->stpEnd = ZERO_STOP;
	return ;

}
void mFunction(DEC_DATA* decDataPtr)
{
	int   i;

	decDataPtr->asciiPtr++;  // N123
	i = atoi(decDataPtr->asciiPtr);  //DECODING      M00 M01 M30
	switch(i)
	{
	case 0:
		decDataPtr->decToIntpBlockPtr->stpEnd = M00_STOP;
		break;
	case 01:
		decDataPtr->decToIntpBlockPtr->stpEnd = M01_STOP;
		break;
	case 30:
		decDataPtr->decToIntpBlockPtr->stpEnd = M30_END;
		break;
	}
	passDigit(decDataPtr);
	passSpace(decDataPtr);
	decDataPtr->decToIntpBlockPtr->motType = ZERO_TYPE;

	return ;
}
void fFunction(DEC_DATA*    decDataPtr)
{
	decDataPtr->asciiPtr++;  
	decDataPtr->decToIntpBlockPtr->feed = atof(decDataPtr->asciiPtr);
	decDataPtr->decToIntpBlockPtr->feedVaild = true;

	passFloat(decDataPtr);
	passSpace(decDataPtr);
	return;
}  //fFunction()
void xyzFunction(DEC_DATA* decDataPtr)
{
	if (*decDataPtr->asciiPtr == 'X' || *decDataPtr->asciiPtr == 'x')  // example X12.345Y-10.2
	{	
		decDataPtr->asciiPtr++;  // 12.345Y-10.2
		decDataPtr->decToIntpBlockPtr->cordInput[0] = true; // Coordinate Input Check Bool
		decDataPtr->decToIntpBlockPtr->inputMod = XYZ_INPUT; // XYZ Input-Mode
		decDataPtr->decToIntpBlockPtr->cordValue[0] = atof(decDataPtr->asciiPtr);  //DECODING
	}
	if (*decDataPtr->asciiPtr == 'Y' || *decDataPtr->asciiPtr == 'y')  // example X12.345Y-10.2
	{	
		decDataPtr->asciiPtr++;  
		decDataPtr->decToIntpBlockPtr->cordInput[1] = true;
		decDataPtr->decToIntpBlockPtr->inputMod = XYZ_INPUT; // XYZ Input-Mode
		decDataPtr->decToIntpBlockPtr->cordValue[1] = atof(decDataPtr->asciiPtr);  
	}
	if (*decDataPtr->asciiPtr == 'Z' || *decDataPtr->asciiPtr == 'z')  // example X12.345Y-10.2
	{	
		decDataPtr->asciiPtr++; 
		decDataPtr->decToIntpBlockPtr->cordInput[2] = true;
		decDataPtr->decToIntpBlockPtr->inputMod = XYZ_INPUT; // XYZ Input-Mode
		decDataPtr->decToIntpBlockPtr->cordValue[2] = atof(decDataPtr->asciiPtr);  
	}

	passFloat(decDataPtr);
	passSpace(decDataPtr);
	return ;
}
void uvwFunction(DEC_DATA* decDataPtr)
{
	if ((*decDataPtr->asciiPtr == 'U')||(*decDataPtr->asciiPtr == 'u') )  // example X12.345Y-10.2
	{	
		decDataPtr->asciiPtr++;  // 12.345Y-10.2
		decDataPtr->decToIntpBlockPtr->cordInput[0] = true; // Coordinate Input Check Bool
		decDataPtr->decToIntpBlockPtr->inputMod = UVW_INPUT; // UVW Input-Mode
		decDataPtr->decToIntpBlockPtr->cordValue[0] = atof(decDataPtr->asciiPtr);  //DECODING
	}
	if ((*decDataPtr->asciiPtr == 'V')||(*decDataPtr->asciiPtr == 'v'))  // example X12.345Y-10.2
	{	
		decDataPtr->asciiPtr++;  
		decDataPtr->decToIntpBlockPtr->cordInput[1] = true;
		decDataPtr->decToIntpBlockPtr->inputMod = UVW_INPUT; // UVW Input-Mode
		decDataPtr->decToIntpBlockPtr->cordValue[1] = atof(decDataPtr->asciiPtr); 

	}
	if ((*decDataPtr->asciiPtr == 'W')||(*decDataPtr->asciiPtr == 'w'))  // example X12.345Y-10.2
	{	
		decDataPtr->asciiPtr++;  
		decDataPtr->decToIntpBlockPtr->cordInput[2] = true;
		decDataPtr->decToIntpBlockPtr->inputMod = UVW_INPUT; // UVW Input-Mode
		decDataPtr->decToIntpBlockPtr->cordValue[2] = atof(decDataPtr->asciiPtr);  
	}


	passFloat(decDataPtr);
    passSpace(decDataPtr);
	return ;
}
void ijkFunction(DEC_DATA* decDataPtr)
{
	if ((*decDataPtr->asciiPtr == 'I')||(*decDataPtr->asciiPtr == 'i') )  // example X12.345Y-10.2
	{	
		decDataPtr->asciiPtr++;  // 12.345Y-10.2
		decDataPtr->decToIntpBlockPtr->ijkInput[0] = true;
		decDataPtr->decToIntpBlockPtr->ijkCordValue[0] = atof(decDataPtr->asciiPtr);  //DECODING
	}
	if ((*decDataPtr->asciiPtr == 'J')||(*decDataPtr->asciiPtr == 'j'))  // example X12.345Y-10.2
	{	
		decDataPtr->decToIntpBlockPtr->ijkInput[1] = true;
		decDataPtr->asciiPtr++;  
		decDataPtr->decToIntpBlockPtr->ijkCordValue[1] = atof(decDataPtr->asciiPtr);  
	}
	if ((*decDataPtr->asciiPtr == 'K')||(*decDataPtr->asciiPtr == 'k'))  // example X12.345Y-10.2
	{	
		decDataPtr->decToIntpBlockPtr->ijkInput[2] = true;
		decDataPtr->asciiPtr++;  
		decDataPtr->decToIntpBlockPtr->ijkCordValue[2] = atof(decDataPtr->asciiPtr);  
	}

	passFloat(decDataPtr);
	passSpace(decDataPtr);
	return ;
}





