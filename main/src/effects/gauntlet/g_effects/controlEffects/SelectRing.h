// SELECTRING_H

#ifndef SELECTRING_H
#define SELECTRING_H

#include "../../../shared/effects/BaseEffect.h"
#include "../../Rings.h"
#include "../../../shared/EffectHelpers.h"

// Effect for selecting an effect or preset using the encoder.
class SelectRing : public BaseEffect
{
private:
    int ringStart;
    int ringEnd;
    int effectIndex;
    Rings rings;
    int numEffects = 0;
    uint8_t hue = 0;

public:
    SelectRing(CRGBPalette256 pal = DEFAULT_PALETTE)
        : BaseEffect(pal), rings(vleds)
    {
        ringStart = rings.getRingStart(rings.getNumRings() - 2);
        ringEnd = rings.getRingEnd(rings.getNumRings() - 2) - 4;
        effectIndex = 0;
    }

    void trigger() override
    {
    }

    void setEffect(int effectIndex, int numEffects)
    {
        this->numEffects = numEffects;
        this->effectIndex = effectIndex % numEffects;
    }

    void update() override
    {
        clearVleds(vleds);
        for (int i = ringEnd; i > ringEnd - numEffects; i--)
        {
            vleds[i] = CHSV(0, 0, 50);
        }
        vleds[ringEnd - effectIndex] = CHSV(hue, 255, 255);
        hue += 2;
    }

    void reset()
    {
        clearVleds(vleds);
        effectIndex = 0;
    }
};
#endif // SELECTRING_H
