// PALLETTERING_H
#ifndef PALLETTERING_H
#define PALLETTERING_H

#include "../../../shared/effects/BaseEffect.h"
#include "../../Rings.h"
#include "../../../shared/EffectHelpers.h"

// Effect for selecting a palette using the encoder.
class PaletteRing : public BaseEffect
{
private:
    int endIndex;
    int effectIndex;
    Rings rings;
    int hue = 0;
    int hueSpread = 5;

public:
    PaletteRing() : rings(vleds)
    {
        endIndex = rings.getRingEnd(rings.getNumRings() - 2);
        effectIndex = 0;
    }

    void trigger() override
    {
    }

    void setHue(int hue)
    {
        this->hue = hue;
    }

    void update() override
    {
        clearVleds(vleds);
        for (int i = endIndex; i > endIndex - ((hueSpread * 2) + 1); i--)
        {
            u8_t nextHue = (this->hue + (-i + endIndex) - hueSpread) % 255;
            vleds[i] = CHSV(nextHue, 255, 50);
        }
    }

    void reset()
    {
        clearVleds(vleds);
        effectIndex = 0;
    }
};

#endif // PALLETTERING_H