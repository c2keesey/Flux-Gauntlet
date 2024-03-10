// CONTROLRING_H

#ifndef CONTROLRING_H
#define CONTROLRING_H

#include "../../shared/effects/BaseEffect.h"
#include "../Rings.h"
#include "../../shared/EffectHelpers.h"

class ControlRing : public BaseEffect
{
private:
    int ringStart;
    int ringEnd;
    bool triggered = false;
    int curPos;
    unsigned long updateRate;
    unsigned long prevUpdateMillis = 0;
    Rings rings;
    int ringi = 2;

public:
    ControlRing(CRGBPalette256 pal = DEFAULT_PALETTE, unsigned long holdTime = 1000)
        : BaseEffect(pal), rings(vleds)
    {
        ringStart = rings.getRingStart(rings.getRingsLength() - 2);
        ringEnd = rings.getRingEnd(rings.getRingsLength() - 2);
        curPos = ringStart;
        updateRate = holdTime / max(1, (ringEnd - ringStart));
    }

    void trigger() override
    {
        triggered = true;
    }

    void cancel()
    {
        curPos = ringStart;
        triggered = false;
        ringi = 2;
        for (int i = 0; i < NUM_LEDS; i++)
        {
            vleds[i] = CRGB::Black;
        }
    }

    void update() override
    {
        if (!triggered)
        {
            return;
        }
        if (curPos < ringEnd)
        {
            // if (millis() - prevUpdateMillis > updateRate)
            // {
            EVERY_N_MILLIS(updateRate)
            {
                prevUpdateMillis = millis();
                vleds[curPos] = CRGB::White;
                curPos++;
            }
        }
        else if (ringi < rings.getRingsLength() - 1)
        {
            clearVleds(vleds);
            rings.drawRing(rings.getRingsLength() - ringi, CRGB::White);
            ringi++;
        }
        else
        {
            cancel();
        }
    }

    void setHoldTime(unsigned long holdTime)
    {
        updateRate = holdTime / (ringEnd - ringStart);
    }
};
#endif // CONTROLRING_H
