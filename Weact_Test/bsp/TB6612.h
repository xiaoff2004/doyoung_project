#ifndef __TB6612_H__
#define __TB6612_H__

#include "main.h"

typedef struct
{
	uint8_t State;
	float SpeedIn;
	int16_t cnt;
	float SpeedOut;
}Encoder_Info;

extern volatile Encoder_Info EncoderA,EncoderB;


#define htim_EncoderA 			htim1
#define htim_EncoderB 			htim2
#define htim_IT_5 					htim9
#define htim_IT_10 				htim4
#define htim_pwm 					htim5
#define SpeedBuff_Len 10
#define channel_PWMA 			TIM_CHANNEL_1
#define channel_PWMB 			TIM_CHANNEL_2

extern float SpeedBuff[SpeedBuff_Len];


void Motor_Init(void);
void Motor_SetState(uint8_t State);
void Motor_Setspeed(volatile Encoder_Info* encoder,float speed);
float speed_low_Filter(float NewSpeedOut,float *RecordBuff);

#endif
