#include "LTM8522HR.hpp"
#include "math.h"

// 7 segs digits pattern ( 0,1,2,3,4,5,6,7,8,9,empty,- )
const byte LTM8522HR::num[12] = {
    0b11111100, 0b01100000, 0b11011010,
    0b11110010, 0b01100110, 0b10110110,
    0b10111110, 0b11100000, 0b11111110,
    0b11110110, 0b00000000, 0b00000010};

LTM8522HR::LTM8522HR(uint32_t dataPin, uint32_t clockPin, uint32_t selectPin)
{
  _dataPin = dataPin;
  _clockPin = clockPin;
  _selectPin = selectPin;
  pinMode(_dataPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_selectPin, OUTPUT);
}

LTM8522HR::~LTM8522HR()
{
  stop();
}

void LTM8522HR::begin()
{
  digitalWrite(_selectPin, LOW);
  clear();
}

void LTM8522HR::stop()
{
  clear();
  digitalWrite(_selectPin, HIGH);
}

void LTM8522HR::clear()
{
  pushBit(1); // start bit
  pushDigit(10);
  pushDigit(10);
  pushDigit(10);
  pushRemainder();
  pushBit(0); // latching bit
}

void LTM8522HR::print(uint16_t number, byte dpPosition)
{
  // Cap number to 999
  uint16_t filtered_number = MAX_NUMBER ^ ((number ^ MAX_NUMBER) & -(number < MAX_NUMBER));
  pushBit(1); // start bit
  for (uint16_t place = 3; place > 0; place--)
  {
    uint16_t digit = digitAtPos(filtered_number, place);
    pushDigit(digit, dpPosition == place);
  }
  pushRemainder();
  pushBit(0); // latching bit
}

// extra 10 bits for unused output pins
void LTM8522HR::pushRemainder()
{
  for (int i = 0; i < 10; i++)
  {
    pushBit(0);
  }
}

void LTM8522HR::pushDigit(int digit, bool decimal)
{
  for (int segment = 7; segment != 0; segment--)
    pushBit((num[digit] >> segment) & 1);
  pushBit(decimal);
}

void LTM8522HR::pushBit(bool state)
{
  digitalWrite(_dataPin, state ? HIGH : LOW);
  digitalWrite(_clockPin, HIGH);
  digitalWrite(_clockPin, LOW);
}

uint16_t LTM8522HR::digitAtPos(uint16_t number, uint16_t pos)
{
  return (uint16_t)(number / (float)pow(10.0, pos - 1)) % 10;
}