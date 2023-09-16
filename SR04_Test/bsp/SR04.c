#include "SR04.h"
#include "tim.h"
#include "delay.h"
#include "gpio.h"

volatile Sound_Info Sound={0};

void Sound_Init(void)
{
	HAL_TIM_Base_Init(&htim1);
	HAL_TIM_IC_Start(&htim1,TIM_CHANNEL_2);
}

void Sound_Trig(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_SET);
	delay_us(15);
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_10,GPIO_PIN_RESET);
}

