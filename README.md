# Install compiler arduino in Ubuntu 16.04

### Install avr-gcc toolchain

>sudo apt-get update
>sudo apt-get upgrade
>sudo apt-get install gcc-avr binutils-avr avr-libc

May install gdb-avr. It is useful for in-system debugging/emulation.

>sudo apt-get install gdb-avr

### Install avrdude

avr-gcc only support the software development cross-compile, don't do anything about burning hex file to microcontroller.

>sudo apt-get install avrdude

# Compile simple source code to blink led


### Compile
 
avr-gcc -g -Os -mmcu=atmega2560 -c blink.c 
avr-gcc -g -mmcu=atmega2560 -o blink.elf blink.o
avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex

### Burning

**Arduino 2560**

avrdude -c arduino -v -p atmega2560 -cwiring -P /dev/ttyS0 -b115200 -D -Uflash:w:blink.hex:i

**Arduino 328p**

avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyS0 -b 115200 -U flash:w:example/max7219.hex


# Example

### Control Max 7219

#### SPI protocol

Master          Slave

MOSI    -->    MOSI (Master out slave in) - (SDI, DIN)

MISO    <--    MISO (Master in slave out) - (SDO, DOUT)

CLK     -->    CLK (clock) - (SCK)

CS      -->    CS (Chip select)


-SPI is a synchronous, full duplex.

-Both master and slave can transmit data at the same time.

-Data is synchronized on the rising or falling clock eage.


Arduino mega2560 and matrix max7219

MOSI (PB2)      <-->    DIN

SCK  (PB1)      <-->    CLK

SS  (PB0)       <-->    CS

Arduino mega328p and matrix max7219

MOSI_PIN <--> PB0

CS_PIN <--> PB1

CLK_PIN <--> PB2

##### Dont use SPI, Only use normally GPIO.

Setup output as Diagram timming of Max7219


