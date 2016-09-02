/*
 * Page_Three.c
 *
 *  Created on: Aug 25, 2016
 *      Author: wchen
 */

#include "GUI.h"
#include "Font.h"

extern GUI_BITMAP bmBrightnessIconBlack;
unsigned char Bright_Level;
const unsigned short Bright_Duty[] = {100,200,300,400,500,600,700};
void Bright_Bar_Update()
{
	int x0 = 118,x1=128,i;

	//brightness probar
	for(i=0;i<7;i++)
	{
		if(Bright_Level >= i)
			GUI_SetColor(GUI_YELLOW);
		else
			GUI_SetColor(GUI_GRAY);
		GUI_FillRect(x0, 332, x1, 342);
		x0 += 13;
		x1 += 13;
	}
}
void Page_Three_Init()
{
	GUI_RECT myRect = {0,364,319,383};

	//clear window
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();

	//The sun picture
	GUI_DrawBitmap(&bmBrightnessIconBlack, 15,36);

	Bright_Bar_Update();

	//"BRIGHTNESS"
	GUI_SetFont(&GUI_FontCalibri_19_Bold);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringInRect("BRIGHTNESS", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);

	//page index
	GUI_SetColor(GUI_WHITE);
	GUI_DrawCircle(141,463,6);
	GUI_DrawCircle(164,463,6);
	GUI_FillCircle(187,463,6);
}

void Handle_Page_Three()
{
	if(Tune_Key_Flag && Tune_Key_Toggle)
	{
		Tune_Key_Toggle = 0;

		Bright_Level ++;
		if(Bright_Level > 6)
			Bright_Level = 0;

		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, Bright_Duty[Bright_Level]);

		Bright_Bar_Update();
	}
}
