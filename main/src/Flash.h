// Flash.h

#ifndef FLASH_H
#define FLASH_H

#include "BaseEffect.h"

class Flash : public BaseEffect
{
private:
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
    }

    void draw() override
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            vleds[i].fadeToBlackBy(random(1, 70));
        }
    }
};
#endif // BLAST_H
