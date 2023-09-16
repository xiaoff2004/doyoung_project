#ifndef __CONTRL_H__
#define __CONTRL_H__

#include "main.h"

#define ratiox 19
#define ratioy 25

extern uint32_t x[5];
extern uint32_t y[5];
extern uint8_t flag;

#define speedin 256


uint8_t Key_scan(void);
void init(void);
void reset(void);
void lining(void);
void rectanglelining(void);
void redLoca_init(void);
void rectanglelining(void);



#endif

