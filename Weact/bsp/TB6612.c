#include "TB6612.h"
#include "main.h"
#include "gpio.h"
#include "tim.h"

volatile Encoder_Info EncoderA;
volatile Encoder_Info EncoderB;

void Motor_SetDir(volatile Encoder_Info *encoder,uint8_t dir)
{
	if(encoder==&EncoderA)
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
	else if(encoder==&EncoderB)
	{
		if(dir==1)
		{
			HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_SET);
		}
		else 
		{
			HAL_GPIO_WritePin(BIN1_GPIO_Port,BIN1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(BIN2_GPIO_Port,BIN2_Pin,GPIO_PIN_RESET);
		}
	}
}

void Motor_Init(void)
{	
	HAL_TIM_Base_Init(&htim_pwm);
	HAL_TIM_PWM_Init(&htim_pwm);
	HAL_TIM_PWM_Start(&htim_pwm,Channel_PWMA);
	HAL_TIM_PWM_Start(&htim_pwm,Channel_PWMB);
	Encoder_Info EncoderA ={0};
	Encoder_Info EncoderB ={0};	
	HAL_TIM_Encoder_Start(&htim_EncoderA,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim_EncoderA,TIM_CHANNEL_2);
	HAL_TIM_Encoder_Start(&htim_EncoderB,TIM_CHANNEL_1);
	HAL_TIM_Encoder_Start(&htim_EncoderB,TIM_CHANNEL_2);
	HAL_TIM_Base_Start_IT(&htim_IT_10);
	__HAL_TIM_SET_COMPARE(&htim_pwm,Channel_PWMA,EncoderA.SpeedIn);
	__HAL_TIM_SET_COMPARE(&htim_pwm,Channel_PWMB,EncoderB.SpeedIn);
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
		Motor_SetDir(encoder,1);
		Tempspeed=(uint32_t)-speed;
	}
	
	else 
		{
			Motor_SetDir(encoder,0);
			Tempspeed=(uint32_t)speed;
		}
	if(Tempspeed>1000)
		Tempspeed=1000;
	if(encoder==&EncoderA)	
		__HAL_TIM_SET_COMPARE(&htim_pwm,Channel_PWMA,Tempspeed);
	else if(encoder==&EncoderB)
		__HAL_TIM_SET_COMPARE(&htim_pwm,Channel_PWMB,Tempspeed);	
}

