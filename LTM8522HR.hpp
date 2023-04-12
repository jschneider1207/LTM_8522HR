#ifndef __LTM8522HR_H__
#define __LTM8522HR_H__
#include <Arduino.h>

class LTM8522HR
{
public:
    LTM8522HR(uint32_t dataPin, uint32_t clockPin, uint32_t selectPin);
    void begin();
    void stop();
    void clear();
    void print(uint16_t number, byte dpPosition = 0);

    ~LTM8522HR();

private:
    void pushDigit(int digit, bool decimal = false);
    void pushBit(bool state);
    void pushRemainder();
    uint16_t digitAtPos(uint16_t number, uint16_t pos);
    byte _dataPin, _clockPin, _selectPin;
    static const byte num[12];
};

static const uint16_t MAX_NUMBER = 0x3E7;

#endif // __LTM8522HR_H__
