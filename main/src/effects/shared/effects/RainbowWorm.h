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
    RainbowWorm(CRGBPalette256 pal = DEFAULT_PALETTE)
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
                    vleds[i] = ColorFromPalette(palette, move + i * 2);
                }
                move = (move + 2) % 255;
            }
        }
        else
        {
            for (int i = 0; i < NUM_LEDS; i++)
            {
                vleds[i].fadeToBlackBy(random(1, 20));
            }
        }
    }
    void update() override
    {
    }
};

#endif // RAINBOWWORM_H
