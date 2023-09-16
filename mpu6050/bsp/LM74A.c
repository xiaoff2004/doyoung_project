#include "LM75A.h"
#include "main.h"
#include "i2c.h"



HAL_StatusTypeDef LM75A_Read(uint8_t MemAddr,uint8_t Buffer[],uint16_t Len)
{
	HAL_StatusTypeDef result=HAL_I2C_Mem_Read(&hi2c1,LM75A_ADD,MemAddr,I2C_MEMADD_SIZE_8BIT,Buffer,Len,100);
	return result;
}

void LM75A_ReadTemp(uint8_t *TempBuffer)
{
	uint8_t RXBuffer[2];
	uint8_t t=0,a=0;
	if(LM75A_Read(0x00,RXBuffer,2)==HAL_OK)
	{
		t=RXBuffer[0];
		*TempBuffer=0;
		if(t &0x80)
		{
			*TempBuffer=1;
			t=~t;
			t++;
		}
		if(t & 0x01){ a=a+1; } //从高到低按位加入温度积加值（0~125）
	if(t & 0x02){ a=a+2; }
	if(t & 0x04){ a=a+4; }
	if(t & 0x08){ a=a+8; }
	if(t & 0x10){ a=a+16; }
	if(t & 0x20){ a=a+32; }
	if(t & 0x40){ a=a+64; }
	TempBuffer++;
	*TempBuffer = a;
	a = 0;
	t = RXBuffer[1]; //处理小数部分，取0.125精度的前2位（12、25、37、50、62、75、87）
	if(t & 0x20){ a=a+12; }
	if(t & 0x40){ a=a+25; }
	if(t & 0x80){ a=a+50; }
	TempBuffer++;
	*TempBuffer = a;   
	}
}
