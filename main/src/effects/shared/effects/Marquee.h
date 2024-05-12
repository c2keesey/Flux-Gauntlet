// Marquee.h

#ifndef MARQUEE_H
#define MARQUEE_H

#include "BaseEffect.h"
#include "../EffectHelpers.h"

class Marquee : public BaseEffect
{
private:
    bool active = false;
    int speed;
    float pos = 0;

public:
    Marquee(int speed = 5) : speed(speed)
    {
    }

    void trigger() override
    {
        active = !active;
    }

    void draw() override
    {
    }
};

#endif // MARQUEE_H
