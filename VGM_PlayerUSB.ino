#include "ym2149.h"
#include "sn76489.h"
#include "clock.h"

// Define here USB baud rate to receive song data
#define BAUD 57600

unsigned char cmd, addr, data;

void setup() {
  
  Serial.begin(BAUD);
  while (!Serial) {
    ;
  }
  
  SetClock();
  SetBus();

  ClearRegisters();

  Serial.println("Ready");  
}

void loop() {
  while (!(Serial.available() >0)) {}
  if (Serial.available() > 0)
    cmd = Serial.read();

    // AY-3-8910
    if (cmd == 0xA0) {
    
      while (!(Serial.available() >0)) {}
      if (Serial.available() > 0)
        addr = Serial.read();
    
      while (!(Serial.available() >0)) {}
      if (Serial.available() > 0)
        data = Serial.read();      
      
      YMWriteData(addr, data);
    }

    // SN76489
    else if (cmd == 0x50) {
      while (! (Serial.available() > 0)) {}
      if (Serial.available() > 0)
        data = Serial.read();

        SN76489WriteData(data);
    }

    else if (cmd == 0xFF) {
      ClearRegisters();
    }
}

void SetBus() {
  YMSetBus();
  SN76489SetBus();
}

void ClearRegisters() {
  YM_Off();
  SN76489_Off();
}

