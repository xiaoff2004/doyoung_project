#ifndef __FLASH_H__

#define __FLASH_H__


#include "main.h"
#include "stm32f1xx_hal.h"


#define ADDR_FLASH_PAGE_0     ((uint32_t)0x8000000)
#define ADDR_FLASH_PAGE_(n)   (ADDR_FLASH_PAGE_0+((uint32_t)(n)*FLASH_PAGE_SIZE))

#define ADDR_USER_FLASH_PAGE_NUM 2
#define ADDR_START_USER_FLASH_PAGE ADDR_FLASH_PAGE_(64-ADDR_USER_FLASH_PAGE_NUM)
#define ADDR_LAST_USER_FLASH_PAGE (ADDR_FLASH_PAGE_0+FLASH_PAGE_SIZE*64)

uint32_t flash_read(uint32_t addr); 
void flash_write(uint32_t addr,uint32_t buffer);

#endif
