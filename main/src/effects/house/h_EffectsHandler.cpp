#include "h_EffectsHandler.h"

#include <FastLED.h>
#include "../shared/effects/RainbowWorm.h"
#include "../shared/palettes.h"
#include "../house/h_effects/Eminate.h"
#include "../house/h_effects/Sparks.h"
#include "../shared/effects/FireworkShow.h"
#include "../shared/effects/Ataraxy.h"

extern CRGB *leds[];

h_EffectsHandler::h_EffectsHandler() : EffectsHandler()
{
    // setupEffectLibrary();
}

BaseEffect *h_EffectsHandler::getEffect(size_t index)
{
    return activeEffects[index];
}

size_t h_EffectsHandler::getEffectCount() const
{
    return activeEffects.size();
}

void h_EffectsHandler::setupEffectLibrary()
{
    BaseEffect *effect = new FireworkShow(10, DEFAULT_PALETTE, 0.05f, 40.0f);
    activeEffects.push_back(effect);
}

void h_EffectsHandler::setupTestLibrary()
{
    // BaseEffect *effect = new Ataraxy();
    // activeEffects.push_back(effect);
}

void h_EffectsHandler::triggerEffect(size_t index)
{
    activeEffects[index]->triggerWrite();
}

void h_EffectsHandler::drawFrame()
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
                *leds[j] += copyArray[j];
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