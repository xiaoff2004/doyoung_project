#include "pid.h"
#include "main.h"
#include "TB6612.h"


volatile PID2_Info Pid1Speed;

void PID1_Init(volatile PID1_Info *pid,float p,float i,float d,float maxsum,float maxoutput)
{
	pid->kp=p;
	pid->ki=i;
	pid->kd=d;
	pid->MaxSum=maxsum;
	pid->MaxOutput=maxoutput;
	pid->Sum=0;
	pid->Err=0;
}

void PID1_Conctrl(volatile PID1_Info *pid,volatile Encoder_Info *encoder)
{
	pid->LastErr=pid->Err;
	pid->Err=encoder->SpeedIn-encoder->SpeedOut;
	pid->Sum+=pid->Err;
	
	if(pid->Sum>pid->MaxSum)
		pid->Sum=pid->MaxSum;
	else if(pid->Sum<pid->MaxSum*-1)
		pid->Sum=pid->MaxSum*-1;
	
	pid->Output=pid->Err*pid->kp
							+pid->Sum*pid->ki
							+(pid->Err-pid->LastErr)*pid->kd;
	
	if(pid->Output>pid->MaxOutput)
		pid->Output=pid->MaxOutput;
	else if(pid->Output<pid->MaxOutput*-1)
		pid->Output=pid->MaxOutput*-1;
}

void PID2_Init(volatile PID2_Info *pid,float p,float i,float d)
{
	pid->kp=p;
	pid->ki=i;
	pid->kd=d;
	pid->LastErr=0;
	pid->LastLastErr=0;
}

void PID2_Conctrl(volatile PID2_Info *pid,volatile Encoder_Info *encoder)
{
	pid->LastLastErr=pid->LastErr;
	pid->LastErr=pid->Err;
	pid->Err=encoder->SpeedIn-encoder->SpeedOut;
	
	pid->Output=(pid->Err-pid->LastErr)*pid->kp
							+pid->Err*pid->ki
							+(pid->Err-2.0f*pid->LastErr+pid->LastLastErr)*pid->kd;
	if(pid->Output>1000)
		pid->Output=1000;
	else if(pid->Output<-1000)
		pid->Output=-1000;
}
