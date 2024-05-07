// Flash.h

#ifndef FLASH_H
#define FLASH_H

#include "../../shared/effects/BaseEffect.h"

class Flash : public BaseEffect
{
private:
    unsigned long TIMEOUT = 5000;
    unsigned long lastTrigger = 0;

public:
    Flash()
    {
    }

    void trigger() override
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            vleds[i] = CHSV(random8(), random(40, 75), 200);
        }
        lastTrigger = millis();
    }

    bool isEffectActive() override
    {
        return millis() - lastTrigger < TIMEOUT;
    }

    void draw() override
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            if (vleds[i].v <= 0)
            {
                continue;
            }
            uint8_t fade_amt = random8(1, 10); // TODO: give each pixel a fade amount to increase fade spread
            vleds[i].v = qsub8(vleds[i].v, fade_amt);
        }
    }
    void update() override
    {
    }
};
#endif // BLAST_H
