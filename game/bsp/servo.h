#ifndef __SERVO_H__
#define __SERVO_H__

#include "main.h"


#define servo_channel TIM_CHANNEL_2

#define htim_servox htim2
#define htim_servoy htim5

#define speedx_kp 1
#define speedx_ki 1
#define speedx_kd 1

#define speedy_kp 1
#define speedy_ki 1
#define speedy_kd 1

#define locax_kp 1
#define locax_ki 1
#define locax_kd 1

#define locay_kp 1
#define locay_ki 1
#define locay_kd 1

typedef struct
{
	uint32_t NowLocation,LastLocation;
	uint32_t SpeedIn;
	uint32_t TargeetLocation;
  uint32_t speedout;
}servo_Info;

typedef struct
{
	uint32_t kp,ki,kd;
	uint32_t err,lasterr,lastlasterr;
	uint32_t sum;
	uint32_t output,maxoutput;
}speed_Info;

typedef struct
{
	uint32_t kp,ki,kd;
	uint32_t err,lasterr;
	uint32_t sum,maxsum;
	uint32_t output,maxoutput;
}Loca_Info;

typedef struct
{
	uint32_t x0,y0;
	uint32_t x1,y1;
	uint32_t x2,y2;
	uint32_t x3,y3;
	uint32_t x4,y4;
	uint32_t x,y;
	
}rectangle_Info;

extern volatile servo_Info servox;
extern volatile servo_Info servoy;

extern volatile speed_Info speedx;
extern volatile speed_Info speedy;

extern volatile Loca_Info locax;
extern volatile Loca_Info locay;

extern volatile rectangle_Info rectangle;

void servo_init(void);
void servo_set_Loca(volatile servo_Info *x,uint32_t TargetLoca);
void servo_set_speed(volatile servo_Info *x,uint32_t speed);
void PIDloca_Init(volatile Loca_Info *pid,uint32_t p,uint32_t i,uint32_t d,uint32_t maxsum,uint32_t maxoutput);
void PIDloca_contrl(volatile Loca_Info *pid,volatile servo_Info *servo,volatile rectangle_Info *rectangle,uint8_t n);
void PIDspeed_Init(volatile speed_Info *pid,uint32_t p,uint32_t i,uint32_t d);
void PIDspeed_contrl(volatile speed_Info *pid,volatile servo_Info *servo);
void PIDlocaspeed_contrl(volatile speed_Info *speed,volatile Loca_Info *loca,volatile servo_Info *servo);


#endif
