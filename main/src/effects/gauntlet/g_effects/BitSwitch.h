#ifndef BITSWITCH_H
#define BITSWITCH_H

#include "../../shared/effects/BaseEffect.h"
#include "../../shared/EffectHelpers.h"
#include "../Rings.h"
#include <vector>

class BitSwitch : public BaseEffect
{
private:
    Rings rings;
    bool active = false;
    unsigned long lastUpdate = 0;
    unsigned long updateRate = 100;
    bool randomize;

public:
    BitSwitch(ColorPalette *pal = &rainbow_cp, bool randomize = false) : BaseEffect(pal), rings(vleds), randomize(randomize)
    {
        initColors();
        rotPalSpread = 25;
    }

    void trigger() override
    {
        initColors();
        active = !active;
    }

    void initColors()
    {
        if (randomize)
        {
            for (int i = 0; i < NUM_LEDS; i++)
            {
                updateVleds(i, palette->getRandomColor());
            }
        }
        else
        {
            for (int i = 0; i < rings.getNumRings(); i++)
            {
                CHSV color = palette->getRandomColor();
                for (int j = rings.getRingStart(i); j < rings.getRingEnd(i); j++)
                {
                    CHSV nextColor = CHSV((color.h + j - rings.getRingStart(i)) % 255, color.s, color.v);
                    updateVleds(j, nextColor);
                }
            }
        }
    }

    void rotatePalette(int index) override
    {
        BaseEffect::rotatePalette(index);
        initColors();
    }

    void update() override
    {
        if (!active)
        {
            clearVleds(vleds);
            return;
        }
        if (millis() - lastUpdate < updateRate)
        {
            return;
        }
        lastUpdate = millis();
        for (int i = 0; i < rings.getNumRings(); i++)
        {
            if (i % 2 == 0)
            {
                CHSV startColor = vleds[rings.getRingStart(i)];
                for (int j = rings.getRingStart(i); j < rings.getRingEnd(i) - 1; j++)
                {
                    vleds[j] = vleds[j + 1];
                }
                vleds[rings.getRingEnd(i) - 1] = startColor;
            }
            else
            {
                CHSV endColor = vleds[rings.getRingEnd(i) - 1];
                for (int j = rings.getRingEnd(i) - 1; j > rings.getRingStart(i); j--)
                {
                    vleds[j] = vleds[j - 1];
                }
                vleds[rings.getRingStart(i)] = endColor;
            }
        }
    }
};

#endif // BITSWITCH_H
