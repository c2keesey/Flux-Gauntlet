// Blast.h

#ifndef BLAST_H
#define BLAST_H

#include "../../shared/effects/BaseEffect.h"

class Blast : public BaseEffect
{
private:
    uint8_t hue = 0;
    uint8_t len = 6;
    int speed = 15;
    int rings[16] = {21, 27, 25, 23, 23, 22, 20, 19, 19, 19, 17, 16, 15, 12, 12, 10};
    int numRings = 16;
    int breakpoints[17] = {0};

public:
    Blast(ColorPalette *pal = &rainbow_cp) : BaseEffect(pal)
    {
        minUpdatePeriod = 50;
        palette = pal;
        for (int i = 0; i < numRings; i++)
        {
            breakpoints[i + 1] = breakpoints[i] + rings[i];
        }
    }

    void trigger() override
    {
        CHSV color = palette->getNextColor();
        for (uint8_t i = 0; i < breakpoints[1]; i++)
        {
            vleds[i] = color;
        }
    }

    // TODO: Add additional vleds to ends of vleds, and return update BaseEffect getVleds() to draw first ring properly
    void draw() override
    {
        if (millis() - prevMillis > speed)
        {
            prevMillis = millis();
            for (int i = 0; i < rings[numRings - 1]; i++)
            {
                vleds[NUM_LEDS - i - 1] = CHSV(0, 0, 0);
            }
            int samplePos = NUM_LEDS - 1 - rings[numRings - 1];
            for (int i = numRings - 1; i > 0; i--)
            {
                CHSV samplePixel = vleds[samplePos];
                for (int j = 0; j < rings[i]; j++)
                {
                    vleds[samplePos + 1 + j] = samplePixel;
                }
                samplePos -= rings[i - 1];
                for (int j = 0; j < rings[i - 1]; j++)
                {
                    vleds[samplePos + 1 + j] = CHSV(0, 0, 0);
                }
            }
        }
    }

    void update() override
    {
    }
};
#endif // BLAST_H
