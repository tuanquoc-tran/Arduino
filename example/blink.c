#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h> 
#include <stdio.h>

int main()
{
	DDRB  |= (1<<PB5);
	while(1)
	{	
		PORTB   |= (1 << PB5);
		_delay_ms(500);
		PORTB   &= (0 << PB5);
		_delay_ms(500);
	}
	return 0;
}
