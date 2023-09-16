#include "servo.h"
#include "main.h"
#include "tim.h"
#include "stdio.h"
#include "contrl.h"

volatile servo_Info servox;
volatile servo_Info servoy;

volatile speed_Info speedx;
volatile speed_Info speedy;

volatile Loca_Info locax;
volatile Loca_Info locay;

volatile rectangle_Info rectangle={0};

void servo_init(void)
{
	HAL_TIM_PWM_Start(&htim_servox,servo_channel);
	HAL_TIM_PWM_Start(&htim_servoy,servo_channel);
	servox.SpeedIn=5;
	servoy.SpeedIn=5;
	servox.TargeetLocation=11232;
	servoy.TargeetLocation=18936;
	__HAL_TIM_SetCompare(&htim_servox,servo_channel,servox.TargeetLocation);
	__HAL_TIM_SetCompare(&htim_servoy,servo_channel,servoy.TargeetLocation);
}

void servo_set_Loca(volatile servo_Info *servo,uint32_t TargetLoca)
{
	if(TargetLoca>25000)
		TargetLoca=25000;
	if(servo==&servox)
		servox.TargeetLocation=TargetLoca;
	else if(servo==&servoy)
		servoy.TargeetLocation=TargetLoca;	
	//(n*1000/9+5000)
}

void servo_set_speed(volatile servo_Info *x,uint32_t speed)
{
	if(speed>1000)
		speed=1000;
	if(x==&servox)
		servox.SpeedIn=speed;
	else if(x==&servoy)
		servoy.SpeedIn=speed;	
}


void PIDloca_Init(volatile Loca_Info *pid,uint32_t p,uint32_t i,uint32_t d,uint32_t maxsum,uint32_t maxoutput)
{
	pid->kp=p;
	pid->ki=i;
	pid->kd=d;
	pid->maxsum=maxsum;
	pid->maxoutput=maxoutput;
	pid->sum=0;
	pid->err=0;
}

void PIDloca_contrl(volatile Loca_Info *pid,volatile servo_Info *servo,volatile rectangle_Info *rectangle,uint8_t n)
{
	pid->lasterr=pid->lasterr;
	if(servo==&servox)
		switch(n)
		{
			case 0:pid->err=rectangle->x0-servo->speedout;
			case 1:pid->err=rectangle->x1-servo->speedout;
			case 2:pid->err=rectangle->x2-servo->speedout;
			case 3:pid->err=rectangle->x3-servo->speedout;			
		}
	if(n==0)
		pid->err=rectangle->x0-servo->speedout;
	else if(n==1)
		pid->err=rectangle->x1-servo->speedout;
	else if(n==2)
		pid->err=rectangle->x2-servo->speedout;
	else if(n==1)
		pid->err=rectangle->x1-servo->speedout;
	else if(n==2)
		pid->err=rectangle->x2-servo->speedout;
	pid->sum+=pid->err;
	if(pid->sum>pid->maxsum)
		pid->sum=pid->maxsum;
	pid->output=pid->kp*pid->err+pid->ki*pid->sum+pid->kd*(pid->err-pid->lasterr);
	if(pid->output>pid->maxoutput)
		pid->output=pid->maxoutput;

}

void PIDspeed_Init(volatile speed_Info *pid,uint32_t p,uint32_t i,uint32_t d)
{
	pid->lasterr=0;
	pid->err=0;
	pid->kp=p;
	pid->ki=i;
	pid->kd=d;
	pid->output=0;
}

void PIDspeed_contrl(volatile speed_Info *pid,volatile servo_Info *servo)
{
	pid->lastlasterr=pid->lasterr;
	pid->lasterr=pid->err;
	
	
	if(servo==&servox)
		pid->err=servo->SpeedIn-(servo->NowLocation-servo->LastLocation)/ratiox;
	else 
		pid->err=servo->SpeedIn-(servo->NowLocation-servo->LastLocation)/ratioy;
	
	
	pid->output+=pid->kp*(pid->err-pid->lasterr)-pid->ki*pid->err+pid->kd*(pid->err-2*pid->lasterr+pid->lastlasterr);
	if(pid->output>pid->maxoutput)
		pid->output=pid->maxoutput;

}

void PIDlocaspeed_contrl(volatile speed_Info *speed,volatile Loca_Info *loca,volatile servo_Info *servo)
{
	loca->lasterr=loca->lasterr;
	loca->err=servo->SpeedIn-servo->speedout;
	loca->sum+=loca->err;
	if(loca->sum>loca->maxsum)
		loca->sum=loca->maxsum;
	loca->output=loca->kp*loca->err+loca->ki*loca->sum+loca->kd*(loca->err-loca->lasterr);
	if(loca->output>loca->maxoutput)
		loca->output=loca->maxoutput;

	
	
	speed->lastlasterr=speed->lasterr;
	speed->lasterr=speed->err;
	speed->err=loca->output-servo->speedout;
	speed->output+=speed->kp*(speed->err-speed->lasterr)-speed->ki*speed->err+speed->kd*(speed->err-2*speed->lasterr+speed->lastlasterr);
	if(speed->output>speed->maxoutput)
		speed->output=speed->maxoutput;

}

