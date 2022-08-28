#!/bin/sh

echo "_________________________________________"
echo "\n"
echo " Update load hex file to microcontroller"
echo "_________________________________________"

avrdude -c arduino -v -p atmega2560 -cwiring -P /dev/ttyS0 -b115200 -D -Uflash:w:example/controll_max7219.hex:i

