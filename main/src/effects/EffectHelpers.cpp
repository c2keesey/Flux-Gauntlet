#include "EffectHelpers.h"
#include "../config/config.h"

void clearVleds(CRGB *vleds)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        vleds[i] = CRGB::Black;
    }
}

CRGB ColorFraction(CRGB colorIn, float fraction)
{
    fraction = min(1.0f, fraction);
    return CRGB(colorIn).fadeToBlackBy(255 * (1.0f - fraction));
}

void drawPrecise(float fPos, float len, CRGB color, CRGB *vleds)
{
    float availFirstPixel = 1.0f - (fPos - (long)fPos);
    float amtFirstPixel = min(availFirstPixel, len);
    float remaining = min(len, FastLED.size() - fPos);
    int iPos = fPos;

    if (remaining > 0.0f)
    {
        vleds[iPos++] += ColorFraction(color, amtFirstPixel);
        remaining -= amtFirstPixel;
    }
    while (remaining > 1.0f)
    {
        vleds[iPos++] += color;
        remaining--;
    }
    if (remaining > 0.0f)
    {
        vleds[iPos] += ColorFraction(color, remaining);
    }
}