#include "encoder.h"
#include "main.h"
#include "gpio.h"




//uint8_t EncoderRead(void)
//{
//	uint8_t result=0;
//	uint8_t State;
//	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==GPIO_PIN_SET)
//		flag=1;
//	if(flag==1)
//	{
//		if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==GPIO_PIN_RESET))
//	{
//		delay_us(100);
//		State=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);
//		HAL_Delay(3);
//		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==GPIO_PIN_RESET)
//			switch(State)
//			{
//				case GPIO_PIN_RESET  :result=1;
//				case GPIO_PIN_SET    :result=2;
//			}
//		
//	}
//	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)==GPIO_PIN_RESET) 
//	{
//		HAL_Delay(20);
//		if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_7)==GPIO_PIN_RESET)
//			result=3;
//	}
//	}
//	count=0;
//		while((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)!=GPIO_PIN_SET) && (count <=6000))
//		{
//			count++;
//			flag=0;
//			delay_us(20);
//		}
//	
//	
//	return result;
//}

uint8_t Encoder_Scan(void)
{
	uint8_t result=0,temp=1;
	temp=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);
	delay_ms(3);
	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)==GPIO_PIN_RESET)
	{
		switch(temp)
		{
			case 0 :result=1;
			case 1 :result=2;
		}
	}
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)==GPIO_PIN_RESET)
		result=3;
	return result;
}

