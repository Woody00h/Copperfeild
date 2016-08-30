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
			(MyM2DComm.M2DUnionPtr)->MyM2DStruct[1] = rxdata;
			MyM2DComm.DataPtr = 2;
		}

		//head check
		if( MyM2DComm.DataPtr == 2 && (MyM2DComm.M2DUnionPtr)->MyM2DStruct.Head == FRAME_HEAD)
		{
			MyM2DComm.HeadFlag = 1;
		}
	}
	else
	{
		(MyM2DComm.M2DUnionPtr)->MyM2DStruct[MyM2DComm.DataPtr] = rxdata;
		if(MyM2DComm.DataPtr >= (BUF_LENGTH-1))
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

		if(MyM2DComm.DataPtr >= 6 && MyM2DComm.DataPtr == (WORD_SWAP((MyM2DComm.M2DUnionPtr)->MyM2DStruct.Length) + 4))
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
	u16 len = WORD_SWAP(comm->M2DUnionPtr->MyM2DStruct.Length);

	for (i = 0; i < (len+2); i++)
	{
		checksum += comm->M2DUnionPtr->Main2DispBuf[i];
	}

	comm->M2DUnionPtr->MyM2DStruct.Length = 0;
	comm->M2DUnionPtr->MyM2DStruct.Head = 0;

	if (checksum == WORD_SWAP(comm->M2DUnionPtr->MyM2DStruct.CheckSum))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
