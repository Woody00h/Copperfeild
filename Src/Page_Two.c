/*
 * Page_Two.c
 *
 *  Created on: Aug 24, 2016
 *      Author: wchen
 */
#include "GUI.h"
#include "DIALOG.h"
#include "Font.h"
#include "Page.h"

extern unsigned char New_PM_Data;
WM_HWIN hWin;

void Page_Two_Init()
{
	hWin = CreateWindow();
	GUI_Exec();
}

void Handle_Page_Two()
{
	unsigned char page_change = 0,i;
	WM_HWIN      hbar;
	WM_HWIN      htext;
	if(New_PM_Data)
	{
		New_PM_Data = 0;
		if(Old_Hepa_Life != Hepa_Life)
		{
			Old_Hepa_Life = Hepa_Life;

			//progress bar
			hbar = WM_GetDialogItem(hWin, ID_PROGBAR_0);
			htext = WM_GetDialogItem(hWin, ID_TEXT_8);

			Value2String(Hepa_Life,PM2_5_String);
			for(i=0;;i++)
			{
				if(PM2_5_String[i] == '\0')
				{
					PM2_5_String[i] = '%';
					PM2_5_String[i+1] = '\0';
					break;
				}
			}
			TEXT_SetText(htext, PM2_5_String);

			PROGBAR_SetValue(hbar,100-Hepa_Life);

			if(Hepa_Life>60)
			{
				PROGBAR_SetBarColor(hbar,1,GUI_GREEN);
				TEXT_SetTextColor(htext,GUI_GREEN);
			}
			else if(Hepa_Life>30)
			{
				PROGBAR_SetBarColor(hbar,1,GUI_YELLOW);
				TEXT_SetTextColor(htext,GUI_YELLOW);
			}
			else
			{
				PROGBAR_SetBarColor(hbar,1,GUI_RED);
				TEXT_SetTextColor(htext,GUI_RED);
			}

			page_change = 1;
		}

		if(Old_Carbon_Life != Carbon_Life)
		{
			Old_Carbon_Life = Carbon_Life;
			hbar = WM_GetDialogItem(hWin, ID_PROGBAR_1);
			htext = WM_GetDialogItem(hWin, ID_TEXT_9);

			Value2String(Carbon_Life,PM2_5_String);
			for(i=0;;i++)
			{
				if(PM2_5_String[i] == '\0')
				{
					PM2_5_String[i] = '%';
					PM2_5_String[i+1] = '\0';
					break;
				}
			}
			TEXT_SetText(htext, PM2_5_String);

			PROGBAR_SetValue(hbar,100-Carbon_Life);

			if(Carbon_Life>60)
			{
				PROGBAR_SetBarColor(hbar,1,GUI_GREEN);
				TEXT_SetTextColor(htext,GUI_GREEN);
			}
			else if(Carbon_Life>30)
			{
				PROGBAR_SetBarColor(hbar,1,GUI_YELLOW);
				TEXT_SetTextColor(htext,GUI_YELLOW);
			}
			else
			{
				PROGBAR_SetBarColor(hbar,1,GUI_RED);
				TEXT_SetTextColor(htext,GUI_RED);
			}

			page_change = 1;
		}

		if(page_change)
		GUI_Exec();
	}
}
