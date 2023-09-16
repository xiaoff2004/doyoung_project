#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "main.h"


extern uint8_t step;

void Motor_Stop(void);
void Motor_Step8(uint8_t n,uint16_t speed);
void Motor_Num(uint8_t dir,uint16_t num,uint16_t speed);
void Motor_Loop(uint8_t dir,uint16_t loop,uint16_t speed);

#endif
