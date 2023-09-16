#include "TM1620.h"
#include "main.h"
#include "gpio.h"


const uint8_t buff[21]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0x00};//数字0~9及0~9加点显示段码表
    //---------------   0    1    2    3    4    5    6    7    8    9    0.   1.   2.   3.   4.   5.   6.   7.   8.   9.   无   

void delay_us(uint32_t uS)
{ 								//uS微秒级延时程序（参考值即是延时数，72MHz时最大值233015）	
	SysTick->LOAD=72*uS;      //重装计数初值（当主频是72MHz，72次为1微秒）
	SysTick->VAL=0x00;        //清空定时器的计数器
	SysTick->CTRL=0x00000005;//时钟源HCLK，打开定时器
	while(!(SysTick->CTRL&0x00010000)); //等待计数到0
	SysTick->CTRL=0x00000004;//关闭定时器
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
	TM1620_Command(0x40);//设置数据，0x40,0x44分别对应地址自动加一和固定地址模式
	TM1620_Command(0x8d);//亮度控制显示，开显示，0x88,  0x89,  0x8a,  0x8b,  0x8c,  0x8d,  0x8e,  0x8f分别对应脉冲宽度为:
					 			//-------------------1/16,  2/16,  4/16,  10/16, 11/16, 12/16, 13/16, 14/16	 //0x80关
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
