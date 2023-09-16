#include "motor.h"
#include "main.h"
#include "gpio.h"


uint8_t step;

void delay_us(uint32_t uS){ //uS微秒级延时程序（参考值即是延时数，72MHz时最大值233015）	
	SysTick->LOAD=72*uS;      //重装计数初值（当主频是72MHz，72次为1微秒）
	SysTick->VAL=0x00;        //清空定时器的计数器
	SysTick->CTRL=0x00000005;//时钟源HCLK，打开定时器
	while(!(SysTick->CTRL&0x00010000)); //等待计数到0
	SysTick->CTRL=0x00000004;//关闭定时器
}

void Motor_Stop(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_8|GPIO_PIN_9,GPIO_PIN_RESET);
}	

void Motor_Step8(uint8_t n,uint16_t speed)
{
	switch(n)
	{
		case 0:
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4|GPIO_PIN_8|GPIO_PIN_9,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_SET);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8|GPIO_PIN_9,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_4,GPIO_PIN_SET);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_8|GPIO_PIN_9,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_9,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4|GPIO_PIN_8,GPIO_PIN_SET);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_9,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,GPIO_PIN_SET);
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_4,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8|GPIO_PIN_9,GPIO_PIN_SET);
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_8,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,GPIO_PIN_SET);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4|GPIO_PIN_8,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3|GPIO_PIN_9,GPIO_PIN_SET);
			break;	
		default:
				break;
	}
	HAL_Delay(speed);
	Motor_Stop();
}

void Motor_Num(uint8_t dir,uint16_t num,uint16_t speed)
{
	 for(uint16_t i=0;i<num;i++)
	{
		if(dir==0)
		{
			if(step==0) step=8;
			step--;
		}
		else if(dir==1)
		{
			step++;
			if(step>=8) step=0;
		}
		Motor_Step8(step,speed);
	}
}

void Motor_Loop(uint8_t dir,uint16_t loop,uint16_t speed)
{
	Motor_Num(dir,loop*4076,speed);
}
