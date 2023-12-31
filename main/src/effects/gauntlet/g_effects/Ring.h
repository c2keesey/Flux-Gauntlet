// Blast.h

#ifndef RING_H
#define RING_H

#include "../../shared/effects/BaseEffect.h"

struct Particle
{
    float pos;
    CRGB color;
    float speed;
    Particle(float p, CRGB c, float s) : pos(p), color(c), speed(s) {}
};

class Ring : public BaseEffect
{
private:
    uint8_t hue = 0;
    uint8_t len = 6;
    int speed = 15;
    int rings[16] = {21, 27, 25, 23, 23, 22, 20, 19, 19, 19, 17, 16, 15, 12, 12, 10};
    int ringsLength = 16;
    int breakpoints[17] = {0};

public:
    Ring(CRGBPalette256 pal = DEFAULT_PALETTE) : BaseEffect(pal)
    {
    }

    void trigger() override
    {
        CRGB color = ColorFromPalette(palette, random8());
        int ring = random8(ringsLength);
        int start = random8(breakpoints[ring]);
    }

    void update() override
    {
    }
};
#endif // RING_H
