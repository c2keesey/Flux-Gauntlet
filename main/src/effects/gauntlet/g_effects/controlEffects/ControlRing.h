// CONTROLRING_H

#ifndef CONTROLRING_H
#define CONTROLRING_H

#include "../../../shared/effects/BaseEffect.h"
#include "../../Rings.h"
#include "../../../shared/EffectHelpers.h"

// TODO: make FSM
class ControlRing : public BaseEffect
{
private:
    int ringStart;
    int ringEnd;
    bool triggered = false;
    int curPos;
    unsigned long updateRate;
    unsigned long origUpdateRate;
    unsigned long prevUpdateMillis = 0;
    Rings rings;
    int ringi = 2;
    int loop;
    bool isSetMode = false;

public:
    ControlRing(ColorPalette *pal = &rainbow_cp, unsigned long holdTime = 500)
        : BaseEffect(pal), rings(vleds)
    {
        ringStart = rings.getRingStart(rings.getNumRings() - 2);
        ringEnd = rings.getRingEnd(rings.getNumRings() - 2);
        curPos = ringStart;
        updateRate = holdTime / max(1, (ringEnd - ringStart));
        origUpdateRate = updateRate;
        loop = 0;
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
        loop = 0;
        isSetMode = false;
        updateRate = origUpdateRate;
        for (int i = 0; i < NUM_LEDS; i++)
        {
            vleds[i] = BLACK;
        }
    }

    void setMode(bool isSet)
    {
        isSetMode = isSet;
    }

    void update() override
    {
        if (!triggered)
        {
            return;
        }
        if (curPos < ringEnd && !isSetMode)
        {
            // if (millis() - prevUpdateMillis > updateRate)
            // {
            CHSV loopColor = loop == 0 ? CHSV(0, 0, 50) : CHSV(192, 150, 50);
            EVERY_N_MILLIS(updateRate)
            {
                prevUpdateMillis = millis();
                vleds[curPos] = loopColor;
                curPos++;
            }
        }
        // After first loop
        else if (loop == 0 && !isSetMode)
        {
            for (int i = ringStart; i < ringEnd; i++)
            {
                vleds[i].v = 255;
            }
            loop = 1;
            curPos = ringStart;
            updateRate *= 2;
        }
        // After second loop
        else if (ringi < rings.getNumRings() - 1)
        {
            for (int i = ringStart; i < ringEnd; i++)
            {
                vleds[i].v = 255;
            }
            clearVleds(vleds);
            CHSV loopColor = loop == 0 ? CHSV(0, 0, 255) : CHSV(192, 255, 255);
            rings.drawRing(rings.getNumRings() - ringi, loopColor);
            ringi++;
        }
        else
        {
            cancel();
        }
    }
};
#endif // CONTROLRING_H
