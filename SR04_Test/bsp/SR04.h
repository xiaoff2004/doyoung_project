#ifndef __SR04_H__
#define __SR04_H__

#include "main.h"

typedef struct
{
	uint16_t OverFlowNum;
	uint16_t t1;
	uint16_t t2;
	uint16_t time;
	uint8_t EdgeState;
	uint16_t Distance;
}Sound_Info;

extern volatile Sound_Info Sound;

void Sound_Init(void);
void Sound_Trig(void);


#endif
