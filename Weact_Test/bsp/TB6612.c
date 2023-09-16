#include "TB6612.h"
#include "main.h"
#include "gpio.h"
#include "tim.h"

volatile Encoder_Info EncoderA,EncoderB;

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
	HAL_TIM_PWM_Start(&htim_pwm,channel_PWMA);
	HAL_TIM_PWM_Start(&htim_pwm,channel_PWMB);
	Encoder_Info EncoderA ={0};
	Encoder_Info EncoderB ={0};
	
	__HAL_TIM_SET_COMPARE(&htim_EncoderA,TIM_CHANNEL_1,EncoderA.SpeedIn);
	HAL_TIM_Encoder_Start(&htim_EncoderA,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim_EncoderA,TIM_CHANNEL_2);
	
	
	__HAL_TIM_SET_COMPARE(&htim_EncoderA,TIM_CHANNEL_1,EncoderB.SpeedIn);
	HAL_TIM_Encoder_Start(&htim_EncoderA,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim_EncoderA,TIM_CHANNEL_2);
	
	
	HAL_TIM_Base_Start_IT(&htim_IT_5);
	HAL_TIM_Base_Start_IT(&htim_IT_10);
}

void Motor_SetState(uint8_t State)
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
	
	if(encoder==&EncoderA)		
		__HAL_TIM_SET_COMPARE(&htim_pwm,channel_PWMA,speed);
	else if(encoder==&EncoderB)		
		__HAL_TIM_SET_COMPARE(&htim_pwm,channel_PWMB,speed);
	
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
