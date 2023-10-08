/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_time.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
enum lightState
{
  RED1_GREEN2,
  RED1_YELLOW2,
  GREEN1_RED2,
  YELLOW1_RED2,
};
int currentState = RED1_GREEN2;
int nextState = 0;
void clearAllLed()
{
  HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 1);
  HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 1);
  HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 1);
  HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 1);
  HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 1);
  HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 1);
}
/// @brief
/// @param state: RED1_GREEN2 -> RED1_YELLOW2 -> YELLOW1_RED2 -> GREEN1_RED2 ->  RED1_YELLOW2...
/// @return
int changeState(int state)
{
  clearAllLed();
  switch (state)
  {
  case RED1_GREEN2:
    HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);
    HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 0);
    nextState = 1;
    return 300;
  case RED1_YELLOW2:
    HAL_GPIO_WritePin(RED1_GPIO_Port, RED1_Pin, 0);
    HAL_GPIO_WritePin(YELLOW2_GPIO_Port, YELLOW2_Pin, 0);
    nextState = 2;
    return 200;
  case GREEN1_RED2:
    HAL_GPIO_WritePin(GREEN1_GPIO_Port, GREEN1_Pin, 0);
    HAL_GPIO_WritePin(RED2_GPIO_Port, RED2_Pin, 0);
    nextState = 3;
    return 300;
  case YELLOW1_RED2:
    HAL_GPIO_WritePin(YELLOW1_GPIO_Port, YELLOW1_Pin, 0);
    HAL_GPIO_WritePin(GREEN2_GPIO_Port, GREEN2_Pin, 0);
    nextState = 0;
    return 200;
  default:
    return 0;
  }
}
int num0[] = {0, 0, 0, 0, 0, 0, 1};
int num1[] = {1, 0, 0, 1, 1, 1, 1};
int num2[] = {0, 0, 1, 0, 0, 1, 0};
int num3[] = {0, 0, 0, 0, 1, 1, 0};
int num4[] = {1, 0, 0, 1, 1, 0, 0};
int num5[] = {0, 1, 0, 0, 1, 0, 0};
int num6[] = {0, 1, 0, 0, 0, 0, 0};
int num7[] = {0, 0, 0, 1, 1, 1, 1};
int num8[] = {0, 0, 0, 0, 0, 0, 0};
int num9[] = {0, 0, 0, 0, 1, 0, 0};
void displayNumber(int numberArr[])
{
  HAL_GPIO_WritePin(A_GPIO_Port, A_Pin, numberArr[0]);
  HAL_GPIO_WritePin(B_GPIO_Port, B_Pin, numberArr[1]);
  HAL_GPIO_WritePin(C_GPIO_Port, C_Pin, numberArr[2]);
  HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, numberArr[3]);
  HAL_GPIO_WritePin(E_GPIO_Port, E_Pin, numberArr[4]);
  HAL_GPIO_WritePin(F_GPIO_Port, F_Pin, numberArr[5]);
  HAL_GPIO_WritePin(G_GPIO_Port, G_Pin, numberArr[6]);
}
void display7Seg(int num)
{
  switch (num)
  {
  case 0:
    displayNumber(num0);
    break;
  case 1:
    displayNumber(num1);
    break;
  case 2:
    displayNumber(num2);
    break;
  case 3:
    displayNumber(num3);
    break;
  case 4:
    displayNumber(num4);
    break;
  case 5:
    displayNumber(num5);
    break;
  case 6:
    displayNumber(num6);
    break;
  case 7:
    displayNumber(num7);
    break;
  case 8:
    displayNumber(num8);
    break;
  case 9:
    displayNumber(num9);
    break;
  }
}
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  clearAllLed();
  // int timer = changeState(currentState);
  setTimer1(100);
  int count = 0;
  display7Seg(0);
  while (1)
  {
    if (timer1_flag == 1)
    {
      if (count >= 10)
        count = 0;
      display7Seg(count++);
      // currentState = nextState;
      // timer = changeState(currentState);
      setTimer1(100);
    }
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
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
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
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, A_Pin | B_Pin | C_Pin | D_Pin | E_Pin | F_Pin | G_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, RED1_Pin | YELLOW1_Pin | GREEN1_Pin | RED2_Pin | YELLOW2_Pin | GREEN2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : A_Pin B_Pin C_Pin D_Pin
                           E_Pin F_Pin G_Pin */
  GPIO_InitStruct.Pin = A_Pin | B_Pin | C_Pin | D_Pin | E_Pin | F_Pin | G_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : RED1_Pin YELLOW1_Pin GREEN1_Pin RED2_Pin
                           YELLOW2_Pin GREEN2_Pin */
  GPIO_InitStruct.Pin = RED1_Pin | YELLOW1_Pin | GREEN1_Pin | RED2_Pin | YELLOW2_Pin | GREEN2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  timerRun();
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

#ifdef USE_FULL_ASSERT
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
