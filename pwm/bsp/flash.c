# include "flash.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "string.h"


uint32_t flash_read(uint32_t addr)  
{
  uint32_t readFlashData = *(__IO uint32_t*)(addr); 
	return readFlashData;
}
	
void flash_write(uint32_t addr,uint32_t buffer)
{
	HAL_FLASH_Unlock();
	uint32_t FlashErr =0;
	FLASH_EraseInitTypeDef FlashErease;
	FlashErease.TypeErase =FLASH_TYPEERASE_PAGES;
	FlashErease.PageAddress =addr;
	FlashErease.NbPages=1;
	HAL_FLASHEx_Erase(&FlashErease,&FlashErr);
	FLASH_WaitForLastOperation(HAL_MAX_DELAY);
	CLEAR_BIT(FLASH->CR,FLASH_CR_PER);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,addr,buffer);
	HAL_FLASH_Lock();
}
