// CONTROLRING_H

#ifndef CONTROLRING_H
#define CONTROLRING_H

#include "../../../shared/effects/BaseEffect.h"
#include "../../Rings.h"
#include "../../../shared/EffectHelpers.h"

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
    int loop;
    bool isSetMode = false;

public:
    ControlRing(CRGBPalette256 pal = DEFAULT_PALETTE, unsigned long holdTime = 500)
        : BaseEffect(pal), rings(vleds)
    {
        ringStart = rings.getRingStart(rings.getRingsLength() - 2);
        ringEnd = rings.getRingEnd(rings.getRingsLength() - 2);
        curPos = ringStart;
        updateRate = holdTime / max(1, (ringEnd - ringStart));
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
            CHSV loopColor = loop == 0 ? CHSV(0, 0, 255) : CHSV(192, 255, 255);
            EVERY_N_MILLIS(updateRate)
            {
                prevUpdateMillis = millis();
                vleds[curPos] = loopColor;
                curPos++;
            }
        }
        else if (loop == 0 && !isSetMode)
        {
            loop = 1;
            curPos = ringStart;
        }
        else if (ringi < rings.getRingsLength() - 1)
        {
            clearVleds(vleds);
            CHSV loopColor = loop == 0 ? CHSV(0, 0, 255) : CHSV(192, 255, 255);
            rings.drawRing(rings.getRingsLength() - ringi, loopColor);
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
