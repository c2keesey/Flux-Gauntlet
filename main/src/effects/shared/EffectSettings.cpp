/**
 * @file EffectSettings.cpp
 * @brief Implementation of presets and library of effects for the gauntlet.
 */
#include <vector>
#include <map>
#include "EffectLibrary.h"
#include "../../config/config.h"

using EI = EffectLibrary::EffectInst;
using PC = EffectLibrary::PresetContainer;

// Effect factory functions
BaseEffect *BlastEffect() { return new Blast(); }
BaseEffect *PewEffect() { return new Pew(); }
BaseEffect *FlashEffect() { return new Flash(); }

// Effect factories map
std::map<EI, std::function<BaseEffect *()>> EffectLibrary::effectFactories = {
    {EI::BLAST, BlastEffect},
    {EI::PEW, PewEffect},
    {EI::FLASH, FlashEffect},
    // TODO: finish adding effect factories
};

// Preset containers
constexpr PC ActionPreset = {EI::BLAST, EI::PEW, EI::FLASH};
constexpr PC TestPreset = {EI::FLASH, EI::BLAST, EI::PEW};

// Preset map
std::map<Preset, PC> EffectLibrary::presetMap = {
    {Preset::ACTION, ActionPreset},
    {Preset::TEST, TestPreset},

};

// Effect vectors
std::vector<EI> EffectLibrary::primaryEffects = {
    EI::BLAST,
    EI::PEW,
    EI::FLASH};

std::vector<EI> EffectLibrary::secondaryEffects = {
    EI::BLAST,
    EI::PEW,
    EI::FLASH};

std::vector<EI> EffectLibrary::specEffects = {
    EI::BLAST,
    EI::PEW,
    EI::FLASH};

std::map<EffectButton, std::vector<EI>> EffectLibrary::buttonEffectMap = {
    {PRIMARY_BUTTON, EffectLibrary::primaryEffects},
    {SECONDARY_BUTTON, EffectLibrary::secondaryEffects},
    {SPEC_BUTTON, EffectLibrary::specEffects}};

// TODO: setup palettes

// void EffectLibrary::setupPaletteLibrary()
// {
//     palettes.push_back(RainbowColors_p);
//     palettes.push_back(ocean_gp_v2);
//     palettes.push_back(strong_watermellon);
//     palettes.push_back(emerald_dragon_gp);
//     palettes.push_back(valentine);
// }