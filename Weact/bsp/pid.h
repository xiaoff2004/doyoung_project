#ifndef __PID_H__
#define __PID_H__

#include "main.h"
#include "TB6612.h"

#define SpeedA_KP1 450  
#define SpeedA_KI1 45
#define SpeedA_KD1 0


#define LocationA_KP1 1  
#define LocationA_KI1 0.8
#define LocationA_KD1 0

#define SpeedB_KP1 450  
#define SpeedB_KI1 45
#define SpeedB_KD1 0


#define LocationB_KP1 1 
#define LocationB_KI1 0.8
#define LocationB_KD1 0

#define r 2.35f

#define SpeedBuff_Len 10
#define d_dir_date 25



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


extern volatile PID2_Info PidASpeed;
extern volatile PID1_Info PidALocation;

extern volatile PID2_Info PidBSpeed;
extern volatile PID1_Info PidBLocation;

extern volatile uint8_t dir_flag,dir_state;
extern volatile float dir_date;
extern volatile float SpeedBuffA[SpeedBuff_Len];
extern volatile float SpeedBuffB[SpeedBuff_Len];


void PID1_Init(volatile PID1_Info *pid,float p,float i,float d,float maxsum,float maxoutput);
void PID1_Conctrl(volatile PID1_Info *pid,volatile Encoder_Info *encoder);
void PID2_Init(volatile PID2_Info *pid,float p,float i,float d);
void PID2_Conctrl(volatile PID2_Info *pid,volatile Encoder_Info *encoder);
void PID21_Contrl(volatile PID1_Info *pidlocation,volatile PID2_Info *pidspeed,volatile Encoder_Info *encoder);
float speed_low_Filter(volatile float NewSpeedOut,volatile float *RecordBuff);
void LineWalking(volatile Encoder_Info *encoderA,volatile Encoder_Info *encoderB);

#endif
