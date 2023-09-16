#ifndef __PID_H__
#define __PID_H__

#include "main.h"
#include "TB6612.h"

#define KP1 0
#define KI1 0
#define KD1 0

typedef struct
{
	float kp,ki,kd;
	float Err,LastErr;
	float Sum,MaxSum;
	float Output,MaxOutput;
}PID1_Info;

typedef struct
{
	float kp,ki,kd;
	float Err,LastErr,LastLastErr;
	float Output;
}PID2_Info;

extern volatile PID2_Info Pid1Speed;

void Motor_SetDir(uint8_t dir);
void PID1_Init(volatile PID1_Info *pid,float p,float i,float d,float maxsum,float maxoutput);
void PID1_Conctrl(volatile PID1_Info *pid,volatile Encoder_Info *encoder);
void PID2_Init(volatile PID2_Info *pid,float p,float i,float d);
void PID2_Conctrl(volatile PID2_Info *pid,volatile Encoder_Info *encoder);

#endif
