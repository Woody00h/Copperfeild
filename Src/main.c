/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "ili9488.h"
#include "GUI.h"
#include "GUIDEMO.h"
#include "Page.h"
#include "ParticleSensor.h"
#include "B2B_Comm.h"

#define REFRESH_COUNT           ((uint32_t)1386)   /* SDRAM refresh counter */
#define SDRAM_TIMEOUT           ((uint32_t)0xFFFF)
#define LED3_ON					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET)
#define LED3_OFF				HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET)
#define LED4_ON					HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET)
#define LED4_OFF				HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET)

#define SDRAM_MODEREG_BURST_LENGTH_1             ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2             ((uint16_t)0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4             ((uint16_t)0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8             ((uint16_t)0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL      ((uint16_t)0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED     ((uint16_t)0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2              ((uint16_t)0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3              ((uint16_t)0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD    ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED ((uint16_t)0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE     ((uint16_t)0x0200)

/* Private variables ---------------------------------------------------------*/
LTDC_HandleTypeDef	hltdc;
TIM_HandleTypeDef	htim4;
SDRAM_HandleTypeDef	hsdram2;
UART_HandleTypeDef 	UART7_Handle;
FMC_SDRAM_CommandTypeDef Command;
unsigned char New_PM_Data;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_FMC_Init(void);
void MX_LTDC_Init(void);
void UART4_Init();
void UART7_Init();
void MX_TIM4_Init(void);

unsigned char page_key_flag;
unsigned char page_key_toggle;
unsigned char page_key_debounce_timer;
unsigned char tune_key_flag;
unsigned char tune_key_toggle;
unsigned char tune_key_debounce_timer;
PAGE_TYPE Active_Page;

void __errno()
{

}

void Timer_ISR()
{
	if(page_key_debounce_timer)		page_key_debounce_timer--;
	if(tune_key_debounce_timer)		tune_key_debounce_timer--;
}
int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_FMC_Init();
  UART4_Init();
  UART7_Init();
  MX_TIM4_Init();
  __HAL_RCC_CRC_CLK_ENABLE();

  GUI_Init();

  Page_One_Init();
//  Page_Two_Init();
//  Page_Three_Init();
//  CreateWindow();
//  GUI_Exec();

  page_key_debounce_timer = 100;
  tune_key_debounce_timer = 100;
  while (1)
  {
    /* particle sensor */
	if(Sensor3.PMSFrameFlag)
	{
	  Sensor3.PMSFrameFlag = 0;
		if(FrameCheck(&Sensor3))
		{
			Sensor3.data_pm2_5 = WORD_SWAP(Sensor3.PMSUnion->MyPMFrame.PM2_5_US);
			In_PM.PM_Value = Sensor3.data_pm2_5;
			New_PM_Data = 1;
		}
	}

	/*main board to display board communication*/
	if(MyM2DComm.FrameFlag)
	{
		MyM2DComm.FrameFlag = 0;
		if(M2DFrameCheck(&MyM2DComm))
		{
			Hepa_Life = (MyM2DComm.M2DUnionPtr->MyM2DStruct.L_HEPA_Life + MyM2DComm.M2DUnionPtr->MyM2DStruct.R_HEPA_Life)>>1;
			if(Hepa_Life > 99)
				Hepa_Life = 99;

			Carbon_Life = (MyM2DComm.M2DUnionPtr->MyM2DStruct.L_Carbon_Life + MyM2DComm.M2DUnionPtr->MyM2DStruct.R_Carbon_Life)>>1;
			if(Carbon_Life > 99)
				Carbon_Life = 99;

			VOC_Level = MyM2DComm.M2DUnionPtr->MyM2DStruct.VOC_Level;
			Out_PM.PM_Value = MyM2DComm.M2DUnionPtr->MyM2DStruct.PM2_5_US;
			if(Out_PM.PM_Value > 99)
				Out_PM.PM_Value = 99;

			New_PM_Data = 1;
		}
	}

	Read_Key();
	Handle_Page_One();

	asm("wfi");
  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 120;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 6;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* LTDC init function */
void MX_LTDC_Init(void)
{

  LTDC_LayerCfgTypeDef pLayerCfg;

  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 2;
  hltdc.Init.VerticalSync = 0;
  hltdc.Init.AccumulatedHBP = 5;
  hltdc.Init.AccumulatedVBP = 2;
  hltdc.Init.AccumulatedActiveW = 325;
  hltdc.Init.AccumulatedActiveH = 482;
  hltdc.Init.TotalWidth = 328;
  hltdc.Init.TotalHeigh = 484;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }

  //LTDC_BLENDING_FACTOR1_PAxCA
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = 319;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = 479;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
//  pLayerCfg.FBStartAdress = (unsigned int)fb;
  pLayerCfg.FBStartAdress = 0xD0000000;
  pLayerCfg.ImageWidth = 320;
  pLayerCfg.ImageHeight = 480;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }

}

/**
  * @brief  Programs the SDRAM device.
  * @param  RefreshCount: SDRAM refresh counter value
  */
void BSP_SDRAM_Initialization_sequence(uint32_t RefreshCount)
{
  __IO uint32_t tmpmrd =0;

  /* Step 1:  Configure a clock configuration enable command */
  Command.CommandMode             = FMC_SDRAM_CMD_CLK_ENABLE;
  Command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
  Command.AutoRefreshNumber       = 1;
  Command.ModeRegisterDefinition  = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram2, &Command, SDRAM_TIMEOUT);

  /* Step 2: Insert 100 us minimum delay */
  /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
  HAL_Delay(1);

  /* Step 3: Configure a PALL (precharge all) command */
  Command.CommandMode             = FMC_SDRAM_CMD_PALL;
  Command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
  Command.AutoRefreshNumber       = 1;
  Command.ModeRegisterDefinition  = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram2, &Command, SDRAM_TIMEOUT);

  /* Step 4: Configure an Auto Refresh command */
  Command.CommandMode             = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
  Command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
  Command.AutoRefreshNumber       = 4;
  Command.ModeRegisterDefinition  = 0;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram2, &Command, SDRAM_TIMEOUT);

  /* Step 5: Program the external memory mode register */
  tmpmrd = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_1          |
                     SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |
                     SDRAM_MODEREG_CAS_LATENCY_3           |
                     SDRAM_MODEREG_OPERATING_MODE_STANDARD |
                     SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

  Command.CommandMode             = FMC_SDRAM_CMD_LOAD_MODE;
  Command.CommandTarget           = FMC_SDRAM_CMD_TARGET_BANK2;
  Command.AutoRefreshNumber       = 1;
  Command.ModeRegisterDefinition  = tmpmrd;

  /* Send the command */
  HAL_SDRAM_SendCommand(&hsdram2, &Command, SDRAM_TIMEOUT);

  /* Step 6: Set the refresh rate counter */
  /* Set the device refresh rate */
  HAL_SDRAM_ProgramRefreshRate(&hsdram2, RefreshCount);
}

/* FMC initialization function */
static void MX_FMC_Init(void)
{
  FMC_SDRAM_TimingTypeDef SdramTiming;

  /** Perform the SDRAM2 memory initialization sequence
  */
  hsdram2.Instance = FMC_SDRAM_DEVICE;
  /* hsdram2.Init */
  hsdram2.Init.SDBank = FMC_SDRAM_BANK2;
  hsdram2.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
  hsdram2.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
  hsdram2.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
  hsdram2.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
  hsdram2.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
  hsdram2.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
  hsdram2.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
  hsdram2.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
  hsdram2.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_1;
  /* SdramTiming */
  SdramTiming.LoadToActiveDelay = 2;
  SdramTiming.ExitSelfRefreshDelay = 7;
  SdramTiming.SelfRefreshTime = 4;
  SdramTiming.RowCycleDelay = 7;
  SdramTiming.WriteRecoveryTime = 2;
  SdramTiming.RPDelay = 2;
  SdramTiming.RCDDelay = 2;

  if (HAL_SDRAM_Init(&hsdram2, &SdramTiming) != HAL_OK)
  {
    Error_Handler();
  }

  /* SDRAM initialization sequence */
   BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  //LCD RESET, SPI_CS, SPI_SIMO, SPI_CLK
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7, GPIO_PIN_SET);

  /*RTS PB4*/
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);

  /*LCD RESET, SPI_CS, SPI_SIMO, SPI_CLK */
  GPIO_InitStruct.Pin =  GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*RTS PB4*/
  GPIO_InitStruct.Pin =  GPIO_PIN_4;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*2 keys PA8 PC9*/
  GPIO_InitStruct.Pin =  GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin =  GPIO_PIN_9;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure BACKLIGHT */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF2_TIM4;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */
void UART4_Init()
{
	UART_HandleTypeDef UART4_Handle;
	GPIO_InitTypeDef UART4_GPIO;

	__GPIOA_CLK_ENABLE();

	UART4_GPIO.Pin = GPIO_PIN_1 | GPIO_PIN_0;
	UART4_GPIO.Alternate = GPIO_AF8_UART4;
	UART4_GPIO.Speed = GPIO_SPEED_FAST;
	UART4_GPIO.Mode = GPIO_MODE_AF_PP;
	UART4_GPIO.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOA,&UART4_GPIO);

	__UART4_CLK_ENABLE();
	UART4_Handle.Instance = UART4;
	UART4_Handle.Init.BaudRate = 9600;
	UART4_Handle.Init.WordLength = UART_WORDLENGTH_8B;
	UART4_Handle.Init.StopBits = UART_STOPBITS_1;
	UART4_Handle.Init.Parity = UART_PARITY_NONE;
	UART4_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART4_Handle.Init.Mode = UART_MODE_TX_RX;
	UART4_Handle.Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_Init(&UART4_Handle);
	UART4->CR1 = 0x202C;

	HAL_NVIC_SetPriority(UART4_IRQn, 4, 0);
	HAL_NVIC_EnableIRQ(UART4_IRQn);
}

/* USER CODE BEGIN 4 */
void UART7_Init()
{
	GPIO_InitTypeDef UART7_GPIO;

	__GPIOF_CLK_ENABLE();

	UART7_GPIO.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	UART7_GPIO.Alternate = GPIO_AF8_UART7;
	UART7_GPIO.Speed = GPIO_SPEED_FAST;
	UART7_GPIO.Mode = GPIO_MODE_AF_PP;
	UART7_GPIO.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOF,&UART7_GPIO);

	__UART7_CLK_ENABLE();
	UART7_Handle.Instance = UART7;
	UART7_Handle.Init.BaudRate = 9600;
	UART7_Handle.Init.WordLength = UART_WORDLENGTH_8B;
	UART7_Handle.Init.StopBits = UART_STOPBITS_1;
	UART7_Handle.Init.Parity = UART_PARITY_NONE;
	UART7_Handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART7_Handle.Init.Mode = UART_MODE_TX_RX;
	UART7_Handle.Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_Init(&UART7_Handle);
	UART7->CR1 = 0x202C;

	HAL_NVIC_SetPriority(UART7_IRQn, 4, 0);
	HAL_NVIC_EnableIRQ(UART7_IRQn);
}
void MX_TIM4_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
  TIM_OC_InitTypeDef sConfigOC;

  __TIM4_CLK_ENABLE();

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 599;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 699;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.RepetitionCounter = 0;
  HAL_TIM_Base_Init(&htim4);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig);

  HAL_TIM_OC_Init(&htim4);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig);

  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  HAL_TIMEx_ConfigBreakDeadTime(&htim4, &sBreakDeadTimeConfig);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 300;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
//  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);

  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
}

void Read_Key()
{
	page_key_flag = 0;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET)
	{
		page_key_debounce_timer = 100;
		page_key_toggle = 1;
	}
	else
	{
		if(!page_key_debounce_timer)
		{
			page_key_flag = 1;
		}
	}

	tune_key_flag = 0;
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_9) == GPIO_PIN_RESET)
	{
		tune_key_debounce_timer = 100;
		tune_key_toggle = 1;
	}
	else
	{
		if(!tune_key_debounce_timer)
		{
			tune_key_flag = 1;
		}
	}
}
void Start_New_Page(PAGE_TYPE New_Page)
{
	Active_Page = New_Page;
	switch (Active_Page)
	{
	case PAGE_ONE:
		Page_One_Init();
		break;
	case PAGE_TWO:
		break;
	case PAGE_THREE:
		Page_Three_Init();
		break;
	case PAGE_FOUR:
		break;
	default:
		break;
	}

}
void Handle_Pages()
{
	switch (Active_Page)
	{
	case PAGE_ONE:
		Handle_Page_One();
		break;
	case PAGE_TWO:
		break;
	case PAGE_THREE:
		Handle_Page_Three();
		break;
	case PAGE_FOUR:
		break;
	default:
		break;
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
