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
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "mpu6050.h"
#include "stdio.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "cmsis_armcc.h"
#include "send_to_client.h"
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
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	OLED_Init();
	MPU_Init();
	uint8_t cnt=0;
	while(mpu_dmp_init()!=0) {OLED_Display_Buffer(0,0,"MPU ERR!");HAL_Delay(10);cnt++;if(cnt==8) {__set_FAULTMASK(1);NVIC_SystemReset();} }
	OLED_Display_Buffer(0,0,"MPU OKK!");
	HAL_Delay(1000);
	OLED_Display_Clear();
	short Gyro[3]={0};
	short Accel[3]={0};
	short temp=0;
	float buff[3]={0};
//	OLED_Display_Buffer(2,0,"ax:");
//	OLED_Display_Buffer(4,0,"ay:");
//	OLED_Display_Buffer(6,0,"az:");
//	OLED_Display_Buffer(2,9,"gx:");
//	OLED_Display_Buffer(4,9,"gy:");
//	OLED_Display_Buffer(6,9,"gz:");
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  HAL_Delay(3);
//		mpu_reset_fifo();
//		HAL_Delay(1);
//	  temp=MPU_GetTemp();
	  MPU_GetGyro(Gyro,Gyro+1,Gyro+2);
	  MPU_GetAccel(Accel,Accel+1,Accel+2);
	  for(uint8_t i=0;i<3;i++)
	  {
		Gyro[i]=MPU_GetGyro2(Gyro[i]);
		Accel[i]=MPU_GetAccel2(Accel[i]);
	  }
	  if(mpu_dmp_get_data(buff,buff+1,buff+2)==0)
//	  OLED_Display_Num(0,5,temp,4);
//	  OLED_Display_Num(2,0,buff[0]*1000,8);
//	  OLED_Display_Num(4,0,buff[1]*1000,8);
//	  OLED_Display_Num(6,0,buff[2]*1000,8);
//	  OLED_Display_Num(2,9,Gyro[0],5);
//	  OLED_Display_Num(4,9,Gyro[1],5);
//	  OLED_Display_Num(6,9,Gyro[2],5);
//	  printf("Temp:%5d\r\n ax:%5d ay:%5d az:%5d\r\n gx:%5d gy:%5d gz:%5d\r\n",temp,Accel[0],Accel[1],Accel[2],Gyro[0],Gyro[1],Gyro[2]);
//			printf("pitch=%f,roll=%f,yaw=%f\r\n",buff[0],buff[1],buff[2]);
		OLED_Display_Num(0,0,(uint16_t)(buff[0]*1000),5);
	  OLED_Display_Num(2,0,(uint16_t)(buff[1]*1000),5);
	  OLED_Display_Num(4,0,(uint16_t)(buff[2]*1000),5);
	  usart_report_imu(Accel[0],Accel[1],Accel[2],Gyro[0],Gyro[1],Gyro[2],buff[0],buff[1],buff[2]);
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
