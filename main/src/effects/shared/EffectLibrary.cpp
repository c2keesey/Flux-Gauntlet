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
    std::map<std::string, BaseEffect *> effects = initEffects();

    // Assign effects to button maps
    buttonEffectMap[THUMB] = std::vector<BaseEffect *>{
        effects["ringFlash"],
        effects["panelFlash_2"],
        effects["panelFlash_3"],
        effects["flash_1"],
    };

    buttonEffectMap[INDEX] = std::vector<BaseEffect *>{
        effects["lightning_1"],
        effects["fireworkShow_2"],
    };

    buttonEffectMap[MIDDLE] = std::vector<BaseEffect *>{
        effects["blastCollide_1"],
        effects["blast_1"],
        effects["blast_america"],
        effects["blast_christmas"],
        effects["blast_mecha"],
    };

    buttonEffectMap[RINGF] = std::vector<BaseEffect *>{
        effects["casimir_1"],
        effects["casimir_mecha"],
        effects["reverseTred_smallfast_vr"],
    };

    buttonEffectMap[PINKY] = std::vector<BaseEffect *>{
        effects["reverseTred_smallfast"],
        effects["reverseTred_longslow"],
        effects["reverseTred_1"],
        effects["reverseTred_smallfast_vr"],
        effects["big_firework"],
        effects["twinkle_1"],
        effects["pew_1"],
        effects["bitSwitch_carnival"],
        effects["bitSwitch_smooth"]};

    // Setup presets
    PresetContainer favorites = {
        effects["ringFlash"],
        effects["lightning_1"],
        effects["blast_1"],
        effects["casimir_1"],
        effects["big_firework"]};
    presetMap[FAVORITES] = favorites;

    PresetContainer actionPreset = {
        effects["panelFlash_2"],
        effects["big_firework"],
        effects["lightning_1"],
        effects["casimir_1"],
        effects["pew_1"]};
    presetMap[ACTION] = actionPreset;

    PresetContainer fireAndIce = {
        effects["flash_1"],
        effects["blast_ice"],
        effects["blast_fire"],
        effects["pew_fire"],
        effects["pew_ice"],
    };
    presetMap[FIREANDICE] = fireAndIce;

    PresetContainer ambient = {
        effects["flash_1"],
        effects["blast_ice"],
        effects["blast_fire"],
        effects["pew_fire"],
        effects["pew_ice"],
    };
    presetMap[AMBIENT] = ambient;
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

ColorPalette EffectLibrary::getPalette(int index)
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
