/*
 * B2B_Comm.h
 *
 *  Created on: Aug 30, 2016
 *      Author: wchen
 */

#ifndef B2B_COMM_H_
#define B2B_COMM_H_

#define LITTLE_ENDIAN

#ifdef B2B_COMM
#define B2B_COMM_EXTERN
#else
#define B2B_COMM_EXTERN extern
#endif

#define B2B_FRAME_HEAD 0x444d


#define B2B_BUF_LENGTH 30
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct
{
	u16 Head;
	u16 Length;
	u16 PM2_5_US;
	u16 PM10_US;
	u16 PQ0_3;
	u16 AQI_Out;
	u16 AQI_In;
	u8  L_Filter_Type;
	u8  R_Filter_Type;
	u8  L_HEPA_Life;
	u8  L_Carbon_Life;
	u8  R_HEPA_Life;
	u8  R_Carbon_Life;
	u8  VOC_Level;
	u8  Reserve1;
	u8  Reserve2;
	u8  Err;
	u16 CheckSum;
}Main2DispStruct;

typedef struct
{
	u16 Head;
	u16 Length;
	u16 PM2_5_US;
	u16 PM10_US;
	u16 PQ0_3;
	u8  Brightness;
	u8  Err;
	u16 CheckSum;
}Disp2MainStruct;

typedef union
{
	u8 Main2DispBuf[B2B_BUF_LENGTH];
	Main2DispStruct MyM2DStruct;
}Main2DispUnion;

typedef union
{
	u8 Disp2MainBuf[20];
	Disp2MainStruct MyD2MStruct;
}Disp2MainUnion;

typedef struct
{
	Main2DispUnion * M2DUnionPtr;
	u8 HeadFlag;
	u8 HeadPointer;
	u8 DataPtr;
	u8 FrameFlag;
}Main2DispComm;

B2B_COMM_EXTERN Main2DispUnion MyM2DUnion;
B2B_COMM_EXTERN Disp2MainUnion MyD2MUnion;
B2B_COMM_EXTERN u8 M2DFrameCheck(Main2DispComm *comm);
extern Main2DispComm  MyM2DComm;
#endif /* B2B_COMM_H_ */
