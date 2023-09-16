#include "oled.h"
#include "main.h"
#include "ASCII_8x16.h"
#include "i2c.h"
#include "stdio.h"

void OLED_Init(void)
{
	OLED_Display_Off();
	OLED_Display_Clear();
	OLED_Display_On();
	OLED_Display_Clear();
}

void OLED_Display_On(void)
{
	uint8_t buff[28]={
	0xae,//0xae:关显示，0xaf:开显示
    0x00,0x10,//开始地址（双字节）       
	0xd5,0x80,//显示时钟频率？
	0xa8,0x3f,//复用率？
	0xd3,0x00,//显示偏移？
	0XB0,//写入页位置（0xB0~7）
	0x40,//显示开始线
	0x8d,0x14,//VCC电源
	0xa1,//设置段重新映射？
	0xc8,//COM输出方式？
	0xda,0x12,//COM输出方式？
	0x81,0xff,//对比度，指令：0x81，数据：0~255（255最高）
	0xd9,0xf1,//充电周期？
	0xdb,0x30,//VCC电压输出
	0x20,0x00,//水平寻址设置
	0xa4,//0xa4:正常显示，0xa5:整体点亮
	0xa6,//0xa6:正常显示，0xa7:反色显示
	0xaf//0xae:关显示，0xaf:开显示
	}; //
	HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,CMD,I2C_MEMADD_SIZE_8BIT,buff,28,1000);
}

void OLED_Display_Off(void)
{
	uint8_t buff[3]={0xae,//0xae:关显示，0xaf:开显示
					0x8d,0x10};//VCC电源				
	HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,CMD,I2C_MEMADD_SIZE_8BIT,buff,3,1000);
}

void OLED_Display_light(uint8_t n)      // 0<n<255
{
	uint8_t buff={0x81};
	HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,CMD,I2C_MEMADD_SIZE_8BIT,&buff,1,1000);
	HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,CMD,I2C_MEMADD_SIZE_8BIT,&n,1,1000);
}

void OLED_Display_Clear(void)
{
	uint8_t j,t;
	uint8_t buf[2]={0x10,0x00};
	for(t=0xB0;t<0xB8;t++)
	{
		HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,CMD,I2C_MEMADD_SIZE_8BIT,&t,1,1000); 	
		HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,CMD,I2C_MEMADD_SIZE_8BIT,&buf[0],1,1000);
		HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,CMD,I2C_MEMADD_SIZE_8BIT,&buf[1],1,1000);
		for(j=0;j<132;j++)
		{	
			HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,DAT,I2C_MEMADD_SIZE_8BIT,&buf[1],1,1000);
 		}
	}
}

void OLED_Display_8x16(uint8_t x,uint8_t y,uint16_t w)
{
	uint8_t j,t,c=0;
	uint8_t buf[4];
	y=y+2; 
	for(t=0;t<2;t++)
	{
		buf[0]=0xb0+x; buf[1]=y/16+0x10; buf[2]=y%16;
		HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,CMD,I2C_MEMADD_SIZE_8BIT,&buf[0],1,1000); 
		HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,CMD,I2C_MEMADD_SIZE_8BIT,&buf[1],1,1000); 
		HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,CMD,I2C_MEMADD_SIZE_8BIT,&buf[2],1,1000);	
		for(j=0;j<8;j++)
		{ 
			buf[3]=ASCII_8x16[(w*16)+c-512];
			HAL_I2C_Mem_Write(&hi2c1,OLED0561_ADD,DAT,I2C_MEMADD_SIZE_8BIT,&buf[3],1,1000);
			c++;}x++; 
	}
}



void OLED_Display_Buffer_8x16(uint8_t x,uint8_t y,uint8_t *buff)
{
	uint8_t i=0;
	while(*buff !='\0')
	{
		OLED_Display_8x16(x,(y+i)*8,*buff++);
		i++;
	}
}

//OLED_Display_Buffer_8x16(2,2,"Now Temp");


void OLED_Display_Num(uint8_t x,uint8_t y,uint16_t w,uint8_t len)
{
	uint16_t temp=w;
	for(uint8_t i=0;i<len;i++)
	{
		OLED_Display_8x16(x,(y+len-1-i)*8,temp%10+'0');
		temp=temp/10;
	}
}
