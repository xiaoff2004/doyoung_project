#ifndef __LM75A_H__
#define __LM75A_H__

#include "main.h"

#define LM75A_ADD 0x9E

void LM75A_ReadTemp(uint8_t *TempBuffer);


#endif
