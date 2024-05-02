// CASIMIR_H
#ifndef CASIMIR_H
#define CASIMIR_H

#include "../../shared/effects/BaseEffect.h"
#include "../Rings.h"
#include "../../shared/EffectHelpers.h"
#include <vector>

class Casimir : public BaseEffect
{
private:
    struct CasimirRing
    {
        int index;
        int length;
        int end;
        CHSV color;
        bool growing;

        CasimirRing(int idx, int len, CHSV clr, bool grow)
            : index(idx), length(len), end(idx + len), color(clr), growing(grow) {}
    };

    Rings rings;
    int numEffects = 0;
    std::vector<CasimirRing> active;
    int startColorOffset = 90;
    int startColorVariation = 20;

public:
    Casimir(CRGBPalette256 pal = DEFAULT_PALETTE) : BaseEffect(pal), rings(vleds)
    {
        triggerDelay = 50;
    }

    void trigger() override
    {
        CHSV startColor = CHSV(random8(startColorVariation) + startColorOffset, 255, 255);
        int ringStart = random(NUM_LEDS - 10);
        active.push_back({ringStart, rings.getRingLength(rings.getRingFromIndex(ringStart)), startColor, true});
    }

    void update() override
    {
        for (auto it = active.begin(); it != active.end();)
        {
            updateVleds(it->index, it->color);
            it->index++;
            it->color.hue += 2;
            if (it->index >= it->end)
            {
                if (it->growing)
                {
                    it->growing = false;
                    it->index = it->index - it->length;
                    it->color = CHSV(0, 0, 0);
                    ++it;
                }
                else
                {
                    it = active.erase(it);
                }
            }
            else
            {
                ++it;
            }
        }
    }
};

#endif // CASIMIR_H