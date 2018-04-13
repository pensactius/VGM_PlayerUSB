/*
  D2 .. D9  connect to DAx into YM2149
  D11       Connects to Clk into YM2149
  A3        connects to BC1 into YM2149
  A2        connects to BDIR into YM2149
  BC2       is always connected to +5V
*/

#include "ym2149.h"
void _send_address(uint8_t addr);
void _send_data(uint8_t data) ;
void _set_bus_out(void) ;
void _set_bus_in(void);

enum { DATA_READ = B10 <<2, DATA_WRITE = B01 <<2, ADDRESS_MODE = B11 <<2 };

void YMSetBus()
{
  DDRC |= _BV(PC2) | _BV(PC3); // A2, A3 as OUTPUTs
}
void YMWriteData(uint8_t addr, uint8_t data)
{
  _send_address(addr);
  _send_data(data);
}

void YM_Off() { 
  for (int i=0; i<14; i++) {
    YMWriteData(i, 0);
  }
}

void _send_address(uint8_t addr) {
  _set_bus_out();
  PORTC = (PORTC & 0xf3) | ADDRESS_MODE;  // Ctrl bits to PB2,PB3 (D10-D11)
  PORTD = (PORTD & 0x02) | ( (addr & 0x3f) << 2); // 6 first bits to PD2-PD7 (D2-D7)
  PORTB = (PORTB & 0xfc) | ( (addr & 0xc0) >> 6); // 2 last bits to PB0,PB1 (D8-D9)
  _delay_us(1.); //tAS = 300ns
  
  PORTC = (PORTC & 0xf3) /*INACTIVE*/ ;
  _delay_us(1.); //tAH = 80ns
}

void _send_data(uint8_t data) {
  _set_bus_out();
  PORTD = (PORTD & 0x02) | ( (data & 0x3f) << 2); // 6 first bits to PD2-PD7 (D2-D7)
  PORTB = (PORTB & 0xfc) | ( (data & 0xc0) >> 6); // 2 last bits to PB0,PB1 (D8-D9)
  PORTC = (PORTC & 0xf3) | DATA_WRITE;    // Ctrl bits to PC2,PC3 (A2,A3)
  _delay_us(1.); // 300ns < tDW < 10us
  PORTC = (PORTC & 0xf3) /*INACTIVE*/ ; // To fit tDW max
  _delay_us(1.); // tDH = 80ns
}

void _set_bus_out(void) {
  DDRB |= 0x03; // Bits 0 and 1 (D8,D9)
  DDRD |= 0xfc; // Bits 2 to 7  (D2-D7)
}
void _set_bus_in(void) {
  DDRB &= 0xfc; // Bits 0 and 1 (D8,D9)
  DDRD &= ~0xfc; // Bits 2 to 7 (D2-D7)
}

