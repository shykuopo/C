#include "stdafx.h"
#include "..\..\CNC\INC\CNC.h"



extern  CNC_DATA* cncDataPtr;


void initFifo(DEC_TO_INTP_FIFO* decToIntpFifo)
{
	decToIntpFifo->head.wrIndex = 0;
	decToIntpFifo->head.rdIndex = 0;

	return ;
} //initFifo

FIFO_STATUS wrDecToIntpFifo(DEC_TO_INTP_FIFO* decToIntpFifoPtr , DEC_TO_INTP_Block* decToIntpBlockPtr)
{
	int wrIndex ;
	wrIndex = decToIntpFifoPtr->head.wrIndex;

	if(decToIntpFifoPtr->valid[wrIndex] == false && wrIndex < DEC_TO_INTP_FIFO_LENGTH)
	{
		decToIntpFifoPtr->block[wrIndex] = *decToIntpBlockPtr;

		bool a = decToIntpFifoPtr->valid;
		double b = decToIntpFifoPtr->block[wrIndex].cordValue[0];
		bool c = decToIntpFifoPtr->block[wrIndex].cordInput[0];
		double d = decToIntpFifoPtr->block[wrIndex].feed;
		decToIntpFifoPtr->valid[wrIndex] = true;
		if(wrIndex == (DEC_TO_INTP_FIFO_LENGTH-1))
		{
			decToIntpFifoPtr->head.wrIndex=0;
		}
		else if(wrIndex < (DEC_TO_INTP_FIFO_LENGTH-1))
		{
			decToIntpFifoPtr->head.wrIndex++;
		}
		return WR_DONE;
	}
	else if(decToIntpFifoPtr->valid[wrIndex] == true)
	{
		return FIFO_FULL;	
	}
}//wrDecToIntpFifo

FIFO_STATUS rdDecToIntpFifo(DEC_TO_INTP_FIFO* decToIntpFifoPtr,DEC_TO_INTP_Block* decToIntpBlockPtr)
{
	int rdIndex;
	rdIndex = decToIntpFifoPtr->head.rdIndex;
	if(decToIntpFifoPtr->valid[rdIndex] == true && rdIndex < DEC_TO_INTP_FIFO_LENGTH)
	{
		*decToIntpBlockPtr = decToIntpFifoPtr->block[rdIndex];
		decToIntpFifoPtr->valid[rdIndex] = false;
		if(rdIndex == (DEC_TO_INTP_FIFO_LENGTH-1))
		{
			decToIntpFifoPtr->head.rdIndex=0;
		}
		else if(rdIndex < (DEC_TO_INTP_FIFO_LENGTH-1))
		{
			decToIntpFifoPtr->head.rdIndex++;
		}
		return RD_DONE;
	}


	else if(decToIntpFifoPtr->valid[rdIndex] == false)
	{
		return FIFO_EMPTY;
	}
	
}//rdDecToIntpFifo

