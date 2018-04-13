#ifndef __CLOCK_H__
#define __CLOCK_H__

// Constantes para conseguir diferentes velocidades
// a partir de la señal de reloj de 16MHz de Arduino.
#define DIV_4MHz  2
#define DIV_2MHz  3

/* 
 * Descomentar una de las siguientes lineas para generar la velocidad 
 * de reloj deseada por el pin 11
 * 
 * DIV_4MHz: Reloj a 4 MHz -> SN76489 y YM2413
 * DIV_2MHz: Reloj a 2 MHz -> AY-3-8910
 * 
 */
#define CLK_SPEED DIV_4MHz
//#define CLK_SPEED DIV_2MHz

// Crea una señal de clk por el pin 11 a la velocidad CLK_SPEED
void SetClock();

#endif
