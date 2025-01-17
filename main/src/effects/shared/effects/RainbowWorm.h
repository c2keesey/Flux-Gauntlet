// RainbowWorm.h

#ifndef RAINBOWWORM_H
#define RAINBOWWORM_H

#include "BaseEffect.h"

class RainbowWorm : public BaseEffect
{
private:
    int speed = 10;
    uint8_t value = 30;
    bool active = false;
    int move = 0;
    bool fadeIn = true;

public:
    RainbowWorm(ColorPalette *pal = &rainbow_cp)
    {
        palette = pal;
        triggerDelay = 500;
    }

    void trigger() override
    {
        active = !active;
        value = 0;
    }

    void draw() override
    {
        if (active)
        {
            if (millis() - prevMillis > speed)
            {
                prevMillis = millis();
                if (fadeIn)
                {
                    value += value < 150 ? 2 : 1;
                }
                else
                {
                    value -= 1;
                }
                if (value >= 255)
                {
                    fadeIn = false;
                    value = 255;
                }
                else if (value <= 200)
                {
                    fadeIn = true;
                }
                for (int i = 0; i < NUM_LEDS; i++)
                {
                    vleds[i] = CHSV(move + i * 2, 255, value);
                }
                move = (move + 2) % 255;
            }
        }
        else
        {
            for (int i = 0; i < NUM_LEDS; i++)
            {
                vleds[i].val -= random(1, 20);
                vleds[i].val = max((uint8_t)0, vleds[i].val);
            }
        }
    }
    void update() override
    {
    }
};

#endif // RAINBOWWORM_H
