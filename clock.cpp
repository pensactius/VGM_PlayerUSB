#include <Arduino.h>
#include "clock.h"

// Genera una señal de reloj a 4MHz o 2MHz por el pin D11
// Modificar el fichero clock.h para especificar la velocidad
// a generar.
void SetClock() {

  // Inicializa D11 (PB3) como salida
   DDRB  |=  _BV(PORTB3);
  // Toggle OC2A on compare match
  TCCR2A &= ~_BV(COM2A1);
  TCCR2A |=  _BV(COM2A0);
  // Clear Timer on Compare match
  TCCR2B &= ~_BV(WGM22);
  TCCR2A |=  _BV(WGM21);
  TCCR2A &= ~_BV(WGM20);
  // Use CLK I/O without prescaling
  TCCR2B &= ~_BV(CS22);
  TCCR2B &= ~_BV(CS21);
  TCCR2B |=  _BV(CS20);
  // Divide la señal de reloj de Arduino de 16 MHz a la 
  // velocidad indicada por CLK_SPEED
  OCR2A = CLK_SPEED; 
}
