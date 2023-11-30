// Twinkle.h

#ifndef TWINKLE_H
#define TWINKLE_H

#include "BaseEffect.h"
#include "config.h"

class Twinkle : public BaseEffect
{
private:
    int speed;
    unsigned long prevMillis = 0;
    unsigned long fadeMillis = 0;
    uint8_t value = 0;
    bool active = false;

public:
    Twinkle(int speed = 20, CRGBPalette256 pal = DEFAULT_PALETTE)
        : speed(speed), BaseEffect(pal)
    {
        triggerDelay = 500;
    }

    void trigger() override
    {
        active = !active;
        value = 0;
    }

    void draw() override
    {
        if (millis() >= fadeMillis + 5)
        {
            fadeMillis = millis();
            for (int i = 0; i < NUM_LEDS; i++)
            {
                vleds[i].fadeToBlackBy(random(1, 10));
            }
        }
        if (!active)
        {
            return;
        }
        if (millis() >= prevMillis + speed)
        {
            prevMillis = millis();
            for (int i = 0; i < 5; i++)
            {

                vleds[random16(NUM_LEDS)] = ColorFromPalette(palette, random8());
            }
        }
    }
};

#endif // TWINKLE_H
