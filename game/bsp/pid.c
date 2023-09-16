#include "pid.h"
#include "main.h"
#include "TB6612.h"
#include "gpio.h"
#include "oled.h"
#include "mpu6050.h"
#include "stdio.h"

volatile PID2_Info PidASpeed;
volatile PID1_Info PidALocation;
volatile PID2_Info PidBSpeed;
volatile PID1_Info PidBLocation;
volatile uint8_t dir_flag=0,dir_state=0;
volatile float dir_date=0;


volatile float SpeedBuffA[SpeedBuff_Len]={0};
volatile float SpeedBuffB[SpeedBuff_Len]={0};
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
	pid->Output=0;
}

void PID2_Conctrl(volatile PID2_Info *pid,volatile Encoder_Info *encoder)
{
	pid->LastLastErr=pid->LastErr;
	pid->LastErr=pid->Err;
	pid->Err=encoder->SpeedIn-encoder->SpeedOut;
	
	pid->Output+=((pid->Err-pid->LastErr)*pid->kp
							+pid->Err*pid->ki
							+(pid->Err-2.0f*pid->LastErr+pid->LastLastErr)*pid->kd);
	if(pid->Output>1000)
		pid->Output=1000;
	else if(pid->Output<-1000)
		pid->Output=-1000;
}

void PID21_Contrl(volatile PID1_Info *pidlocation,volatile PID2_Info *pidspeed,volatile Encoder_Info *encoder)
{
	pidlocation->LastErr=pidlocation->Err;
	pidlocation->Err=encoder->SpeedIn-encoder->SpeedOut;
	pidlocation->Sum+=pidlocation->Err;
	if(pidlocation->Sum>=pidlocation->MaxSum)
		pidlocation->Sum=pidlocation->MaxSum;
	
	pidlocation->Output=pidlocation->kp*pidlocation->Err
											+pidlocation->ki*pidlocation->Sum
											+pidlocation->kd*(pidlocation->Err-pidlocation->LastErr);
//	encoder->SpeedIn-=encoder->SpeedOut*r*0.01f;
	if(pidlocation->Output>=pidlocation->MaxOutput)
		pidlocation->Output=pidlocation->MaxOutput;
	else if(pidlocation->Output<=-pidlocation->MaxOutput)
		pidlocation->Output=-pidlocation->MaxOutput;
	pidspeed->LastLastErr=pidspeed->LastErr;
	pidspeed->LastErr=pidspeed->Err;
	pidspeed->Err=pidlocation->Output-encoder->SpeedOut;
	pidspeed->Output+=((pidspeed->Err-pidspeed->LastErr)*pidspeed->kp
							+pidspeed->Err*pidspeed->ki
							+(pidspeed->Err-2.0f*pidspeed->LastErr+pidspeed->LastLastErr)*pidspeed->kd);
	if(pidspeed->Output>500)
		pidspeed->Output=500;
	else if(pidspeed->Output<-500)
		pidspeed->Output=-500;
}

float speed_low_Filter(volatile float NewSpeedOut,volatile float *RecordBuff)
{
	float sum=0.0f;
	for(uint8_t i=SpeedBuff_Len;i>0;i--)
	{
		RecordBuff[i]=RecordBuff[i-1];
		sum+=RecordBuff[i-1];
	}
	RecordBuff[SpeedBuff_Len]=NewSpeedOut;
	sum+=NewSpeedOut;
	return sum/SpeedBuff_Len;
}



void LineWalking(volatile Encoder_Info *encoderA,volatile Encoder_Info *encoderB)
{
	if(dir_state==1 )
	{
		float temp_dir_date=0,d_temp_dir_date=0;
		if(mpu_dmp_get_data(0,0,&temp_dir_date)==0){printf("%f",temp_dir_date);}		
		d_temp_dir_date=temp_dir_date-dir_date;
			
			
		if(d_temp_dir_date<0)
				{
					d_temp_dir_date=-d_temp_dir_date;
				}
				
				
		if(dir_flag==1 || dir_flag==2)
				{
					if(d_temp_dir_date<=90.0f+d_dir_date && d_temp_dir_date >=90.0f -d_dir_date)
							{dir_date=0;}
				}
		else if(dir_flag==3)
				{
					if(d_temp_dir_date<=180.0f+2.0f*d_dir_date && d_temp_dir_date >=180.0f -2.0f*d_dir_date)
					   {dir_date=0;}					
				}
		
	}	
	
	uint16_t Line[4];
	Line[0]=!HAL_GPIO_ReadPin(SW2_GPIO_Port,SW2_Pin);
	Line[1]=!HAL_GPIO_ReadPin(SW1_GPIO_Port,SW1_Pin);
	Line[2]=!HAL_GPIO_ReadPin(SW3_GPIO_Port,SW3_Pin);
	Line[3]=!HAL_GPIO_ReadPin(SW4_GPIO_Port,SW4_Pin);
	uint16_t temp=(uint16_t)Line[0]*8+(uint16_t)Line[1]*4+(uint16_t)Line[2]*2+(uint16_t)Line[3];
	
			 if(temp==6)  {encoderA->SpeedIn=encoderA->TargetSpeedIn;encoderB->SpeedIn=encoderB->TargetSpeedIn;dir_state=0;} //0110
	else if(temp==15) {if(dir_flag==0){encoderA->SpeedIn=encoderA->TargetSpeedIn*0.0f;encoderB->SpeedIn=encoderB->TargetSpeedIn*0.0f;dir_state=1;if(mpu_dmp_get_data(0,0,&dir_date)==0){printf("%f",dir_date);}}
											else	if(dir_flag==1){encoderA->SpeedIn=encoderA->TargetSpeedIn*0.0f;encoderB->SpeedIn=encoderB->TargetSpeedIn*1.0f;dir_state=1;if(mpu_dmp_get_data(0,0,&dir_date)==0){printf("%f",dir_date);}}
											else	if(dir_flag==2){encoderA->SpeedIn=encoderA->TargetSpeedIn*1.0f;encoderB->SpeedIn=encoderB->TargetSpeedIn*0.0f;dir_state=1;if(mpu_dmp_get_data(0,0,&dir_date)==0){printf("%f",dir_date);}}
											else	if(dir_flag==3){encoderA->SpeedIn=encoderA->TargetSpeedIn*1.0f;encoderB->SpeedIn=encoderB->TargetSpeedIn*-1.0f;dir_state=1;if(mpu_dmp_get_data(0,0,&dir_date)==0){printf("%f",dir_date);}}} //1111
	else if(temp==0  && dir_state==0)  {encoderA->SpeedIn=encoderA->TargetSpeedIn;encoderB->SpeedIn=encoderB->TargetSpeedIn;} //0000
	
		
	else if(temp==1  && dir_state==0)  {encoderA->SpeedIn=encoderA->TargetSpeedIn;encoderB->SpeedIn=encoderB->TargetSpeedIn*0.3f;} //0001
	else if(temp==2  && dir_state==0)  {encoderA->SpeedIn=encoderA->TargetSpeedIn;encoderB->SpeedIn=encoderB->TargetSpeedIn*0.5f;} //0010
	else if(temp==3  && dir_state==0)  {encoderA->SpeedIn=encoderA->TargetSpeedIn;encoderB->SpeedIn=encoderB->TargetSpeedIn*0.5f;} //0011
	else if(temp==7  && dir_state==0)  {encoderA->SpeedIn=encoderA->TargetSpeedIn;encoderB->SpeedIn=encoderB->TargetSpeedIn*0.0f;} //0111
	
	else if(temp==4  && dir_state==0)  {encoderA->SpeedIn=encoderA->TargetSpeedIn*0.5f;encoderB->SpeedIn=encoderB->TargetSpeedIn;}  //0100
	else if(temp==8  && dir_state==0)  {encoderA->SpeedIn=encoderA->TargetSpeedIn*0.3f;encoderB->SpeedIn=encoderB->TargetSpeedIn;}  //1000
	else if(temp==12 && dir_state==0)	 {encoderA->SpeedIn=encoderA->TargetSpeedIn*0.5f;encoderB->SpeedIn=encoderB->TargetSpeedIn;}  //1100
	else if(temp==14 && dir_state==0)  {encoderA->SpeedIn=encoderA->TargetSpeedIn*0.0f;encoderB->SpeedIn=encoderB->TargetSpeedIn;} //1110


		
	
}

