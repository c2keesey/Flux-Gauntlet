// Pew.h

#ifndef PEW_H
#define PEW_H

#include <vector>
#include <tuple>
#include "BaseEffect.h"
#include "EffectHelpers.h"
class Pew : public BaseEffect
{
private:
    uint8_t hue;
    uint8_t len;
    int speed;
    bool rainbow;
    std::vector<Beam> beams = {};

public:
    Pew(uint8_t hue = 0, uint8_t len = 4, int speed = 1, bool rainbow = true)
        : hue(hue), len(len), speed(speed), rainbow(rainbow)
    {
    }

    void trigger() override
    {

        hue = rainbow ? random8() : hue;
        CRGB color;
        hsv2rgb_rainbow(CHSV(hue, 255, 255), color);
        beams.push_back({NUM_LEDS - 1, color});
    }

    void update() override
    {
        clearVleds(vleds);
        for (int i = beams.size() - 1; i >= 0; --i)
        {
            CRGB color;
            drawPrecise(beams[i].pos, len, beams[i].color, vleds);
            beams[i].pos -= 0.01f;

            if (beams[i].pos <= 0.0)
            {
                beams.erase(beams.begin() + i);
            }
        }
    }
};

#endif // PEW_H
