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

extern volatile Encoder_Info Encoder1;


#define htim_Encoder 	htim3
#define htim_IT 			htim2
#define htim_pwm 			htim1

#define SpeedBuff_Len 10

extern float SpeedBuff[SpeedBuff_Len];


void Motor_Init(void);
void MOtor_SetState(uint8_t State);
void Motor_Setspeed(volatile Encoder_Info* encoder,float speed);
float speed_low_Filter(float NewSpeedOut,float *RecordBuff);

#endif
