/*
 * ili9488.c
 *
 *  Created on: Jul 28, 2016
 *      Author: wchen
 */


#include "ili9488.h"

void SPI_SendData(unsigned char data)
{
	unsigned char n;

	for(n=0; n<8; n++)
	{
		if(data & 0x80)
			SPI_DI_H;
		else
			SPI_DI_L;
		data<<= 1;

		SPI_CLK_L;	_nop_();_nop_();_nop_();_nop_();
		SPI_CLK_H;	_nop_();_nop_();_nop_();_nop_();
	}
}

void SPI_WriteComm(unsigned char cmd)
{
	SPI_CS_L;
	_nop_();_nop_();_nop_();_nop_();


	SPI_DI_L; //command
	_nop_();_nop_();_nop_();_nop_();

	SPI_CLK_L;	_nop_();_nop_();_nop_();_nop_();
	SPI_CLK_H;	_nop_();_nop_();_nop_();_nop_();

	SPI_SendData(cmd);

	SPI_CS_H;
}

void SPI_WriteData(unsigned char data)
{
	SPI_CS_L;
	_nop_();_nop_();_nop_();_nop_();


	SPI_DI_H; //data
	_nop_();_nop_();_nop_();_nop_();

	SPI_CLK_L;	_nop_();_nop_();_nop_();_nop_();
	SPI_CLK_H;	_nop_();_nop_();_nop_();_nop_();

	SPI_SendData(data);

	SPI_CS_H;
}

void ili9488_Init()
{

	RST_H;
	HAL_Delay(10);
	RST_L;
    HAL_Delay(100);
    RST_H;
	HAL_Delay(100);



	//adjust control 3
	SPI_WriteComm(0XF7);
	SPI_WriteData(0xA9);
	SPI_WriteData(0x51);
	SPI_WriteData(0x2C);
	SPI_WriteData(0x82);

	//power control 1
	SPI_WriteComm(0xC0);
	SPI_WriteData(0x11);
	SPI_WriteData(0x09);

	//power control 2
	SPI_WriteComm(0xC1);
	SPI_WriteData(0x41);

	//VCOM cotrol
	SPI_WriteComm(0XC5);
	SPI_WriteData(0x00);
	SPI_WriteData(0x2A);
	SPI_WriteData(0x80);

	//Frame Rate Control (In Normal Mode/Full Colors)
	SPI_WriteComm(0xB1);
	SPI_WriteData(0xB0);
	SPI_WriteData(0x11);

	//Display Inversion Control
	SPI_WriteComm(0xB4);
	SPI_WriteData(0x02);

	//Display Function Control
	SPI_WriteComm(0xB6);
	SPI_WriteData(0x20);
	SPI_WriteData(0x22);

	//Entry Mode Set
	SPI_WriteComm(0xB7);
	SPI_WriteData(0xc6);

	//HS Lanes Control
	SPI_WriteComm(0xBE);
	SPI_WriteData(0x00);
	SPI_WriteData(0x04);

	//Set Image Function
	SPI_WriteComm(0xE9);
	SPI_WriteData(0x00);

	//Memory Access Control
	SPI_WriteComm(0x36);
	SPI_WriteData(0x08);

	//Interface Pixel Format
	SPI_WriteComm(0x3A);
	SPI_WriteData(0x55);

	//PGAMCTRL (Positive Gamma Control)
	SPI_WriteComm(0xE0);
	SPI_WriteData(0x00);
	SPI_WriteData(0x07);
	SPI_WriteData(0x12);
	SPI_WriteData(0x0B);
	SPI_WriteData(0x18);
	SPI_WriteData(0x0B);
	SPI_WriteData(0x3F);
	SPI_WriteData(0x9B);
	SPI_WriteData(0x4B);
	SPI_WriteData(0x0B);
	SPI_WriteData(0x0F);
	SPI_WriteData(0x0B);
	SPI_WriteData(0x15);
	SPI_WriteData(0x17);
	SPI_WriteData(0x0F);

	//NGAMCTRL (Negative Gamma Control)
	SPI_WriteComm(0XE1);
	SPI_WriteData(0x00);
	SPI_WriteData(0x16);
	SPI_WriteData(0x1B);
	SPI_WriteData(0x02);
	SPI_WriteData(0x0F);
	SPI_WriteData(0x06);
	SPI_WriteData(0x34);
	SPI_WriteData(0x46);
	SPI_WriteData(0x48);
	SPI_WriteData(0x04);
	SPI_WriteData(0x0D);
	SPI_WriteData(0x0D);
	SPI_WriteData(0x35);
	SPI_WriteData(0x36);
	SPI_WriteData(0x0F);

	//Sleep OUT
	SPI_WriteComm(0x11);

	HAL_Delay(120);

	//Display ON
	SPI_WriteComm(0x29);
	}
