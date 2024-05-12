#ifndef SPARKS_H
#define SPARKS_H

#include <vector>
#include "../../shared/effects/BaseEffect.h"

struct Spark
{
    int pos;
    int vel; // pixels per second
    CRGB color;
};

class Sparks : public BaseEffect
{
public:
    Sparks(ColorPalette palette = rainbow_cp, int rate = 1, int halfLife = 1);

    virtual void update() override;
    virtual void trigger() override;

protected:
    int rate;
    int halfLife;
    std::vector<Spark> sparkVector = {};
};

#endif // SPARKS_H
