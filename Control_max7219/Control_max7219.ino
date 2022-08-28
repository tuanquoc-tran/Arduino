// Assumes one MAX7219 IC with up to 8 
// 7-segment LED displays attached.
// The sketch displays a counter increasing
// once per second.
// SPI interface is through the SPI 
// library and so uses the native hardware 
// interface pin for the target MCU.
#include "Arduino.h"
#include "SPI.h"

// Define the number of 7-seg digits 
// in the display. Valid range [1..8]
const uint8_t NUM_DIGITS = 2;

// Define the SS pin
const uint8_t pinSS = 53;

// Opcodes for the MAX7221 and MAX7219
const uint16_t OP_NOOP = 0;
const uint16_t OP_DIGIT0 = 1;
// note: all OP_DIGITn are +n offsets from OP_DIGIT0
const uint16_t OP_DIGIT1 = 2;
const uint16_t OP_DIGIT2 = 3;
const uint16_t OP_DIGIT3 = 4;
const uint16_t OP_DIGIT4 = 5;
const uint16_t OP_DIGIT5 = 6;
const uint16_t OP_DIGIT6 = 7;
const uint16_t OP_DIGIT7 = 8;
const uint16_t OP_DECODEMODE = 9;
const uint16_t OP_INTENSITY = 10;
const uint16_t OP_SCANLIMIT = 11;
const uint16_t OP_SHUTDOWN = 12;
const uint16_t OP_DISPLAYTEST = 15;

void sendData(uint16_t cmd, uint8_t data)
// Send a simple command to the MAX7219
// using the hardware SPI interface
{
  uint16_t x = (cmd << 8) | data;
  SPI.beginTransaction(SPI(8000000, MSBFIRST, SPI_MODE0));
  digitalWrite(pinSS, LOW);
  SPI.transfer16(x);
  digitalWrite(pinSS, HIGH);
  SPI.endTransaction();
}
 
void update(uint32_t n)
// Work out the individual digits to
// be displayed and show them.
{
  for (uint8_t i = 0; i < NUM_DIGITS; i++)
  {
    uint8_t digit = n % 10;
    sendData(OP_DIGIT0 + i, digit);
    n /= 10;
  }
}

void setup(void) 
{
  pinMode(pinSS, OUTPUT);
  SPI.begin();
  // Set the MAX7219 parameters
  sendData(OP_SHUTDOWN, 1);
  sendData(OP_DECODEMODE, 0xff);
  sendData(OP_SCANLIMIT, NUM_DIGITS-1);
  sendData(OP_INTENSITY, 7);

  // turn on all LED for short time
  sendData(OP_DISPLAYTEST, 1);
  delay(500);
  sendData(OP_DISPLAYTEST, 0);

  // initialize the display
  update(0);
}

void loop(void) 
{
  static uint32_t timeLast = 0;
  static uint32_t counter = 0;

  if (millis() - timeLast >= 1000)
  {
    timeLast = millis();
    counter++;
    update(counter);
  }
}
