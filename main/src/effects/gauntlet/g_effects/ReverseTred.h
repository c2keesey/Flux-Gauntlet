#ifndef REVERSETRED_H
#define REVERSETRED_H

#include "../../shared/effects/BaseEffect.h"
#include "../../shared/EffectHelpers.h"
#include <vector>

class ReverseTred : public BaseEffect
{
private:
    bool active = true;
    // size_t index1 = 0;
    // size_t index2 = 0;
    u8_t baseColorSpread = 10;
    CHSV topColor = CHSV(0, 0, 0);
    CHSV baseColor = CHSV(0, 0, 0);
    int spacing;
    float pos = 0;
    int shift = 0;
    unsigned long baseMovePeriod = 500;
    unsigned long lastMoveMillis = 0;
    float moveSpeed;
    int length;

public:
    ReverseTred(ColorPalette *pal = &rainbow_cp, float moveSpeed = 0.01f, int spacing = 8, int length = 2) : BaseEffect(pal), moveSpeed(moveSpeed), spacing(spacing), length(length)
    {
    }

    void trigger() override
    {
        active = !active;
        if (!active)
        {
            clearVleds(vleds);
        }
        // index1 = palette->getNewRandomIndex();
        // index2 = palette->getNewRandomIndex();
        baseColor = palette->getRandomColor();
        topColor = palette->getRandomColor();
    }

    void update() override
    {
        if (!active)
        {
            return;
        }
        clearVleds(vleds);
        for (int i = 0; i < NUM_LEDS; i++)
        {
            updateVleds(i, baseColor);
        }
        // if (millis() - lastMoveMillis > baseMovePeriod)
        // {
        //     ++shift;
        // }
        for (int i = 0; i < NUM_LEDS; i += spacing)
        {
            drawPrecise(pos + i, length, topColor, vleds, 50);
        }
        pos += moveSpeed;
        if (pos >= spacing)
        {
            pos = 0;
        }
    }
};

#endif // REVERSETRED_H
