/*
 * Page_Two.c
 *
 *  Created on: Aug 24, 2016
 *      Author: wchen
 */
#include "GUI.h"
#include "DIALOG.h"
#include "Font.h"


extern GUI_BITMAP bmProducts_Standard_Filter;

void Page_Two_Init()
{
	GUI_RECT myRect = {0,17,319,30};
	PROGBAR_Handle Hepa_ProgBar;

	//clear window
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();

	//"FILTER CONFIGURATION"
	GUI_SetFont(&GUI_FontCalibri_13_Bold);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringInRect("FILTER CONFIGURATION", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);

	GUI_DrawBitmap(&bmProducts_Standard_Filter,33,46);

	Hepa_ProgBar = PROGBAR_CreateEx(120,268,128,14,0,WM_CF_SHOW,PROGBAR_CF_HORIZONTAL,0);
}

