// Blast.h

#ifndef BLAST_H
#define BLAST_H

#include "../../shared/effects/BaseEffect.h"
#include "../Rings.h"

struct BlastRing
{
    int ringI;
    CHSV color;
};

class Blast : public BaseEffect
{
private:
    uint8_t hue = 0;
    uint8_t len = 6;
    int speed = 15;
    Rings rings;
    std::vector<BlastRing> active;

public:
    Blast(ColorPalette *pal = &rainbow_cp) : BaseEffect(pal), rings(vleds)
    {
        minUpdatePeriod = 50;
    }

    void trigger() override
    {
        CHSV color = palette->getNextColor();
        active.push_back({0, color});
    }

    // TODO: Add additional vleds to ends of vleds, and return update BaseEffect getVleds() to draw first ring properly
    void draw() override
    {
        if (millis() - prevMillis > speed)
        {
            prevMillis = millis();
            clearVleds(vleds);
            for (auto it = active.begin(); it != active.end();)
            {
                for (int i = rings.getRingStart(it->ringI); i < rings.getRingEnd(it->ringI); i++)
                {
                    updateVleds(i, it->color);
                }
                it->ringI++;
                if (it->ringI >= rings.getNumRings())
                {
                    it = active.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    void update() override
    {
    }
};
#endif // BLAST_H
