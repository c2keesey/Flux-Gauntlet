// The big one, long fade high spread

#ifndef BIGFIREWORK_H
#define BIGFIREWORK_H

#include "../../shared/effects/FireworkShow.h"

class BigFirework : public FireworkShow
{
private:
    const int fireworkOffset = 100; // Push to the middle third

public:
    BigFirework() : FireworkShow(0.05f, 15.0f, 100, 128) {}

    void trigger() override
    {
        int pos = random(fireworkOffset + 50, NUM_LEDS - fireworkOffset);
        fireworks.push_back(Firework(pos, 0.05f, 15.0f, 50, 200, 255));
        fireworks.push_back(Firework(pos, 0.05f, 5.0f, 0, 20, 254));
    }
};

#endif // BIGFIREWORK_H