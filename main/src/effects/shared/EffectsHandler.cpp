#include "EffectsHandler.h"

#include <FastLED.h>
#include "../../config/config.h"

extern CRGB leds[];

EffectsHandler::EffectsHandler()
{
}

void EffectsHandler::drawFrame()
{
    FastLED.clear(false);
    for (size_t i = 0; i < getEffectCount(); i++)
    {

        getEffect(i)->draw();
    }
    for (size_t i = 0; i < getEffectCount(); i++)
    {
        if (getEffect(i) != nullptr)
        {
            CRGB *copyArray = getEffect(i)->getVleds();
            for (int j = 0; j < NUM_LEDS; j++)
            {
                leds[j] += copyArray[j];
            }
        }
    }
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].r = min(leds[i].r, (uint8_t)255);
        leds[i].g = min(leds[i].g, (uint8_t)255);
        leds[i].b = min(leds[i].b, (uint8_t)255);
    }
    FastLED.show();
}