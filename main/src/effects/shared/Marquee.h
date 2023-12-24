// Marquee.h

#ifndef MARQUEE_H
#define MARQUEE_H

#include "BaseEffect.h"
#include "EffectHelpers.h"

class Marquee : public BaseEffect
{
private:
    bool active = false;
    int speed;
    float pos = 0;

public:
    Marquee(CRGBPalette256 pal = DEFAULT_PALETTE, int speed = 5) : BaseEffect(pal), speed(speed)
    {
    }

    void trigger() override
    {
        active = !active;
    }

    void draw() override
    {
        if (active)
        {
            if (millis() - prevMillis > speed)
            {
                prevMillis = millis();
                for (int i = 0; i < NUM_LEDS; i++)
                {
                    vleds[i] = CRGB::Black;
                }
                drawPrecise(pos, 3, CRGB::Purple, vleds);
                pos += 0.1f;
            }
        }
    }
};

#endif // MARQUEE_H
