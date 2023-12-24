// Pew.h

#ifndef PEW_H
#define PEW_H

#include "../shared/BaseEffect.h"

class Pew : public BaseEffect
{
private:
    uint8_t hue;
    uint8_t len;
    int speed;
    bool rainbow;

public:
    Pew(uint8_t hue = 0, uint8_t len = 6, int speed = 15, bool rainbow = true)
        : hue(hue), len(len), speed(speed), rainbow(rainbow)
    {
    }

    void trigger() override
    {

        hue = rainbow ? random8() : hue;
        vleds[NUM_LEDS - 1] = CHSV(hue, 255, 50);
        vleds[NUM_LEDS - 2] = CHSV(hue, 255, 150);
        vleds[NUM_LEDS - 3] = CHSV(hue, 255, 255);
        vleds[NUM_LEDS - 4] = CHSV(hue, 255, 150);
        vleds[NUM_LEDS - 5] = CHSV(hue, 255, 50);
    }

    void draw() override
    {
        if (millis() - prevMillis > speed)
        {
            prevMillis = millis();
            for (int i = 0; i < NUM_LEDS - 1; i++)
            {
                vleds[i] = vleds[i + 1];
                vleds[i + 1] = CRGB::Black;
            }
        }
    }
};

#endif // PEW_H
