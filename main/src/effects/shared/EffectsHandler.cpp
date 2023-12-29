#include "EffectsHandler.h"

#include <FastLED.h>
#include "../../config/config.h"

extern CRGB *leds[];

EffectsHandler::EffectsHandler()
{
}

void EffectsHandler::drawFrame()
{
    FastLED.clear(false);
    for (auto &effect : activeEffects)
    {
        effect->draw();
    }
    for (auto &effect : activeEffects)
    {
        if (effect != nullptr)
        {
            CRGB *copyArray = effect->getVleds();
            for (int i = 0; i < NUM_LEDS; i++)
            {
                *leds[i] += copyArray[i];
            }
        }
    }
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i]->r = min(leds[i]->r, (uint8_t)255);
        leds[i]->g = min(leds[i]->g, (uint8_t)255);
        leds[i]->b = min(leds[i]->b, (uint8_t)255);
    }
    FastLED.show();
}
