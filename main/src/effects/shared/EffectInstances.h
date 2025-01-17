#ifndef EFFECTINSTANCES_H
#define EFFECTINSTANCES_H

#include <map>
#include <string>
#include "EffectInstances.h"
#include "effects/BaseEffect.h"

enum Preset
{
    FAVORITES,
    ACTION,
    FIREANDICE,
    FIRE_MIRRORED,
    SIMULATION,
};

std::map<std::string, BaseEffect *> initEffects();

#endif // EFFECTINSTANCES_H
