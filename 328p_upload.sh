#!/bin/sh

echo "_________________________________________"
echo "\n"
echo " Update load hex file to microcontroller"
echo "_________________________________________"

avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyS0 -b 115200 -U flash:w:example/max7219.hex
