#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>

class Button
{
private:
    uint8_t pin;
    bool lastState;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;
    int enum_val;

public:
    Button(uint8_t pin, int enum_val, unsigned long debounceDelay = 50)
    {
        this->pin = pin;
        this->debounceDelay = debounceDelay;
        this->enum_val = enum_val;
        lastState = HIGH;
        lastDebounceTime = 0;
        pinMode(pin, INPUT_PULLUP);
    }

    bool isPressed()
    {
        bool reading = digitalRead(pin);
        if (reading != lastState)
        {
            lastDebounceTime = millis();
            lastState = reading;
        }
        if ((millis() - lastDebounceTime) > debounceDelay)
        {
            if (lastState == LOW)
            {
                return true;
            }
        }
        return false;
    }

    int getEnumVal()
    {
        return enum_val;
    }
};

#endif // BUTTON_H