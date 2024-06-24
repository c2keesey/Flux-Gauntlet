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
    AMBIENT,
};

std::map<std::string, BaseEffect *> initEffects();

#endif // EFFECTINSTANCES_H
