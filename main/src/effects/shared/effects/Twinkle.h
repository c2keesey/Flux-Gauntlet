// Twinkle.h

#ifndef TWINKLE_H
#define TWINKLE_H

#include "BaseEffect.h"
#include "../ColorPaletteInstances.h"
#include "../../../config/config.h"
#include "../EffectHelpers.h"

struct TwinkleLED
{
    int pos;
    CHSV color;
    bool fadeIn;
    int fadeSpeed;
    // float pos; // TODO: Movement
    // int lifetime; // TODO: Decay
    TwinkleLED(int p, CHSV c, int fs, bool f = true) : pos(p), color(c), fadeIn(f), fadeSpeed(fs) {}
};

class Twinkle : public BaseEffect
{
private:
    unsigned long fadeMillis = 0;
    uint8_t value = 0;
    bool active = false;
    int fadeRate = 20;
    int spawnRate = 50;
    std::vector<TwinkleLED> tleds;
    CHSV orange = CHSV(17, 255, 255);
    CHSV purple = CHSV(191, 255, 255);

    void updateTwinkles()
    {
        for (auto it = tleds.begin(); it != tleds.end();)
        {
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
                    updateVleds(it->pos, it->color);
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
            updateVleds(it->pos, it->color);
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

    void update() override
    {
        if (!active)
        {
            return;
        }
        EVERY_N_MILLIS(spawnRate)
        {
            CHSV color = random(2) == 0 ? orange : purple;
            color.v = 0;
            tleds.push_back(TwinkleLED(random(NUM_LEDS), color, random(1, 5)));
        }
        EVERY_N_MILLIS(fadeRate)
        {
            updateTwinkles();
            drawTwinkles();
        }
    }
};

#endif // TWINKLE_H
