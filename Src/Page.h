/*
 * Page.h
 *
 *  Created on: Aug 24, 2016
 *      Author: wchen
 */

#ifndef _PAGE_
#define _PAGE_

#include "WM.h"

#define ID_WINDOW_0 (GUI_ID_USER + 0x00)
#define ID_IMAGE_0 (GUI_ID_USER + 0x01)
#define ID_TEXT_0 (GUI_ID_USER + 0x02)
#define ID_PROGBAR_0 (GUI_ID_USER + 0x03)
#define ID_PROGBAR_1 (GUI_ID_USER + 0x04)
#define ID_TEXT_1 (GUI_ID_USER + 0x05)
#define ID_TEXT_2 (GUI_ID_USER + 0x06)
#define ID_TEXT_3 (GUI_ID_USER + 0x07)
#define ID_IMAGE_1 (GUI_ID_USER + 0x08)
#define ID_TEXT_4 (GUI_ID_USER + 0x09)
#define ID_TEXT_5 (GUI_ID_USER + 0x0A)
#define ID_TEXT_6 (GUI_ID_USER + 0x0B)
#define ID_TEXT_7 (GUI_ID_USER + 0x0C)
#define ID_TEXT_8 (GUI_ID_USER + 0x0D)
#define ID_TEXT_9 (GUI_ID_USER + 0x0E)

#define ID_IMAGE_0_IMAGE_0 0x00
#define ID_IMAGE_1_IMAGE_0 0x01

typedef enum {
	CLEAN,
	MODERATE,
	POOR,
}PM_LEVEL;

typedef enum {
	PAGE_ONE,
	PAGE_TWO,
	PAGE_THREE,
	PAGE_FOUR,
}PAGE_TYPE;

typedef struct
{
	unsigned short PM_Value;
	unsigned short Old_PM_Value;
	PM_LEVEL  PM_Level;
	PM_LEVEL  Old_PM_Level;
}PM_Info;

extern unsigned char Old_Hepa_Life;
extern unsigned char Old_Carbon_Life;
extern unsigned char Hepa_Life;
extern unsigned char Carbon_Life;
extern unsigned char VOC_Level;
extern PM_Info In_PM;
extern PM_Info Out_PM;
extern WM_HWIN hWin;
extern unsigned char page_key_flag;
extern unsigned char page_key_toggle;
extern unsigned char tune_key_flag;
extern unsigned char tune_key_toggle;
extern unsigned char Bright_Level;
extern const unsigned short Bright_Duty[];
extern unsigned char PM2_5_String[];

void Page_One_Init();
void Page_Two_Init();
void Page_Three_Init();

void Handle_Page_One();
void Handle_Page_Two();
void Handle_Page_Three();
WM_HWIN CreateWindow(void);
#endif
