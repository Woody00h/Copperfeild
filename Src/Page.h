/*
 * Page.h
 *
 *  Created on: Aug 24, 2016
 *      Author: wchen
 */

#ifndef _PAGE_
#define _PAGE_

typedef enum {
	CLEAN,
	MODERATE,
	POOR,
}PM_LEVEL;

typedef struct
{
	unsigned short PM_Value;
	unsigned short Old_PM_Value;
	PM_LEVEL  PM_Level;
	PM_LEVEL  Old_PM_Level;
}PM_Info;


extern unsigned char Hepa_Life;
extern unsigned char Carbon_Life;
extern unsigned char VOC_Level;
extern PM_Info In_PM;
extern PM_Info Out_PM;

void Page_One_Init();
void Page_Two_Init();

#endif
