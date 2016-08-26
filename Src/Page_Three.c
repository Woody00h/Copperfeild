/*
 * Page_Three.c
 *
 *  Created on: Aug 25, 2016
 *      Author: wchen
 */

#include "GUI.h"
#include "Font.h"

extern GUI_BITMAP bmBrightnessIconBlack;

#define FRAME_BUF_BASE 0XD0000000
void My_BMP_Draw(GUI_BITMAP * bmp , unsigned short x, unsigned short y)
{
	unsigned short * bufindex = (unsigned short *)(FRAME_BUF_BASE + y*320*2 + x*2);
	unsigned short * buf;
	unsigned short *bmpdata = (unsigned short *)(bmp->pData);
	unsigned short line,col;

	if(bmp)
	{
		for(line = 0; line < bmp->YSize; line++)
		{
			buf = bufindex;
			for(col = 0; col < bmp->XSize; col++)
			{
				*buf = *bmpdata;
				buf++;
				bmpdata++;
			}
			bufindex += 320;
		}
	}
}
void Page_Three_Init()
{
	int x0 = 118,x1=128,i;
	GUI_RECT myRect = {0,364,319,383};

	//clear window
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();

	//The sun picture
	GUI_DrawBitmap(&bmBrightnessIconBlack, 15,36);

	//lightness probar
	GUI_SetColor(GUI_YELLOW);
	for(i=0;i<7;i++)
	{
		GUI_FillRect(x0, 332, x1, 342);
		x0 += 13;
		x1 += 13;
	}

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
