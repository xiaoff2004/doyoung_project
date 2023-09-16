#ifndef __TM1620_H__
#define __TM1620_H__

#include "main.h"


#define DIN_HIGH HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_SET)
#define DIN_DOWN HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,GPIO_PIN_RESET)

#define SCLK_HIGH HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_SET)
#define SCLK_DOWN HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,GPIO_PIN_RESET)

void TM1620_Init(void);
void TM1620_display(uint8_t addr,uint8_t date);
void TM1620_display_add(uint8_t addr,uint8_t date);


#endif
