// Twinkle.h

#ifndef TWINKLE_H
#define TWINKLE_H

#include "BaseEffect.h"
#include "../ColorPaletteInstances.h"
#include "../../../config/config.h"
#include "../EffectHelpers.h"

struct TwinkleLED
{
    float pos;
    CHSV color;
    bool fadeIn;
    int fadeSpeed;
    int size;
    float drift; // Changed from int to float
    // float pos; // TODO: Movement
    // int lifetime; // TODO: Decay
    TwinkleLED(float p, CHSV c, int fs, int s = 1, float d = 0.0f, bool f = true) : pos(p), color(c), fadeIn(f), fadeSpeed(fs), size(s), drift(d)
    {
        if (s == 0)
        {
            size = random(1, 4);
        }
    }
};

class Twinkle : public BaseEffect
{
private:
    unsigned long fadeMillis = 0;
    uint8_t value = 0;
    bool active = false;
    int updateRate = 20;
    int spawnRate = 20; // 40ms = 25fps
    std::vector<TwinkleLED> tleds;
    CHSV orange = CHSV(17, 255, 255);
    CHSV purple = CHSV(191, 255, 255);
    const u8_t hueVariance = 10;

    void updateTwinkles()
    {
        clearVleds(vleds);
        for (auto it = tleds.begin(); it != tleds.end();)
        {
            it->pos += it->drift;

            if (it->pos < 0 || it->pos >= NUM_LEDS)
            {
                it = tleds.erase(it); // Erase if out of bounds
                continue;             // Skip to the next iteration
            }

            if (it->fadeIn)
            {
                it->color.value = qadd8(it->color.value, it->fadeSpeed);
                if (it->color.value == 255)
                {
                    it->fadeIn = false;
                }
                ++it;
            }
            else
            {
                it->color.value = qsub8(it->color.value, it->fadeSpeed);
                if (it->color.value == 0)
                {
                    it = tleds.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    void drawTwinkles()
    {
        for (auto it = tleds.begin(); it != tleds.end(); it++)
        {
            for (int i = 0; i < it->size; i++)
            {
                drawPrecise(it->pos + i, it->size, it->color, vleds, 10);
            }
        }
    }

public:
    Twinkle(int speed = 20, ColorPalette *pal = &rainbow_cp)
        : BaseEffect(pal)
    {
        this->speed = speed;
    }

    void trigger() override
    {
        active = !active;
    }

    // CHSV getColor()
    // {
    //     CHSV color = palette->getExactRandomColor();
    //     color.h += random(-hueVariance, hueVariance);
    //     return color;
    // }

    CHSV getColor()
    {
        u8_t randSat = random(230, 255);
        CHSV color = random8() > 128 ? CHSV(0, randSat, 255) : CHSV(20, randSat, 255);
        color.h = qadd8(color.h, random8(0, hueVariance));
        return color;
    }

    void update() override
    {
        if (!active)
        {
            return;
        }
        EVERY_N_MILLIS(spawnRate)
        {
            CHSV color = getColor();
            color.v = 0;
            float randomDrift = static_cast<float>(random(-300, 300)) / 10000.0f; // Generate random float between -1 and 1
            tleds.push_back(TwinkleLED(random(NUM_LEDS), color, random(1, 7), 1, randomDrift));
        }
        EVERY_N_MILLIS(updateRate)
        {
            updateTwinkles();
            drawTwinkles();
        }
    }
};

#endif // TWINKLE_H
