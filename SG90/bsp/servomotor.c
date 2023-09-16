#include "servomotor.h"
#include "main.h"
#include "tim.h"

void Servomotor_Init(void)
{
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
}
void Servomotor(uint16_t angle)
{
	float temp= angle*10/9+50;
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,(uint16_t)temp);
}
