#include "servo.h"
#include "main.h"
#include "tim.h"


void servo_init(void)
{
	HAL_TIM_PWM_Start(&htim_x,channel_servo);
	HAL_TIM_PWM_Start(&htim_y,channel_servo);
	__HAL_TIM_SetCompare(&htim_x,channel_servo,10000);
	__HAL_TIM_SetCompare(&htim_y,channel_servo,10000);
}

void servo_set_loca(uint8_t i,uint16_t loca)
{
	if(loca>=25000)
		loca=25000;
	else 
		if(i==0)
		 __HAL_TIM_SetCompare(&htim_x,channel_servo,loca);
		else 
			__HAL_TIM_SetCompare(&htim_y,channel_servo,loca);
}

