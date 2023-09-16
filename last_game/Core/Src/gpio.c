/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SDA_Pin|SCL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin
                           PAPin PAPin */
  GPIO_InitStruct.Pin = RST_Pin|SET_Pin|RHT_Pin|LFT_Pin
                          |DWN_Pin|UP_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(SDA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SCL_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */
uint8_t Key_Scan(void)
{
	uint8_t temp=0;
	if(HAL_GPIO_ReadPin(UP_GPIO_Port,UP_Pin)==GPIO_PIN_RESET 
	||HAL_GPIO_ReadPin(DWN_GPIO_Port,DWN_Pin)==GPIO_PIN_RESET
	||HAL_GPIO_ReadPin(LFT_GPIO_Port,LFT_Pin)==GPIO_PIN_RESET
	||HAL_GPIO_ReadPin(RHT_GPIO_Port,RHT_Pin)==GPIO_PIN_RESET
	||HAL_GPIO_ReadPin(SET_GPIO_Port,SET_Pin)==GPIO_PIN_RESET
	||HAL_GPIO_ReadPin(RST_GPIO_Port,RST_Pin)==GPIO_PIN_RESET)
	{
		HAL_Delay(25);
		if(HAL_GPIO_ReadPin(UP_GPIO_Port,UP_Pin)==GPIO_PIN_RESET)
			temp=1;
		else if(HAL_GPIO_ReadPin(DWN_GPIO_Port,DWN_Pin)==GPIO_PIN_RESET)
			temp=2;
		else if(HAL_GPIO_ReadPin(LFT_GPIO_Port,LFT_Pin)==GPIO_PIN_RESET)
			temp=3;
		else if(HAL_GPIO_ReadPin(RHT_GPIO_Port,RHT_Pin)==GPIO_PIN_RESET)
			temp=4;
		else if(HAL_GPIO_ReadPin(SET_GPIO_Port,SET_Pin)==GPIO_PIN_RESET)
			temp=5;
		else if(HAL_GPIO_ReadPin(RST_GPIO_Port,RST_Pin)==GPIO_PIN_RESET)
			temp=6;	
	}
	return temp;
}
	
/* USER CODE END 2 */
