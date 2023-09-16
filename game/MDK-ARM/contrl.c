#include "contrl.h"
#include "main.h"
#include "servo.h"
#include "oled.h"

uint32_t x[5]={0};
uint32_t  y[5]={0};
uint8_t flag=0;

uint32_t date(uint32_t a,uint32_t b)
{
	if(a>b)
		return a-b;
	else 
		return b-a;
}

uint8_t Key_scan(void)
{
	uint8_t n=0;
	if(HAL_GPIO_ReadPin(LFT_GPIO_Port,LFT_Pin)	==GPIO_PIN_RESET 
		||HAL_GPIO_ReadPin(RHT_GPIO_Port,RHT_Pin)	==GPIO_PIN_RESET  
		||HAL_GPIO_ReadPin(DWN_GPIO_Port,DWN_Pin) ==GPIO_PIN_RESET 
		||HAL_GPIO_ReadPin(UP_GPIO_Port,UP_Pin) 	==GPIO_PIN_RESET 
		||HAL_GPIO_ReadPin(RST_GPIO_Port,RST_Pin)	==GPIO_PIN_RESET  
		||HAL_GPIO_ReadPin(SET_GPIO_Port,SET_Pin)	==GPIO_PIN_RESET
		||HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)	==GPIO_PIN_RESET)
	{
		HAL_Delay(50);
		if(HAL_GPIO_ReadPin(UP_GPIO_Port,UP_Pin) 	==GPIO_PIN_RESET)
			n=1;
		else if(HAL_GPIO_ReadPin(DWN_GPIO_Port,DWN_Pin) ==GPIO_PIN_RESET)
			n=2;
		else if(HAL_GPIO_ReadPin(LFT_GPIO_Port,LFT_Pin)	==GPIO_PIN_RESET)
			n=3;
		else if(HAL_GPIO_ReadPin(RHT_GPIO_Port,RHT_Pin)	==GPIO_PIN_RESET)
			n=4;
		else if(HAL_GPIO_ReadPin(SET_GPIO_Port,SET_Pin)	==GPIO_PIN_RESET)
			n=5;
		else if(HAL_GPIO_ReadPin(RST_GPIO_Port,RST_Pin)	==GPIO_PIN_RESET)
			n=6;
		else if(HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin)	==GPIO_PIN_RESET)
			n=7;
	}

	return n;
}

void init(void)
{
	if(Key_scan()== 1)
	{
		servoy.TargeetLocation+=64;
	}
	if(Key_scan()== 2)
	{
		servoy.TargeetLocation-=64;
	}
	if(Key_scan()== 3)
	{
		servox.TargeetLocation+=64;
	}
	if(Key_scan()== 4)
	{
		servox.TargeetLocation-=64;
	}
	if(Key_scan()== 5)
	{
		for(uint8_t i=0;i<5;i++)
		{
			if(x[i]==0)
			{
				x[i]=servox.TargeetLocation;
				y[i]=servoy.TargeetLocation;
				OLED_Display_Num(4,0,i,1);
				if(i==4)
				{
					rectangle.x4=servox.TargeetLocation;
					rectangle.y4=servoy.TargeetLocation;
				
				}
			break;	
			}
		}
	}
	if(Key_scan()== 6)
	{
		lining();		
	}
if(Key_scan()==7)
{
	servox.TargeetLocation=rectangle.x4;
	servoy.TargeetLocation=rectangle.y4;
}	

}


void lining(void)
{	
	servo_set_speed(&servox,2);
	servo_set_speed(&servoy,2);
	OLED_Display_Buffer(6,0,"lining");
	for(uint8_t i=0;i<4;i++)
	{
		servox.TargeetLocation=x[i];
		servoy.TargeetLocation=y[i];
		HAL_Delay(2000);
	}
	servox.TargeetLocation=rectangle.x4;
	servoy.TargeetLocation=rectangle.y4;
	flag=1;

	
	
	
//	for(uint16_t j=0;j<51;j++)
//	{
//		servox.TargeetLocation=x[3]+(x[0]-x[3])*j/50;
//		servoy.TargeetLocation=y[3]+(y[0]-y[3])*j/50;
//		HAL_Delay(100);
//		
//	}
//	for(uint16_t j=0;j<51;j++)
//	{
//		servox.TargeetLocation=x[0]+(x[1]-x[0])*j/50;
//		servoy.TargeetLocation=y[0]+(y[1]-y[0])*j/50;
//		HAL_Delay(100);
//		
//	}
//	for(uint16_t j=0;j<51;j++)
//	{
//		servox.TargeetLocation=x[1]+(x[2]-x[1])*j/50;
//		servoy.TargeetLocation=y[1]+(y[2]-y[1])*j/50;
//		HAL_Delay(100);
//		
//	}
//	for(uint16_t j=0;j<51;j++)
//	{
//		servox.TargeetLocation=x[2]+(x[3]-x[2])*j/50;
//		servoy.TargeetLocation=y[2]+(y[3]-y[2])*j/50;
//		HAL_Delay(100);
//		
//	}

}



void rectanglelining(void)
{
	PIDloca_contrl(&locax,&servox,&rectangle,0);
	PIDloca_contrl(&locay,&servoy,&rectangle,0);
	servox.TargeetLocation+=locax.output;
	servoy.TargeetLocation+=locay.output;
	OLED_Display_Num(0,0,servox.TargeetLocation,5);
	OLED_Display_Num(2,0,servoy.TargeetLocation,5);
	
//	servox.SpeedIn=speedin/date(rectangle.y0,rectangle.y);
//	servoy.SpeedIn=speedin/date(rectangle.x0,rectangle.x);
//	HAL_Delay(5000);
//	servox.TargeetLocation+=(rectangle.x1-rectangle.x0)/ratiox;
//	servoy.TargeetLocation+=(rectangle.y1-rectangle.y0)/ratioy;
//	servox.SpeedIn=speedin/date(rectangle.y1,rectangle.y0);
//	servoy.SpeedIn=speedin/date(rectangle.x0,rectangle.x1);
//	HAL_Delay(5000);
//	servox.TargeetLocation+=(rectangle.x2-rectangle.x1)/ratiox;
//	servoy.TargeetLocation+=(rectangle.y2-rectangle.y1)/ratioy;
//	servox.SpeedIn=speedin/date(rectangle.y2,rectangle.y1);
//	servoy.SpeedIn=speedin/date(rectangle.x1,rectangle.x2);
//	HAL_Delay(5000);
//	servox.TargeetLocation+=(rectangle.x3-rectangle.x2)/ratiox;
//	servoy.TargeetLocation+=(rectangle.y3-rectangle.y2)/ratioy;
//	servox.SpeedIn=speedin/date(rectangle.y2,rectangle.y3);
//	servoy.SpeedIn=speedin/date(rectangle.x2,rectangle.x3);
//	HAL_Delay(5000);
//	servox.TargeetLocation+=(rectangle.x0-rectangle.x3)/ratiox;
//	servoy.TargeetLocation+=(rectangle.y0-rectangle.y3)/ratioy;
//	servox.SpeedIn=speedin/date(rectangle.y3,rectangle.y0);
//	servoy.SpeedIn=speedin/date(rectangle.x3,rectangle.x0);
}


