#include "StdAfx.h"
#include <string.h>
#include "../INC/sys.h"



void sysInit(SYS_DATA *sysDataPtr, LINK_DATA *linkDataPtr)
{
	sysDataPtr->linkDataPtr = linkDataPtr ;
return ; 

}

void sysCtrl(SYS_DATA* sysDataPtr)
{
	sysMain (sysDataPtr) ;
	return ;
}

void sysClose(SYS_DATA* sysDataPtr)
{
	return ;
}

void sysReset(SYS_DATA* sysDataPtr)
{
	return ;
}