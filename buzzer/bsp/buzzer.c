#include "main.h"
#include "buzzer.h"
#include "gpio.h"
#include "tim.h"


void BuzzerOpen(void)
{
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET);
}


void BuzzerClose(void)
{
	HAL_TIM_PWM_Stop(&htim3,TIM_CHANNEL_2);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
}

void BuzzerChangeFreqen(uint32_t ARR)
{
	TIM3->ARR=ARR-1;
	TIM3->CCR2=(ARR/2-1);
}
