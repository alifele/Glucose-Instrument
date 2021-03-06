/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define LED_RED_PIN GPIO_PIN_0
#define LED_GREEN_PIN GPIO_PIN_1
#define LED_BLUE_PIN GPIO_PIN_2
#define LED_PINK_PIN GPIO_PIN_3
#define LED_ORANGE_PIN GPIO_PIN_4
#define LED_WHITE_PIN GPIO_PIN_5
#define LED_IR_PIN GPIO_PIN_6

#define LED_RED_PORT GPIOC
#define LED_GREEN_PORT GPIOC
#define LED_BLUE_PORT GPIOC
#define LED_PINK_PORT GPIOC
#define LED_ORANGE_PORT GPIOC
#define LED_WHITE_PORT GPIOC
#define LED_IR_PORT GPIOC

#define DataNumber 500


void Get_data(GPIO_TypeDef *LED_PORT,GPIO_TypeDef *LED_PIN, uint16_t * values_list, uint16_t counter);
void Transmit_data(char *name, uint16_t *values_list);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADC_Start(&hadc1);

  uint16_t average = 0;
  uint16_t red_values[DataNumber] = {};
  uint16_t blue_values[DataNumber] = {};
  uint16_t green_values[DataNumber] = {};
  uint16_t pink_values[DataNumber] = {};
  uint16_t white_values[DataNumber] = {};
  uint16_t orange_values[DataNumber] = {};
  uint16_t IR_values[DataNumber] = {};


  uint16_t counter = 0; // is the counter of data. will be DataNumber as max value.
  char buffer[10] = "";

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


	  while (strcmp(buffer, "start")){
		  HAL_UART_Receive(&huart3, buffer, strlen("start"), HAL_MAX_DELAY);
	  }



//	  HAL_UART_Transmit(&huart3, "getting data.\r\n", strlen("getting data.\r\n"), HAL_MAX_DELAY);
//	  HAL_Delay(2);
//	  HAL_UART_Transmit(&huart3, "getting data..\r\n", strlen("getting data..\r\n"), HAL_MAX_DELAY);
//	  HAL_Delay(2);
//	  HAL_UART_Transmit(&huart3, "getting data...\r\n", strlen("getting data...\r\n"), HAL_MAX_DELAY);
//	  HAL_Delay(2);
//	  HAL_UART_Transmit(&huart3, "getting data....\r\n", strlen("getting data....\r\n"), HAL_MAX_DELAY);

	  for (counter = 0; counter < DataNumber ; ++counter) {

	  Get_data(LED_RED_PORT, LED_RED_PIN, red_values, counter);
	  Get_data(LED_PINK_PORT, LED_PINK_PIN, pink_values, counter);
	  Get_data(LED_BLUE_PORT, LED_BLUE_PIN, blue_values, counter);
	  Get_data(LED_WHITE_PORT, LED_WHITE_PIN, white_values, counter);
//	  Get_data(LED_GREEN_PORT, LED_GREEN_PIN, green_values, counter);
	  Get_data(LED_ORANGE_PORT, LED_ORANGE_PIN, orange_values, counter);

	  }

	  Transmit_data("red\r\n", red_values);
	  Transmit_data("blue\r\n", blue_values);
	  Transmit_data("white\r\n", white_values);
	  Transmit_data("pink\r\n", pink_values);
//	  Transmit_data("green\r\n", green_values);
	  Transmit_data("orange\r\n", orange_values);

	  HAL_UART_Transmit(&huart3, "AllDone!", strlen("AllDone!"), HAL_MAX_DELAY);
	  strcpy(buffer, "");





  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC4 PC5 PC6 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void Get_data(GPIO_TypeDef *LED_PORT,GPIO_TypeDef *LED_PIN, uint16_t * values_list, uint16_t counter){

	uint16_t average = 0;

	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);
	average = 0;
	for (int i = 0; i < 10; i++ ) {
	  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	  average += HAL_ADC_GetValue(&hadc1);
	}
	average *= 0.1;
	values_list[counter] = average;
	HAL_Delay(1);
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET);
	HAL_Delay(1);

}


void Transmit_data(char *name, uint16_t *values_list){

	char msg[10] = "hello\r\n";

	HAL_UART_Transmit(&huart3, name, strlen(name), HAL_MAX_DELAY);
	HAL_Delay(200);
	for (int i = 0; i < DataNumber ; i++) {
		sprintf(msg, "%d\n", values_list[i]);
		HAL_UART_Transmit(&huart3, msg, strlen(msg), HAL_MAX_DELAY);
	}
	//HAL_UART_Transmit(&huart3, "done!\r\n", strlen("done!\r\n"), HAL_MAX_DELAY);
	HAL_Delay(200);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
