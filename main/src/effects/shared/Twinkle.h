// Twinkle.h

#ifndef TWINKLE_H
#define TWINKLE_H

#include "BaseEffect.h"
#include "../../config/config.h"

class Twinkle : public BaseEffect
{
private:
    unsigned long fadeMillis = 0;
    uint8_t value = 0;
    bool active = false;
    int fadeSpeed = 20;

public:
    Twinkle(int speed = 20, CRGBPalette256 pal = DEFAULT_PALETTE)
        : BaseEffect(pal)
    {
        this->speed = speed;
        triggerDelay = 500;
    }

    void trigger() override
    {
        active = !active;
        value = 0;
    }

    void draw() override
    {
        if (millis() >= fadeMillis + fadeSpeed)
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
     void update() override
    {
    }
};

#endif // TWINKLE_H
