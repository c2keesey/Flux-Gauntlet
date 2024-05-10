#ifndef RINGOSCIL_H
#define RINGOSCIL_H

#include "../../shared/effects/BaseEffect.h"
#include "../../shared/EffectHelpers.h"
#include "../Rings.h"
#include <vector>

struct Oscillator
{
    int index;
    CHSV color;
    bool direction;

    Oscillator(int idx, CHSV clr, bool dir)
        : index(idx), color(clr), direction(dir) {}
};

// TODO: fix bug sometimes crashes
class RingOscil : public BaseEffect
{
private:
    Rings rings;
    std::vector<Oscillator> activeRings;
    uint8_t fadeRate;

public:
    RingOscil(CRGBPalette256 pal = DEFAULT_PALETTE, uint8_t fadeRate = 10) : BaseEffect(pal), rings(vleds) {}

    void trigger() override
    {
        Oscillator newOscil = Oscillator(random(rings.getNumRings()), CHSV(random8(), 255, 255), random(2) == 0);
        activeRings.push_back(newOscil);
    }

    void update() override
    {
        clearVleds(vleds);
        // Oscillate
        EVERY_N_MILLIS(20)
        {
            for (auto it = activeRings.begin(); it != activeRings.end();)
            {
                if (it->index <= 0 || it->index >= rings.getNumRings() - 1)
                {
                    it->direction = !it->direction;
                }
                if (it->direction)
                {
                    it->index++;
                }
                else
                {
                    it->index--;
                }
                ++it;
            }
        }

        // Fade
        EVERY_N_MILLIS(fadeRate)
        {
            for (auto it = activeRings.begin(); it != activeRings.end();)
            {
                it->color.v = qsub8(it->color.v, 2);
                ++it;
            }
        }

        // Remove dead rings
        auto it = std::remove_if(activeRings.begin(), activeRings.end(), [](const Oscillator &o)
                                 { return o.color.v <= 25; });
        activeRings.erase(it, activeRings.end());

        // Draw
        for (auto it = activeRings.begin(); it != activeRings.end();)
        {
            rings.drawRing(it->index, it->color);
            ++it;
        }
    }
};

#endif // RINGOSCIL_H
