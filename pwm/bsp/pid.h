#ifndef __PID_H__
#define __PID_H__

#include "main.h"
#include "TB6612.h"

#define Speed_KP1 5.9  
#define Speed_KI1 1
#define Speed_KD1 0


#define Location_KP1 0.2  
#define Location_KI1 0.22
#define Location_KD1 0

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
extern volatile PID1_Info Pid1Location;

void Motor_SetDir(uint8_t dir);
void PID1_Init(volatile PID1_Info *pid,float p,float i,float d,float maxsum,float maxoutput);
void PID1_Conctrl(volatile PID1_Info *pid,volatile Encoder_Info *encoder);
void PID2_Init(volatile PID2_Info *pid,float p,float i,float d);
void PID2_Conctrl(volatile PID2_Info *pid,volatile Encoder_Info *encoder);
void PID21_Contrl(volatile PID1_Info *pidlocation,volatile PID2_Info *pidspeed,volatile Encoder_Info *encoder);

#endif
