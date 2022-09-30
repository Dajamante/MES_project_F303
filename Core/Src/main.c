/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"
#include "console.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
char* trimmer();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

char* trimmer(uint8_t *buf, int len){
	int real_length = 0;

	for(int i = 0; i < len; i++){
		if (buf[i] == '\0') {
			real_length=i;
			break;
		}
	}
	char *trimmed = calloc((real_length), 1);
	int j;
	for(j = 0; j < real_length; j++){
			trimmed[j] = buf[j];
	}

	return trimmed;

}

int _read(int file, char *result, size_t len){
	HAL_StatusTypeDef status;

	int retcode = 0;

	if (len != 0){
		status = HAL_UART_Receive(&huart1, (uint8_t *) result, len, HAL_MAX_DELAY);

		if (status == HAL_OK){

			retcode = len;
		} else {
			retcode = -1;
		}
	}

	return retcode;
}

int _write(int file, char *outgoing, int len){
	HAL_UART_Transmit(&huart1, (uint8_t*) outgoing, len, 100);
	return len;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	int ch;
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  setvbuf(stdin, NULL, _IONBF, 0);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      //uint8_t line[64];
      //uint8_t response[12] = {'\0'};
      uint8_t command[12] = {'\0'};

      //strcpy((char*)line, "Reading instructions:\n. Chose note, clock or something.");
      printf("Reading instructions: chose note, clock or something.\n");

      int i = 0;
      while((ch !='\n') && (ch = getchar())){
    	  printf("%c", ch);
    	  command[i++] = ch;
      }

      printf("Command %s", command);
      printf("Type of command : %d\n", sizeof(command));
      ch ='\0';
      command[i] = ch;
      printf("Size of command : %d \n", sizeof(command));
      printf("Const char command : %s \n", ((const char *) command));

      char * trimmed = trimmer(command, 12);
      printf("Trimmed : %s \n", trimmed);
      printf("size of trimmed %d\n", strlen(trimmed));
      //HAL_UART_Transmit(&huart1, response, 12, HAL_MAX_DELAY);
      //HAL_UART_Receive_IT(&huart1, response, 1);
      //%*c dispose of the new line.
      // https://stackoverflow.com/questions/63621779/how-to-clear-the-content-of-a-string-which-has-already-been-used-in-c-programmin
      //while (response[0] != '\n'){
      //	  command[i++] = response[0];
      //}
      // Null terminate the string
      //command[i] ='\0';

      //HAL_UART_Transmit(&huart1, command, strlen((char*) command), HAL_MAX_DELAY);
      //scanf("%15[^\n]%*c", line2);
      //printf("Your line: %s\n", line);
      if (strcmp(trimmed, "clock") == 0){
          printf("You chose clock\n");
          callClock();
      } else if (strcmp(trimmed, "note") == 0){
            printf("You chose note\n");
           callNote();
       } else if (strcmp(trimmed, "something") == 0){
           printf("You chose something\n");
           callSomething();
       } else {
           printf("Don't.\n");
      }

      //memset(line, 0, sizeof(line));
      //memset(line, 0, sizeof(response));
      memset(trimmed, 0, strlen(trimmed));
      memset(command, 0, sizeof(command));

	  //strcpy((char*)buf, "UUUU");
	  //HAL_UART_Transmit(&huart1, buf, strlen((char*)buf), HAL_MAX_DELAY);
	  //HAL_Delay(500);

	  //strcpy((char*)buf, "UUUU");
	  //HAL_UART_Transmit(&huart2, buf, strlen((char*)buf), HAL_MAX_DELAY);
	  //HAL_Delay(500);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


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
