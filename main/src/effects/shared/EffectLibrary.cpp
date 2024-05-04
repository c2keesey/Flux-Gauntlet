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

EffectLibrary::EffectLibrary()
{
}

void EffectLibrary::init()
{
    // Instantiate effects
    buttonEffectMap[PRIMARY_BUTTON] = std::vector<BaseEffect *>{
        new Blast(),
        new Pew(),
        new Flash()};
    buttonEffectMap[SECONDARY_BUTTON] = std::vector<BaseEffect *>{new Blast(), new Pew(), new Flash()};
    buttonEffectMap[SPEC_BUTTON] = std::vector<BaseEffect *>{new Blast(), new Pew(), new Flash()};

    // // Setup presets
    PresetContainer actionPreset = {buttonEffectMap[PRIMARY_BUTTON][0], buttonEffectMap[SECONDARY_BUTTON][1], buttonEffectMap[SPEC_BUTTON][2]};
    presetMap[Preset::ACTION] = actionPreset;

    PresetContainer testPreset = {buttonEffectMap[PRIMARY_BUTTON][0], buttonEffectMap[SECONDARY_BUTTON][0], buttonEffectMap[SPEC_BUTTON][0]};

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

BaseEffect *EffectLibrary::getPreset(EffectButton button, Preset preset) const
{
    if (presetMap.count(preset) == 0)
    {
        return nullptr;
    }

    if (button == PRIMARY_BUTTON)
    {
        return presetMap.at(preset).primary;
    }
    else if (button == SECONDARY_BUTTON)
    {
        return presetMap.at(preset).secondary;
    }
    else if (button == SPEC_BUTTON)
    {
        return presetMap.at(preset).spec;
    }
    else
    {
        return nullptr;
    }
}

BaseEffect *EffectLibrary::getPresetFromI(EffectButton button, int index) const
{
    if (index < 0 || index >= static_cast<int>(presetMap.size()))
    {
        return nullptr;
    }

    Preset preset = static_cast<Preset>(index);
    return getPreset(button, preset);
}

// TODO: Check index bounds
BaseEffect *EffectLibrary::getEffect(EffectButton button, int index)
{
    return buttonEffectMap[button][index];
}

CRGBPalette256 EffectLibrary::getPalette(int index)
{
    return palettes[index];
}

int EffectLibrary::getNumEffects(EffectButton button)
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
