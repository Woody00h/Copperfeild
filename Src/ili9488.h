/*
 * ili9488.h
 *
 *  Created on: Jul 28, 2016
 *      Author: wchen
 */

#ifndef ILI9488_H_
#define ILI9488_H_

#include "stm32f4xx_hal.h"

#define SPI_CS_L 	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_RESET)
#define SPI_CS_H 	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_5,GPIO_PIN_SET)
#define SPI_DI_L	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_RESET)
#define SPI_DI_H	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_4,GPIO_PIN_SET)
#define SPI_CLK_L	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET)
#define SPI_CLK_H	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET)
#define RST_H		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);
#define RST_L		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);
#define _nop_()		asm("nop")

void ili9488_Init();

#endif /* ILI9488_H_ */
