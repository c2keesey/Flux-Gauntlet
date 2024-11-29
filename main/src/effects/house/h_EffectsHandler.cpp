#include "h_EffectsHandler.h"
#include "../../config/config.h"

#include <FastLED.h>
#include "../shared/effects/RainbowWorm.h"
#include "../shared/palettes.h"
#include "../house/h_effects/Eminate.h"
#include "../house/h_effects/Sparks.h"
#include "../shared/effects/FireworkShow.h"
#include "../shared/effects/Ataraxy.h"
#include "../shared/effects/Twinkle.h"
#include "../shared/effects/Fire.h"
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
    // BaseEffect *effect = new FireworkShow(0.05f, 40.0f);
    // activeEffects.push_back(effect);

    // BaseEffect *effect2 = new Twinkle(20, &halloween_cp);

    // // effect2->trigger();

    // // Top
    // BaseEffect *effect3 = new ClassicFireEffect(BFL_CORNER, BFR_CORNER, 5, 100);
    // // Left
    // BaseEffect *effect4 = new ClassicFireEffect(0, BFL_CORNER);
    // // Right
    // BaseEffect *effect5 = new ClassicFireEffect(BFR_CORNER, NUM_LEDS);

    // //     activeEffects.push_back(effect3);
    // //     activeEffects.push_back(effect4);
    // // activeEffects.push_back(effect5);

    // BaseEffect *effect6 = new Twinkle(20, &ice_cp);
    // effect6->trigger();

    // activeEffects.push_back(effect6);
}

void h_EffectsHandler::addEffect(BaseEffect *effect)
{
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
            CHSV *copyArray = getEffect(i)->getVleds();
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