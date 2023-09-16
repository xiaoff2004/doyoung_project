#include "TM1620.h"
#include "main.h"
#include "gpio.h"


const uint8_t buff[21]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0x00};//����0~9��0~9�ӵ���ʾ�����
    //---------------   0    1    2    3    4    5    6    7    8    9    0.   1.   2.   3.   4.   5.   6.   7.   8.   9.   ��   

void delay_us(uint32_t uS)
{ 								//uS΢�뼶��ʱ���򣨲ο�ֵ������ʱ����72MHzʱ���ֵ233015��	
	SysTick->LOAD=72*uS;      //��װ������ֵ������Ƶ��72MHz��72��Ϊ1΢�룩
	SysTick->VAL=0x00;        //��ն�ʱ���ļ�����
	SysTick->CTRL=0x00000005;//ʱ��ԴHCLK���򿪶�ʱ��
	while(!(SysTick->CTRL&0x00010000)); //�ȴ�������0
	SysTick->CTRL=0x00000004;//�رն�ʱ��
}

	
void TM1620_Start(void)
{
	SCLK_HIGH;
	DIN_HIGH;
	delay_us(2);
	DIN_DOWN;
	delay_us(2);
	SCLK_DOWN;
	delay_us(2);
}

void TM1620_Write(uint8_t date)
{
	uint8_t i;
	for(i=0;i<8;i++)
	{
		SCLK_DOWN;
		delay_us(5);
		if((date>>i) & 0x01)
			DIN_HIGH;
		else 
			DIN_DOWN;
		delay_us(5);
		SCLK_HIGH;
		delay_us(5);
	}
	SCLK_DOWN;
	DIN_DOWN;
}

void TM1620_Stop(void)
{
	DIN_DOWN;
	SCLK_HIGH;
	delay_us(2);
	DIN_HIGH;
	delay_us(2);
}

void TM1620_Command(uint8_t date)
{
	TM1620_Start();
	TM1620_Write(date);
	TM1620_Stop();
}



void TM1620_Init(void)
{
	TM1620_Command(0x40);//�������ݣ�0x40,0x44�ֱ��Ӧ��ַ�Զ���һ�͹̶���ַģʽ
	TM1620_Command(0x8d);//���ȿ�����ʾ������ʾ��0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f�ֱ��Ӧ������Ϊ:
					 			//-------------------1/16,  2/16,  4/16,  10/16, 11/16, 12/16, 13/16, 14/16	 //0x80��
}

void TM1620_display(uint8_t addr,uint8_t date)
{
	TM1620_Start();
	TM1620_Write(0xc0+addr);
	TM1620_Write(buff[date]);
	TM1620_Stop();
}

void TM1620_display_add(uint8_t addr,uint8_t date)
{
	TM1620_Start();
	TM1620_Write(0xc0+addr);
	for(uint8_t i=0;i<16;i++)
		TM1620_Write(buff[date]);
	TM1620_Stop();
}
