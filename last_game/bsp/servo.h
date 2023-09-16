#ifndef __SERVO_H__
#define __SERVO_H__

#include "main.h"


#define htim_x htim2
#define htim_y htim5
#define channel_servo TIM_CHANNEL_2



void servo_init(void);
void servo_set_loca(uint8_t i,uint16_t loca);

#endif
