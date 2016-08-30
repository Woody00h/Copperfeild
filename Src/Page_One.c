/*
 * Page_One.c
 *
 *  Created on: Aug 23, 2016
 *      Author: wchen
 */
#include "GUI.h"
#include "Font.h"
#include "ParticleSensor.h"

unsigned short Old_In_PM2_5_Value;
unsigned short Old_Out_PM2_5_Value;
unsigned char PM2_5_String[5];
static const unsigned char len[]={6,10,12,14,16,16};

extern unsigned char New_PM_Data;
void Value2String(unsigned int value, unsigned char * str);

void Page_One_Init()
{
	unsigned short index;
	signed short x;
	unsigned char i;
	GUI_RECT myRect = {0,12,319,30};

	//clear the window
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();

	//display "AIR PARTICLES OUT"
	GUI_SetFont(&GUI_FontCalibri_19_Bold);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringInRect("AIR PARTILCES OUT", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);

	//out pm2.5 value
	Old_In_PM2_5_Value = Sensor3.data_pm2_5;
	GUI_SetFont(&GUI_FontCalibri_99);
	GUI_SetColor(GUI_BLUE);
	Value2String(Sensor3.data_pm2_5,PM2_5_String);
	myRect.x0 = 0;
	myRect.y0 = 48;
	myRect.x1 = 319;
	myRect.y1 = 147;
	GUI_DispStringInRect(PM2_5_String, &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);

	//clean
	GUI_FillRect(121,165,200,193);
	myRect.x0 = 121;
	myRect.y0 = 165;
	myRect.x1 = 200;
	myRect.y1 = 193;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	GUI_SetFont(&GUI_FontCalibri_15_Bold);
	GUI_SetColor(GUI_BLACK);
	GUI_DispStringInRect("CLEAN", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
	GUI_SetTextMode(GUI_TEXTMODE_NORMAL);

	//"AIR PARTICLES IN"
	GUI_SetFont(&GUI_FontCalibri_19_Bold);
	GUI_SetColor(GUI_WHITE);
	myRect.x0 = 0;
	myRect.y0 = 214;
	myRect.x1 = 319;
	myRect.y1 = 232;
	GUI_DispStringInRect("AIR PARTILCES IN", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);

	//IN pm2.5 value
	//Old_Out_PM2_5_Value = OutSensor.data_pm2_5;
	GUI_SetFont(&GUI_FontCalibri_73);
	GUI_SetColor(GUI_ORANGE);
	Value2String(145,PM2_5_String);
	myRect.x0 = 0;
	myRect.y0 = 249;
	myRect.x1 = 319;
	myRect.y1 = 249+73;
	GUI_DispStringInRect(PM2_5_String, &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);

	//MODERATE
	GUI_FillRect(86,339,233,367);
	myRect.x0 = 86;
	myRect.y0 = 339;
	myRect.x1 = 233;
	myRect.y1 = 367;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	GUI_SetFont(&GUI_FontCalibri_15_Bold);
	GUI_SetColor(GUI_BLACK);
	GUI_DispStringInRect("MODERATE", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
	GUI_SetTextMode(GUI_TEXTMODE_NORMAL);

	//line
	GUI_SetColor(GUI_WHITE);
	GUI_DrawVLine(163,385,444);

	//"VOC LEVEL"
	GUI_SetFont(&GUI_FontCalibri_15_Bold);
	GUI_SetColor(GUI_WHITE);
	GUI_GotoXY(32,391);
	GUI_DispString("VOC LEVEL");
	GUI_GotoXY(19,417);
	GUI_DispChar('L');
	GUI_GotoXY(130,417);
	GUI_DispChar('H');

	GUI_SetColor(GUI_GREEN);
	x = 35;
	for(i=0;i<6;i++)
	{
		GUI_DrawVLine(x,424-(len[i]>>1),423+(len[i]>>1));
		x++;
	}
	GUI_FillRect(41,415,47,432);

	index = 50;
	GUI_SetColor(GUI_GREEN);
	GUI_FillRect(index,415,index+12,432);

	index += 15;
	GUI_SetColor(GUI_YELLOW);
	GUI_FillRect(index,415,index+12,432);

	index += 15;
	GUI_SetColor(GUI_YELLOW);
	GUI_FillRect(index,415,index+12,432);

	index += 15;
	GUI_SetColor(GUI_RED);
	GUI_FillRect(index,415,index+12,432);

	GUI_FillRect(110,415,119,432);
	x = 125;
	for(i=0;i<6;i++)
	{
		GUI_DrawVLine(x,424-(len[i]>>1),423+(len[i]>>1));
		x--;
	}

	//HEPA CARBON Life
	GUI_SetColor(GUI_WHITE);
	myRect.x0 = 170;
	myRect.y0 = 416;
	myRect.x1 = 260;
	myRect.y1 = 430;
	GUI_DispStringInRect("CARBON", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
	myRect.x0 = 170;
	myRect.y0 = 392;
	myRect.x1 = 260;
	myRect.y1 = 406;
	GUI_DispStringInRect("HEPA", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);

	GUI_GotoXY(268,392);
	GUI_SetColor(GUI_GREEN);
	GUI_DispString("75%"); //HEPA LIFE
	GUI_GotoXY(268,416);
	GUI_SetColor(GUI_YELLOW);
	GUI_DispString("25%"); //CARBON LIFE

	//circle
	GUI_SetColor(GUI_WHITE);
	GUI_DrawCircle(164,463,6);
	GUI_DrawCircle(187,463,6);
	GUI_FillCircle(141,463,6);

	//"PM2.5"
	GUI_SetFont(&GUI_FontCalibri_11_Bold);
	GUI_GotoXY(251,89);
	GUI_DispString("PM");
	GUI_GotoXY(251,282);
	GUI_DispString("PM");
	GUI_SetFont(&GUI_FontCalibri_9_Bold);
	GUI_GotoXY(277,287);
	GUI_DispString("2.5");
	GUI_GotoXY(277,94);
	GUI_DispString("2.5");
}

void Handle_Page_One()
{
	GUI_RECT myRect;

	if(New_PM_Data)
	{
		New_PM_Data = 0;
		GUI_SetFont(&GUI_FontCalibri_73);

		//differnt color according to the PM Data
		if(Sensor3.data_pm2_5 < 50)
			GUI_SetColor(GUI_BLUE);
		else if(Sensor3.data_pm2_5 < 100)
			GUI_SetColor(GUI_ORANGE);
		else
			GUI_SetColor(GUI_RED);

		Value2String(Sensor3.data_pm2_5,PM2_5_String);
		myRect.x0 = 0;
		myRect.y0 = 249;
		myRect.x1 = 319;
		myRect.y1 = 249+73;
		GUI_ClearRect(60, 249, 245, 249+73);
		GUI_DispStringInRect(PM2_5_String, &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
	}
}
void Value2String(unsigned int value, unsigned char * str)
{
	unsigned char temp;

	if(value > 999)
		value = 999;

	temp = value/100;
	if(temp)
	{
		str[0] = temp + '0'; //百位

		value = value%100;
		temp = value/10;
		str[1] = temp + '0'; //十位

		value = value%10;
		str[2] = value + '0'; //个位

		str[3] = '\0'; //end
	}
	else
	{
		temp = value/10;
		if(temp)
		{
			str[0] = temp + '0'; //十位

			value = value%10;
			str[1] = value + '0'; //个位

			str[2] = '\0'; //end
		}
		else
		{
			str[0] = value + '0'; //个位

			str[1] = '\0'; //end
		}
	}
}
