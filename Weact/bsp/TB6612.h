#ifndef __TB6612_H__
#define __TB6612_H__

#include "main.h"

typedef struct
{
	uint8_t State;
	float   SpeedIn;    //speedin<=16
	float   cnt;
	float   SpeedOut;
}Encoder_Info;

extern volatile Encoder_Info EncoderA;
extern volatile Encoder_Info EncoderB;


#define htim_EncoderA 	htim2
#define htim_EncoderB 	htim5
#define htim_pwm 			htim3
#define htim_IT_10 			htim4


#define Channel_PWMA TIM_CHANNEL_1
#define Channel_PWMB TIM_CHANNEL_2


void Motor_SetDir(volatile Encoder_Info *encoder,uint8_t dir);
void Motor_Init(void);
void MOtor_SetState(uint8_t State);
void Motor_Setspeed(volatile Encoder_Info* encoder,float speed);

#endif
