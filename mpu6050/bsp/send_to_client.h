#ifndef __SEND_TO_CLIENT_H

#define __SEND_TO_CLIENT_H

#include "stm32f1xx.h"
#include "usart.h"
#include "main.h"

void usart_send_char(uint8_t c);
void usart_niming_report(uint8_t fun,uint8_t*data,uint8_t len);
void mpu6050_send_data(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz);
void usart_report_imu(short aacx,short aacy,short aacz,short gyrox,short gyroy,short gyroz,float roll_f,float pitch_f,float yaw_f);


#endif
