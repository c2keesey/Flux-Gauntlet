// Flash.h

#ifndef FLASH_H
#define FLASH_H

#include "../../shared/effects/BaseEffect.h"

class Flash : public BaseEffect
{
private:
    unsigned long TIMEOUT = 500;
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
            vleds[i].fadeToBlackBy(random(1, 70));
        }
    }

    void update() override
    {
    }
};
#endif // BLAST_H
