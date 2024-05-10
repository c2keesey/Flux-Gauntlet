/**
 * @file EffectLibrary.cpp
 * @brief Implementation of EffectLibrary methods.
 */
#include <FastLED.h>
#include "EffectLibrary.h"
#include "effects/BaseEffect.h"
#include "../gauntlet/g_effects/Pew.h"
#include "../gauntlet/g_effects/Flash.h"
#include "../gauntlet/g_effects/Blast.h"
#include "effects/RainbowWorm.h"
#include "effects/Twinkle.h"
#include "effects/FireworkShow.h"
#include "../../config/config.h"
#include "palettes.h"
#include "EffectInstances.h"

EffectLibrary::EffectLibrary()
{
}

void EffectLibrary::init()
{
    // Instantiate effects
    buttonEffectMap[THUMB] = std::vector<BaseEffect *>{flash1, panelFlash2, ringFlash};
    buttonEffectMap[INDEX] = std::vector<BaseEffect *>{fireworkShow1, blast1};
    buttonEffectMap[MIDDLE] = std::vector<BaseEffect *>{blast1, flash1};
    buttonEffectMap[RINGF] = std::vector<BaseEffect *>{blast1, pew1, flash1};
    buttonEffectMap[PINKY] = std::vector<BaseEffect *>{casimir1, twinkle1};

    // Setup presets
    PresetContainer actionPreset = {panelFlash2, fireworkShow2, blast1, casimir1, pew1};
    presetMap[Preset::ACTION] = actionPreset;

    PresetContainer testPreset = {blast1, blast1, blast1, blast1, blast1};
    presetMap[Preset::TEST] = testPreset;
}

EffectLibrary::~EffectLibrary()
{
    // Delete instantiated effects
    for (const auto &buttonEffects : buttonEffectMap)
    {
        for (BaseEffect *effect : buttonEffects.second)
        {
            delete effect;
        }
    }
}

BaseEffect *EffectLibrary::getPreset(ButtonEnum button, Preset preset) const
{
    if (presetMap.count(preset) == 0)
    {
        return nullptr;
    }

    if (button == MIDDLE)
    {
        return presetMap.at(preset).middle;
    }
    else if (button == RINGF)
    {
        return presetMap.at(preset).ringf;
    }
    else if (button == THUMB)
    {
        return presetMap.at(preset).thumb;
    }
    else if (button == INDEX)
    {
        return presetMap.at(preset).index;
    }
    else if (button == PINKY)
    {
        return presetMap.at(preset).pinky;
    }
    else
    {
        return nullptr;
    }
}

BaseEffect *EffectLibrary::getPresetFromI(ButtonEnum button, int index) const
{
    if (index < 0 || index >= static_cast<int>(presetMap.size()))
    {
        return nullptr;
    }

    Preset preset = static_cast<Preset>(index);
    return getPreset(button, preset);
}

// TODO: Check index bounds
BaseEffect *EffectLibrary::getEffect(ButtonEnum button, int index)
{
    return buttonEffectMap[button][index];
}

CRGBPalette256 EffectLibrary::getPalette(int index)
{
    return palettes[index];
}

int EffectLibrary::getNumEffects(ButtonEnum button)
{
    return buttonEffectMap[button].size();
}

int EffectLibrary::getNumPresets()
{
    return presetMap.size();
}

/**
 * Creates and returns a new effect object based on the given effect type.
 * The caller is responsible for deleting the returned effect object
 * when it's no longer needed.
 */
// BaseEffect *EffectLibrary::createEffect(EffectInst effectType)
// {
//     auto it = effectFactories.find(effectType);
//     if (it != effectFactories.end())
//     {
//         return it->second();
//     }
//     return nullptr;
// }
