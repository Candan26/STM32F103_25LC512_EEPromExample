
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
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
#include "main.h"
#include "stm32f1xx_hal.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "25LC512.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
	#define UNSIGNED_CHAR_FIRST_EEPROM_DATA_ADDRESS 0x0001
	#define UNSIGNED_CHAR_SECOND_EEPROM_DATA_ADDRESS 0x0100
	#define UNSIGNED_INT_FIRST_EEPROM_DATA_ADDRESS 0x00C9
	#define UNSIGNED_INT_SECOND_EEPROM_DATA_ADDRESS 0x10C9
	#define UNSIGNED_SHORT_FIRST_EEPROM_DATA_ADDRESS 0x0400
	#define UNSIGNED_SHORT_SECOND_EEPROM_DATA_ADDRESS 0x0500
	unsigned char glb_ucDataFromFirstEEProm[200];
	unsigned char glb_ucDataToFirstEEProm[200];
	unsigned char glb_ucDataFromSecondEEProm[200];
	unsigned char glb_ucDataToSecondEEProm[200];	

	
	unsigned int glb_uiDataFromFirstEEProm[10];
	unsigned int glb_uiDataToFirstEEProm[10]={0x112345,0x212345,0x312345,0x412345,0x512345,0x612345,0x712345,0x812345,0x912345};
	unsigned int glb_uiDataFromSecondEEProm[10];
	unsigned int glb_uiDataToSecondEEProm[10]={0x123459,0x123458,0x123457,0x123456,0x123455,0x123454,0x123453,0x123452,0x123451};		
	
	unsigned short glb_usDataFromFirstEEProm[10];
	unsigned short glb_usDataToFirstEEProm[10]={0x1123,0x2123,0x3123,0x4123,0x5123,0x6123,0x7123,0x8123,0x9123};
	unsigned short glb_usDataFromSecondEEProm[10];
	unsigned short glb_usDataToSecondEEProm[10]={0x3459,0x3458,0x3457,0x3456,0x3455,0x3454,0x3453,0x3452,0x3451};		
	
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART3_UART_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  MX_TIM4_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
	using namespace std;
	/// create eeprom objects
	EEPROM Eprom1(&hspi1,EEPROM_CS0_GPIO_Port,EEPROM_CS0_Pin);
	EEPROM Eprom2(&hspi1,EEPROM_CS1_GPIO_Port,EEPROM_CS1_Pin);
	
	Eprom1.MC25LC512_Initilize();// init eeprom 
	Eprom2.MC25LC512_Initilize();// int eeprom2
	HAL_Delay(150);
	
	
	memcpy(glb_ucDataToFirstEEProm,(char*)"Cagri CANDAN 11/18/2018 First EEProm TEST",62);			
	Eprom1.MC25LC512_Write((unsigned short)UNSIGNED_CHAR_FIRST_EEPROM_DATA_ADDRESS,glb_ucDataToFirstEEProm,62);
	Eprom1.MC25LC512_Read((unsigned short)UNSIGNED_CHAR_FIRST_EEPROM_DATA_ADDRESS,glb_ucDataFromFirstEEProm,62);
	
	Eprom1.MC25LC512_Write((unsigned short)UNSIGNED_INT_FIRST_EEPROM_DATA_ADDRESS,glb_uiDataToFirstEEProm,10);
	Eprom1.MC25LC512_Read((unsigned short)UNSIGNED_INT_FIRST_EEPROM_DATA_ADDRESS,glb_uiDataFromFirstEEProm,10);
	
	
	memcpy(glb_ucDataToSecondEEProm,(char*)"Cagri CANDAN 11/18/2018 Second EEProm TEST",63);		
	Eprom2.MC25LC512_Write((unsigned short)UNSIGNED_CHAR_SECOND_EEPROM_DATA_ADDRESS,glb_ucDataToSecondEEProm,63);
	Eprom2.MC25LC512_Read((unsigned short)UNSIGNED_CHAR_SECOND_EEPROM_DATA_ADDRESS,glb_ucDataFromSecondEEProm,65);
	
	Eprom1.MC25LC512_Write((unsigned short)UNSIGNED_INT_FIRST_EEPROM_DATA_ADDRESS,glb_uiDataToFirstEEProm,10);
	Eprom1.MC25LC512_Read((unsigned short)UNSIGNED_INT_FIRST_EEPROM_DATA_ADDRESS,glb_uiDataFromFirstEEProm,10);
	
	Eprom2.MC25LC512_Write((unsigned short)UNSIGNED_INT_FIRST_EEPROM_DATA_ADDRESS,glb_uiDataToSecondEEProm,10);
	Eprom2.MC25LC512_Read((unsigned short)UNSIGNED_INT_FIRST_EEPROM_DATA_ADDRESS,glb_uiDataFromSecondEEProm,10);
	
	Eprom2.MC25LC512_Write((unsigned short)UNSIGNED_INT_FIRST_EEPROM_DATA_ADDRESS,glb_usDataToSecondEEProm,10);
	Eprom2.MC25LC512_Read((unsigned short)UNSIGNED_INT_FIRST_EEPROM_DATA_ADDRESS,glb_usDataFromSecondEEProm,10);
	

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* USART3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USART2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* TIM4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM4_IRQn);
  /* TIM3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM3_IRQn);
  /* TIM2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* TIM1_CC_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM1_CC_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM1_CC_IRQn);
  /* TIM1_UP_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(TIM1_UP_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);
  /* SPI1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(SPI1_IRQn);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
