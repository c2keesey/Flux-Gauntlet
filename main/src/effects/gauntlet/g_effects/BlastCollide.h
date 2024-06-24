// Blast.h

#ifndef BLASTCOLLIDE_H
#define BLASTCOLLIDE_H

#include "../../shared/effects/BaseEffect.h"
#include "../Rings.h"

class BlastCollide : public BaseEffect
{
private:
    struct BlastRingCollide
    {
        int ringI;
        CHSV color;
        bool isForward;
        bool isFading;
    };

    uint8_t hue = 0;
    uint8_t len = 6;
    int speed = 20;
    Rings rings;
    std::vector<BlastRingCollide> active;

public:
    BlastCollide(ColorPalette *pal = &rainbow_cp) : BaseEffect(pal), rings(vleds)
    {
        minUpdatePeriod = 50;
    }

    void trigger() override
    {
        CHSV color = palette->getNextColor();
        active.push_back({0, color, true, false});
        active.push_back({rings.getNumRings() - 2, color, false, false});
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
                if (it->isFading)
                {
                    it->color.v = qsub8(it->color.v, 20);
                    rings.drawRing(it->ringI, it->color);
                    if (it->color.v == 0)
                    {
                        active.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
                else
                {
                    for (int i = rings.getRingStart(it->ringI); i < rings.getRingEnd(it->ringI); i++)
                    {
                        updateVleds(i, it->color);
                    }
                    if (it->isForward)
                    {
                        it->ringI++;
                    }
                    else
                    {
                        it->ringI--;
                    }
                    if (it->isForward)
                    {
                        if (it->ringI >= rings.getNumRings() / 2)
                        {
                            it->isFading = true;
                            ++it;
                        }
                    }
                    else
                    {
                        if (it->ringI <= rings.getNumRings() / 2)
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
        }
    }

    void update() override
    {
    }
};

#endif // BLASTCOLLIDE_H
