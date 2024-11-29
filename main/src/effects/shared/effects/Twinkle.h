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
    bool rainbowMode = false;
    int updateRate = 20;
    int spawnRate = 20;
    std::vector<TwinkleLED> tleds;
    CHSV orange = CHSV(17, 255, 255);
    CHSV purple = CHSV(191, 255, 255);
    const u8_t hueVariance = 10;

    // Add these new variables for rainbow mode
    uint8_t hueOffset1 = 0;
    uint8_t hueOffset2 = 128; // Start 180 degrees opposite
    uint8_t hueSpeed1 = 1;
    uint8_t hueSpeed2 = 3; // Different speed for interesting combinations

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
    Twinkle(int speed = 20, ColorPalette *pal = &rainbow_cp, bool rainbow = false, int spawn_rate = 20)
        : BaseEffect(pal), rainbowMode(rainbow)
    {
        this->speed = speed;
        this->spawnRate = spawn_rate; // 20 is good for
        hueOffset1 = random8();
        hueOffset2 = random8();
    }

    void trigger() override
    {
        if (!active)
        {
            clearVleds(vleds);
        }
        else
        {
            // When turning off, increase fade speed of all existing twinkles
            for (auto &tled : tleds)
            {
                tled.fadeIn = false;
                tled.fadeSpeed += 2; // Increased fade speed for faster fadeout
            }
        }
        active = !active;
    }

    CHSV getColor()
    {
        if (!rainbowMode)
        {
            u8_t randSat = random(230, 255);
            CHSV color = random8() > 128 ? CHSV(0, randSat, 255) : CHSV(20, randSat, 255);
            color.h = qadd8(color.h, random8(0, hueVariance));
            return color;
        }

        // Rainbow mode color selection
        u8_t randSat = random(230, 255);
        CHSV color;

        if (random8() > 128)
        {
            color = CHSV(hueOffset1, randSat, 255);
        }
        else
        {
            color = CHSV(hueOffset2, randSat, 255);
        }

        // Add slight variance to the hue
        color.h = qadd8(color.h, random8(0, hueVariance));

        // Update the rotating hues
        EVERY_N_MILLIS(1000)
        {
            hueOffset1 += hueSpeed1;
            hueOffset2 += hueSpeed2;
        }

        return color;
    }

    void update() override
    {
        // Return if inactive and no twinkles left to fade out
        if (!active && tleds.empty())
        {
            return;
        }

        // Only spawn new twinkles if active
        if (active)
        {
            EVERY_N_MILLIS(spawnRate)
            {
                CHSV color = getColor();
                color.v = 0;
                float randomDrift = static_cast<float>(random(-300, 300)) / 10000.0f;
                tleds.push_back(TwinkleLED(random(NUM_LEDS), color, random(1, 7), 1, randomDrift));
            }
        }

        EVERY_N_MILLIS(updateRate)
        {
            updateTwinkles();
            drawTwinkles();
        }
    }
};

#endif // TWINKLE_H
