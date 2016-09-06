/*
 * B2B_Comm.c
 *
 *  Created on: Aug 30, 2016
 *      Author: wchen
 */

#define B2B_COMM
#include "B2B_Comm.h"
#include "ParticleSensor.h"
#include "stm32f4xx.h"
#include "Page.h"

extern UART_HandleTypeDef 	UART7_Handle;

#define RXNE 	0x20
#define TXE		0x80

Main2DispComm  MyM2DComm = {&MyM2DUnion,0,0,0,0};

void UART7_IRQHandler()
{
	u8 rxdata;

	if(!(UART7->SR & RXNE))
		return;

	rxdata = UART7->DR;

	if(MyM2DComm.HeadFlag == 0)
	{
		//head receive
		if(MyM2DComm.DataPtr < 2)
		{
			MyM2DComm.M2DUnionPtr->Main2DispBuf[MyM2DComm.DataPtr] = rxdata;
			MyM2DComm.DataPtr ++;
		}
		else
		{
#ifdef LITTLE_ENDIAN
			(MyM2DComm.M2DUnionPtr)->MyM2DStruct.Head >>= 8;
#else
			(MyM2DComm.M2DUnionPtr)->MyM2DStruct.Head <<= 8;
#endif
			(MyM2DComm.M2DUnionPtr)->Main2DispBuf[1] = rxdata;
			MyM2DComm.DataPtr = 2;
		}

		//head check
		if( MyM2DComm.DataPtr == 2 && (MyM2DComm.M2DUnionPtr)->MyM2DStruct.Head == B2B_FRAME_HEAD)
		{
			MyM2DComm.HeadFlag = 1;
		}
	}
	else
	{
		(MyM2DComm.M2DUnionPtr)->Main2DispBuf[MyM2DComm.DataPtr] = rxdata;
		if(MyM2DComm.DataPtr >= (B2B_BUF_LENGTH-1))
		{
			MyM2DComm.HeadFlag = 0;
			MyM2DComm.DataPtr = 0;
			(MyM2DComm.M2DUnionPtr)->MyM2DStruct.Length = 0;
			(MyM2DComm.M2DUnionPtr)->MyM2DStruct.Head = 0;
		}
		else
		{
			MyM2DComm.DataPtr ++;
		}

		if(MyM2DComm.DataPtr >= 6 && MyM2DComm.DataPtr == (MyM2DComm.M2DUnionPtr->MyM2DStruct.Length + 4))
		{
			MyM2DComm.FrameFlag = 1;
			MyM2DComm.HeadFlag = 0;
			MyM2DComm.DataPtr = 0;
		}
	}
}

u8 M2DFrameCheck(Main2DispComm *comm)
{
	u16 checksum = 0;
	u8 i = 0;
	u16 len = comm->M2DUnionPtr->MyM2DStruct.Length;

	for (i = 0; i < (len+2); i++)
	{
		checksum += comm->M2DUnionPtr->Main2DispBuf[i];
	}

	comm->M2DUnionPtr->MyM2DStruct.Length = 0;
	comm->M2DUnionPtr->MyM2DStruct.Head = 0;

	if (checksum == comm->M2DUnionPtr->MyM2DStruct.CheckSum)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Send2MainBoard()
{
	unsigned short sum,i;

	MyD2MUnion.MyD2MStruct.Head 	= 0x464d;
	MyD2MUnion.MyD2MStruct.Length	= 10;
	MyD2MUnion.MyD2MStruct.PM2_5_US	= WORD_SWAP(Sensor3.data_pm2_5);
	MyD2MUnion.MyD2MStruct.PM10_US	= WORD_SWAP(Sensor3.data_pm10);
	MyD2MUnion.MyD2MStruct.PQ0_3	= WORD_SWAP(Sensor3.data_qt0_3);
	MyD2MUnion.MyD2MStruct.Brightness	= Bright_Level;
	MyD2MUnion.MyD2MStruct.Err		= 0;

	sum = 0;
	for(i=0;i<12;i++)
	{
		sum += MyD2MUnion.Disp2MainBuf[i];
	}

	MyD2MUnion.MyD2MStruct.CheckSum = sum;

	HAL_UART_Transmit(&UART7_Handle,MyD2MUnion.Disp2MainBuf,14,1000);

}
