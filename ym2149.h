#ifndef __YM2149_H__
#define __YM2149_H__

#include <Arduino.h>

void YMSetBus();
void YMWriteData(uint8_t addr, uint8_t data);
void YM_Off();

#endif
