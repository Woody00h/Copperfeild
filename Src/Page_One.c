/*
 * Page_One.c
 *
 *  Created on: Aug 23, 2016
 *      Author: wchen
 */
#include "GUI.h"
#include "Font.h"
#include "ParticleSensor.h"
#include "Page.h"
#include "B2B_Comm.h"

PM_Info In_PM;
PM_Info Out_PM;

unsigned char PM2_5_String[8];
static const unsigned char len[]={6,10,12,14,16,16};

unsigned char Hepa_Life;
unsigned char Carbon_Life;
unsigned char Old_Hepa_Life;
unsigned char Old_Carbon_Life;
unsigned char VOC_Level;
unsigned char Old_VOC_Level;

CHILD_PAGE Child_Page;

PM_LEVEL PM_Level(unsigned short value)
{
	if(value > 100)
		return POOR;
	else if(value > 50)
		return MODERATE;
	else
		return CLEAN;

}

void PM_Out_Level_Update()
{
	GUI_RECT myRect;

	//out pm level
	Out_PM.Old_PM_Level = Out_PM.PM_Level;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	GUI_SetFont(&GUI_FontCalibri_15_Bold);
	myRect.y0 = 165;
	myRect.y1 = 193;
	if(Out_PM.PM_Level == CLEAN)
	{
		myRect.x0 = 121;
		myRect.x1 = 200;
		GUI_FillRect(myRect.x0, myRect.y0, myRect.x1, myRect.y1);

		GUI_SetColor(GUI_BLACK);
		GUI_DispStringInRect("CLEAN", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
	}
	else if(Out_PM.PM_Level == MODERATE)
	{
		myRect.x0 = 86;
		myRect.x1 = 233;
		GUI_FillRect(myRect.x0, myRect.y0, myRect.x1, myRect.y1);

		GUI_SetColor(GUI_BLACK);
		GUI_DispStringInRect("MODERATE", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
	}
	else
	{
		myRect.x0 = 121;
		myRect.x1 = 200;
		GUI_FillRect(myRect.x0, myRect.y0, myRect.x1, myRect.y1);

		GUI_SetColor(GUI_BLACK);
		GUI_DispStringInRect("POOR", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
	}
	GUI_SetTextMode(GUI_TEXTMODE_NORMAL);
}
void PM_Out_Update()
{
	GUI_RECT myRect;

	//out pm2.5 value
	Out_PM.Old_PM_Value = Out_PM.PM_Value;
	Out_PM.PM_Level = PM_Level(Out_PM.PM_Value);

	GUI_SetFont(&GUI_FontCalibri_99);
	Value2String(Out_PM.PM_Value,PM2_5_String);

	if(Out_PM.PM_Level == CLEAN)
		GUI_SetColor(GUI_BLUE);
	else if(Out_PM.PM_Level == MODERATE)
		GUI_SetColor(GUI_ORANGE);
	else
		GUI_SetColor(GUI_RED);
	myRect.x0 = 0;
	myRect.y0 = 48;
	myRect.x1 = 319;
	myRect.y1 = 147;
	GUI_DispStringInRect(PM2_5_String, &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
}
void PM_In_Level_Update()
{
	GUI_RECT myRect;

	//in pm level
	In_PM.Old_PM_Level = In_PM.PM_Level;
	myRect.y0 = 339;
	myRect.y1 = 367;
	GUI_SetTextMode(GUI_TEXTMODE_TRANS);
	GUI_SetFont(&GUI_FontCalibri_15_Bold);
	if(In_PM.PM_Level == CLEAN)
	{
		myRect.x0 = 121;
		myRect.x1 = 200;
		GUI_FillRect(myRect.x0, myRect.y0, myRect.x1, myRect.y1);

		GUI_SetColor(GUI_BLACK);
		GUI_DispStringInRect("CLEAN", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
	}
	else if(In_PM.PM_Level == MODERATE)
	{
		myRect.x0 = 86;
		myRect.x1 = 233;
		GUI_FillRect(myRect.x0, myRect.y0, myRect.x1, myRect.y1);

		GUI_SetColor(GUI_BLACK);
		GUI_DispStringInRect("MODERATE", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
	}
	else
	{
		myRect.x0 = 121;
		myRect.x1 = 200;
		GUI_FillRect(myRect.x0, myRect.y0, myRect.x1, myRect.y1);

		GUI_SetColor(GUI_BLACK);
		GUI_DispStringInRect("POOR", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
	}
	GUI_SetTextMode(GUI_TEXTMODE_NORMAL);
}
void PM_In_Update()
{
	GUI_RECT myRect;
	//IN pm2.5 value
	In_PM.Old_PM_Value = In_PM.PM_Value;
	In_PM.PM_Level = PM_Level(In_PM.PM_Value);

	GUI_SetFont(&GUI_FontCalibri_73);
	Value2String(In_PM.PM_Value,PM2_5_String);

	if(In_PM.PM_Level == CLEAN)
		GUI_SetColor(GUI_BLUE);
	else if(In_PM.PM_Level == MODERATE)
		GUI_SetColor(GUI_ORANGE);
	else
		GUI_SetColor(GUI_RED);

	myRect.x0 = 0;
	myRect.y0 = 249;
	myRect.x1 = 319;
	myRect.y1 = 249+73;
	GUI_DispStringInRect(PM2_5_String, &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
}

void VOC_Level_Update()
{
	unsigned short i, x, index;

	Old_VOC_Level = VOC_Level;

	GUI_SetColor(GUI_GREEN);
	x = 35;
	for(i=0;i<6;i++)
	{
		GUI_DrawVLine(x,424-(len[i]>>1),423+(len[i]>>1));
		x++;
	}
	GUI_FillRect(41,415,47,432);

	index = 50;
	if(VOC_Level > 0)
		GUI_SetColor(GUI_GREEN);
	else
		GUI_SetColor(GUI_GRAY);
	GUI_FillRect(index,415,index+12,432);

	index += 15;
	if(VOC_Level > 1)
		GUI_SetColor(GUI_YELLOW);
	else
		GUI_SetColor(GUI_GRAY);
	GUI_FillRect(index,415,index+12,432);

	index += 15;
	if(VOC_Level > 2)
		GUI_SetColor(GUI_YELLOW);
	else
		GUI_SetColor(GUI_GRAY);
	GUI_FillRect(index,415,index+12,432);

	index += 15;
	if(VOC_Level > 3)
		GUI_SetColor(GUI_RED);
	else
		GUI_SetColor(GUI_GRAY);
	GUI_FillRect(index,415,index+12,432);

	if(VOC_Level > 4)
		GUI_SetColor(GUI_RED);
	else
		GUI_SetColor(GUI_GRAY);
	GUI_FillRect(110,415,119,432);
	x = 125;
	for(i=0;i<6;i++)
	{
		GUI_DrawVLine(x,424-(len[i]>>1),423+(len[i]>>1));
		x--;
	}
}

void Hepa_Life_Update()
{
	unsigned char i;

	Old_Hepa_Life = Hepa_Life;

	if(Hepa_Life>60)
		GUI_SetColor(GUI_GREEN);
	else if(Hepa_Life>30)
		GUI_SetColor(GUI_YELLOW);
	else
		GUI_SetColor(GUI_RED);

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
	GUI_SetFont(&GUI_FontCalibri_15_Bold);
	GUI_GotoXY(268,392);
	GUI_DispString(PM2_5_String); //HEPA LIFE
}

void Carbon_Life_Update()
{
	unsigned char i;
	Old_Carbon_Life = Carbon_Life;

	if(Carbon_Life>60)
		GUI_SetColor(GUI_GREEN);
	else if(Carbon_Life>30)
		GUI_SetColor(GUI_YELLOW);
	else
		GUI_SetColor(GUI_RED);

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

	GUI_SetFont(&GUI_FontCalibri_15_Bold);
	GUI_GotoXY(268,416);
	GUI_DispString(PM2_5_String); //CARBON LIFE
}
void Page_One_Init()
{
	GUI_RECT myRect = {0,12,319,30};

	Child_Page = CHILD_AP2_5;
	//clear the window
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();

	//display "AIR PARTICLES OUT"
	GUI_SetFont(&GUI_FontCalibri_19_Bold);
	GUI_SetColor(GUI_WHITE);
	GUI_DispStringInRect("AIR PARTILCES OUT", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);

	PM_Out_Update();
	PM_Out_Level_Update();

	//"AIR PARTICLES IN"
	GUI_SetFont(&GUI_FontCalibri_19_Bold);
	GUI_SetColor(GUI_WHITE);
	myRect.x0 = 0;
	myRect.y0 = 214;
	myRect.x1 = 319;
	myRect.y1 = 232;
	GUI_DispStringInRect("AIR PARTILCES IN", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);

	PM_In_Update();
	PM_In_Level_Update();

	//line
	GUI_SetColor(GUI_WHITE);
	GUI_DrawVLine(163,385,444);

	//"VOC LEVEL"
	Old_VOC_Level = VOC_Level;
	GUI_SetFont(&GUI_FontCalibri_15_Bold);
	GUI_SetColor(GUI_WHITE);
	GUI_GotoXY(32,391);
	GUI_DispString("VOC LEVEL");
	GUI_GotoXY(19,417);
	GUI_DispChar('L');
	GUI_GotoXY(130,417);
	GUI_DispChar('H');

	VOC_Level_Update();

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

	Hepa_Life_Update();
	Carbon_Life_Update();

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
	GUI_RECT myRect = {0,12,319,30};
	if(tune_key_flag && tune_key_toggle)
	{
		tune_key_toggle = 0;

		GUI_ClearRect(277,287,300,300);
		GUI_ClearRect(277,94,300,107);

		switch (Child_Page)
		{
		case CHILD_AP2_5:
			//change to air particles in pm10
			Child_Page = CHILD_AP10;
			//"PM10"
			GUI_SetFont(&GUI_FontCalibri_9_Bold);
			GUI_SetColor(GUI_WHITE);
			GUI_GotoXY(277,287);
			GUI_DispString("10");
			GUI_GotoXY(277,94);
			GUI_DispString("10");
			break;
		case CHILD_AP10:
			Child_Page = CHILD_AQI2_5;
			//"pm2.5"
			GUI_SetFont(&GUI_FontCalibri_9_Bold);
			GUI_SetColor(GUI_WHITE);
			GUI_GotoXY(277,287);
			GUI_DispString("2.5");

			GUI_GotoXY(277,94);
			GUI_DispString("2.5");

			GUI_ClearRect(0,12,319,30);
			GUI_SetFont(&GUI_FontCalibri_19_Bold);
			GUI_DispStringInRect("AQI OUT", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);

			GUI_ClearRect(0,214,319,232);
			myRect.x0 = 0;
			myRect.y0 = 214;
			myRect.x1 = 319;
			myRect.y1 = 232;
			GUI_DispStringInRect("AQI IN", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
			break;
		case CHILD_AQI2_5:
			Child_Page = CHILD_AQI10;
			//"PM10"
			GUI_SetFont(&GUI_FontCalibri_9_Bold);
			GUI_SetColor(GUI_WHITE);
			GUI_GotoXY(277,287);
			GUI_DispString("10");
			GUI_GotoXY(277,94);
			GUI_DispString("10");
			break;
		case CHILD_AQI10:
			Child_Page = CHILD_AP2_5;
			//"pm2.5"
			GUI_SetFont(&GUI_FontCalibri_9_Bold);
			GUI_SetColor(GUI_WHITE);
			GUI_GotoXY(277,287);
			GUI_DispString("2.5");

			GUI_GotoXY(277,94);
			GUI_DispString("2.5");

			GUI_ClearRect(0,12,319,30);
			GUI_SetFont(&GUI_FontCalibri_19_Bold);
			GUI_DispStringInRect("AIR PARTICLES OUT", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);

			GUI_ClearRect(0,214,319,232);
			myRect.x0 = 0;
			myRect.y0 = 214;
			myRect.x1 = 319;
			myRect.y1 = 232;
			GUI_DispStringInRect("AIR PARTICLES IN", &myRect, GUI_TA_VCENTER | GUI_TA_HCENTER);
			break;
		default:
			break;
		}

		New_PM_Data = 1; //force change
	}

	if(New_PM_Data)
	{
		New_PM_Data = 0;

		switch (Child_Page)
		{
		case CHILD_AP2_5:
			In_PM.PM_Value = Sensor3.data_pm2_5;
			Out_PM.PM_Value = MyM2DComm.PM2_5;
			break;
		case CHILD_AP10:
			In_PM.PM_Value = Sensor3.data_pm10;
			Out_PM.PM_Value = MyM2DComm.PM10;
			break;
		case CHILD_AQI2_5:
			In_PM.PM_Value = MyM2DComm.AQI2_5_In;
			Out_PM.PM_Value = MyM2DComm.AQI2_5_Out;
			break;
		case CHILD_AQI10:
			In_PM.PM_Value = MyM2DComm.AQI10_In;
			Out_PM.PM_Value = MyM2DComm.AQI10_Out;
			break;
		default:
			break;
		}

		if(Out_PM.PM_Value > 99)
			Out_PM.PM_Value = 99;

		if(Out_PM.Old_PM_Value != Out_PM.PM_Value)
		{
			GUI_ClearRect(60, 48, 245, 147);
			PM_Out_Update();
		}

		if(Out_PM.Old_PM_Level != Out_PM.PM_Level)
		{
			GUI_ClearRect(86, 165, 233, 193);
			PM_Out_Level_Update();
		}

		if(In_PM.Old_PM_Value != In_PM.PM_Value)
		{
			GUI_ClearRect(60, 249, 245, 249+73);
			PM_In_Update();
		}

		if(In_PM.Old_PM_Level != In_PM.PM_Level)
		{
			GUI_ClearRect(86, 339, 233, 367);
			PM_In_Level_Update();
		}

		if(Old_VOC_Level != VOC_Level)
		{
			VOC_Level_Update();
		}

		if(Old_Hepa_Life != Hepa_Life)
		{
			GUI_ClearRect(265, 390, 315, 407);
			Hepa_Life_Update();
		}

		if(Old_Carbon_Life != Carbon_Life)
		{
			GUI_ClearRect(265, 413, 315, 430);
			Carbon_Life_Update();
		}
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
