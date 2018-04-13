#ifndef __SN76489_H__
#define __SN76489_H__

// Establece el volumen de los cuatro canales al minimo
void SN76489_Off();

// Envia 8 bits de datos por el BUS
void SN76489WriteData(char data);

// Configura el BUS como salida
void SN76489SetBus();

#endif
