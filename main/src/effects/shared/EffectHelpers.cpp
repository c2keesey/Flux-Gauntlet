#include "EffectHelpers.h"
#include "../../config/config.h"

void clearVleds(CHSV *vleds)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        vleds[i] = BLACK;
    }
}

// CRGB colorFraction(CRGB colorIn, float fraction)
// {
//     fraction = max(0.0f, min(1.0f, fraction));
//     uint8_t scale = fraction * 255;
//     return colorIn.nscale8_video(scale);
// }

// void drawPrecise(float fPos, float len, CRGB color, CRGB *vleds)
// {
//     float availFirstPixel = 1.0f - (fPos - (long)fPos);
//     float amtFirstPixel = min(availFirstPixel, len);
//     float remaining = max(0.0f, min(len, NUM_LEDS - fPos));
//     int iPos = fPos;
//     if (iPos < 0 || iPos >= NUM_LEDS)
//     {
//         return;
//     }

//     if (remaining > 0.0f)
//     {
//         vleds[iPos++] += colorFraction(color, amtFirstPixel);
//         remaining -= amtFirstPixel;
//     }
//     while (remaining > 1.0f && iPos < NUM_LEDS)
//     {
//         vleds[iPos++] += color;
//         remaining--;
//     }
//     if (remaining > 0.0f && iPos < NUM_LEDS)
//     {
//         vleds[iPos] += colorFraction(color, remaining);
//     }
// }

CHSV colorFraction(CHSV colorIn, float fraction)
{
    fraction = max(0.0f, min(1.0f, fraction));
    uint8_t scale = fraction * 255;
    return CHSV(colorIn.h, colorIn.s, scale);
}

void drawPrecise(float fPos, float len, CHSV color, CHSV *vleds)
{
    float availFirstPixel = 1.0f - (fPos - (long)fPos);
    float amtFirstPixel = min(availFirstPixel, len);
    float remaining = max(0.0f, min(len, NUM_LEDS - fPos));
    int iPos = fPos;

    if (iPos < 0 || iPos >= NUM_LEDS)
    {
        return;
    }

    if (remaining > 0.0f)
    {
        CHSV blendedColor = colorFraction(color, amtFirstPixel);
        vleds[iPos] = blend(vleds[iPos], blendedColor, amtFirstPixel * 255);
        iPos++;
        remaining -= amtFirstPixel;
    }

    while (remaining > 1.0f && iPos < NUM_LEDS)
    {
        vleds[iPos] = blend(vleds[iPos], color, 255);
        iPos++;
        remaining--;
    }

    if (remaining > 0.0f && iPos < NUM_LEDS)
    {
        CHSV blendedColor = colorFraction(color, remaining);
        vleds[iPos] = blend(vleds[iPos], blendedColor, remaining * 255);
    }
}

float randomAbsRange(float x, float y)
{
    if (x <= y)
    {
        return 0.0;
    }

    float randomNumber = random(0, (x - y) * 2000000.0) / 1000000.0;

    if (randomNumber < (x - y))
    {
        randomNumber -= x;
    }
    else
    {
        randomNumber += y - (x - y);
    }

    return randomNumber;
}

float randomVariance(float number, float variancePercent)
{
    float fraction = static_cast<float>(rand()) / RAND_MAX;
    return number * (1.0f + (fraction - 0.5f) * variancePercent / 100);
}