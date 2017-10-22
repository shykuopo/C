#include "StdAfx.h"
#include"../../LINK/INC/link.h"

void linkInit(LINK_DATA *linkDataPtr)
{

	return  ; 

}


/*if (richTextBox_mdiNcFile->Text->Length < 100)
{
	for (int i=0; i<200; i++)
		mmiPtr->mmiToSysBlock.mdiInput[i] = ' ';

	//將string轉成char
	pin_ptr<const wchar_t> wch = PtrToStringChars(richTextBox_mdiNcFile->Text);
	//wch 存 char陣列之richTextBox_mdiNcFile->Text
	size_t  sizeInBytes = ((richTextBox_mdiNcFile->Text->Length + 1) * 2);
	size_t convertedChars = 0;

	wcstombs_s(&convertedChars, mmiPtr->mmiToSysBlock.mdiInput, sizeInBytes, wch, sizeInBytes);

	if(sysPtr->mdiState == 1)
	{
		mmiPtr->mmiToSysBlock.mdiInput->mdiBlockValid = TRUE;
	}
}
*/