// Pew.h

#ifndef PEW_H
#define PEW_H

#include <vector>
#include <tuple>
#include "../../shared/effects/BaseEffect.h"
#include "../../shared/EffectHelpers.h"
class Pew : public BaseEffect
{
private:
    uint8_t hue;
    uint8_t len;
    float MIN_STEP_SIZE = 0.001f;
    float stepSize;
    bool rainbow;
    std::vector<Beam> beams = {};

public:
    Pew(CRGBPalette256 pal = DEFAULT_PALETTE, uint8_t hue = 0, uint8_t len = 4, int speed = 100, bool rainbow = true)
        : BaseEffect(pal), hue(hue), len(len), rainbow(rainbow)
    {
        this->speed = speed;
        stepSize = speed * MIN_STEP_SIZE;
    }

    void trigger() override
    {

        CRGB color = ColorFromPalette(palette, random8());
        beams.push_back({NUM_LEDS - 1, color});
    }

    void update() override
    {
        clearVleds(vleds);
        for (int i = beams.size() - 1; i >= 0; --i)
        {
            CRGB color;
            drawPrecise(beams[i].pos, len, beams[i].color, vleds);
            beams[i].pos -= 0.01f * speed;

            if (beams[i].pos <= 0.0)
            {
                beams.erase(beams.begin() + i);
            }
        }
    }
    // float getStepSize()
    // {
    //     return speed * MIN_STEP_SIZE * getUpdatePeriod();
    // }

    void setSpeed(int speed)
    {
        this->speed = speed;
    }
};

#endif // PEW_H
