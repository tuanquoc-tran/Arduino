
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h> 
#include <stdio.h>

// Define Pin 
#define MOSI_PIN    PB0
#define CS_PIN      PB1
#define CLK_PIN     PB2

// Define register
#define     NoOP_REG            0x00
#define     Digit0_REG          0x01
#define     Digit1_REG          0x02
#define     Digit2_REG          0x03
#define     Digit3_REG          0x04
#define     Digit4_REG          0x05
#define     Digit5_REG          0x06
#define     Digit6_REG          0x07
#define     Digit7_REG          0x08
#define     DecodeMode_REG      0x09
#define     Intensity_REG       0x0A
#define     Scan_Limit_REG      0x0B
#define     Shutdown_REG        0x0C
#define     Display_Test_REG    0x0F


void write(uint8_t value)
{
    uint8_t bit;
    for (bit = 0; bit < 8 ; bit ++ )
    {
        
        // Clock Low
        PORTB   &= (0 << CLK_PIN);
        __asm("nop");
        if (value & 0x80)
        {
            // Write High
            PORTB   |= (1 << MOSI_PIN);
        }
        else
        {
            // Write Low
            PORTB   &= (0 << MOSI_PIN);
        }
        value = value << 1;
        // Clock High
        PORTB  |= (1 << CLK_PIN);
    }

}
void send_data(uint8_t address, uint8_t data)
{
    // Send 16bit
    // Cs Low
    PORTB   &= (0 << CS_PIN);
    __asm("nop");
    PORTB   &= (0 << CLK_PIN);

    write(address);
    write(data);    

    __asm("nop");
    // Cs High
    PORTB   |= (1 << CS_PIN);

}

void clear_all()
{
    int i;
    for ( i = 1 ; i < 9 ;i++)
    {
        send_data(i,0);
    }
}

void init()
{
    // Set pin as output
    DDRB  |= (1<<MOSI_PIN);
    DDRB  |= (1<< CS_PIN);
    DDRB  |= (1<< CLK_PIN);


    // Send register -> send data
    
    // Demode code
    send_data(DecodeMode_REG,0);

    // Intensity
    send_data(Intensity_REG,0x01);

    // Scan limit
    send_data(Scan_Limit_REG,0x07);

    // Display test
    send_data(Display_Test_REG,0x00);
  
    // Normal operation
    send_data(Shutdown_REG,0x01);
}


const uint8_t IMAGES[][8] = {
{
  0b00000000,
  0b00111000,
  0b01111100,
  0b01100100,
  0b01100100,
  0b01101100,
  0b00111100,
  0b00000010
},{
  0b00000000,
  0b00111100,
  0b01011000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00011000,
  0b00000000
},{
  0b00000000,
  0b00111100,
  0b01100010,
  0b01100000,
  0b01100000,
  0b01100010,
  0b01111100,
  0b00000000
},{
  0b00000000,
  0b00111100,
  0b01100010,
  0b01100010,
  0b01100010,
  0b01100010,
  0b00111100,
  0b00000000
},{
  0b00000000,
  0b01111100,
  0b01100010,
  0b01100010,
  0b01100010,
  0b01100010,
  0b01111100,
  0b00000000
},{
  0b00000000,
  0b01111100,
  0b01100000,
  0b01111100,
  0b01100000,
  0b01100000,
  0b01111100,
  0b00000000
},{
  0b00000000,
  0b01111100,
  0b01100100,
  0b01111100,
  0b01110000,
  0b01101000,
  0b01100100,
  0b00000000
}};
const int IMAGES_LEN = sizeof(IMAGES)/8;


int main()
{
    init();

    uint8_t i,j;
    while (1)
    {
    
        for (j = 0;j < 7; j++)
        {
            clear_all();
            // _delay_ms(100);
            for (i =0; i < 8;i++)
            {
                send_data(i+1,IMAGES[j][i]);

            }
            _delay_ms(1000);
        }
    }
    return 0;
}
