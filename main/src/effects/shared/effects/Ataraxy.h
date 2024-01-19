// Ataraxy.h

#ifndef ATARAXY_H
#define ATARAXY_H

#include "BaseEffect.h"
#include <vector>
#include "../EffectHelpers.h"

const int minV = 50;
// Want high saturation <200 but val can be low
// Mid sat low val is nice too around 200 50 before goes red

struct Orb
{
    float pos;
    int size;
    CRGB color;
    float velocity;
    uint8_t intensity;
    Orb(float p, int s, CRGB c, float v, uint8_t i) : pos(p), size(s), color(c), velocity(v), intensity(i) {}
};

class Ataraxy : public BaseEffect
{
private:
    std::vector<Orb> orbs;

public:
    Ataraxy(CRGBPalette256 pal = DEFAULT_PALETTE)
    {
        palette = pal;
        triggerDelay = 500;
    }

    void trigger() override
    {
        orbs.push_back(Orb(200, 2, CHSV(20, 255, 255), 0, 100));
    }

    void update() override
    {
        drawOrbs();
    }

    void drawOrbs()
    {
        for (auto orb = orbs.begin(); orb != orbs.end();)
        {
            if (orb->pos < 0 || orb->pos > NUM_LEDS - 1)
            {
                orb = orbs.erase(orb);
            }
            else
            {
                drawOrb(&*orb);
                orb++;
            }
        }
    }

    void drawOrb(Orb *orb)
    {
        drawPrecise(orb->pos, orb->size, orb->color, vleds);
    }
};

#endif // ATARAXY_H
