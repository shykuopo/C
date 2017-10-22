#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "..\..\CNC\INC\CNC.h"
#include "../../UTIL/INC/util.h"
#include "../../dec/INC/dec.h"
#include "../../LINK/INC/link.h"

extern  CNC_DATA* cncDataPtr;


void delByteSpace(char* bytePtr,int size)

{
 int i ;

 for (i = 0;i<size ;i++)
 {
	 *bytePtr = 0;
	 bytePtr++;
 
 }

 return;
}

void clear(DEC_DATA *decDataPtr)
{
	char *bufferPtr = decDataPtr->asciiPtr;
	for (int i = 0; i<(decDataPtr->fileSize); i++ )       
	{
		if(*decDataPtr->asciiPtr == ' ' || *decDataPtr->asciiPtr =='\t' || (*decDataPtr->asciiPtr =='\n'&&*(decDataPtr->asciiPtr)=='\n'))
		{
			decDataPtr->asciiPtr++;
		}
		*bufferPtr = *decDataPtr->asciiPtr;
		bufferPtr++;
		decDataPtr->asciiPtr++;
	}
	*bufferPtr = '\0';
	return;

}

void passDigit(DEC_DATA *decDataPtr)
{
	while ((*decDataPtr->asciiPtr>='0')&&(*decDataPtr->asciiPtr<='9'))
	{
		decDataPtr->asciiPtr++;
	}
	return ;
}

char *passFloat(DEC_DATA *decDataPtr)
{

	if ( *decDataPtr->asciiPtr == '+' || *decDataPtr->asciiPtr == '-' )
		decDataPtr->asciiPtr++;

	passDigit(decDataPtr);
	if ( *decDataPtr->asciiPtr == '.')
		decDataPtr->asciiPtr++;
	passDigit(decDataPtr);

		return decDataPtr->asciiPtr;
	

}//passFloat()

void passSpace(DEC_DATA *decDataPtr)
{
	while (*decDataPtr->asciiPtr==' ')
	{
		decDataPtr->asciiPtr++;
	}
	return ;
}