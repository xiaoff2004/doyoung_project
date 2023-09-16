#include "TB6612.h"
#include "main.h"
#include "gpio.h"
#include "tim.h"

volatile Encoder_Info Encoder1;
float SpeedBuff[SpeedBuff_Len]={0};

void Motor_SetDir(uint8_t dir)
{
	if(dir==1)
	{
	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_SET);	
	}
	else
	{
	HAL_GPIO_WritePin(AIN1_GPIO_Port,AIN1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(AIN2_GPIO_Port,AIN2_Pin,GPIO_PIN_RESET);	
	}
}

void Motor_Init(void)
{	
	HAL_TIM_Base_Init(&htim_pwm);
	HAL_TIM_PWM_Init(&htim_pwm);
	HAL_TIM_PWM_Start(&htim_pwm,TIM_CHANNEL_1);
	Encoder_Info Encoder1 ={0};
	__HAL_TIM_SET_COMPARE(&htim_Encoder,TIM_CHANNEL_1,Encoder1.SpeedIn);
	HAL_TIM_Encoder_Start(&htim_Encoder,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim_Encoder,TIM_CHANNEL_2);
	HAL_TIM_Base_Start_IT(&htim_IT);
	
}

void MOtor_SetState(uint8_t State)
{
	if(State==1)
		HAL_GPIO_WritePin(STBY_GPIO_Port,STBY_Pin,GPIO_PIN_SET);
	else 
		HAL_GPIO_WritePin(STBY_GPIO_Port,STBY_Pin,GPIO_PIN_RESET);
}

//0是正转，1是反转
//
void Motor_Setspeed(volatile Encoder_Info* encoder,float speed)
{
	uint16_t Tempspeed;
	if(speed<0)
	{
		Motor_SetDir(0);
		Tempspeed=(uint16_t)-speed;
	}
	
	else 
		{
			Motor_SetDir(1);
			Tempspeed=(uint16_t)speed;
		}
	if(Tempspeed>1000)
		speed=1000;	
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,speed);
	
}

float speed_low_Filter(float NewSpeedOut,float *RecordBuff)
{
	float sum=0.0f;
	for(uint8_t i=SpeedBuff_Len;i>0;i--)
	{
		RecordBuff[i]=SpeedBuff[i-1];
		sum+=RecordBuff[i-1];
	}
	RecordBuff[SpeedBuff_Len]=NewSpeedOut;
	sum+=NewSpeedOut;
	return sum/SpeedBuff_Len;
}
