#include "h_EffectsHandler.h"

#include <FastLED.h>
#include "../shared/effects/RainbowWorm.h"
#include "../shared/palettes.h"
#include "../house/h_effects/Eminate.h"
#include "../house/h_effects/Sparks.h"

h_EffectsHandler::h_EffectsHandler() : EffectsHandler()
{
    setupEffectLibrary();
}

void h_EffectsHandler::setupEffectLibrary()
{
    BaseEffect *effect = new Sparks();
    activeEffects.push_back(effect);
}