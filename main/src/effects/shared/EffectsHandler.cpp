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

    // Draw active effects
    for (size_t i = 0; i < getEffectCount(); i++)
    {
        BaseEffect *effect = getEffect(i);
        if (effect->isEffectActive())
        {
            effect->draw();
        }
    }

    // Combine effect colors
    for (size_t i = 0; i < getEffectCount(); i++)
    {
        BaseEffect *effect = getEffect(i);
        if (effect != nullptr && effect->isEffectActive())
        {
            CHSV *copyArray = effect->getVleds();
            for (int j = 0; j < NUM_LEDS; j++)
            {
                leds[j] += copyArray[j];
            }
        }
    }

    // Limit LED brightness
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].r = min(leds[i].r, (uint8_t)255);
        leds[i].g = min(leds[i].g, (uint8_t)255);
        leds[i].b = min(leds[i].b, (uint8_t)255);
    }

    FastLED.show();
}