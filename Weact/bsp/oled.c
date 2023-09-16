#include "oled.h"
#include "main.h"
#include "ASCII_8x16.h"
#include "softiic.h"
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
//	uint8_t buff[28]={
//	,//0xae:����ʾ��0xaf:����ʾ
//    ,,//��ʼ��ַ��˫�ֽڣ�       
//	,,//��ʾʱ��Ƶ�ʣ�
//	,,//�����ʣ�
//	,,//��ʾƫ�ƣ�
//	,//д��ҳλ�ã�0xB0~7��
//	,//��ʾ��ʼ��
//	,,//VCC��Դ
//	,//���ö�����ӳ�䣿
//	,//COM�����ʽ��
//	,,//COM�����ʽ��
//	,,//�Աȶȣ�ָ�0x81�����ݣ�0~255��255��ߣ�
//	,,//������ڣ�
//	,,//VCC��ѹ���
//	,,//ˮƽѰַ����
//	,//0xa4:������ʾ��0xa5:�������
//	,//0xa6:������ʾ��0xa7:��ɫ��ʾ
//	//0xae:����ʾ��0xaf:����ʾ
//	}; //
	IIC_WriteData(OLED0561_ADD,CMD,0xae);
	IIC_WriteData(OLED0561_ADD,CMD,0x00);
	IIC_WriteData(OLED0561_ADD,CMD,0x10);
	IIC_WriteData(OLED0561_ADD,CMD,0xd5);
	IIC_WriteData(OLED0561_ADD,CMD,0x80);
	IIC_WriteData(OLED0561_ADD,CMD,0xa8);
	IIC_WriteData(OLED0561_ADD,CMD,0x3f);
	IIC_WriteData(OLED0561_ADD,CMD,0xd3);
	IIC_WriteData(OLED0561_ADD,CMD,0x00);
	IIC_WriteData(OLED0561_ADD,CMD,0XB0);
	IIC_WriteData(OLED0561_ADD,CMD,0x40);
	IIC_WriteData(OLED0561_ADD,CMD,0x8d);
	IIC_WriteData(OLED0561_ADD,CMD,0x14);
	IIC_WriteData(OLED0561_ADD,CMD,0xa1);
	IIC_WriteData(OLED0561_ADD,CMD,0xc8);
	IIC_WriteData(OLED0561_ADD,CMD,0xda);
	IIC_WriteData(OLED0561_ADD,CMD,0x12);
	IIC_WriteData(OLED0561_ADD,CMD,0x81);
	IIC_WriteData(OLED0561_ADD,CMD,0xff);
	IIC_WriteData(OLED0561_ADD,CMD,0xd9);
	IIC_WriteData(OLED0561_ADD,CMD,0xf1);
	IIC_WriteData(OLED0561_ADD,CMD,0xdb);
	IIC_WriteData(OLED0561_ADD,CMD,0x30);
	IIC_WriteData(OLED0561_ADD,CMD,0x20);
	IIC_WriteData(OLED0561_ADD,CMD,0x00);
	IIC_WriteData(OLED0561_ADD,CMD,0xa4);
	IIC_WriteData(OLED0561_ADD,CMD,0xa6);
	IIC_WriteData(OLED0561_ADD,CMD,0xaf);
}

void OLED_Display_Off(void)
{
//	uint8_t buff[3]={,//0xae:����ʾ��0xaf:����ʾ
//					,};//VCC��Դ		
	IIC_WriteData(OLED0561_ADD,CMD,0xae);
	IIC_WriteData(OLED0561_ADD,CMD,0x8d);
	IIC_WriteData(OLED0561_ADD,CMD,0x10);					
}

void OLED_Display_light(uint8_t n)      // 0<n<255
{

	IIC_WriteData(OLED0561_ADD,CMD,0x81);
	IIC_WriteData(OLED0561_ADD,CMD,n);
}

void OLED_Display_Clear(void)
{
	uint8_t j,t;
	for(t=0xB0;t<0xB8;t++)
	{
		IIC_WriteData(OLED0561_ADD,CMD,t);
		IIC_WriteData(OLED0561_ADD,CMD,0x10);
		IIC_WriteData(OLED0561_ADD,CMD,0x00);
		for(j=0;j<132;j++)
		{	
			IIC_WriteData(OLED0561_ADD,DAT,0x00);
 		}
	}
}

void OLED_Display(uint8_t x,uint8_t y,uint16_t w)
{
	uint8_t j,t,c=0;
	y=y+2; 
	for(t=0;t<2;t++)
	{
		IIC_WriteData(OLED0561_ADD,CMD,0xb0+x);
		IIC_WriteData(OLED0561_ADD,CMD,y/16+0x10);
		IIC_WriteData(OLED0561_ADD,CMD,y%16);
		for(j=0;j<8;j++)
		{ 
			IIC_WriteData(OLED0561_ADD,DAT,ASCII_8x16[(w*16)+c-512]);
			c++;}x++; 
	}
}



void OLED_Display_Buffer(uint8_t x,uint8_t y,uint8_t *buff)
{
	uint8_t i=0;
	while(*buff !='\0')
	{
		OLED_Display(x,(y+i)*8,*buff++);
		i++;
	}
}

//OLED_Display_Buffer_8x16(2,2,"Now Temp");


void OLED_Display_Num(uint8_t x,uint8_t y,uint16_t w,uint8_t len)
{
	uint16_t temp=w;
	for(uint8_t i=0;i<len;i++)
	{
		OLED_Display(x,(y+len-1-i)*8,temp%10+'0');
		temp=temp/10;
	}
}
