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
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
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
uint8_t Key_scan(void)
{
	uint8_t temp=0;
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)==GPIO_PIN_SET) temp=1;
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)==GPIO_PIN_SET) temp=2;
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_2)==GPIO_PIN_SET) temp=3;
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==GPIO_PIN_SET) temp=4;
	return temp;
}

typedef struct 
{
	uint8_t current;
	uint8_t down;
	uint8_t up;
	uint8_t enter;
	void (*current_operation)();
}Menu_Info;

Menu_Info Menu[]=
{
	//第一层
	{0,1,1,2,(*func_a)},
	{1,0,0,7,(*func_b)},
	
	//第二层
	{2,3,6,0,(*func_a1)},
	{3,4,2,16,(*func_a2)},	
	{4,5,3,19,(*func_a3)},
	{5,6,4,22,(*func_a4)},
	{6,2,5,0,(*func_a5)},
	
	
	
	{7,8,11,22,(*func_b1)},
	{8,9,7,25,(*func_b2)},	
	{9,10,8,28,(*func_b3)},
	{10,11,9,31,(*func_b4)},
	{11,7,10,1,(*func_b5)},
	
	//第三层
	{12,13,14,2,(*func_a11)},
//	{13,14,12,2,(*func_a12)},
//	{14,12,13,2,(*func_a23)},
	
	
	{16,17,18,3,(*func_a12)},
//	{17,18,16,3,(*func_a22)},
//	{18,16,17,3,(*func_a23)},
	
	
	
	{19,20,21,4,(*func_a13)},
//	{20,21,19,4,(*func_a42)},
//	{21,19,20,4,(*func_a43)},
	
	
	
	{22,23,24,5,(*func_b14)},
//	{23,24,22,5,(*func_b12)},
//	{24,22,23,5,(*func_b13)},
//	
	
	{25,26,27,6,(*func_b21)},
//	{26,27,25,6,(*func_b22)},
//	{27,25,26,6,(*func_b23)},
	
	{28,29,30,7,(*func_b22)},
//	{29,30,28,7,(*func_b32)},
//	{30,28,29,7,(*func_b33)},
	
	
	{31,32,33,8,(*func_b23)},
//	{32,33,31,8,(*func_b42)},
//	{33,31,32,8,(*func_b43)},
	
};

void func_a()
{
	OLED_Display_Clear();
	OLED_Display_Buffer(0,0,"Base");	
	OLED_Display_Buffer(2,2,"Expand");
	OLED_Display_Buffer(0,13,"<--");
}

void func_b()
{
	OLED_Display_Clear();
	OLED_Display_Buffer(0,0,"base");	
	OLED_Display_Buffer(2,2,"expand");
	OLED_Display_Buffer(2,13,"<--");
}

void func_a1()
{
	OLED_Display_Clear();
  OLED_Display_Buffer(0,0,"Reset");	
	OLED_Display_Buffer(2,2,"screencircle");
	OLED_Display_Buffer(4,2,"A4circle");
	OLED_Display_Buffer(6,2,"SuperA4circle");
	OLED_Display_Buffer(2,13,"<--");
}

void func_a2()
{
	OLED_Display_Clear();
  OLED_Display_Buffer(0,0,"Reset");	
	OLED_Display_Buffer(2,2,"screencircle");
	OLED_Display_Buffer(4,2,"A4circle");
	OLED_Display_Buffer(6,2,"SuperA4circle");
	OLED_Display_Buffer(4,13,"<--");
}

void func_a3()
{
	OLED_Display_Clear();
  OLED_Display_Buffer(0,0,"Reset");	
	OLED_Display_Buffer(2,2,"screencircle");
	OLED_Display_Buffer(4,2,"A4circle");
	OLED_Display_Buffer(6,2,"SuperA4circle");
	OLED_Display_Buffer(6,13,"<--");
}

void func_a4()
{
  
}

void func_b1()
{
	OLED_Display_Clear();
  OLED_Display_Buffer(0,0,"Track");	
	OLED_Display_Buffer(2,2,"Supertrack");
	OLED_Display_Buffer(4,2,"Stop");
	OLED_Display_Buffer(0,13,"<--");
}

void func_b2()
{
	OLED_Display_Clear();
  OLED_Display_Buffer(0,0,"Track");	
	OLED_Display_Buffer(2,2,"Supertrack");
	OLED_Display_Buffer(4,2,"Stop");
	OLED_Display_Buffer(2,13,"<--");
}

void func_b3()
{
	OLED_Display_Clear();
  OLED_Display_Buffer(0,0,"Track");	
	OLED_Display_Buffer(2,2,"Supertrack");
	OLED_Display_Buffer(4,2,"Stop");
	OLED_Display_Buffer(4,13,"<--");
}

void func_b4()
{
	
}

void func_a11()
{
//  servo_init();
}

void func_a12()
{
//  screencircle();
}

void func_a13()
{
//   A4circle();
}

void func_a14()
{
//   superA4circle();
}

void func_a21()
{
//  Track();
}

void func_a22()
{
//  Supertrack();
}

void func_a23()
{
//   Stop();
}

void func_a24()
{
//   superA4circle();
}

uint16_t fuc_index=0;

void Menu_Key(void)
{
	if(Key_scan==1)
	{
		fuc_index=Menu[fuc_index].down;
	}
	if(Key_scan==2)
	{
		fuc_index=Menu[fuc_index].up;
	}
	if(Key_scan==3)
	{
		fuc_index=Menu[fuc_index].enter;
	}
	
	current_operation=Menu[fuc_index].current_operation;
		
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
  /* USER CODE BEGIN 2 */
	OLED_Init();
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
