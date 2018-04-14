# VGM_PlayerUSB

Reproductor de ficheros VGM por puerto USB. Soporta formato comprimido -ficheros .vgz- y los
 siguientes chips de sonido:

- SN76489
- YM2143
- AY-3-8910 (aka YM2149)

Se incorporan algunos archivos de sonido de ejemplo en la carpeta _songs_. 
Se pueden descargar más archivos VGM en [VGMRips](http://vgmrips.net)

El proyecto consta de dos partes:

- Un programa Arduino que escucha por el puerto serie -a 57600 bps- comandos de escritura a
los chips de sonido. Los comandos siguen el mismo formato que en los ficheros VGM:

```
0x50 dd    : PSG (SN76489/SN76496), escribir valor 'dd'
0x51 aa dd : YM2413, escribir valor 'dd' en el registro 'aa'
A0 aa dd   : AY-3-8910, escribir valor 'dd' en el registro 'aa'
```

- Otro programa escrito en Python **vgm_streamer.py** se encarga de leer e interpretar el archivo en formato VGM. Cada vez que encuentra un comando para escribir a un chip de sonido soportado envía el comando y los operandos (registro  y valor) correspondientes por el puerto USB Arduino. La forma de usar este archivo es:

```
python serial_play.py puerto_usb nombre_archivo_vgm
```
p.ej

```
python serial_play.py /dev/ttyUSB0 'songs/ay8910/02 Vampire Killer.vgz'
```
**Nota 1**: Es necesario una placa Arduino UNO (o Nano) original, no sirven versiones chinas debido al uso de instrucciones del chip AVR propias.

### Conexiones

Conexion SN 76489:
```
clk (14) ...... Arduino D11
~WE ( 5) ...... Arduino D12
Ready(4) ...... N.C
~CE ( 6) ...... Arduino (D10) (Conectar a GND si se necesita este PIN)
D0 - D7  ...... Arduino D2 - D9
VCC (16) ...... ARduino (+5V)
GND ( 8) ...... Arduino (GND)
```

Conexión AY-3-8910:
```
D2 .. D9 ....... DAx into YM2149
D11      ....... Clk into YM2149
A2       ....... BC1 into YM2149
A3       ....... BDIR into YM2149
BC2      ....... +5V
RESET    ....... +5V
```

### Contenido del directorio
```
 sn76489_vgm_player                => Carpeta del proyecto Arduino
  ├── sn76489_vgm_player.ino       => Fichero principal Arduino
  ├── sn76489.h/.cpp               => Funciones de control y escritura al IC sn76489
  ├── VGMPlayer.h/.cpp             => Funciones para reproducir el archivo de música
  ├── vgmdata.h                    => Volcado del archivo VGM en formato de array (vgm_song[])  
  └── Readme.md                    => Este archivo
```

