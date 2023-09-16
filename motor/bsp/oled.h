#ifndef __OLED_H__
#define __OLED_H__

#include "main.h"


#define OLED0561_ADD	    0x78  // OLED��I2C��ַ����ֹ�޸ģ�
#define CMD				0x00  // OLED ָ���ֹ�޸ģ�
#define DAT 			    0x40  // OLED ���ݣ���ֹ�޸ģ�



void OLED_Init(void);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Display_light(uint8_t n);
void OLED_Display_Clear(void);
void OLED_Display_8x16(uint8_t x,uint8_t y,uint16_t date);
void OLED_Display_Buffer_8x16(uint8_t x,uint8_t y,uint8_t *buff);
void OLED_Display_Num(uint8_t x,uint8_t y,uint16_t w,uint8_t len);

#endif
