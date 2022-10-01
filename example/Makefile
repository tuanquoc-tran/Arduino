CC = avr-gcc

.PHONY: clean
# .SILENT: clean
all: control_max7219
	

clean:
	$(RM) *.o a.out *.elf *.hex -rf 

# blink:
# 	$(CC) -g -Os -mmcu=atmega2560 -c blink.c 
# 	$(CC) -g -mmcu=atmega2560 -o blink.elf blink.o
# 	avr-objcopy -j .text -j .data -O ihex blink.elf blink.hex

# max7219:
# 	$(CC) -g -Os -mmcu=atmega2560 -c max7219.c 
# 	$(CC) -g -mmcu=atmega2560 -o max7219.elf max7219.o
# 	avr-objcopy -j .text -j .data -O ihex max7219.elf max7219.hex

control_max7219:
	$(CC) -g -Os -mmcu=atmega328p -c control_max7219.c 
	$(CC) -g -mmcu=atmega328p -o control_max7219.elf control_max7219.o
	avr-objcopy -j .text -j .data -O ihex control_max7219.elf control_max7219.hex
